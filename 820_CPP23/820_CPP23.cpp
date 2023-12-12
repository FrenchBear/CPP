// 820_CPP23.cpp
// Play with C++23 new string features
// From https://www.cppstories.com/2023/six-handy-ops-for-string-processing/?utm_source=pocket_reader
//
// 2023-12-12   PV

#include <iostream>
#include <sstream>
#include <string>
#include <spanstream>

using namespace std;

static void test_contains()
{
    cout << "\ntest_contains\n";

    // Before C++23
    const std::string url = "https://isocpp.org";

    if (url.find("https") != std::string::npos &&
        url.find(".org") != std::string::npos &&
        url.find("isocpp") != std::string::npos)
        std::cout << "You're using the correct site!\n";

    // C++23
    // https://www.open-std.org/jtc1/sc22/wg21/docs/papers/2020/p1679r3.html
    if (url.contains("https") &&
        url.contains(".org") &&
        url.contains("isocpp"))
        std::cout << "you're using the correct site!\n";
}

static void test_starts_ends_with()
{
    cout << "\ntest_starts_ends_with\n";

    // C++20 start_with, ends_with
    // https://www.cppstories.com/2020/08/string-prefix-cpp20.html/

    const std::string url = "https://isocpp.org";

    if (url.starts_with("https") && url.ends_with(".org"))
        std::cout << "you're using the correct site!\n";
}

static void test_ranges() {
    cout << "\ntest_ranges\n";

    const auto source = { 'l', 'i', 'b', '_' };
    std::string target{ "__cpp_containers_ranges" };

    const auto pos = target.find("container");
    auto iter = std::next(target.begin(), pos);

#ifdef __cpp_lib_containers_ranges
    target.insert_range(iter, source);
#else
    target.insert(iter, source.begin(), source.end());
#endif

    std::cout << target << endl;
}

void* operator new(std::size_t sz){
    std::cout << "Allocating: " << sz << '\n';
    return std::malloc(sz);
}

static void test_stringstream_view() {
    cout << "\ntest_stringstream_view\n";

    std::stringstream str;
    str << 42;
    str << " Hello C++20/23 Programming World";
    std::cout << "print with str()\n";
    std::cout << str.str() << '\n';
    // Since C++20, you have the view() member function. This can be used as an alternative to str(). 
    // In short, rather than creating a copy of the internal string, you’ll get a view, 
    // so there is no need to dynamically allocate memory.
    std::cout << "another try...\n";
    std::cout << str.view() << '\n';        
}

static void test_spanstream()
{
    cout << "\ntest_spanstream\n";

    // Allocates memory dynamically
    std::stringstream ss;
    ss << "one string that doesn't fit into SSO";
    ss << "another string that hopefully won't fit";

    // We have here the new type, spanstream, which uses a preallocated buffer (a regular array), and this buffer is used as the internal memory for the stream object.
    std::cout << "spanstream:\n";
    char buffer[128]{ 0 };
    std::span<char> spanBuffer(buffer);
    std::basic_spanstream<char> ss2(spanBuffer);
    ss2 << "one string that doesn't fit into SSO";
    ss2 << "another string that hopefully won't fit";

    std::cout << buffer;
}

int main()
{
    test_contains();
    test_starts_ends_with();
    test_ranges();
    test_stringstream_view();
    test_spanstream();
}