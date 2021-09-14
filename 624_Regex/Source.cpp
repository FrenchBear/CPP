// 624 CPP Regex
// Example of C++ regular expressions
// From A Tour of C++ (2014) - [Addison-Wesley] - Bjarne Stroustrup, chapter 7 
//
// 2017-03-28	PV
// 2017-04-29	PV		GitHub and Linux
// 2021-09-14	PV		Visual Studio 2022

#include <iostream>
#include <iomanip>
#include <regex>
#include <list>

using namespace std;


void TestSearch() {
	list<string> titles {
		"Pour la Science n°508",
		"La Recherche n°304-305",
		"American Scientific issue #1208"
	};

	regex pat(R"(^(.*) n°(\d+)(b|B)?(-\d+)?$)");

	for (string s : titles) {
		smatch matches;		// vector of submatches of type string, with [0] the complete match
		cout << left << setw(40) << s;
		if (regex_search(s, matches, pat)) {
			for (string sub : matches)
				cout << "<" << sub << "> ";
			cout << endl;
		}
		else
			cout << "No match.\n";
	};
	cout << endl;
}


bool is_identifier(const string& s)
{
	regex pat { R"([_[:alpha:]]\w*)" };		// \w is equivalent to [_[:alnum:]]
	return regex_match(s, pat);
}

void TestMatch() {
	list<string> identifiers { "Home", "2b3", "__3__", "@home" };
	for (string s : identifiers)
		cout << left << setw(10) << s << (is_identifier(s) ? "Ok" : "Not a valid identifier") << endl;
	cout << endl;
}


void TestIterator() {
	string input = "aa as; asd ++eˆasdf asdfg";
	regex pat { R"(\s+(\w+))" };
	for (sregex_iterator p(input.begin(), input.end(), pat); p != sregex_iterator {}; ++p)
		cout << (*p)[1] << '\n';
	cout << endl;
}


int main() {
	TestSearch();
	TestMatch();
	TestIterator();


#ifdef _WIN32
	cout << "\n(Pause)";
	cin.get();
#endif
}
