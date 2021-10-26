@echo off
setlocal

if "%RUN_CUSTOM_CONF%"=="" (
  set RUN_CUSTOM_CONF=%~dp0custom_setenv.bat
)

if exist "%RUN_CUSTOM_CONF%" (
  call "%RUN_CUSTOM_CONF%"
)

set MODE_PARAM=-console
set USE_WRAPPER=yes
set BLOCKING_SCRIPT=yes

call "%~dp0runtime.bat" %MODE_PARAM% %*
set EL=%ERRORLEVEL%
endlocal & set EL=%EL%
exit /b %EL%
