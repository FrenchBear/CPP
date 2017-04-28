// CPP613 pimpl
// Complex.h, example of pimpl header

#pragma once

#include <iostream>
#include <memory>
#include <string>

class Complex
{
public:
	// Standard constructors and conversions from other types
	Complex();
	Complex(double r, double i = 0.0);
	Complex(const char *s);
	~Complex();

	// Extra copy/move constructors and assignment operators
	Complex(const Complex& other);					// Copy constructor
	Complex(Complex&& other) noexcept;				// Move constructor
	Complex& operator=(const Complex& other);		// Copy assignment
	Complex& operator=(Complex&& other) noexcept;	// Move assignment

	// Support functions
	double Real() const;
	double Imag() const;
	double Module() const;
	double Argument() const;

	// Unary operators
	Complex operator-() const;

	// Binary operators
	Complex operator+(const Complex& other) const;
	Complex operator-(const Complex& other) const;

	// Assignment operators
	Complex& operator+=(const Complex& other);
	Complex& operator-=(const Complex& other);

	// Conversion to other types
	operator std::wstring() const;
	std::wstring ToWString() const;
	operator std::string() const;

	// Function call operator (scale factor)
	Complex operator()(double) const;

	// pimpl pattern, private implementation is hidden behind a pointer
private:
	class Complex_Impl;
	std::unique_ptr<Complex_Impl> pimpl;
};


// Helper for iostream.  Strictly speaking not needed since a conversion operator to wstring is provided
std::wostream& operator <<(std::wostream& wout, const Complex& c);


// Litteral operator: Suffix i for double numbers make a complex
Complex operator""_i(long double value);
