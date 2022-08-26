// BuildPSF.cpp
// Convert a font defined in C into a PSF file
//
// 2022-08-23	PV		First version
// 2022-08-24	PV		Load_font V2, bitmast always left-aligned on ushort even if width<=8 rather than byte left-aligned

#define _CRT_SECURE_NO_WARNINGS

#include <cstdio>
#include <cassert>
#include <iostream>
#include <fstream>
#include <iomanip>

// Fonts to convert
#include "Crystalfontz.h"
#include "Hitachi_HD44780A00_HD44780A02.h"
#include "Matrix_orbital.h"
#include "Motorola_6847_derived.h"
#include "Std_ASCII_5x7.h"
#include "TI-99-4A.h"
#include "Verdana.h"

using namespace std;
//using ushort = unsigned short;
using ushort = uint16_t;

bool verbose = false;


// ---------------------------------------------------------------------------------------------
// PSF1 format

#define PSF1_MAGIC0     0x36
#define PSF1_MAGIC1     0x04

#define PSF1_MODE512    0x01
#define PSF1_MODEHASTAB 0x02
#define PSF1_MODEHASSEQ 0x04
#define PSF1_MAXMODE    0x05

#define PSF1_SEPARATOR  0xFFFF
#define PSF1_STARTSEQ   0xFFFE

struct psf1_header {
	unsigned char magic[2];     // Magic number
	unsigned char mode;         // PSF font mode
	unsigned char charsize;     // Character size
};


// ---------------------------------------------------------------------------------------------
// PSF2 format
#define PSF2_MAGIC0     0x72
#define PSF2_MAGIC1     0xb5
#define PSF2_MAGIC2     0x4a
#define PSF2_MAGIC3     0x86

// bits used in flags
#define PSF2_HAS_UNICODE_TABLE 0x01

// max version recognized so far
#define PSF2_MAXVERSION 0

// UTF8 separators
#define PSF2_SEPARATOR  0xFF
#define PSF2_STARTSEQ   0xFE

struct psf2_header {
	unsigned char magic[4];
	unsigned int version;
	unsigned int headersize;    // offset of bitmaps in file
	unsigned int flags;
	unsigned int length;        // number of glyphs
	unsigned int charsize;      // number of bytes for each character
	unsigned int height, width; // max dimensions of glyphs
	// charsize = height * ((width + 7) / 8)
};


// ---------------------------------------------------------------------------------------------
// memory_font

// My own representation in memory, all rows are 2 bytes (ushort) independetly from stride/width
struct memory_glyph {
	ushort m1_fixed, m2_fixed;
	ushort m1_variable, m2_variable;

	ushort b1_fixed, b2_fixed;			// Start and stop bits for fixed width, b1_fixed=15 (always) and b2_fixed=b1-width+1 (b2 in [13..0])
	ushort b1_variable, b2_variable;	// Start and stop bits for variable width, eliminating empty columns. b1_variable>=b1_fixed and b2_variable<=b2_fixed, b1_variable>=b2_variable

	ushort* rows;						// Each row is stored on 2 bytes, dots start at bit 15 (b1_fixed) until b2_fixed 
};

struct memory_font {
	memory_font(const char* filename, const char* format, ushort numglyphs, ushort width, ushort height)
	{
		name = _strdup(filename);
		this->format = _strdup(format);		// "PSF1" or "PSF2"
		this->numglyphs = numglyphs;				// usually 256 or 512, can be different for PSF2
		this->width = width;						// 4..16
		this->height = height;						// 5..32
		stride = ((width + 7) / 8);					// 1 or 2 
		glyphs = (struct memory_glyph*)malloc(sizeof(struct memory_glyph) * numglyphs);
		assert(glyphs != nullptr);
		memset(glyphs, 0, sizeof(struct memory_glyph) * numglyphs);
	}

	~memory_font()
	{
		free((void*)name);
		name = nullptr;
		free((void*)format);
		format = nullptr;
		free((void*)glyphs);
		glyphs = nullptr;
	}

	const char* name;
	const char* format;
	ushort numglyphs;
	ushort width, height;			// in bits
	ushort stride;					// width in bytes, = ((width + 7) / 8)
	struct memory_glyph* glyphs;	// One glyph

};


// ---------------------------------------------------------------------------------------------
// Bit helpers


// cout << "i\tl2(i)\tl_p2(i)\tr_p2(i)\tl_b(i)\tr_b(i)\n";
// for (ushort i = 0; i <= 16; i++)
// cout << i << '\t' << log2(i) << '\t' << leftmost_p2(i) << '\t' << rightmost_p2(i) << '\t' << leftmost_bit(i) << '\t' << rightmost_bit(i) << endl;
// 
//	i       l2(i)   l_p2(i) r_p2(i) l_b(i)  r_b(i)
//	0       0       0       0       0       0
//	1       0       1       1       0       0
//	2       1       2       2       1       1
//	3       1       2       1       1       0
//	4       2       4       4       2       2
//	5       2       4       1       2       0
//	6       2       4       2       2       1
//	7       2       4       1       2       0
//	8       3       8       8       3       3
//	9       3       8       1       3       0
//	10      3       8       2       3       1
//	11      3       8       1       3       0
//	12      3       8       4       3       2
//	13      3       8       1       3       0
//	14      3       8       2       3       1
//	15      3       8       1       3       0
//	16      4       16      16      4       4


// Returns log2 of integer = the highest power of 2 in n.  Returns 0 for 0 by convention.
ushort log2(ushort n)
{
	if (n <= 1) return 0;
	ushort r = 0;
	while (n > 1)
	{
		r++;
		n >>= 1;
	}
	return r;
}


// Returns the position of rightmost bit as a power of 2 (if rightmost bit is b3, returns 8) = the lowest power of 2 in row, and 0 for 0 by convention
ushort rightmost_p2(ushort row)
{
	if (row == 0) return 0;
	return row - (row & (row - 1));
}

// Bit variant, returns in [0..15] instead of power of 2, = log2(rightmost_p2)
ushort rightmost_bit(ushort row)
{
	return log2(rightmost_p2(row));
}

// Returns the position of leftmost bit as a power of 2 (if leftmost bit is b15, returns 32768) = the highest power of 2 in row, and 0 for 0 by convention
ushort leftmost_p2(ushort row)
{
	if (row == 0) return 0;
	ushort r = 1;
	while (row > 1)
	{
		row >>= 1;
		r <<= 1;
	}
	return r;
}

// Bit variant, returns in [0..15] instead of power of 2, =log2(leftmost_p2)
ushort leftmost_bit(ushort row)
{
	if (row == 0) return 0;
	ushort r = 0;
	while (row > 1)
	{
		row >>= 1;
		r += 1;
	}
	return r;
}


// ---------------------------------------------------------------------------------------------
// File helpers
// 
// Check if a file exists
inline bool file_exists(const std::string& name) {
	if (FILE* file = fopen(name.c_str(), "r"))
	{
		fclose(file);
		return true;
	}
	else
		return false;
}


// ---------------------------------------------------------------------------------------------
// Read a PSF file (PSF1 or PSF2) and fill a memory_font structure
// Returns a memory_font * or NULL in case of problem
static memory_font* load_font(const char* filename)
{
	string file = filename;

	if (!file_exists(file))
	{
		file = "fonts/"s + filename;
		if (!file_exists(file))
		{
			file = "../../fonts/"s + filename;
			if (!file_exists(file))
			{
				cerr << "Error: Can't find font file " << filename << endl;
				return nullptr;
			}
		}
	}

	FILE* f = fopen(file.c_str(), "rb");
	assert(f != NULL);

	// Determine format PSF1/PSF2 based on magic number
	unsigned char magic[4];
	fread(&magic, sizeof(magic), 1, f);

	memory_font* mf = nullptr;
	unsigned int startoffset;				// Starting position of data in file

	if (magic[0] == PSF1_MAGIC0 && magic[1] == PSF1_MAGIC1)
	{
		psf1_header h1;
		fseek(f, 0, SEEK_SET);
		fread(&h1, sizeof(h1), 1, f);
		if (verbose)
		{
			cout << "PSF1 file " << filename << endl;
			cout << "Mode: " << (unsigned int)h1.mode << endl;
			cout << "Charsize: " << h1.charsize << endl;
			cout << "Implied: width: 8\n";
			cout << "Implied: height: " << h1.charsize << endl;
		}

		ushort numglyphs = 256;
		if ((h1.mode & PSF1_MODE512) != 0) numglyphs = 512;
		mf = new memory_font(filename, "PSF1", numglyphs, 8, (ushort)h1.charsize);
		startoffset = 4;
	}
	else if (magic[0] == PSF2_MAGIC0 && magic[1] == PSF2_MAGIC1 && magic[2] == PSF2_MAGIC2 && magic[3] == PSF2_MAGIC3)
	{
		psf2_header h2;
		fseek(f, 0, SEEK_SET);
		fread(&h2, sizeof(h2), 1, f);
		if (verbose)
		{
			cout << "PSF2 file " << filename << endl;
			cout << "version: " << h2.version << endl;
			cout << "headersize: " << h2.headersize << endl;
			cout << "flags: " << h2.flags << endl;
			cout << "length: " << h2.length << endl;
			cout << "charsize: " << h2.charsize << endl;
			cout << "height: " << h2.height << endl;
			cout << "width: " << h2.width << endl;
		}
		assert(h2.charsize == h2.height * ((h2.width + 7) / 8));
		mf = new memory_font(filename, "PSF2", (ushort)h2.length, (ushort)h2.width, (ushort)h2.height);
		startoffset = h2.headersize;
	}
	else
	{
		cerr << "Error: Unknown format of file " << filename << endl;
		fclose(f);
		return nullptr;
	}

	if (mf->width > 16)
	{
		cerr << "Error: Width " << mf->width << " > 16 not supported in file " << filename << endl;
		fclose(f);
		delete mf;
		return nullptr;
	}

	fseek(f, startoffset, SEEK_SET);
	for (unsigned int g = 0; g < mf->numglyphs; g++)
	{
		struct memory_glyph* cg = mf->glyphs + g;
		ushort row = 0;			// Never more than 16 bits
		unsigned char rowbuffer[2] = { 0, 0 };
		cg->rows = (ushort*)malloc(mf->height * sizeof(ushort));
		ushort* bufferptr = cg->rows;
		ushort m1_variable = 0;					// min of min
		ushort m2_variable = 1 << 15;			// max of max
		assert(bufferptr != nullptr);
		for (unsigned int i = 0; i < mf->height; i++)
		{
			// Convert 1 or 2 bytes to a ushort, independent from endianness
			fread(rowbuffer, 1, mf->stride, f);
			if (mf->stride == 1)
				row = rowbuffer[0] << 8;
			else
				row = (rowbuffer[0] << 8) + rowbuffer[1];
			*bufferptr++ = row;

			if (row)
			{
				ushort row_m1 = leftmost_p2(row);
				ushort row_m2 = rightmost_p2(row);
				if (row_m1 > m1_variable) m1_variable = row_m1;
				if (row_m2 < m2_variable) m2_variable = row_m2;
			}
		}
		cg->m1_fixed = (ushort)1 << 15;
		cg->m2_fixed = (ushort)1 << (16 - mf->width);
		cg->b1_fixed = 15;
		cg->b2_fixed = 16 - mf->width;
		if (m1_variable == 0 && m2_variable == 1 << 15)		// Empty char
		{
			cg->m1_variable = cg->m1_fixed;
			cg->m2_variable = 1 << (16 - mf->width / 2);		// by convention, space variable width = half fixed width
			cg->b1_variable = 15;
			cg->b2_variable = 16 - mf->width / 2;
		}
		else
		{
			cg->m1_variable = m1_variable;
			cg->m2_variable = m2_variable;
			cg->b1_variable = log2(m1_variable);
			cg->b2_variable = log2(m2_variable);
		}

		assert(cg->m1_variable == 1 << cg->b1_variable);
		assert(cg->m2_variable == 1 << cg->b2_variable);
		assert(cg->m1_fixed == 1 << cg->b1_fixed);
		assert(cg->m2_fixed == 1 << cg->b2_fixed);

		assert(log2(cg->m1_variable) == cg->b1_variable);
		assert(log2(cg->m2_variable) == cg->b2_variable);
		assert(log2(cg->m1_fixed) == cg->b1_fixed);
		assert(log2(cg->m2_fixed) == cg->b2_fixed);
	}
	fclose(f);
	return mf;
}


// Visual dump
static void dump_font(memory_font* mf, const char* target)
{
	std::ofstream out(target, std::ofstream::out);
	if (out.bad() || out.fail())
	{
		cerr << "Error creating output file " << target << ": " << strerror(errno) << endl;
		return;
	}

	out << "Font " << mf->name << endl;
	out << "Format: " << mf->format << endl;
	out << "Num glyphs: " << mf->numglyphs << endl;
	out << "Width, Height: " << mf->width << ", " << mf->height << endl;
	out << "Stride: " << mf->stride << endl;
	out << endl;

	for (unsigned int c = 0; c < mf->numglyphs; c++)
	{
		struct memory_glyph* mg = mf->glyphs + c;
		ushort* bufferptr = mg->rows;

		out << "Char " << c;
		if (c > 32 && c < 127)
			out << " " << (char)c;
		out << " " << mg->b1_fixed << "-" << mg->b2_fixed << " [" << mg->b1_variable << "-" << mg->b2_variable << "]";
		out << endl;

		for (unsigned int i = 0; i < mf->height; i++)
		{
			ushort row = *bufferptr++;
			out << hex << setw(4) << setfill('0') << row << resetiosflags(ios::showbase) << setfill(' ') << dec << "  ";
			for (ushort m = mg->m1_fixed; m >= mg->m2_fixed; m >>= 1)
				if ((row & m) != 0)
					out << "# ";
				else
					out << ((m > mg->m1_variable || m < mg->m2_variable) ? "  " : ". ");
			out << endl;
		}
		out << endl;
	}

	out.close();
}

static void dump(const char* filename)
{
	cout << filename << endl;

	char target[_MAX_PATH + 1];
	strcpy(target, filename);
	strcpy(target + strlen(target) - 3, "txt");

	auto mf = load_font(filename);
	dump_font(mf, target);
}

static void Transpose_Range(const uint8_t font[][5], uint8_t* buffer, ushort from, ushort to, ushort width, ushort height, ushort* pactwidth, ushort* pactheight)
{
	assert(height <= 8);
	uint8_t tmpchar[8] = { 0 };

	for (ushort i = from; i <= to; i++)
	{
		assert(i >= 0 && i <= 255);

		memset(tmpchar, 0, height);
		ushort wmax = 0;
		for (ushort j = 0; j < 5; j++)
		{
			uint8_t bm = font[i - from][j];
			if (bm != 0 && j > wmax) wmax = j;
			for (ushort k = 0; k < height; k++)
			{
				tmpchar[k] <<= 1;
				if (bm & 1)
				{
					tmpchar[k] |= 1;
					if (k == 7) cout << "Row 8 for char " << i << endl;
				}
				bm >>= 1;
				//if (bm == 0) break;
			}
			ushort rmax = 16;
#pragma warning(disable: 6385)
			for (ushort k = 0; k < height; k++)
				if (tmpchar[height - k])
				{
					rmax = height - k;
					break;
				}
			if (rmax > 0 && rmax > *pactheight)
				*pactheight = rmax;
		}
		if (wmax > 0 && wmax > *pactwidth)
			*pactwidth = wmax;
		for (ushort k = 0; k < height; k++)
			tmpchar[k] <<= 3;
		memcpy(buffer + height * i, tmpchar, height);
	}
}

static void Store_Range(const uint8_t* font, uint8_t* buffer, ushort from, ushort to, ushort width, ushort height, ushort* pactwidth, ushort* pactheight)
{
	assert(height <= 12);		// Because of tmpchar fixed size
	for (ushort i = from; i <= to; i++)
	{
		assert(i >= 0 && i <= 255);

		uint8_t tmpchar[12] = { 0 };
		for (ushort j = 0; j < height; j++)
			tmpchar[j] = font[(i - from) * width + j];

		ushort rmax = 16;
#pragma warning(disable: 6385)
		for (ushort k = 0; k < height; k++)
			if (tmpchar[height - k])
			{
				rmax = height - k;
				break;
			}
		if (rmax > 0 && rmax > *pactheight)
			*pactheight = rmax;
		*pactwidth = 8;
		//for (ushort k = 0; k < height; k++)
		//	tmpchar[k] <<= 8;
		memcpy(buffer + height * i, tmpchar, height);
	}
}


static void Build_Font(const char* target, void (*fillbuffer)(uint8_t* buffer, ushort width, ushort height, ushort*, ushort*), ushort width, ushort height)
{
	assert(width >= 4 && width <= 8);		// Only handle 8 bits width max for now

	psf2_header h2{
		.magic = {PSF2_MAGIC0, PSF2_MAGIC1, PSF2_MAGIC2, PSF2_MAGIC3},
		.version = 1,
		.headersize = sizeof(psf2_header),
		.flags = 0,
		.length = 256,
		.charsize = height,
		.height = height,
		.width = width
	};

	FILE* f = fopen(target, "wb");
	fwrite(&h2, sizeof(h2), 1, f);

	uint8_t* buffer = (uint8_t*)malloc((size_t)256 * h2.charsize);
	assert(buffer != nullptr);
	memset(buffer, 0, (size_t)256 * h2.charsize);

	ushort actheight = 1, actwidth = 1;
	fillbuffer(buffer, (ushort)h2.width, (ushort)h2.charsize, &actwidth, &actheight);

	cout << endl;
	if (actwidth + 1 < (ushort)h2.width)
		cout << "Warning: header defines width " << h2.width << " but data shows that width=" << actwidth + 1 << endl;
	if (actheight + 1 < (ushort)h2.height)
		cout << "Warning: header defines height " << h2.height << " but data shows that heighr=" << actheight + 1 << endl;
	cout << endl;

	fwrite(buffer, h2.charsize, 256, f);
	fclose(f);
	free(buffer);

	dump(target);
}

void Fill_Crystalfont(uint8_t* buffer, ushort width, ushort height, ushort* pactwidth, ushort* pactheight) {
	Transpose_Range(font_cf, buffer, 16, 255, width, height, pactwidth, pactheight);
}

void Fill_HitachiA00(uint8_t* buffer, ushort width, ushort height, ushort* pactwidth, ushort* pactheight) {
	Transpose_Range(font_A00, buffer, 32, 127, width, height, pactwidth, pactheight);
	Transpose_Range(font_A00h, buffer, 160, 255, width, height, pactwidth, pactheight);
}

void Fill_HitachiA02(uint8_t* buffer, ushort width, ushort height, ushort* pactwidth, ushort* pactheight) {
	Transpose_Range(font_A02, buffer, 16, 255, width, height, pactwidth, pactheight);
}

void Fill_Matrix_orbital(uint8_t* buffer, ushort width, ushort height, ushort* pactwidth, ushort* pactheight) {
	Transpose_Range(font_mo, buffer, 16, 255, width, height, pactwidth, pactheight);
}

void Fill_Motorola_6847(uint8_t* buffer, ushort width, ushort height, ushort* pactwidth, ushort* pactheight) {
	Store_Range((uint8_t*)byCoCoFont, buffer, 0, 255, width, height, pactwidth, pactheight);
}

void Fill_Motorola_6847_3(uint8_t* buffer, ushort width, ushort height, ushort* pactwidth, ushort* pactheight) {
	Store_Range((uint8_t*)byCoCo3Font, buffer, 0, 127, width, height, pactwidth, pactheight);
}

void Fill_Std_5x7(uint8_t* buffer, ushort width, ushort height, ushort* pactwidth, ushort* pactheight) {
	Transpose_Range(font_5x7, buffer, 0, 255, width, height, pactwidth, pactheight);
}

void Fill_TI99_Large(uint8_t* buffer, ushort width, ushort height, ushort* pactwidth, ushort* pactheight) {
	Store_Range((uint8_t*)ti_994A_large, buffer, 32, 95, width, height, pactwidth, pactheight);
}

void Fill_TI99_Normal(uint8_t* buffer, ushort width, ushort height, ushort* pactwidth, ushort* pactheight) {
	Store_Range((uint8_t*)ti_994A_normal, buffer, 32, 127, width, height, pactwidth, pactheight);
}

void Fill_TI998_Large(uint8_t* buffer, ushort width, ushort height, ushort* pactwidth, ushort* pactheight) {
	Store_Range((uint8_t*)ti_998_large, buffer, 32, 95, width, height, pactwidth, pactheight);
}

void Fill_TI998_Normal(uint8_t* buffer, ushort width, ushort height, ushort* pactwidth, ushort* pactheight) {
	Store_Range((uint8_t*)ti_998_40col, buffer, 32, 127, width, height, pactwidth, pactheight);
}

void Fill_TI998_32col(uint8_t* buffer, ushort width, ushort height, ushort* pactwidth, ushort* pactheight) {
	Store_Range((uint8_t*)ti_998_32col, buffer, 0, 127, width, height, pactwidth, pactheight);
}

void Fill_Verdana(uint8_t* buffer, ushort width, ushort height, ushort* pactwidth, ushort* pactheight) {
	Transpose_Range(verdana, buffer, 32, 127, width, height, pactwidth, pactheight);
}


int main()
{
#ifdef _WIN32
	system("CHCP 65001 >NUL");
#endif

	cout << "C++ 20 Convert Crystalfontz to PSF\n\n";

	//Build_Font(R"(C:\Development\GitHub\CPP\810_psf_fonts\fonts\5x8Crystalfont.psf)", Fill_Crystalfont, 5, 8);
	//Build_Font(R"(C:\Development\GitHub\CPP\810_psf_fonts\fonts\Hitachi-HD44780A00.psf)", Fill_HitachiA00, 5, 8);
	//Build_Font(R"(C:\Development\GitHub\CPP\810_psf_fonts\fonts\Hitachi-HD44780A02.psf)", Fill_HitachiA02, 5, 8);
	//Build_Font(R"(C:\Development\GitHub\CPP\810_psf_fonts\fonts\Matrix_orbital.psf)", Fill_Matrix_orbital, 5, 8);
	//Build_Font(R"(C:\Development\GitHub\CPP\810_psf_fonts\fonts\Motorola_6847.psf)", Fill_Motorola_6847, 8, 12);
	//Build_Font(R"(C:\Development\GitHub\CPP\810_psf_fonts\fonts\Motorola_6847_3.psf)", Fill_Motorola_6847_3, 8, 8);
	//Build_Font(R"(C:\Development\GitHub\CPP\810_psf_fonts\fonts\Std_5x7.psf)", Fill_Std_5x7, 5, 7);
	//Build_Font(R"(C:\Development\GitHub\CPP\810_psf_fonts\fonts\TI99_Large.psf)", Fill_TI99_Large, 8, 8);
	//Build_Font(R"(C:\Development\GitHub\CPP\810_psf_fonts\fonts\TI99_Normal.psf)", Fill_TI99_Normal, 8, 8);
	//Build_Font(R"(C:\Development\GitHub\CPP\810_psf_fonts\fonts\TI998_Large.psf)", Fill_TI998_Large, 8, 8);
	//Build_Font(R"(C:\Development\GitHub\CPP\810_psf_fonts\fonts\TI998_Normal.psf)", Fill_TI998_Normal, 8, 8);
	//Build_Font(R"(C:\Development\GitHub\CPP\810_psf_fonts\fonts\TI998_32col.psf)", Fill_TI998_32col, 8, 8);
	//Build_Font(R"(C:\Development\GitHub\CPP\810_psf_fonts\fonts\Verdana.psf)", Fill_Verdana, 5, 8);


	dump(R"(C:\Development\GitHub\CPP\810_psf_fonts\fonts\Verdana.psf)");
	dump(R"(C:\Development\GitHub\CPP\810_psf_fonts\fonts\TI998_32col.psf)");
	dump(R"(C:\Development\GitHub\CPP\810_psf_fonts\fonts\TI998_Normal.psf)");
	dump(R"(C:\Development\GitHub\CPP\810_psf_fonts\fonts\TI998_Large.psf)");
	dump(R"(C:\Development\GitHub\CPP\810_psf_fonts\fonts\TI99_Normal.psf)");
	dump(R"(C:\Development\GitHub\CPP\810_psf_fonts\fonts\TI99_Large.psf)");
	dump(R"(C:\Development\GitHub\CPP\810_psf_fonts\fonts\Std_5x7.psf)");
	dump(R"(C:\Development\GitHub\CPP\810_psf_fonts\fonts\Motorola_6847_3.psf)");
	dump(R"(C:\Development\GitHub\CPP\810_psf_fonts\fonts\Motorola_6847.psf)");
	dump(R"(C:\Development\GitHub\CPP\810_psf_fonts\fonts\Matrix_orbital.psf)");
	dump(R"(C:\Development\GitHub\CPP\810_psf_fonts\fonts\Hitachi-HD44780A02.psf)");
	dump(R"(C:\Development\GitHub\CPP\810_psf_fonts\fonts\Hitachi-HD44780A00.psf)");
	dump(R"(C:\Development\GitHub\CPP\810_psf_fonts\fonts\5x8Crystalfont.psf)");
	dump(R"(C:\Development\GitHub\CPP\810_psf_fonts\fonts\6x9-ISO8859-1_9.psf)");
	dump(R"(C:\Development\GitHub\CPP\810_psf_fonts\fonts\5x8-ISO8859-1_8.psf)");
	dump(R"(C:\Development\GitHub\CPP\810_psf_fonts\fonts\5x7-ISO8859-1_7.psf)");
	dump(R"(C:\Development\GitHub\CPP\810_psf_fonts\fonts\zap-vga09.psf)");
	dump(R"(C:\Development\GitHub\CPP\810_psf_fonts\fonts\Lat2-TerminusBold20x10.psf)");
	dump(R"(C:\Development\GitHub\CPP\810_psf_fonts\fonts\Lat2-TerminusBold22x11.psf)");
	dump(R"(C:\Development\GitHub\CPP\810_psf_fonts\fonts\Lat2-TerminusBold24x12.psf)");
	dump(R"(C:\Development\GitHub\CPP\810_psf_fonts\fonts\Lat2-TerminusBold28x14.psf)");
	dump(R"(C:\Development\GitHub\CPP\810_psf_fonts\fonts\Lat2-TerminusBold32x16.psf)");
	dump(R"(C:\Development\GitHub\CPP\810_psf_fonts\fonts\Lat2-TerminusBoldVGA14.psf)");
	dump(R"(C:\Development\GitHub\CPP\810_psf_fonts\fonts\Lat2-TerminusBoldVGA16.psf)");
	dump(R"(C:\Development\GitHub\CPP\810_psf_fonts\fonts\Lat2-VGA8.psf)");
	dump(R"(C:\Development\GitHub\CPP\810_psf_fonts\fonts\Lat2-VGA14.psf)");
	dump(R"(C:\Development\GitHub\CPP\810_psf_fonts\fonts\Lat2-VGA16.psf)");
	dump(R"(C:\Development\GitHub\CPP\810_psf_fonts\fonts\Lat2-VGA28x16.psf)");
	dump(R"(C:\Development\GitHub\CPP\810_psf_fonts\fonts\Lat2-VGA32x16.psf)");
	dump(R"(C:\Development\GitHub\CPP\810_psf_fonts\fonts\Lat2-Fixed13.psf)");
	dump(R"(C:\Development\GitHub\CPP\810_psf_fonts\fonts\Lat2-Fixed14.psf)");
	dump(R"(C:\Development\GitHub\CPP\810_psf_fonts\fonts\Lat2-Fixed15.psf)");
	dump(R"(C:\Development\GitHub\CPP\810_psf_fonts\fonts\Lat2-Fixed16.psf)");
	dump(R"(C:\Development\GitHub\CPP\810_psf_fonts\fonts\Lat2-Fixed18.psf)");
	dump(R"(C:\Development\GitHub\CPP\810_psf_fonts\fonts\Lat2-Terminus12x6.psf)");
	dump(R"(C:\Development\GitHub\CPP\810_psf_fonts\fonts\Lat2-Terminus14.psf)");
	dump(R"(C:\Development\GitHub\CPP\810_psf_fonts\fonts\Lat2-Terminus16.psf)");
	dump(R"(C:\Development\GitHub\CPP\810_psf_fonts\fonts\Lat2-Terminus18x10.psf)");
	dump(R"(C:\Development\GitHub\CPP\810_psf_fonts\fonts\Lat2-Terminus20x10.psf)");
	dump(R"(C:\Development\GitHub\CPP\810_psf_fonts\fonts\Lat2-Terminus22x11.psf)");
	dump(R"(C:\Development\GitHub\CPP\810_psf_fonts\fonts\Lat2-Terminus24x12.psf)");
	dump(R"(C:\Development\GitHub\CPP\810_psf_fonts\fonts\Lat2-Terminus28x14.psf)");
	dump(R"(C:\Development\GitHub\CPP\810_psf_fonts\fonts\Lat2-Terminus32x16.psf)");
	dump(R"(C:\Development\GitHub\CPP\810_psf_fonts\fonts\Lat2-TerminusBold14.psf)");
	dump(R"(C:\Development\GitHub\CPP\810_psf_fonts\fonts\Lat2-TerminusBold16.psf)");
	dump(R"(C:\Development\GitHub\CPP\810_psf_fonts\fonts\Lat2-TerminusBold18x10.psf)");
	dump(R"(C:\Development\GitHub\CPP\810_psf_fonts\fonts\Tamsyn10x20b.psf)");
	dump(R"(C:\Development\GitHub\CPP\810_psf_fonts\fonts\Tamsyn10x20r.psf)");
	dump(R"(C:\Development\GitHub\CPP\810_psf_fonts\fonts\Tamsyn7x13b.psf)");
	dump(R"(C:\Development\GitHub\CPP\810_psf_fonts\fonts\Tamsyn7x14b.psf)");
	dump(R"(C:\Development\GitHub\CPP\810_psf_fonts\fonts\Tamsyn7x14r.psf)");
	dump(R"(C:\Development\GitHub\CPP\810_psf_fonts\fonts\Tamsyn8x15b.psf)");
	dump(R"(C:\Development\GitHub\CPP\810_psf_fonts\fonts\Tamsyn8x15r.psf)");
	dump(R"(C:\Development\GitHub\CPP\810_psf_fonts\fonts\Tamsyn8x16b.psf)");
	dump(R"(C:\Development\GitHub\CPP\810_psf_fonts\fonts\Tamsyn8x16r.psf)");
	dump(R"(C:\Development\GitHub\CPP\810_psf_fonts\fonts\Tamsyn5x9b.psf)");
	dump(R"(C:\Development\GitHub\CPP\810_psf_fonts\fonts\Tamsyn5x9r.psf)");
	dump(R"(C:\Development\GitHub\CPP\810_psf_fonts\fonts\Tamsyn6x12b.psf)");
	dump(R"(C:\Development\GitHub\CPP\810_psf_fonts\fonts\Tamsyn6x12r.psf)");
	dump(R"(C:\Development\GitHub\CPP\810_psf_fonts\fonts\Tamsyn7x13r.psf)");
	dump(R"(C:\Development\GitHub\CPP\810_psf_fonts\fonts\cp850-8x8.psf)");
}
