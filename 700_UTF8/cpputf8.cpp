// cpputf8: test of utf8 in C++
// From http://utfcpp.sourceforge.net/
//
// 2019-11-07   PV
// 2022-07-13	PV		C++ refresh

#include <iostream>
#include <vector>
#include <cstring>
#include <assert.h>

#include "utf8.h"

using namespace std;
using namespace utf8;

int main()
{
    // Convert utf8 to utf32
    const char *u8str = "Aé♫山𝄞🐗";      // Do not use u8 prefix!!!  This source is already utf-8 encoded
    vector<int> utf32result;
    unchecked::utf8to32(u8str, u8str + strlen(u8str), back_inserter(utf32result));
    assert(utf32result.size() == 6);

    // And convert back to utf8
    vector<unsigned char> utf8result;
    utf32to8(begin(utf32result), end(utf32result), back_inserter(utf8result));
    assert(strlen(u8str) == utf8result.size());

	cout << u8str << endl;
}
