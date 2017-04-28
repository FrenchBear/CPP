// 626 CPP unordered_map cplx_hasher
// Example of use of unordered_map with complex class not supporting operator <
//
// 2017-04-08	PV

#include <iostream>
#include <unordered_map>
#include <complex>

using namespace std;


using cplx = complex<double>;

struct cplx_hasher {
	size_t operator()(const cplx& z) const {
		return hash<double>()(z.real()) ^ hash<double>()(z.imag());
	}
};

int main() {
	unordered_map<string, int> dic {
		{ "Pierre", 1965 },
		{ "Claude", 1956 }
	};

	cout << dic.at("Pierre") << endl;

	string k = "Claude";
	auto it = dic.find(k);
	if (it == dic.end())
		cout << k << " not in dic.keys\n";
	else
		cout << "dic[\"" << it->first << "\"] = " << it->second << endl;

	unordered_map<cplx, string, cplx_hasher> cm {
		{0.0, "Zero"},
		{1.0i, "Imaginary unit"},
		{1.0, "Real unit"}
	};

	cout << cm[1.0i] << endl;

	cout << "\n(Pause)";
	cin.get();
}
