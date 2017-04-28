// CPP613 pimpl
// Complex.cpp, example of pimpl implementation
//
// Two different private implementations depend on RECTANGULAR constant being defined:
// Use rectangular coordinates x,y when it is defined, or polar coordinates m,a if not defined
// With pimpl idiom, a change will only impact this file and no change in Complex.h,
// avoiding cascade recompilations after a change of private implementation

// 2017-02-02	PV
// 2017-02-11	PV	Conversion from string, litteral operator _i, function call operator


#include <iostream>
#include <memory>
#include <string>
#define _USE_MATH_DEFINES
#include <math.h>
#include <regex>

#include "Complex.h"

using namespace std;


#define RECTANGULAR



class Complex::Complex_Impl {
public:
	Complex_Impl() {
		wcout << L"Complex::Complex_Impl" << endl;
	}

	~Complex_Impl() {
		wcout << L"~Complex::Complex_Impl" << endl;
	}

#ifdef RECTANGULAR
	double x, y;
#else
	double m, a;
#endif
};






Complex::Complex() : Complex(0.0, 0.0) { }

Complex::Complex(double r, double i) : pimpl(new Complex_Impl) {
#ifdef RECTANGULAR
	pimpl->x = r;
	pimpl->y = i;
#else
	pimpl->m = sqrt(r*r + i*i);
	pimpl->a = atan2(i, r);
#endif
}


// Conversion from const char *
Complex::Complex(const char *s) : pimpl(new Complex_Impl) {
	const char *reDouble = R"((\+|-)?((\d+(\.\d*)?)|(\.\d+))((e|E)(\+|-)?\d+)?((i|I)?))";
	typedef std::regex_iterator<const char *> Myiter;

	Myiter::regex_type rd(reDouble);
	Myiter next(s, s + strlen(s), rd);
	Myiter end;
	double r = 0.0, i = 0.0;
	for (; next != end; ++next) {
		string smatch = next->str();
		double d = atof(smatch.c_str());
		char c = smatch[smatch.length() - 1];
		if (c == 'i' || c == 'I')
			i += d;
		else
			r += d;
	}
#ifdef RECTANGULAR
	pimpl->x = r;
	pimpl->y = i;
#else
	pimpl->m = sqrt(r*r + i*i);
	pimpl->a = atan2(i, r);
#endif
}

Complex::~Complex() {};


// Copy constructor
Complex::Complex(const Complex& other) : pimpl(new Complex_Impl) {
#ifdef RECTANGULAR
	pimpl->x = other.pimpl->x;
	pimpl->y = other.pimpl->y;
#else
	pimpl->m = other.pimpl->m;
	pimpl->a = other.pimpl->a;
#endif
}

// Move constructor
Complex::Complex(Complex&& other) noexcept {
	if (this != &other)
		pimpl = move(other.pimpl);
}

// Copy assignment
Complex& Complex::operator=(const Complex& other) {
#ifdef RECTANGULAR
	pimpl->x = other.pimpl->x;
	pimpl->y = other.pimpl->y;
#else
	pimpl->m = other.pimpl->m;
	pimpl->a = other.pimpl->a;
#endif
	return *this;
}

// Move assignment
Complex& Complex::operator=(Complex&& other) noexcept {
	if (this != &other)
		// Should delete current pimpl??
		pimpl = move(other.pimpl);
	return *this;
}



double Complex::Real() const {
#ifdef RECTANGULAR
	return pimpl->x;
#else
	return pimpl->m*cos(pimpl->a);
#endif
}

double Complex::Imag() const {
#ifdef RECTANGULAR
	return pimpl->y;
#else
	return pimpl->m*sin(pimpl->a);
#endif
}

double Complex::Module() const {
#ifdef RECTANGULAR
	return sqrt(pimpl->x*pimpl->x + pimpl->y*pimpl->y);
#else
	return pimpl->m;
#endif
}

double Complex::Argument() const {
#ifdef RECTANGULAR
	return atan2(pimpl->y, pimpl->x);
#else
	return pimpl->a;
#endif
}


Complex Complex::operator-() const {
#ifdef RECTANGULAR
	return Complex(-pimpl->x, -pimpl->y);
#else
	Complex res(*this);
	res.pimpl->a += M_PI;
	return res;
#endif
}


Complex Complex::operator+(const Complex& other) const {
	return Complex(*this) += other;
	//#ifdef RECTANGULAR
	//	return Complex(pimpl->x + other.pimpl->x, pimpl->y + other.pimpl->y);
	//#else
	//	return Complex(Real() + other.Real(), Imag()+other.Imag());
	//#endif
}

Complex Complex::operator-(const Complex& other) const {
	return this->operator+(-other);
}


Complex& Complex::operator+=(const Complex& other) {
#ifdef RECTANGULAR
	pimpl->x += other.pimpl->x;
	pimpl->y += other.pimpl->y;
#else
	double r = Real() + other.Real();
	double i = Imag() + other.Imag();
	pimpl->m = sqrt(r*r + i*i);
	pimpl->a = atan2(i, r);
#endif
	return *this;
};

Complex& Complex::operator-=(const Complex& other) {
	return operator+=(-other);
}



// Function call operator (scale factor)
Complex Complex::operator()(double factor) const {
#ifdef RECTANGULAR
	return Complex(factor*pimpl->x, factor*pimpl->y);
#else
	Complex res(*this);
	res.pimpl->m *= factor;
	return res;
#endif
}




Complex::operator std::wstring() const {
	return ToWString();
}


// Variant of to_string for double numbers that eliminate trailing zeroes
// Not totally sure whether a generic version is Ok of if it'd be better to provide only a double (anf float) implementation
// From http://stackoverflow.com/questions/13686482/c11-stdto-stringdouble-no-trailing-zeros
namespace util { 
	std::string to_string(const double& t) { 
		std::string str{ std::to_string(t) }; 
		int offset{ 1 }; 
		if (str.find_last_not_of('0') == str.find('.')) { offset = 0; } 
		str.erase(str.find_last_not_of('0') + offset, std::string::npos); 
		return str; 
	} 

	std::wstring to_wstring(const double& t) {
		std::wstring str{ std::to_wstring(t) };
		int offset{ 1 };
		if (str.find_last_not_of(L'0') == str.find(L'.')) { offset = 0; }
		str.erase(str.find_last_not_of(L'0') + offset, std::string::npos);
		return str;
	}

	//template <typename T>
	//std::string to_string(const T& t) {
	//	std::string str{ std::to_string(t) };
	//	int offset{ 1 };
	//	if (str.find_last_not_of('0') == str.find('.')) { offset = 0; }
	//	str.erase(str.find_last_not_of('0') + offset, std::string::npos);
	//	return str;
	//}

	//template <typename T>
	//std::wstring to_wstring(const T& t) {
	//	std::wstring str{ std::to_wstring(t) };
	//	int offset{ 1 };
	//	if (str.find_last_not_of(L'0') == str.find(L'.')) { offset = 0; }
	//	str.erase(str.find_last_not_of(L'0') + offset, std::string::npos);
	//	return str;
	//}
}


wstring Complex::ToWString() const {
#ifdef RECTANGULAR
	return util::to_wstring(pimpl->x) + (pimpl->y >= 0 ? L"+" : L"") + util::to_wstring(pimpl->y) + L"i";
#else
	// Not supported by Consolas Unicode (next 2)
	// L" ̲/" 
	// L"∠"
	// Alternative
	// L" ∟ Λ ∆ ∕ ⌂ ╱ ╳ ◄ ◊ "
	return to_wstring(pimpl->m) + L" Λ " + to_wstring(pimpl->a) + L"rd";
#endif
}


Complex::operator std::string() const {
#ifdef RECTANGULAR
	return to_string(pimpl->x) + string(pimpl->y >= 0 ? "+" : "") + to_string(pimpl->y) + "i";
#else
	return to_string(pimpl->m) + " /_ " + to_string(pimpl->a) + "rd";
#endif
}


// Helper for wide iostream.  
// Strictly speaking not needed since a conversion operator to wstring is provided, an equivalent for ostream
// is not provided.
wostream& operator <<(wostream& wout, const Complex& c)
{
	wout << c.ToWString();
	return wout;
}


// Litteral operator: Suffix _i for double numbers make a complex
Complex operator""_i(long double value)
{	// return imaginary _Val
	return Complex(0.0, static_cast<double>(value));
}
