// 552 CPP for_each
// Examples of for_each iterator in C++
//
// 2016-10-04	PV
// 2017-04-29	PV		GitHub and Linux

#define _SCL_SECURE_NO_WARNINGS		// Otherwise use of copy generated a deprecated error

#include <stdio.h>
#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;


// The function object multiplies an element by a Factor
template <class Type>
class MultValue
{
private:
	Type Factor;   // The value to multiply by
public:
	// Constructor initializes the value to multiply by
	MultValue(const Type& _Val) : Factor(_Val) {
	}

	// The function call for the element to be multiplied
	void operator ( ) (Type& elem) const
	{
		elem *= Factor;
	}
};

// The function object to determine the average
class Average
{
private:
	long num;      // The number of elements
	long sum;      // The sum of the elements

public:
	// Constructor initializes the value to multiply by
	Average() : num(0), sum(0)
	{
	}

	// The function call to process the next element
	void operator ( ) (int elem)
	{
		num++;      // Increment the element count
		sum += elem;   // Add the value to the partial sum
	}

	// return Average
	operator double()
	{
		return static_cast<double>(sum) / static_cast<double>(num);
	}

	operator int()
	{
		return (int)(static_cast<double>(sum) / static_cast<double>(num));
	}
};



int main() {
	vector <int> v1;
	vector <int>::iterator Iter1;

	// Constructing vector v1
	int i;
	for (i = -4; i <= 2; i++)
	{
		v1.push_back(i);
	}

	cout << "Original vector  v1 = ( ";
	for (Iter1 = v1.begin(); Iter1 != v1.end(); Iter1++)
		cout << *Iter1 << " ";
	cout << ")." << endl;

	// Using for_each to multiply each element by a Factor
	for_each(v1.begin(), v1.end(), MultValue<int>(-2));

	cout << "Multiplying the elements of the vector v1\n "
		<< "by the factor -2 gives:\n v1mod1 = ( ";
	for (Iter1 = v1.begin(); Iter1 != v1.end(); Iter1++)
		cout << *Iter1 << " ";
	cout << ")." << endl;

	// The function object is templatized and so can be
	// used again on the elements with a different Factor
	for_each(v1.begin(), v1.end(), MultValue<int>(5));

	cout << "Multiplying the elements of the vector v1mod\n "
		<< "by the factor 5 gives:\n v1mod2 = ( ";
	for (Iter1 = v1.begin(); Iter1 != v1.end(); Iter1++)
		cout << *Iter1 << " ";
	cout << ")." << endl;

	// The local state of a function object can accumulate
	// information about a sequence of actions that the
	// return value can make available, here the Average
	double avemod2 = for_each(v1.begin(), v1.end(), Average());
	cout << "The double average of the elements of v1 is:\n Average ( v1mod2 ) = "
		<< avemod2 << "." << endl;
	int avemod2i = for_each(v1.begin(), v1.end(), Average());
	cout << "The int average of the elements of v1 is:\n Average ( v1mod2 ) = "
		<< avemod2i << "." << endl;

#ifdef _WIN32
	cout << "(Pause)";
	getchar();
#endif
	return 0;
}
