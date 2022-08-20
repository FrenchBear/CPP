// CS810_psf.cpp
// Play with C++, dump psf font files
//
// 2022-08-20	PV		First version

#define _CRT_SECURE_NO_WARNINGS

#include <cstdio>
#include <cassert>
#include <iostream>
#include <iomanip>

#ifdef _WIN32
#include <format> // std::format
#else
#include "gpp_format.h"
#endif

using namespace std;

// File header

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
	unsigned char magic[2];     /* Magic number */
	unsigned char mode;         /* PSF font mode */
	unsigned char charsize;     /* Character size */
};


// PSF2 format
#define PSF2_MAGIC0     0x72
#define PSF2_MAGIC1     0xb5
#define PSF2_MAGIC2     0x4a
#define PSF2_MAGIC3     0x86

/* bits used in flags */
#define PSF2_HAS_UNICODE_TABLE 0x01

/* max version recognized so far */
#define PSF2_MAXVERSION 0

/* UTF8 separators */
#define PSF2_SEPARATOR  0xFF
#define PSF2_STARTSEQ   0xFE

struct psf2_header {
	unsigned char magic[4];
	unsigned int version;
	unsigned int headersize;    /* offset of bitmaps in file */
	unsigned int flags;
	unsigned int length;        /* number of glyphs */
	unsigned int charsize;      /* number of bytes for each character */
	unsigned int height, width; /* max dimensions of glyphs */
	/* charsize = height * ((width + 7) / 8) */
};


inline bool file_exists(const std::string& name) {
	if (FILE* file = fopen(name.c_str(), "r")) {
		fclose(file);
		return true;
	}
	else {
		return false;
	}
}

static void dump_font(const char* filename)
{
	string file = "fonts/"s + filename;
	if (!file_exists(file))
	{
		file = "../../fonts/"s + filename;
		if (!file_exists(file))
		{
			cout << "Error, can't find font file " << filename << endl;
			return;
		}
	}

	cout << "Processing " << file << endl;
	FILE* f = fopen(file.c_str(), "rb");
	assert(f != NULL);

	unsigned char magic[4];
	int iVersion = 0;
	psf1_header h1;
	psf2_header h2;
	fread(&magic, sizeof(magic), 1, f);

	unsigned int numglyphs;
	unsigned int width, height;
	unsigned int charsize;
	unsigned int startoffset;

	if (magic[0] == PSF1_MAGIC0 && magic[1] == PSF1_MAGIC1)
	{
		cout << "PSF1 file\n";
		iVersion = 1;
		fseek(f, 0, SEEK_SET);
		fread(&h1, sizeof(h1), 1, f);
		cout << "Mode: " << (unsigned int)h1.mode << endl;
		cout << "Charsize: " << h1.charsize << endl;
		cout << "Implied: width: 8\n";
		cout << "Implied: height: " << h1.charsize << endl;

		numglyphs = 256;
		if ((h1.mode & PSF1_MODE512) != 0) numglyphs = 512;
		width = 8;
		height = h1.charsize;
		charsize = h1.charsize;
		startoffset = 4;
	}
	else if (magic[0] == PSF2_MAGIC0 && magic[1] == PSF2_MAGIC1 && magic[2] == PSF2_MAGIC2 && magic[3] == PSF2_MAGIC3)
	{
		cout << "PSF2 file\n";
		iVersion = 2;
		fseek(f, 0, SEEK_SET);
		fread(&h2, sizeof(h2), 1, f);
		cout << "version: " << h2.version << endl;
		cout << "headersize: " << h2.headersize << endl;
		cout << "flags: " << h2.flags << endl;
		cout << "length: " << h2.length << endl;
		cout << "charsize: " << h2.charsize << endl;
		cout << "height: " << h2.height << endl;
		cout << "width: " << h2.width << endl;
		assert(h2.charsize == h2.height * ((h2.width + 7) / 8));

		numglyphs = h2.length;
		width = h2.width;
		height = h2.height;
		charsize = h2.charsize;
		startoffset = h2.headersize;
	}
	else
	{
		cout << "Unknown format\n";
		fclose(f);
		return;
	}

	cout << "\nContinue\n";
	cout << "Num glyphs: " << numglyphs << endl;
	cout << "Width, Height: " << width << ", " << height << endl;
	cout << "Charsize: " << charsize << endl;
	cout << "Start offset: " << startoffset << endl;

	if (width >= 64)
	{
		cout << "width>64 not supported...\n";
		fclose(f);
		return;
	}

	fseek(f, startoffset, SEEK_SET);

	for (unsigned int g = 0; g < numglyphs; g++)
	{

		int stride = ((width + 7) / 8);	// Number of bytes per row
		unsigned int row;		// 32 bits max width
		for (unsigned int i = 0; i < height; i++)
		{
			row = 0;
			string r = "";
			fread((char*)&row, 1, stride, f);

			// Compensate wrong endianness for 2 bytres only, to rewrite clean
			if (stride == 1)
				/* nop */;
			else if (stride == 2)
				row = ((row & 0xFF) << 8) | ((row >> 8) & 0xff);
			else
				assert("unsupported stride in endianness correction");

			cout << hex << setw((short)(2 * stride)) << setfill('0') << row << resetiosflags(ios::showbase) << setfill(' ') << dec << "  ";
			unsigned int m = (unsigned)1 << (8 * stride - 1);
			for (unsigned int j = 0; j < width; j++)
			{
				r += (((row & m) != 0) ? "# " : ". ");
				m >>= 1;
			}
			cout << r << endl;
		}
		cout << endl;
	}
	fclose(f);
}

int main()
{
#ifdef _WIN32
	system("CHCP 65001 >NUL");
#endif

	cout << "C++ 20 PSF dump\n\n";

	//dump_font("Lat2-VGA14.psf");
	//dump_font("Lat2-VGA28x16.psf");
	//dump_font("Lat2-Terminus12x6.psf");
	//dump_font("Lat2-TerminusBold18x10.psf");
	//dump_font("Lat2-TerminusBold28x14.psf");
	dump_font("Lat2-TerminusBold32x16.psf");

	return 0;
}
