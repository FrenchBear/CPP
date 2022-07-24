@if "%VCToolsVersion%"=="" call devcmd
echo cl /W4 /Zi /EHsc /std:c++20 io.cpp
cl /W4 /Zi /EHsc /std:c++20 io.cpp