@if "%VCToolsVersion%"=="" call devcmd
echo cl /W4 /Zi /EHsc /std:c++20 psf.cpp
cl /W4 /Zi /EHsc /std:c++20 psf.cpp