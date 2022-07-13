@if "%VCToolsVersion%"=="" call devcmd
cl /W4 /Zi /EHsc /std:c++20 cpptuple.cpp
