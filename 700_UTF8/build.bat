@if "%VCToolsVersion%"=="" call devcmd
echo cl /W4 /Zi /EHsc /std:c++20 cpputf8.cpp
cl /W4 /Zi /EHsc /std:c++20 cpputf8.cpp