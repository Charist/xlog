@echo off

SET CD_DIR=%CD%
rem @IF EXIST Windows\2015 DEL /F /S /Q Windows\2015\*.*

CD Windows\2015

call "%VS140COMNTOOLS%\vsvars32.bat"

cmake  -DCMAKE_BUILD_TYPE=Release -G "Visual Studio 14 2015" %CD_DIR%

CD %~dp0
CD ..\