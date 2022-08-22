@if "%VCToolsVersion%"=="" call devcmd
@REM echo cl /W4 /Zi /EHsc /std:c11 fnts2fon.c
cl /W3 /Zi /EHsc /std:c11 /I.. /I../include /wd4996 /Fe:fnt2psf.exe fnt2psf.c cnvshell.c mswfntr.c ..\lib\psf.lib
