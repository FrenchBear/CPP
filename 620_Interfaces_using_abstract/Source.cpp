// 620 CPP interfaces using abstract
// Implement C#-like interfaces using abstract keyword
// abstact is microsoft-specific, and enables overloaded implementation using baseclass:: prefix as discriminator
// if thwo bases classes contains an identically named member, here Count() method.  Note that using =0 pure virtual
// specified in base class does NOT allow this trick (see http://www.gotw.ca/gotw/039.htm for a possible solution)
//
// 2017-03-14	PV
// 2017-04-29	PV		GitHub and Linux; g++ does not support abstract, tampered with code (badly)
// 2021-09-14	PV		Visual Studio 2022

#define _SCL_SECURE_NO_WARNINGS
#include <iostream>
#include <string>
#include <typeinfo>
#include <time.h>
#include <algorithm>
#include <memory>
#include <vector>

using namespace std;

#ifndef _WIN32
#define abstract =0
#endif


template <typename T>
struct IList {
	virtual void Add(const T &item) abstract;
	virtual void Clear() abstract;
	virtual bool Contains(const T& item) abstract;
	virtual int Count() abstract;
};

template <typename T>
struct ICollection {
public:
#ifdef _WIN32
	virtual int Count() abstract;
#else
	virtual int Count2() abstract;
#endif
	virtual bool isReadOnly() abstract;
};

template <typename T>
class List :public IList<T>, public ICollection<T> {
private:
	vector<T> v;

public:
	List() {}

	void Add(const T &item) override {
		v.emplace_back(item);
	}

	void Clear() override {
		v.clear();
	}

	bool Contains(const T& item) override {
		return std::find(v.begin(), v.end(), item) != v.end();
	}

#ifdef _WIN32
	int IList<T>::Count() {
		return (int)(v.size());
	}

	int ICollection<T>::Count() {
		return (int)(v.size());
	}
#else
	int Count() override {
		return v.size();
	}

	int Count2() override {
		return v.size();
	}
#endif
	bool isReadOnly() override {
		return false;
	}
};

int main() {
	List<int> li;
	li.Add(7);
	li.Add(12);

	cout << "li.Contains(10): " << li.Contains(10) << endl;
	cout << "li.Contains(12): " << li.Contains(12) << endl;
	cout << "li.isReadOnly(): " << li.isReadOnly() << endl;
	cout << "li.Count(): " << ((IList<int> *)&li)->Count() << endl;

#ifdef _WIN32
	cout << "\n(Pause)";
	cin.get();
#endif
}

