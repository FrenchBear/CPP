// 627 CPP use of iterators
//
// 2017-04-08	PV

// Avoid iterator checking for the end exception in debug mode
#define 	_ITERATOR_DEBUG_LEVEL 0

#include <iostream>
#include <list>
#include <vector>
#include <complex>
#include <algorithm>

using namespace std;


using cplx = complex<double>;

template <typename T>
void print_iterable(ostream& os, const T& i) {
	bool bfirst = true;
	for (const auto& item : i) {
		if (bfirst)
			bfirst = false;
		else
			os << ", ";
		os << item;
	}
}

template <typename T>
ostream& operator<<(ostream& os, const vector<T>& vt) {
	os << '{';
	print_iterable(os, vt);
	os << '}';
	return os;
}

template <typename T>
ostream& operator<<(ostream& os, const list<T>& lt) {
	os << '[';
	print_iterable(os, lt);
	os << ']';
	return os;
}


// Example of vector filtering using a predicate
template <typename T>
vector<T> find_all_in_vector(vector<T>v, bool(*predicate)(const T& item)) {
	vector<T> vout;
	for (const auto& item : v)
		if (predicate(item))
			vout.push_back(item);
	return vout;
}


// More general, container filtering
template <typename C, typename T>
C find_all_in_container(C c, bool(*predicate)(const T& item)) {
	C cout;
	for (const auto& item : c)
		if (predicate(item))
			cout.push_back(item);
	return cout;
}


template <typename T>
using Iterator = typename T::iterator;


int main() {
	// Let's start with a vector of complex values...
	vector<cplx> vc { 2.0, 0.0, 1.0i, 0.3 + 0.5i, -0.4 + 0.1i, 0.0 };
	cout << vc << endl;

	// Sort by module, provides a lambda comparer instead of defining bool operator<(const cplx& c1, const cplx& c2)
	sort(vc.begin(), vc.end(), [](const cplx& c1, const cplx& c2) { return abs(c1) < abs(c2); });
	cout << vc << endl;

	// unique_copy fill existing slots in the list, does not add new elements as needed
	// so we need to dimension the list in advance
	list<cplx> lc(10);
	unique_copy(vc.begin(), vc.end(), lc.begin());
	cout << lc << endl;

	// using a back_inserter iterator solves the problem and grows the list as needed
	list<cplx> l2;
	unique_copy(vc.begin(), vc.end(), back_inserter(l2));
	cout << l2 << endl;

	// example of a filtering method, all complexes with a modulus <= 0.5
	// note that find_all_in_vector(vc, predicate) is not enough to infer template type arg
	auto predicate = [](const cplx& c) -> bool {return abs(c) <= 0.5; };
	cout << find_all_in_vector<cplx>(vc, predicate) << endl;

	// filtering a list with container filter function
	auto l3 = find_all_in_container<list<cplx>, cplx>(lc, predicate);
	cout << l3 << endl;

	// A string::iterator returns an object, with operator * returning a char,
	// operator ++ to move to next element, and operators == and != to compare to sentinel
	using X = Iterator<string>;
	string s { "Hello" };
	X sit = s.begin();
	X send = s.end();		// sentinel
	cout << addressof(sit) << ' ' << *sit << ' ' << addressof(send) << endl;
	for (; sit != send; ++sit)
	{
		if (*sit <= 32)
			cout << "\\x" << hex << (int)(unsigned char)(*sit) << ' ';
		else
			cout << *sit << ' ';
	}
	cout << endl;


	cout << "\n(Pause)";
	cin.get();
}
