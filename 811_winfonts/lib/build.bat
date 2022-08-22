@if "%VCToolsVersion%"=="" call devcmd
cl /c /W3 /O2 /std:c11 /I.. /I../include /wd4996 /favor:INTEL64 *.c
lib /out:psf.lib *.obj
