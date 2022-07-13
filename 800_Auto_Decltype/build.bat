@if "%VCToolsVersion%"=="" call devcmd
cl /W4 /Zi /EHsc /std:c++20 CS800_Auto.cpp
REM cl /W4 /O2 /EHsc pcpp.cpp