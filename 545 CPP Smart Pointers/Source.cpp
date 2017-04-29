// 545 CPP Smart Pointers
// Example of smart pointers in C++
//
// 2016-08-13	PV
// 2016-10-12	PV	Expanded code
// 2017-04-29	PV	GitHub/Linux sharing

#include <stdio.h>
#include <iostream>
#include <memory>

using namespace std;


class A {
public:
	A() {
		cout << "A default constructor\n";
	}

	~A() {
		cout << "A destructor\n";
	}

	void method1() {
		cout << "Hello\n";
	}
};

shared_ptr<A> aFactory() {
	return shared_ptr<A>(new A);
}

class B {
private:
	shared_ptr<A> a;

public:
	B() {
		cout << "B default constructor\n";
	}

	~B() {
		cout << "B destructor\n";
	}

	void doStuff() {
		a = aFactory();
		a->method1();
	}

	shared_ptr<A> getA() {
		return a;
	}

};

int main() {
	B *pb = new B;
	pb->doStuff();
	shared_ptr<A> a = pb->getA();
	a->method1();
	delete pb;
	pb = nullptr;

	a->method1();
	a = nullptr;		// Only a this point A destructor is called

#ifdef _WIN32
	cout << "\n(Pause) ";
	getchar();
#endif
	return 0;
}
