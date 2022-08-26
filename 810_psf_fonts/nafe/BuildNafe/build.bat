@if "%VCToolsVersion%"=="" call devcmd
cl /W4 /Zi /EHsc /std:c11 psf2txt.c
cl /W4 /Zi /EHsc /std:c11 txt2psf.c