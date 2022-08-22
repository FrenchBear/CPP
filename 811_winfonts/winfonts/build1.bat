@if "%VCToolsVersion%"=="" call devcmd
@REM echo cl /W4 /Zi /EHsc /std:c11 fnts2fon.c
cl /W3 /Zi /EHsc /std:c11 /Fe:fon2fnts.exe fon2fnts.c mz.c ne.c pe.c nerootd.c peresd.c neroote.c perese.c nesubd.c nesube.c
