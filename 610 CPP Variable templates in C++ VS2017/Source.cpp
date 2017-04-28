// Variable templates in C++ VS2017
// 2017-01-17	PV
//
// Example from http://www.open-std.org/jtc1/sc22/wg21/docs/papers/2013/n3651.pdf


//#include <iostream>
//using namespace std;


template <typename T>
T t16[16];

template<typename T>
const constexpr T pi = T(3.1415926535897932385);
template<typename T>
T area_of_circle_with_radius(T r) {
	return pi<T> * r * r;
}

int main() {
	double sd = area_of_circle_with_radius(2.0);
	float sf = area_of_circle_with_radius(2.0f);
	int si = area_of_circle_with_radius(2);

	int *ip = t16<int>;
	char *cp = t16<char>;
	double *dp = t16<double>;

	ip[0] = 12;
	cp[0] = 'a';
	dp[0] = pi<double>;

	//cout << "(pause)";
	//cin.get();
	return 0;
}