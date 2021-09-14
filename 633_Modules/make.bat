@echo off
REM Exeute this in Visual Studio 2017 Developer Command Prompt
REM %comspec% /k "C:\Program Files (x86)\Microsoft Visual Studio\2017\Enterprise\Common7\Tools\VsDevCmd.bat"
REM Need to have Standard Library Modules installed for CPP

CALL "C:\Program Files (x86)\Microsoft Visual Studio\2017\Enterprise\Common7\Tools\VsDevCmd.bat"

cl /experimental:module /EHsc /MD /std:c++latest test.cxx