// From https://stackoverflow.com/questions/11898680/yield-keyword-for-c-how-to-return-an-iterator-from-my-function
// But reading on Boost at https://studiofreya.com/cpp/boost/ :
// "The advantages with Boost are tremendous, but there are a couple of backsides to the medal. Each release is heavy,
// "and it contains easily about 55000 files, and takes about 500 megabytes of space. If you use a library which have to
// "be built, the disk cost can increase with 5-10GB. 
// Okay...  So I'll check later!

#include <fstream>
#include <functional>
#include <iostream>
#include <string>
#include <boost/coroutine2/all.hpp>

using namespace std;

typedef boost::coroutines2::coroutine<const string&> coro_t;

void cat(coro_t::push_type& yield, int argc, char* argv[])
{
    for (int i = 1; i < argc; ++i) {
        ifstream ifs(argv[i]);
        for (;;) {
            string line;
            if (getline(ifs, line)) {
                yield(line);
            } else {
                break;
            }
        }
    }
}

int main(int argc, char* argv[])
{
    using namespace std::placeholders;
    coro_t::pull_type seq(
            boost::coroutines2::fixedsize_stack(),
            bind(cat, _1, argc, argv));
    for (auto& line : seq) {
        cout << line << endl;
    }
}
