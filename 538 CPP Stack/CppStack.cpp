// CppStack.cpp : Defines the entry point for the console application.
//

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

	cout << "\n(Pause) ";
	getchar();
	return 0;
}
