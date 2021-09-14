// 618 CPP Pointer to member
//
// 2017-02-16	PV
// 2017-03-14	PV		Added Window example
// 2017-04-29	PV		GitHub and Linux
// 2021-09-14	PV		Visual Studio 2022

#include <iostream>
using namespace std;


class Testpm {
public:
	void m_func1() const { cout << "m_func1(): " << m_num1 << endl; }
	void m_func2() const { cout << "m_func2(): " << m_num2 << endl; }
	int m_num1;
	int m_num2;
};

void test(Testpm& obj, void(Testpm::* pmfn)() const, int Testpm::* pmd) {
	(obj.*pmd)++;
	(obj.*pmfn)();
}


class Window
{
public:
	Window() {}                            
	Window(int x1, int y1, int x2, int y2) {} 
	bool SetCaption(const char *szTitle) { return false; } 
	const char *GetCaption() { return szWinCaption; }
	char *szWinCaption;                    
	int id;
};

char * Window::*pwCaption   =   &Window::szWinCaption;
int Window::*pid  =  &Window::id; 



int main() {
	void(Testpm::*pmfn1)() const = &Testpm::m_func1;
	auto pmfn2 = &Testpm::m_func2;
	int Testpm::*pmd1 = &Testpm::m_num1;
	int Testpm::*pmd2 = &Testpm::m_num2;

	Testpm obj{ 3, 5 };
	test(obj, pmfn1, pmd1);
	test(obj, pmfn2, pmd2);
	
	
	Window w, *pw = &w;

	w.*pwCaption = nullptr;
	pw->*pid = 2;

	
#ifdef _WIN32
	cout << "\n(Pause)";
	cin.get();
#endif
}
