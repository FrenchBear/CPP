// 614 CPP Range-based loops
// Example of enumerable classes
//
// 2017-02-04	PV
// 2017-02-07	PV		Range example
// 2017-02-10	PV		ZipRange and template Zip
// 2017-04-29	PV		GitHub and Linux
// 2021-09-14	PV		Visual Studio 2022

#include<iostream>
#include<limits>
#include<utility>


using namespace std;


// Implementation with a private embedded iterator class and two public member functions begin() and end()
class TripletInt {
private:
	const int first, second, third;

	class Iterator
	{
	public:
		Iterator(const TripletInt* p_vec, int pos) : _pos(pos), _p_vec(p_vec) { }

		// These three methods form the basis of an iterator for use with a range-based for loop
		bool operator!= (const Iterator& other) const {
			return _pos != other._pos;
		}

		int operator* () const {
			switch (_pos) {
			case 0: return _p_vec->first;
			case 1: return _p_vec->second;
			case 2: return _p_vec->third;
			}
			return 0;		// Just to avoid a warning, should not get through this
		}

		const Iterator& operator++ () {
			++_pos;
			// Although not strictly necessary for a range-based for loop, following the normal
			// convention of returning a value from operator++ is a good idea.
			return *this;
		}

	private:
		int _pos;
		const TripletInt *_p_vec;
	};

public:
	TripletInt(int i, int j, int k) : first(i), second(j), third(k) {}

	Iterator begin() const {
		return Iterator(this, 0);
	}

	Iterator end() const {
		return Iterator(this, 3);
	}
};


// Implementation with a public embedded iterator class and two public external (non-member) functions begin(TripletChar&) and end(TripletChar&)
// Iterator class has to be public
class TripletChar {
private:
	char first, second, third;

public:
	class Iterator
	{
	private:
		int _pos;
		const TripletChar *_p_vec;

	public:
		Iterator(const TripletChar* p_vec, int pos) : _pos(pos), _p_vec(p_vec) { }

		bool operator!= (const Iterator& other) const {
			return _pos != other._pos;
		}

		char operator* () const {
			switch (_pos) {
			case 0: return _p_vec->first;
			case 1: return _p_vec->second;
			case 2: return _p_vec->third;
			}
			return '\0';
		}

		const Iterator& operator++ () {
			++_pos;
			return *this;
		}
	};

	TripletChar(char i, char j, char k) : first(i), second(j), third(k) {}
};

TripletChar::Iterator begin(const TripletChar& tc) {
	return TripletChar::Iterator(&tc, 0);
}

TripletChar::Iterator end(const TripletChar& tc) {
	return TripletChar::Iterator(&tc, 3);
}



// Simple example of a range class similar to Python's, which is only useful as an enumerator
// Shouldn't really use numeric_limits<int>::max() but another status variable
// Maybe also a templated version to iterate using int, long, short, ...
class Range {
private:
	int start, stop;

	class Iterator
	{
	private:
		int cur;
		const Range *p;

	public:
		Iterator(const Range* p, int cur) : cur(cur), p(p) { }

		// These three methods form the basis of an iterator for use with a range-based for loop
		bool operator!= (const Iterator& other) const {
			return cur != other.cur;
		}

		int operator* () const {
			return cur;
		}

		const Iterator& operator++ () {
			if (cur < p->stop - 1)
				++cur;
			else
				cur = numeric_limits<int>::max();
			return *this;
		}
	};

public:
	Range(int stop) : start(0), stop(stop) {}
	Range(int start, int stop) : start(start), stop(stop) {}

	Iterator begin() const {
		return Iterator(this, start);
	}

	Iterator end() const {
		return Iterator(this, numeric_limits<int>::max());
	}
};



// First Zip attempt, only works on two Range enumerators to validate decltype syntax and other practical things
class ZipRange {
private:
	const Range e1;
	const Range e2;

	// Initially used (new Range) instead of ((Range *)0), but this forced the existence of a parameterless constructor for Range
	// that was artifially added.

	// This is how it's done in boost according to http://stackoverflow.com/questions/5147492/member-function-call-in-decltype
	//typedef decltype(((Range *)0)->begin()) RangeIterator;
	//typedef decltype(*((Range *)0)->begin()) RangeAtom;

	// Actually it can be rewritten in a better way using std::declval<T>()
	// From http://stackoverflow.com/questions/31783292/how-to-use-decltype-with-member-functions
	typedef decltype(declval<Range>().begin()) RangeIterator;
	typedef decltype(*declval<Range>().begin()) RangeAtom;


	class Iterator {
	private:
		const ZipRange *p;
		int cur;
		RangeIterator begin1, end1, begin2, end2;

	public:
		Iterator(const ZipRange* p, int cur) : p(p), cur(cur), begin1(p->e1.begin()), end1(p->e1.end()), begin2(p->e2.begin()), end2(p->e2.end()) {}

		// These three methods form the basis of an iterator for use with a range-based for loop
		bool operator!= (const Iterator& other) const {
			return cur != other.cur;
		}

		pair<RangeAtom, RangeAtom> operator* () const {
			return pair<RangeAtom, RangeAtom>(*begin1, *begin2);
		}

		const Iterator& operator++ () {
			if (begin1 != end1 && begin2 != end2)
			{
				++begin1;
				++begin2;
				if (!(begin1 != end1) || !(begin2 != end2))
					cur = -2;
			}
			else
				cur = -2;	// Reached the end
			return *this;
		}
	};

public:
	ZipRange(Range r1, Range r2) : e1(r1), e2(r2) {}

	Iterator begin() const {
		return Iterator(this, -1);
	}

	Iterator end() const {
		return Iterator(this, -2);
	}
};


// Templated version of Zip, takes two enumerable types T1 and T2, and provide enumeration support for pair<T1Atom, T2Atom>
// where T1Atom is the type enumerated by T1 and T2Atom the type enumerated by T2
// T1 and T2 must implement member functions begin() end and(), if implemented externally such as in TripleChar it won't work
template <typename T1, typename T2>
class Zip {
private:
	const T1 e1;
	const T2 e2;

	typedef decltype(declval<T1>().begin()) T1Iterator;
	typedef decltype(*declval<T1>().begin()) T1Atom;
	typedef decltype(declval<T2>().begin()) T2Iterator;
	typedef decltype(*declval<T2>().begin()) T2Atom;

	class Iterator {
	private:
		const Zip *p;
		bool finished;
		T1Iterator begin1, end1;
		T2Iterator begin2, end2;

	public:
		Iterator(const Zip* p, bool finished) : p(p), finished(finished), begin1(p->e1.begin()), end1(p->e1.end()), begin2(p->e2.begin()), end2(p->e2.end()) {}

		// These three methods form the basis of an iterator for use with a range-based for loop
		bool operator!= (const Iterator& other) const {
			return finished != other.finished;
		}

		pair<T1Atom, T2Atom> operator* () const {
			return pair<T1Atom, T2Atom>(*begin1, *begin2);
		}

		const Iterator& operator++ () {
			if (!finished) {
				++begin1;
				++begin2;
				// Since operator== is not defined, but operator!= is...
				if (!(begin1 != end1) || !(begin2 != end2))
					finished = true;
			}
			return *this;
		}
	};

public:
	Zip(T1 r1, T2 r2) : e1(r1), e2(r2) {}

	Iterator begin() const {
		return Iterator(this, false);
	}

	Iterator end() const {
		return Iterator(this, true);
	}
};




int main() {
	TripletInt ti(3, 12, 25);
	cout << "ti: ";
	for (auto i : ti)
		cout << i << ' ';
	cout << endl;


	TripletChar tc('a', 'z', 'e');
	cout << "tc: ";
	for (auto c : tc)
		cout << c << ' ';
	cout << endl;

	for (auto i : Range(10, 20))
		cout << i << ' ';
	cout << endl;

	auto && __range = Range(5);
	for (auto __begin = __range.begin(), __end = __range.end();
		__begin != __end; ++__begin) {
		auto range_declaration = *__begin;

		cout << range_declaration << ' ';
	}
	cout << endl;


	// Test of 1st Zip implementation limited to Range
	Range r1(10);
	Range r2(75, 95);
	ZipRange zr(r1, r2);
	for (auto p : zr)
		cout << "(" << p.first << ", " << p.second << ") ";
	cout << endl;

	// Final zip version
	Zip<Range, TripletInt> z(r1, ti);
	for (auto p : z)
		cout << "(" << p.first << ", " << p.second << ") ";
	cout << endl;


#ifdef _WIN32
	cout << "\n(Pause)";
	cin.get();
#endif
	return 0;
}
