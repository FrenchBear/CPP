@if "%VCToolsVersion%"=="" call devcmd
echo cl /W4 /Zi /EHsc /std:c++20 cpptuple.cpp
cl /W4 /Zi /EHsc /std:c++20 cpptuple.cpp