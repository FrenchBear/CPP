// 538 CppStack.cpp
// First play in C++ after years using stack from STL
//
// 2017-04-28	PV	Simplified version for GitHub/Linux sharing

#include <stdio.h>
#include <iostream>
#include <stack>

using namespace std;


int main()
{
	stack<int> myStack;

	myStack.push(2);
	myStack.push(3);
	myStack.push(5);
	myStack.push(7);

	cout << "Nb elements: " << myStack.size() << endl;
	while (myStack.size()>0)
	{
		cout << "Element: " << myStack.top() << endl;
		myStack.pop();
	}

#ifdef _WIN32
	cout << "\n(Pause) ";
	getchar();
#endif
	return 0;
}
