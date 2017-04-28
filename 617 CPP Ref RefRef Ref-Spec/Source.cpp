// CPP617 Ref RefRef Ref-Spec
// Play with C++ references
// 2017-02-13	PV

#include <iostream>

using namespace std;


class MemoryBlock {
public:
	//int mb() { return i; };
	//int mb() const { return i; };
	void mb() & { cout << "mb() &" << endl; };
	void mb() const& { cout << "mb() const&" << endl; };
	void mb() && { cout << "mb() &&" << endl; };
	void mb() const&& { cout << "mb() const&&" << endl; };
};


void g(MemoryBlock&) {
	cout << "In g(MemoryBlock&)" << endl;
}

void g(const MemoryBlock&) {
	cout << "In g(const MemoryBlock&)" << endl;
}


void g(MemoryBlock&& r) {
	cout << "In g(MemoryBlock&&)" << endl;
}

void g(const MemoryBlock&&) {
	cout << "In g(const MemoryBlock&&)" << endl;
}



MemoryBlock&& f(MemoryBlock&& block) {
	g(block);
	return static_cast<MemoryBlock&&>(block);
}


const MemoryBlock GetMemoryBlock() {
	return MemoryBlock();
}


int main() {
	g(f(MemoryBlock()));
	
	cout << endl;
	
	auto b = MemoryBlock();
	g(b);
	g(move(b));
	g((MemoryBlock&&)b);
	
	cout << endl;
	
	g((const MemoryBlock&)b);
	g((const MemoryBlock&&)b);

	cout << endl;

	// A rvalue can be used to initialize a lvalue ref...
	const int& five = 5;

	b.mb();
	(MemoryBlock()).mb();
	const auto c = MemoryBlock();
	c.mb();
	(GetMemoryBlock()).mb();


	cout << "\n(Pause)";
	cin.get();
}
