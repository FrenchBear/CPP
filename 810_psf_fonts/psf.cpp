// CS810_psf.cpp
// Play with C++, dump psf font files
//
// 2022-08-20	PV		First version
// 2022-08-21	PV		Second version, memory_font structure

#define _CRT_SECURE_NO_WARNINGS

#include <cstdio>
#include <cassert>
#include <iostream>
#include <fstream>
#include <iomanip>

#ifdef _WIN32
#include <format> // std::format
#else
#include "gpp_format.h"
#endif

using namespace std;
using ushort = unsigned short;


bool verbose = false;


// File headers

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


// My own representation in memory, all rows are 2 bytes (ushort) independetly from stride/width
struct memory_glyph {
	ushort m1_fixed, m2_fixed;
	ushort m1_variable, m2_variable;
	ushort* rows;			// each row is stored on 2 bytes
};

struct memory_font {
	memory_font(const char* filename, ushort numglyphs, ushort width, ushort height)
	{
		name = _strdup(filename);
		this->numglyphs = numglyphs;
		this->width = width;
		this->height = height;
		stride = ((width + 7) / 8);
		glyphs = (struct memory_glyph*)malloc(sizeof(struct memory_glyph) * numglyphs);
		assert(glyphs != nullptr);
		memset(glyphs, 0, sizeof(struct memory_glyph) * numglyphs);
	}

	~memory_font()
	{
		free((void*)name);
		name = nullptr;
		free((void*)glyphs);
		glyphs = nullptr;
	}

	const char* name;
	ushort numglyphs;
	ushort width, height;			// in bits
	ushort stride;					// width in bytes, = ((width + 7) / 8)
	struct memory_glyph* glyphs;	// One glyph

};

// Helper
inline bool file_exists(const std::string& name) {
	if (FILE* file = fopen(name.c_str(), "r"))
	{
		fclose(file);
		return true;
	}
	else
		return false;
}

ushort rightmost_bit(ushort row)
{
	return row - (row & (row - 1));
}

ushort leftmost_bit(ushort row)
{
	ushort r = 1;
	while (row > 1)
	{
		row >>= 1;
		r <<= 1;
	}
	return r;
}

// Returns a memory_font * or null in case of problem
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
		mf = new memory_font(filename, numglyphs, 8, (ushort)h1.charsize);
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
		mf = new memory_font(filename, (ushort)h2.length, (ushort)h2.width, (ushort)h2.height);
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
	//ushort* bufferptr = mf->buffer;
	for (unsigned int g = 0; g < mf->numglyphs; g++)
	{
		ushort row = 0;			// Never more than 16 bits
		unsigned char rowbuffer[2] = { 0,0 };
		mf->glyphs[g].rows = (ushort*)malloc(mf->height * sizeof(ushort));
		ushort* bufferptr = mf->glyphs[g].rows;
		ushort m1_variable = 0;
		ushort m2_variable = 1 << 15;
		assert(bufferptr != nullptr);
		for (unsigned int i = 0; i < mf->height; i++)
		{
			// Convert 1 or 2 bytes to a ushort, independent from endianness
			fread(rowbuffer, 1, mf->stride, f);
			if (mf->stride == 1)
				row = rowbuffer[0];
			else
				row = (rowbuffer[0] << 8) + rowbuffer[1];
			*bufferptr++ = row;

			if (row)
			{
				ushort row_m1 = leftmost_bit(row);
				ushort row_m2 = rightmost_bit(row);
				if (row_m1 > m1_variable) m1_variable = row_m1;
				if (row_m2 < m2_variable) m2_variable = row_m2;
			}
		}
		mf->glyphs[g].m1_fixed = (ushort)1 << (8 * mf->stride - 1);
		mf->glyphs[g].m2_fixed = (ushort)1 << (8 * mf->stride - mf->width);
		if (m1_variable == 0 && m2_variable == 1 << 15)
		{
			mf->glyphs[g].m1_variable = 1 << (mf->width / 2);
			mf->glyphs[g].m2_variable = 1;
		}
		else
		{
			mf->glyphs[g].m1_variable = m1_variable;
			mf->glyphs[g].m2_variable = m2_variable;
		}
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
	out << "Num glyphs: " << mf->numglyphs << endl;
	out << "Width, Height: " << mf->width << ", " << mf->height << endl;
	out << "Stride: " << mf->stride << endl;

	for (unsigned int c = 0; c < mf->numglyphs; c++)
	{
		out << "Char " << c;
		if (c > 32 && c < 127)
			out << " " << (char)c;
		out << endl;

		struct memory_glyph* mg = mf->glyphs + c;
		ushort* bufferptr = mg->rows;
		for (unsigned int i = 0; i < mf->height; i++)
		{
			string r = "";
			ushort row = *bufferptr++;
			out << hex << setw((short)(2 * mf->stride)) << setfill('0') << row << resetiosflags(ios::showbase) << setfill(' ') << dec << "  ";
			//ushort m1 = (ushort)1 << (8 * mf->stride - 1);
			//ushort m2 = (ushort)1 << (8 * mf->stride - mf->width);
			for (ushort m = mg->m1_variable; m >= mg->m2_variable; m >>= 1)
				r += (((row & m) != 0) ? "# " : ". ");
			out << r << endl;
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

int main()
{
#ifdef _WIN32
	system("CHCP 65001 >NUL");
#endif

	cout << "C++ 20 PSF dump\n\n";

	dump("C:\\Development\\GitHub\\CPP\\810_psf_fonts\\fonts\\5x7-ISO8859-1_7.psf");
	dump("C:\\Development\\GitHub\\CPP\\810_psf_fonts\\fonts\\5x8-ISO8859-1_8.psf");
	dump("C:\\Development\\GitHub\\CPP\\810_psf_fonts\\fonts\\6x9-ISO8859-1_9.psf");
	dump("C:\\Development\\GitHub\\CPP\\810_psf_fonts\\fonts\\cp850-8x8.psf");
	dump("C:\\Development\\GitHub\\CPP\\810_psf_fonts\\fonts\\Tamsyn5x9b.psf");
	dump("C:\\Development\\GitHub\\CPP\\810_psf_fonts\\fonts\\Tamsyn5x9r.psf");
	dump("C:\\Development\\GitHub\\CPP\\810_psf_fonts\\fonts\\zap-vga09.psf");
	dump("C:\\Development\\GitHub\\CPP\\810_psf_fonts\\fonts\\Lat2-VGA8.psf");
	dump("C:\\Development\\GitHub\\CPP\\810_psf_fonts\\fonts\\Tamsyn6x12b.psf");
	dump("C:\\Development\\GitHub\\CPP\\810_psf_fonts\\fonts\\Tamsyn6x12r.psf");
	dump("C:\\Development\\GitHub\\CPP\\810_psf_fonts\\fonts\\Tamsyn7x13b.psf");
	dump("C:\\Development\\GitHub\\CPP\\810_psf_fonts\\fonts\\Tamsyn7x13r.psf");
	dump("C:\\Development\\GitHub\\CPP\\810_psf_fonts\\fonts\\Tamsyn7x14r.psf");
	dump("C:\\Development\\GitHub\\CPP\\810_psf_fonts\\fonts\\Tamsyn7x14b.psf");
	dump("C:\\Development\\GitHub\\CPP\\810_psf_fonts\\fonts\\Tamsyn8x15r.psf");
	dump("C:\\Development\\GitHub\\CPP\\810_psf_fonts\\fonts\\Tamsyn8x15b.psf");
	dump("C:\\Development\\GitHub\\CPP\\810_psf_fonts\\fonts\\Lat2-Terminus12x6.psf");
	dump("C:\\Development\\GitHub\\CPP\\810_psf_fonts\\fonts\\Tamsyn8x16r.psf");
	dump("C:\\Development\\GitHub\\CPP\\810_psf_fonts\\fonts\\Tamsyn8x16b.psf");
	dump("C:\\Development\\GitHub\\CPP\\810_psf_fonts\\fonts\\Lat2-Fixed13.psf");
	dump("C:\\Development\\GitHub\\CPP\\810_psf_fonts\\fonts\\Lat2-Fixed14.psf");
	dump("C:\\Development\\GitHub\\CPP\\810_psf_fonts\\fonts\\Lat2-Terminus14.psf");
	dump("C:\\Development\\GitHub\\CPP\\810_psf_fonts\\fonts\\Lat2-TerminusBold14.psf");
	dump("C:\\Development\\GitHub\\CPP\\810_psf_fonts\\fonts\\Lat2-TerminusBoldVGA14.psf");
	dump("C:\\Development\\GitHub\\CPP\\810_psf_fonts\\fonts\\Lat2-VGA14.psf");
	dump("C:\\Development\\GitHub\\CPP\\810_psf_fonts\\fonts\\Lat2-Fixed15.psf");
	dump("C:\\Development\\GitHub\\CPP\\810_psf_fonts\\fonts\\Lat2-Fixed16.psf");
	dump("C:\\Development\\GitHub\\CPP\\810_psf_fonts\\fonts\\Lat2-Terminus16.psf");
	dump("C:\\Development\\GitHub\\CPP\\810_psf_fonts\\fonts\\Lat2-TerminusBold16.psf");
	dump("C:\\Development\\GitHub\\CPP\\810_psf_fonts\\fonts\\Lat2-TerminusBoldVGA16.psf");
	dump("C:\\Development\\GitHub\\CPP\\810_psf_fonts\\fonts\\Lat2-VGA16.psf");
	dump("C:\\Development\\GitHub\\CPP\\810_psf_fonts\\fonts\\Lat2-Fixed18.psf");
	dump("C:\\Development\\GitHub\\CPP\\810_psf_fonts\\fonts\\Lat2-Terminus18x10.psf");
	dump("C:\\Development\\GitHub\\CPP\\810_psf_fonts\\fonts\\Lat2-TerminusBold18x10.psf");
	dump("C:\\Development\\GitHub\\CPP\\810_psf_fonts\\fonts\\Tamsyn10x20b.psf");
	dump("C:\\Development\\GitHub\\CPP\\810_psf_fonts\\fonts\\Tamsyn10x20r.psf");
	dump("C:\\Development\\GitHub\\CPP\\810_psf_fonts\\fonts\\Lat2-Terminus20x10.psf");
	dump("C:\\Development\\GitHub\\CPP\\810_psf_fonts\\fonts\\Lat2-TerminusBold20x10.psf");
	dump("C:\\Development\\GitHub\\CPP\\810_psf_fonts\\fonts\\Lat2-Terminus22x11.psf");
	dump("C:\\Development\\GitHub\\CPP\\810_psf_fonts\\fonts\\Lat2-TerminusBold22x11.psf");
	dump("C:\\Development\\GitHub\\CPP\\810_psf_fonts\\fonts\\Lat2-Terminus24x12.psf");
	dump("C:\\Development\\GitHub\\CPP\\810_psf_fonts\\fonts\\Lat2-TerminusBold24x12.psf");
	dump("C:\\Development\\GitHub\\CPP\\810_psf_fonts\\fonts\\Lat2-VGA28x16.psf");
	dump("C:\\Development\\GitHub\\CPP\\810_psf_fonts\\fonts\\Lat2-Terminus28x14.psf");
	dump("C:\\Development\\GitHub\\CPP\\810_psf_fonts\\fonts\\Lat2-TerminusBold28x14.psf");
	dump("C:\\Development\\GitHub\\CPP\\810_psf_fonts\\fonts\\Lat2-Terminus32x16.psf");
	dump("C:\\Development\\GitHub\\CPP\\810_psf_fonts\\fonts\\Lat2-TerminusBold32x16.psf");
	dump("C:\\Development\\GitHub\\CPP\\810_psf_fonts\\fonts\\Lat2-VGA32x16.psf");

	/*
	ushort n = 0x0C30;
	ushort m1 = leftmost_bit(n);
	ushort m2 = rightmost_bit(n);
	printf("n  = %08x\n", n);
	printf("m1 = %08x\n", m1);
	printf("m2 = %08x\n", m2);
	*/

	//auto mf = load_font("5x7-ISO8859-1_7.psf");
	//auto mf = load_font("Tamsyn5x9r.psf");
	//auto mf = load_font("cp850-8x8.psf");
	//auto mf = load_font("Tamsyn6x12r.psf");
	//auto mf = load_font("zap-vga09.psf");
	//auto mf = load_font("Lat2-VGA8.psf");
	//auto mf = load_font("Lat2-Terminus12x6.psf");
	//auto mf = load_font("Lat2-Fixed13.psf");
	//auto mf = load_font("Lat2-VGA14.psf");
	//auto mf = load_font("Lat2-VGA28x16.psf");
	//auto mf = load_font("Lat2-Terminus12x6.psf");
	//auto mf = load_font("Lat2-TerminusBold18x10.psf");
	//auto mf = load_font("Lat2-TerminusBold28x14.psf");
	//auto mf = load_font("Lat2-TerminusBold32x16.psf");
	//auto mf = load_font("Lat2-TerminusBold24x12.psf");

	//if (mf)
	//	dump_font(mf);

	return 0;
}
