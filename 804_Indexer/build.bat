@if "%VCToolsVersion%"=="" call devcmd
echo cl /W4 /Zi /EHsc /std:c++20 indexer.cpp
cl /W4 /Zi /EHsc /std:c++20 indexer.cpp