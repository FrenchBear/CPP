// CPP615 Exceptions
// Test of try/catch in C++
// 2017-02-04	PV

#include <iostream>

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


	cout << "\n(Pause)";
	cin.get();
	return 0;
}