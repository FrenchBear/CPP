// 628 CPP stream iterators
// Examples of stream iterators
// Stroustrup Tour of C++, §10.4
//
// 2017-04-09	PV
// 2017-04-29	PV	GitHub and Linux

#include <iostream>
#include <iterator>
#include <fstream>		// for ifstream
#include <sstream>		// for istringstream
#include <string>
#include <vector>
#include <algorithm>

using namespace std;


void TestOutputStreamIterator() {
	ostream_iterator<string> oo { cout };

	// Simple direct output using stdout iterator
	*oo = "Hello, ";
	++oo;		// mimic write in an array through a pointer, through useless here
	*oo = "world!\n";

	// Another example, with copy that ouse an output iterator
	vector<string> vs { "Once ", "upon ", "a ", "time ", "in ", "a ", "far ", "away ", "kingdom...\n" };
	copy(vs.begin(), vs.end(), oo);
}

void TestInputStreamOperator() {
	string s = "The quick brown fox jumps over the lazy dog";
	istringstream is(s);

	istream_iterator<string> isit { is };
	istream_iterator<string> eos {};

	for (auto it = isit; it !=eos; ++it)
		cout << *it << ' ';
	cout << endl;
}


// Simple input stream iterator on lines
class line : public string {};

std::istream &operator>>(std::istream &is, line &l)
{
	std::getline(is, l);
	l.erase(0, l.find_first_not_of(" \t\n\r\f\v"));		// left trim (http://stackoverflow.com/questions/1798112/removing-leading-and-trailing-spaces-from-a-string)
	return is;
}


// Gets lines from filename, left-trims them, sorts, remove duplicates, and copy to stdout
void SortAndRemoveDuplicates(string filename) {
	ifstream ifs { filename };

	istream_iterator<line> isit { ifs };
	istream_iterator<line> eos {};			// sentinel

	ostream_iterator<string> oo { cout, "\n" };	// "\n" is a separator

	vector<string> b { isit, eos };
	sort(b.begin(), b.end());
	unique_copy(b.begin(), b.end(), oo);
}


int main() {
	TestOutputStreamIterator();
	TestInputStreamOperator();
	SortAndRemoveDuplicates(R"(Source.cpp)");


#ifdef _WIN32
	cout << "\n(Pause)";
	cin.get();
#endif
}
