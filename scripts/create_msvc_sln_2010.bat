@echo off
SET CD_DIR=%CD%
@IF EXIST msvc\2010 DEL /F /S /Q msvc\2010\*.*

CD msvc\2010

call "%VS100COMNTOOLS%\vsvars32.bat"

cmake -G "Visual Studio 10 2010" %CD_DIR%

CD %~dp0
