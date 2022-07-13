// CPP616 Strings
// Various types of strings in C++
//
// 2017-02-09	PV
// 2017-02-11	PV		Test2
// 2017-04-29	PV		GitHub and Linux
// 2021-09-14	PV		Visual Studio 2022

#include <iostream>
#include <string>

using namespace std;

#ifdef _WIN32
#pragma warning(disable: 4566)		// Warning	C4566: Character represented by universal - character - name '\u2502' cannot be represented in the current code page(1252)
#endif

// My own tests
/*
Crazy output:

cout t1: O¨ þa? H?LÓ??!
cout t2: O├╣ ├ºa? H╠éL├á­ƒìî!
cout t3: 0116B310
cout t4: 0116B334
cout t5: 0116B358
wcout t1: O¨ þa? H?LÓ??!
wcout t2: O├╣ ├ºa? H╠éL├á­ƒìî!
wcout t3: O¨ þa? Hcout s1: O¨ þa? H?LÓ??!
cout s2: O├╣ ├ºa? H╠éL├á­ƒìî!
*/
void Test1() {
	// string info from http://en.cppreference.com/w/cpp/language/string_literal

	// c:\temp\project1cpp\source.cpp(32) : warning C4566 : character represented by universal - character - name '\u0302' cannot be represented in the current code page(1252)
	// c:\temp\project1cpp\source.cpp(32) : warning C4566 : character represented by universal - character - name '\U0001F34C' cannot be represented in the current code page(1252)
	const char *t1 = "Où ça? ĤLà🍌!";			// The type of an unprefixed string literal is const char[]

	auto t2 = u8"Où ça? ĤLà🍌!";		// The type of a u8"..." string literal is const char[]

	const wchar_t *t3 = L"Où ça? ĤLà🍌!";		// The type of a L"..." string literal is const wchar_t[]

	const char16_t *t4 = u"Où ça? ĤLà🍌!";	// UTF-16	The type of a u"..." string literal is const char16_t[]

	const char32_t *t5 = U"Où ça? ĤLà🍌!";	// UTF-32	The type of a U"..." string literal is const char32_t[]

										// c:\temp\project1cpp\source.cpp(31) : warning C4566 : character represented by universal - character - name '\u0302' cannot be represented in the current code page(1252)
										// c:\temp\project1cpp\source.cpp(31) : warning C4566 : character represented by universal - character - name '\U0001F34C' cannot be represented in the current code page(1252)
	const char *t6 = R"(Où ça? ĤLà🍌!)";

	// c:\temp\project1cpp\source.cpp(25) : warning C4566 : character represented by universal - character - name '\u0302' cannot be represented in the current code page(1252)
	// c:\temp\project1cpp\source.cpp(25) : warning C4566 : character represented by universal - character - name '\U0001F34C' cannot be represented in the current code page(1252)
	string s1 = "Où ça? ĤLà🍌!"s;

	auto s2 = u8"Où ça? ĤLà🍌!"s;

	wstring s3 = L"Où ça? ĤLà🍌!";

	u16string s4 = u"Où ça? ĤLà🍌!";

	u32string s5 = U"Où ça? ĤLà🍌!";


	cout << "cout t1: " << t1 << endl;

#ifdef _WIN32
	cout << "cout t2: " << t2 << endl;
	cout << "cout t3: " << t3 << endl;
	cout << "cout t4: " << t4 << endl;
	cout << "cout t5: " << t5 << endl;
#endif

	wcout << "wcout t1: " << t1 << endl;
#ifdef _WIN32
	wcout << "wcout t2: " << t2 << endl;
	wcout << "wcout t3: " << t3 << endl;
	wcout << "wcout t4: " << t4 << endl;
	wcout << "wcout t5: " << t5 << endl;
#endif

	cout << "cout s1: " << s1 << endl;
#ifdef _WIN32
	cout << "cout s2: " << s2 << endl;
#endif
	//cout << "cout s3: " << s3 << endl;
	//cout << "cout s4: " << s4 << endl;
	//cout << "cout s5: " << s5 << endl;

	//wcout << "wcout s1: " << s1 << endl;
	//wcout << "wcout s2: " << s2 << endl;
	wcout << "wcout s3: " << s3 << endl;
	//wcout << "wcout s4: " << s4 << endl;
	//wcout << "wcout s5: " << s5 << endl;

}



// From msdn String and Character Literals (C++)
// https://docs.microsoft.com/en-us/cpp/cpp/string-and-character-literals-cpp
void Test2() {
	using namespace std::string_literals; // enables s-suffix for std::string literals  

	// Character literals  
	auto c0 = 'A'; // char  
#ifdef _WIN32
	auto c1 = u8'A'; // char  
#endif
	auto c2 = L'A'; // wchar_t  
	auto c3 = u'A'; // char16_t  
	auto c4 = U'A'; // char32_t  

	// String literals  
	auto s0 = "hello"; // const char*  
	auto s1 = u8"hello"; // const char*, encoded as UTF-8  
	auto s2 = L"hello"; // const wchar_t*  
	auto s3 = u"hello"; // const char16_t*, encoded as UTF-16  
	auto s4 = U"hello"; // const char32_t*, encoded as UTF-32  

	// Raw string literals containing unescaped \ and "  
	auto R0 = R"("Hello \ world")"; // const char*  
	auto R1 = u8R"("Hello \ world")"; // const char*, encoded as UTF-8  
	auto R2 = LR"("Hello \ world")"; // const wchar_t*  
	auto R3 = uR"("Hello \ world")"; // const char16_t*, encoded as UTF-16  
	auto R4 = UR"("Hello \ world")"; // const char32_t*, encoded as UTF-32  

	// Combining string literals with standard s-suffix  
	auto S0 = "hello"s; // std::string  
	auto S1 = u8"hello"s; // std::string  
	auto S2 = L"hello"s; // std::wstring  
	auto S3 = u"hello"s; // std::u16string  
	auto S4 = U"hello"s; // std::u32string  

	// Combining raw string literals with standard s-suffix  
	auto S5 = R"("Hello \ world")"s; // std::string from a raw const char*  
	auto S6 = u8R"("Hello \ world")"s; // std::string from a raw const char*, encoded as UTF-8  
	auto S7 = LR"("Hello \ world")"s; // std::wstring from a raw const wchar_t*  
	auto S8 = uR"("Hello \ world")"s; // std::u16string from a raw const char16_t*, encoded as UTF-16  
	auto S9 = UR"("Hello \ world")"s; // std::u32string from a raw const char32_t*, encoded as UTF-32  
}


void Test3() {
	char newline = '\n';
	char tab = '\t';
	char backspace = '\b';
	char backslash = '\\';
	char nullChar = '\0';

	// Universal character names
	// In character literals and native (non-raw) string literals, any character may be represented by a universal character name.
	// Universal character names are formed by a prefix \U followed by an eight-digit Unicode code point, or by a prefix \u
	// followed by a four digit Unicode code point. All eight or four digits, respectively, must be present to make a well-formed
	// universal character name.
	char u1 = 'A';          // 'A'  
	char u2 = '\101';       // octal, 'A'   
	char u3 = '\x41';       // hexadecimal, 'A'  
	char u4 = '\u0041';     // \u UCN 'A'  
	char u5 = '\U00000041'; // \U UCN 'A'
}

int main() {
	Test1();
	Test2();


#ifdef _WIN32
	cout << "\n(Pause)";
	cin.get();
#endif
	return 0;
}
