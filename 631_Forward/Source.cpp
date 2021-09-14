// 631 CPP Forward
// Play fith std::forward
//
// 2021-09-14	PV		Visual Studio 2022

#include <iostream>

using namespace std;

class Widget { };


void Zip(const Widget &lhw1, const Widget &lhw2) {
	cout << "Zip(const Widget &lhw1, const Widget &lhw2)\n";
}

void Zip(const Widget &lhw1, Widget &&rhw2) {
	cout << "Zip(const Widget &lhw1, Widget &&rhw2)\n";
}

void Zip(Widget &&rhw1, const Widget &lhw2) {
	cout << "Zip(Widget &&rhw1, const Widget &lhw2)\n";
}

void Zip(Widget &&rhw1, Widget &&rhw2) {
	cout << "Zip(Widget &&rhw1, Widget &&rhw2)\n";
}


template <typename T1, typename T2>
void Zap(T1 &&ur1, T2&& ur2) {
	Zip(forward<T1>(ur1), forward<T2>(ur2));
}


int main() {
	Widget w1, w2;

	Zip(w1, w2);
	Zip(move(w1), w2);
	Zip(w1, move(w2));
	Zip(move(w1), move(w2));

	cout << endl;

	Zap(w1, w2);
	Zap(move(w1), w2);				// Must use T1 and T2 in template, otherwise error if single type T
	Zap(w1, move(w2));				// Same here, it's indeed type parameter that holds info whether & or &&
	Zap(move(w1), move(w2));

	cout << "\n(Pause)";
	cin.get();
}
