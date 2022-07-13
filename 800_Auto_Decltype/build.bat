@if "%VCToolsVersion%"=="" call devcmd
cl /W4 /Zi /EHsc /std:c++20 /wd4189 auto.cpp
