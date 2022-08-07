// 554 CPP containers
// Play with C++ STL containers
//
// 2016-10-12	PV
// 2017-02-03	PV		Extra containers (map, ...)
// 2017-04-29	PV		GitHub and Linux
// 2021-09-14	PV		Visual Studio 2022

#ifdef _WIN32
#include <Windows.h>
#endif

#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include <array>
#include <deque>
#include <list>
#include <forward_list>
#include <map>
#include <unordered_map>
#include <set>
#include <unordered_set>
#include <stack>
#include <queue>
#include <tuple>


using namespace std;


// Templated support for vector printing
template <typename T>
string VectorToString(const vector<T>& v) {
	stringstream ss;
	bool first = true;
	for (const T& var : v)
	{
		if (first)
		{
			ss << "{";
			first = false;
		}
		else
			ss << ", ";
		ss << var;
	}
	ss << "}";
	return ss.str();
}

template <typename T>
ostream& operator <<(ostream& out, const vector<T>& v) {
	out << VectorToString(v);
	return out;
}



// Templated generic container name and content printing
template <typename T>
void PrintNameAndStructure(const char* name, T& st) {
	// cout << endl << typeid(T).name() << endl;		
	// Works, but for string, result is waaaaaaay too long.  For instance, list<string> returns
	// class std::list<class std::basic_string<char,struct std::char_traits<char>,class std::allocator<char> >,class std::allocator<class std::basic_string<char,struct std::char_traits<char>,class std::allocator<char> > > >

	cout << name << ": ";
	for (const auto& item : st)
		cout << item << ' ';
	cout << endl;
};

#define PrintStructure(st) PrintNameAndStructure(#st, st);



// Templated find if element exist
template <typename C, class T> void FindIt(const C& c, T val) {
	if (c.find(val) != c.end())
		cout << "Element " << val << " found" << endl;
	else
		cout << "Element " << val << " not found" << endl;
}


int main() {
#ifdef _WIN32
	SetConsoleOutputCP(1250);			// Show ANSI accents correctly in 8-bit char mode
#endif

	vector<int> v1{ 2, 3, 5, 7, 11, 13 };
	cout << "vector<int>\r\n";
	cout << v1 << endl;

	cout << "\r\nvector<string>\r\n";
	vector<string> v2;
	v2.push_back("Il");
	v2.push_back("etait");
	v2.push_back("un");
	v2.push_back("petit");
	v2.push_back("navire");
	cout << v2 << endl;

	cout << "v2.size(): " << v2.size() << endl;
	cout << "v2.max_size(): " << v2.max_size() << endl;

	cout << "v2.empty(): " << v2.empty() << endl;
	v2.clear();
	cout << "v2.empty(): " << v2.empty() << endl;

	v2.resize(3);
	v2[0] = "Yes";
	v2[1] = "of";
	v2[2] = "course";
	cout << v2 << endl;

	// =====================================================================
	// http://stackoverflow.com/questions/4364536/c-null-reference
	// C++ 8.3.2/1:
	// A reference shall be initialized to refer to a valid object or function. [Note: In particular,
	// a null reference cannot exist in a well-defined program, because the only way to create such a reference
	// would be to bind it to the “object” obtained by dereferencing a null pointer, which causes undefined behavior.
	// As described in 9.6, a reference cannot be bound directly to a bit-field.]
	// C++ 1.9 / 4:
	// Certain other operations are described in this International Standard as undefined (for example,
	// the effect of dereferencing the null pointer)

	cout << "\r\nNULL reference\r\n";
	int &ir = *(int*)0;
	if (&ir == nullptr)
		cout << "NULL\n";
	else
		cout << ir << endl;
	// =====================================================================

	// Vectors allow constant time insertions and deletions at the end of the sequence.
	// Inserting or deleting elements in the middle of a vector requires linear time.
	// The performance of the deque Class container is superior with respect to insertions
	// and deletions at the beginning and end of a sequence.
	// The list Class container is superior with respect to insertions and deletions
	// at any location within a sequence.

	// The STL vector class is a template class of sequence containers that arrange elements 
	// of a given type in a linear arrangement and allow fast random access to any element.
	// They should be the preferred container for a sequence when random-access performance 
	// is at a premium.

	vector<const char *> v3{ "Once", "a" };
	v3.insert(v3.begin() + 1, "Upon");
	v3.push_back("Time");
	v3[2] = "A";
	cout << "\r\nvector<const char *>\r\n";
	cout << v3 << endl;




	// array<Ty, N> is an object that controls a sequence of length N of elements of type Ty.
	array<double, 3> ad{ 3.1416, 1.4142, 2.7182 };
	cout << "\r\narray<double, 3>\r\n";
	PrintStructure(ad);
	cout << "ad[1]: " << ad[1] << endl;


	// The STL list class is a template class of sequence containers that maintain their elements
	// in a linear arrangement and allow efficient insertions and deletions at any location within
	// the sequence. The sequence is stored as a bidirectional linked list of elements, 
	// each containing a member of some type Type.
	list<string> l1;
	l1.push_back("Lord");
	l1.push_front("Yes");
	list <string>::iterator Iter1 = l1.begin();
	Iter1++;
	l1.insert(Iter1, "My");
	//l1[1] = "my";		Indexed access not supported
	cout << "\r\nlist<string>\r\n";
	PrintStructure(l1);
	// Linear search
	auto FindInListOfString = [](list<string> container, string searched) -> string {
		for (const auto& i : container)
			if (i == searched)
				return searched + " found";
		return searched + " not found";
	};
	cout << FindInListOfString(l1, "Yes") << endl;
	cout << FindInListOfString(l1, "Devil") << endl;



	forward_list<int> fli;
	for (int i = 1; i < 20; i++)
		fli.emplace_front(i*i);				// Insert at the beginning
	cout << "\r\nforward_list<int>\r\n";
	PrintStructure(fli);					// Prints in "reverse" order of insertion


	// Arranges elements of a given type in a linear arrangement and, like a vector, enables fast 
	// random access to any element, and efficient insertion and deletion at the back of the 
	// container. However, unlike a vector, the deque class also supports efficient insertion 
	// and deletion at the front of the container.
	deque<int> d1{ 1,3,5,7 };
	d1.pop_front();
	d1.push_front(2);
	d1.push_back(11);
	d1[2] = -3;				// Indexed access supported
	cout << "\r\ndeque<int>\r\n";
	PrintStructure(d1)


	// map imposes unicity of key.  Implemented as a btree, so keys need to be ordered
	// For instance, a map<complex<double>, T> causes a build error:
	// Error C2678 binary '<': no operator found which takes a left-hand operand of type 'const cplx' (or there is no acceptable conversion)
	map<string, string> colorMap{ {"bleu", "blue"}, {"blanc", "white"}, {"rouge", "red"} };
	colorMap.insert(pair<string, string>("vert", "green"));
	colorMap.insert(pair<string, string>("blanc", "white North"));		// Actually no effect since key already exists
	cout << "\r\nmap<string, string>\r\n";
	cout << "colorMap: ";
	for (auto i : colorMap)
		cout << "(" << i.first << ", " << i.second << "), ";
	cout << endl;
	cout << "colorMap[\"rouge\"]: " << colorMap["rouge"] << endl;
	auto findInMap = [](auto m, auto key) { 
		auto res = m.find(key);
		if (res == m.end())
			cout << "map does not contain key " << key << endl;
		else {
			cout << "map[" << key << "] = " << (*res).second << endl;
		}
		//<< m[res].second << endl;
	};
	findInMap(colorMap, "noir");
	findInMap(colorMap, "bleu");


	// unordered_map means that the key does not need to support ordering with < operator
	// while map is implemented as a btree and need ordered keys, unordered_map is implemented as
	// a hashtable, and the key needs support for hashing, which is provided for standard types.
	unordered_map<long long, int> umap;
	long long f = 1;
	for (int i = 1 ; i < 20; f *= i, i++)
		umap.insert(pair<long long, int>(f, i));
	cout << "\r\nunordered_map<long long, int>\r\n";
	cout << "umap: ";
	for (auto i : umap)
		cout << "(" << i.first << ", " << i.second << "), ";
	cout << endl;
	cout << "umap[120ll]: " << umap[120ll] << endl;
	findInMap(umap, 620ll);
	findInMap(umap, 720ll);


	// multimap accepts duplicate keys.  No indexing
	multimap<int, string> numToStringMultimap{ {1,"one"}, {2,"deux"}, {2, "two"} };
	typedef pair<int, string> intstring;
	numToStringMultimap.insert(intstring(1, "un"));
	numToStringMultimap.insert(intstring(3, "three"));
	numToStringMultimap.insert(intstring(3, "trois"));
	cout << "\r\nmultimap<int, string>\r\n";
	cout << "numToStringMultimap = ";
	for (auto i : numToStringMultimap)
		cout << i.first << " " << i.second << ", ";
	cout << endl;


	// set automatically eliminate duplicates, ordered by the key.  No indexing
	set<char> letters{ 'c','l','a','s','s','e' };
	cout << "\r\nset<char>\r\n";
	PrintStructure(letters);
	auto TestContainsLetter = [&letters](char c) { cout << (letters.find(c) == letters.end() ? "letters does not contain " : "letters contains ") << "'" << c << "'" << endl; };
	TestContainsLetter('k');
	TestContainsLetter('l');

	// STL multiset class is used for the storage and retrieval of data from a collection in which the values
	// of the elements contained need not be unique and in which they serve as the key values according to which
	// the data is automatically ordered. The key value of an element in a multiset may not be changed directly.
	// Instead, old values must be deleted and elements with new values inserted.
	multiset<int> msint{ 1,2,3,4,4,3,2,1 };
	msint.insert(0);
	cout << "\r\nmultiset<int>\r\n";
	PrintStructure(msint);

	// unordered_set class describes an object that controls a varying-length sequence of elements of type 
	//  const Key.The sequence is weakly ordered by a hash function, which partitions the sequence into an
	//	ordered set of subsequences called buckets.Within each bucket a comparison function determines
	//	whether any pair of elements has equivalent ordering.Each element serves as both a sort key and a
	//	value.The sequence is represented in a way that permits lookup, insertion, and removal of an
	//	arbitrary element with a number of operations that can be independent of the number of elements in the
	//	sequence(constant time), at least when all buckets are of roughly equal length.In the worst case,
	//	when all of the elements are in one bucket, the number of operations is proportional to the number of
	//	elements in the sequence(linear time).Moreover, inserting an element invalidates no iterators, and
	//	removing an element invalidates only those iterators which point at the removed element.
	unordered_set<int> usint;
	for (int i = 0, j = 1, t = 0; i < 1000; t = i + j, i = j, j = t)
		usint.insert(i);
	cout << "\r\nunordered_set<int>\r\n";
	PrintStructure(usint);
	cout << "Number of buckets: " << usint.bucket_count() << endl;
	FindIt(usint, 13);
	FindIt(usint, 25);


	stack<bool> sb;
	sb.push(true);
	sb.push(true);
	sb.push(false);
	sb.push(true);
	cout << "\r\nstack<bool>\r\n";
	cout << "sb.size(): " << sb.size() << endl;
	cout << "sb from top to bottom: ";
	while (sb.size() > 0)
	{
		cout << sb.top() << ' ';
		sb.pop();
	}
	cout << endl;


	// A template container adaptor class that provides a restriction of functionality for some underlying container type,
	// limiting access to the front and back elements. Elements can be added at the back or removed from the front,
	// and elements can be inspected at either end of the queue.
	queue<string> qs;
	qs.push("once");
	qs.push("upon");
	qs.push("a");
	qs.push("time");
	cout << "\r\nqueue<string>\r\n";
	cout << "qs: ";
	while (qs.size() > 0)
	{
		cout << qs.front() << ' ';
		qs.pop();
	}
	cout << endl;



	// The priority_queue class orders its elements so that the largest element is always at the top position.
	// It supports insertion of an element and the inspection and removal of the top element
	priority_queue<int> q3;
	q3.push(2);
	q3.push(1);
	q3.push(3);
	cout << "\r\npriority_queue<int>\r\n";
	cout << "q3: ";
	while (!q3.empty())
	{
		cout << q3.top() << " ";
		q3.pop();
	}
	cout << endl;



	typedef tuple<unsigned char, unsigned short, unsigned int, unsigned long, unsigned long long> inttuple;
	inttuple t(5, 4, 3, 2ul, 1ull);
	cout << "\r\ntuple<...>\r\n";
	cout << "t: (" << static_cast<int>(get<0>(t)) << ", " << get<1>(t) << ", " << get<2>(t) << ", " << get<3>(t) << ", " << get<4>(t) << ")" << endl;



#ifdef _WIN32
	cout << "\r\n(Pause)";
	cin.get();
#endif

	return 0;
}
