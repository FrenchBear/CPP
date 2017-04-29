// 623 CPP Stroustrup
// Example of C++ based on C++ Tour
//
// 2017-03-17..28	PV
// 2017-04-29		PV	GitHub and Linux; if constexpr not supported by g++

#define _SCL_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <assert.h>
#include <iostream>
#include <iomanip>
#include <string>
#include <vector>
#include <map>
#include <memory>
#include <initializer_list>
#include <memory.h>
#include <complex>
#include <exception>


using namespace std;


template <typename T>
class Collection {
public:
	using value_type = T;
	virtual T& operator[](int i) = 0;
	virtual const T& operator[](int i) const = 0;
	virtual size_t size() const = 0;
	virtual T* begin() const = 0;
	virtual T* end() const = 0;
};


template <typename T>
class Vector :public Collection<T> {
private:
	T* elem;
	size_t sz;

public:
	Vector() : elem(nullptr), sz(0) {
		cout<<"Vector default ctor\n";
	}

	Vector(size_t s) {
		cout<<"Vector ctor(int)\n";
		sz = s;
		elem = new T[s];
		// int specialization calls memset to clear elements
	}

	Vector(initializer_list<T> li) {
		cout<<"Vector ctor(initializer_list<T>)\n";
		sz = li.size();
		elem = new T[sz];
		copy(li.begin(), li.end(), elem);
		//T* dest = elem;
		//for (auto s = li.begin(); s != li.end(); ++s)
		//	*dest++ = move(*const_cast<T*>(s));
	}

	~Vector() {
		cout<<"Vector dtor\n";
		delete[] elem;
	}

	Vector(const Vector& a) {
		cout<<"Vector ctor copy\n";
		sz = a.sz;
		elem = new T[sz];
		for (size_t i = 0; i<sz; i++)
			elem[i] = a[i];
	}

	Vector& operator=(const Vector& a) {
		cout<<"Vector copy assignment operator\n";
		if (this!=&a) {
			T* p = new T[a.sz];
			for (size_t i = 0; i<sz; i++)
				elem[i] = a[i];
			delete[] elem;
			elem = p;
			sz = a.sz;
		}
		return *this;
	}

	Vector(Vector&& a) {
		cout<<"Vector ctor move\n";
		sz = a.sz;
		elem = a.elem;
		a.sz = 0;
		a.elem = nullptr;
	}

	Vector& operator=(Vector&& a) {
		cout<<"Vector move assignment operator\n";
		if (this!=&a) {
			sz = a.sz;
			elem = a.elem;
			a.sz = 0;
			a.elem = nullptr;
		}
		return *this;
	}

	T& operator[](int i) override {
		if (i<0||(unsigned int)i>=sz)
			throw out_of_range("Index out of range");
		return elem[i];
	}

	const T& operator[](int i) const override {
		if (i<0||(unsigned int)i>=sz)
			throw out_of_range("Index out of range");
		return elem[i];
	}

	size_t size() const override {
		return sz;
	}

	// Make the class enumerable
	T* begin() const override {
		return sz==0 ? nullptr : elem;
	}

	T* end() const override {
		return sz==0 ? nullptr : (elem+sz);
	}
};


// Specialization of Vector<T> constructor for int, with zero-initialization not provided by int type.
// On the other hand, putting memset in Vector<T> constructor erases to zero the content
// of elem initialized by T constructor (if it exists), since constructor is called by
// a new T[nn] in C++ contrary to C#
template<>
Vector<int>::Vector(size_t s) {
	cout<<"Vector ctor(int) for T=int\n";
	sz = s;
	elem = new int[s];
	memset(elem, 0, s*sizeof(int));		// Zero-initialized for integers
}


// Simple templated addition of Vector<T>
template <typename T>
Vector<T> operator+(const Vector<T>& a, const Vector<T>& b) {
	cout<<"Vector operator +\n";

	if (a.size()!=b.size())
		throw exception();	// "Vector size mismatch for operator +");
	Vector<T> res(a.size());
	for (size_t i = 0; i<a.size(); i++)
		res[i] = a[i]+b[i];
	return res;
}


// Printing support for Vector<T> through its base class
template <typename T>
ostream& operator <<(ostream& out, const Collection<T>& c) {
	bool first = true;
	for (const auto& i:c)
	{
		out<<(first ? "{" : ", ")<<i;
		first = false;
	}
	out<<"}";
	return out;
}


template<typename T>
T Somme(const Collection<T> &c) {
	T sum = T();		// Trick to zero-initialize all types, ~= C# default(T)
	for (auto& i:c)
		sum += i;
	return sum;
}

template<typename T>
//typedef Vector<T> vec;	// Templated typedef is illegal, rejected by compiler
using vec = Vector<T>;


void TestSum() {
	Vector<int> v1 { 1, 2, 3, 4, 5 };
	Vector<int> v2 { 10, 20, 30, 40, 50 };
	vec<int> v3 { 100, 200, 300, 400, 500 };

	Vector<int>sum(2);
	sum = v1+v2+v3;
	//cout << (Collection<int> &)(sum) << endl;
	cout<<sum<<"  -->  "<<Somme(sum)<<endl;
}


Vector<int> getVector() {
	Vector<int> z { 1, 2, 3, 4, 5 };
	return z;
}

void Test1() {
	Vector<int> v = getVector();
	v = v+getVector();
}

void Test2() {
	Vector<int> v { 7 };
	cout<<v<<endl;
}



template<typename T, int N>
struct Buffer {
	//using value_type = T;
	constexpr int size() { return N; }
	T buffer[N];

	Buffer() = default;

	Buffer(initializer_list<T> li) {
		cout<<"Buffer(initializer_list<T>) begin\n";
		assert(li.size()==N);
		//copy(li.begin(), li.end(), buffer);
		T* dest = buffer;
		for (auto s = li.begin(); s!=li.end(); ++s)
			*dest++ = move(*const_cast<T*>(s));
		cout<<"Buffer(initializer_list<T>) end\n";
	}
};


void TestBuffer() {
	//Buffer<char, 100> bc;
	//Buffer<Vector<int>, 5> b5;

	for (size_t i = 0; i<3; i++)
	{
		cout<<"i="<<i<<endl;
		Buffer<Vector<int>, 2> b2 { Vector<int>(10), Vector<int>(12) };
		cout<<b2.buffer[0].size()<<" << "<<b2.buffer[1].size()<<endl;
	}
}

void TestSomme() {
	Vector<complex<double>> vc { 2.0+3i, 5.0-2i, -3.2 };
	Vector<double> vd { 1.414, 3.1416, 2.718, 1.732 };
	Vector<unsigned char> vuc { '0', '1' };
	Vector<string> vs { "Once ", "upon ", "a ", "time" };

	auto test = [](const auto& c) {cout<<c<<"  ->  "<<Somme(c)<<endl; };
	test(vc);
	test(vd);
	test(vuc);
	test(vs);
}


template <typename C>
bool contains_duplicate(const C& c) {
	typedef typename C::value_type T;
	//using T = typename C::value_type;			// Both are accepted and identical

	for (size_t i = 0; i<c.size(); i++)
	{
		const T& item_i = c[i];
		for (size_t j = i+1; j<c.size(); j++)
			if (item_i==c[j])
				return true;
	}
	return false;
}


void TestDuplicate() {
	Vector<complex<double>> vc { 2.0+3i, 5.0-2i, -3.2 };
	Vector<double> vd { 1.414, 3.1416, 2.718, 3.1416, 1.732 };
	Vector<unsigned char> vuc { '0', '1' };
	Vector<string> vs { "Once ", "upon ", "a ", "time", "upon " };

	auto test = [](const auto& c) {cout<<c<<"  ->  "<<contains_duplicate(c)<<endl; };
	test(vc);
	test(vd);
	test(vuc);
	test(vs);
}


extern int x;   // no definition of x required
int f() {
#if false
	// g++ and VS don't accept this syntax
	if constexpr (true)
		return 0;
	else 
	if (x)
		return x;
	else
		return -x;
#else
	return 0;
#endif
}



int main() {
	TestDuplicate();


#ifdef _WIN32
	cout << "\n(Pause)";
	cin.get();
#endif
}
