// 630 CPP parallelism
// Examples of multi-threading in C++
// Stroustrup Tour of C++, §13
//
// 2017-04-20	PV
// 2017-04-29	PV	GitHub and Linux

#include <iostream>
#include <string>
#include <numeric>
#include <vector>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <chrono>
#include <queue>

using namespace std;
using namespace std::chrono;


// Helper to simplify implementation of operator << for various containers
template<typename C>
void LessLessHelper(ostream& os, C container) {
	bool first = true;
	for (auto it = container.begin(); it != container.end(); ++it) {
		if (first)
			first = false;
		else
			os << ", ";
		os << *it;
	}
}

// Generic operator << for vector
// Actually making it too generic with T container creates many conflicting calls, compiler
// has too many choices to output other types
template <typename T>
ostream& operator <<(ostream& os, vector<T> container) {
	os << '{';
	LessLessHelper(os, container);
	os << '}';
	return os;
}


mutex m;	// controlling mutex for a shared resource (not shown here)


// Take input from v; place result in *res
void f(const vector<double>& v, double* res) {
	cout << "f: about to lock m\n";
	unique_lock<mutex> lck{ m };
	//m.lock();
	cout << "f: locked m\n";
	double s = accumulate(v.begin(), v.end(), 0.0);
	cout << "f: about to release m\n";
	//m.unlock();
	//actually, destruction of lck will unlock
	*res = s / v.size();
	cout << "f: end task\n";
}

class F {
	const vector<double>& v; // source of input
	double*res; // target for output

public:
	F(const vector<double>& vv, double* p) :v{ vv }, res{ p } { }

	// place result in *res
	void operator()() {
		cout << "F::operator(): about to lock m\n";
		unique_lock<mutex> lck{ m };
		//m.lock();
		cout << "F::operator(): locked m\n";
		double s = accumulate(v.begin(), v.end(), 0.0);
		cout << "F::operator(): about to release m\n";
		//m.unlock();
		*res = s / v.size();
		cout << "F::operator(): end task\n";
	}
};


void TestSimpleThreads() {
	vector<double> some_vec{ 1.414, 3.1416, 1.732, 2.718 };
	vector<double> vec2{ 1.0, 2.0, 3.0,7.0 };

	double res1;
	double res2;
	thread t1{ f,cref(some_vec), &res1 };	// f(some_vec,&res1) executes in a separate thread
	thread t2{ F{ vec2,&res2 } };			// F{vec2,&res2}() executes in a separate thread
	t1.join();
	t2.join();

	cout << "res1=" << res1 << endl << "res2=" << res2 << "\n\n";
}





void TestEvents() {
	// events, wait for 20ms in main thread
	auto sw0 = high_resolution_clock::now();
	this_thread::sleep_for(milliseconds{ 20 });
	auto sw1 = high_resolution_clock::now();
	auto d = sw1 - sw0;
	cout << duration_cast<microseconds>(sw1 - sw0).count() << " microseconds passed\n\n";
}



// Two-thread primes

using dur = duration<long long, std::nano>;

struct PrimeMessage {
	int prime;
	dur d;
};

queue<PrimeMessage> mqueue;
condition_variable mcond;
mutex mmutex;

inline void SendMessage(int p, dur d) {
	PrimeMessage m{ p, d };
	unique_lock<mutex> lck{ mmutex };
	mqueue.push(m);
	cout << "SendMessage " << p << ' ' << duration_cast<microseconds>(d).count() << endl;
	lck.unlock();		// important to release lock before notify_one
	mcond.notify_one();
}

void producer() {
	constexpr int pmax = 100;
	vector<bool> tb(pmax / 2 + 1, false);
	int nprime = 1;
	int nv = 3;
	auto start = high_resolution_clock::now();
	SendMessage(2, high_resolution_clock::now() - start);
	while (nv <= pmax)
	{
		if (!tb[(nv - 1) / 2])
		{
			SendMessage(nv, high_resolution_clock::now() - start);
			nprime++;
			int nvr = nv + nv + nv;          // skip even numbers
			while (nvr <= pmax)
			{
				// this test actually slows execution down about 20%
				/* if (!tb[(nvr - 1) / 2]) */ tb[(nvr - 1) / 2] = true;
				nvr += nv + nv;
			}
		}
		nv += 2;
	}
	// Sending prime 0 tells consumer that list is over
	SendMessage(0, high_resolution_clock::now() - start);
	cout << "producer ended\n";
}

void consumer() {
	while (true) {
		unique_lock<mutex> lck{ mmutex };	// acquire mutex
		mcond.wait(lck);					// release lck and wait;
		// re-acquire lck upon wakeup
		while (!mqueue.empty()) {
			auto m = mqueue.front(); // get the message
			mqueue.pop();
			// ... process m ...
			if (m.prime == 0)
				return;		// also release mutex
			cout << "ReceiveMessage " << m.prime << ' ' << duration_cast<microseconds>(m.d).count() << endl;
		}
		lck.unlock(); //release lck
	}
}

void TestPrimesWithTwoThreadsAndMessages() {
	// primes with 2 threads
	thread prime_producer{ producer };
	thread prime_consumer{ consumer };
	prime_producer.join();
	prime_consumer.join();
	cout << endl;
}


double accum(const double* beg, const double* end)
// compute the sum of [beg:end)
{
	return accumulate(beg, end, 0.0);
}


// don't know where async is for MS VC
// also no direct conversion from v.begin() to double *...
//double comp4(vector<double>& v)
//// spawn many tasks if v is large enough
//{
//	if (v.size()<10000) // is it worth using concurrency?
//		return accum(v.begin(), v.end());
//	auto v0 = &v[0];
//	auto sz = v.size();
//	auto f0 = async(accum, v0, v0 + sz / 4); // first quarter
//	auto f1 = async(accum, v0 + sz / 4, v0 + sz / 2); // second quarter
//	auto f2 = async(accum, v0 + sz / 2, v0 + sz*3 / 4); // third quarter
//	auto f3 = async(accum, v0 + sz*3 / 4, v0 + sz); // four th quar ter
//	return f0.get() + f1.g et() + f2.g et() + f3.g et(); // collect and combine the results
//}
//
//void TestAsync() {
//
//}



extern "C" double fmult(int, double);


int main()
{
	TestEvents();

	TestSimpleThreads();

	// TestPrimesWithTwoThreadsAndMessages();

	vector<double> v{ 1.0, 1.414, 1.732, 2.0 };
	auto b = v.begin();
	auto e = v.end();
	cout << *b << " " << *(e - 1) << " " << (e - b) << endl;

	double *pb = &(*v.begin());
	double *pe = pb + v.size();		// &(*v.end()); causes error, end is not dereferenceable

	int_fast64_t i = 0x1122334455667788;

	if (bool b = 3 * v.size() > 5) {

	}

	cout << pb << " " << pe << " " << pe - pb << endl << endl;

	cout << "2*1.414 = " << fmult(2, 1.414) << endl;

#ifdef _WIN32
	cout << "\n(Pause)";
	cin.get();
#endif
}
