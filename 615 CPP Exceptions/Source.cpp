// CPP615 Exceptions
// Test of try/catch in C++
//
// 2017-02-04	PV
// 2017-04-29	PV	GitHub and Linux

#include <iostream>
#include <limits>

using namespace std;


void MyFunc(int c)
{
	if (c > numeric_limits<char>::max())
		throw invalid_argument("MyFunc argument too large.");
}


int main() {
	try
	{
		MyFunc(200); //cause an exception to throw
	}
	catch (invalid_argument& e)
	{
		cerr << "*** Error: " << e.what() << endl;
	}


#ifdef _WIN32
	cout << "\n(Pause)";
	cin.get();
#endif
	return 0;
}
