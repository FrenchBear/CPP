// 620 CPP interfaces using abstract
// Implement C#-like interfaces using abstract keyword
// abstact is microsoft-specific, and enables overloaded implementation using baseclass:: prefix as discriminator
// if thwo bases classes contains an identically named member, here Count() method.  Note that using =0 pure virtual
// specified in base class does NOT allow this trick (see http://www.gotw.ca/gotw/039.htm for a possible solution)
//
// 2017-03-14	PV

#define _SCL_SECURE_NO_WARNINGS
#include <iostream>
#include <string>
#include <typeinfo>
#include <time.h>
#include <algorithm>
#include <memory>
#include <vector>

using namespace std;


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
	virtual int Count() abstract;
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

	int IList<T>::Count() {
		return v.size();
	}

	int ICollection<T>::Count() {
		return v.size();
	}

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

	cout << "\n(Pause)";
	cin.get();
}

