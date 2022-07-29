@ECHO OFF
IF "%~1"=="" (GOTO NOARG) ELSE (GOTO ARG)
:NOARG
FOR %%i IN (*.CSV) DO CONVBIN -j csv -k c -i %%i -o "%%~ni.c" -n %%~ni_map
PAUSE
EXIT
:ARG
CONVBIN -j csv -k c -i "%~1.csv" -o "%~1.c" -n "%~1_map"
PAUSE
EXIT
