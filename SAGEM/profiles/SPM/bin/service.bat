@echo off
setlocal

rem Copyright (c) 1999, 2009 Tanuki Software, Ltd.
rem http://www.tanukisoftware.com
rem All rights reserved.
rem
rem This software is the proprietary information of Tanuki Software.
rem You shall use it only in accordance with the terms of the
rem license agreement you entered into with Tanuki Software.
rem http://wrapper.tanukisoftware.org/doc/english/licenseOverview.html
rem
rem Java Service Wrapper general NT service install script.
rem Optimized for use with version 3.3.2 of the Wrapper.
rem

rem
rem Resolve the real path of the wrapper.exe
rem  For non NT systems, the _REALPATH and _WRAPPER_CONF values
rem  can be hard-coded below and the following test removed.
rem
if "%OS%"=="Windows_NT" goto nt
echo This script works only with NT-based versions of Windows.
goto :eof

:nt
rem
rem Find the application home.
rem
rem %~dp0 is location of current script under NT
set _REALPATH=C:\temp\SAGEM\common\bin

rem
rem Run the environment configuration script
rem
call "%~dp0\setenv.bat"

rem Decide on the wrapper binary.
set _WRAPPER_BASE=wrapper-3.5.43.exe
set _WRAPPER_EXE=%_REALPATH%\%_WRAPPER_BASE%
if exist "%_WRAPPER_EXE%" goto run
echo Unable to locate a Wrapper executable using any of the following names:
echo %_REALPATH%\%_WRAPPER_BASE%
goto :conditionalPausedEnd

:run
if ""%1"" == """"              goto doHelp
if ""%1"" == ""-console""      goto doConf
if ""%1"" == ""-start""        goto doConf
if ""%1"" == ""-pause""        goto doConf
if ""%1"" == ""-resume""       goto doConf
if ""%1"" == ""-stop""         goto doConf
if ""%1"" == ""-install""      goto doConf
if ""%1"" == ""-installstart"" goto doConf
if ""%1"" == ""-remove""       goto doConf
if ""%1"" == ""-dump""         goto doConf
if ""%1"" == ""-query""        goto doConf
if ""%1"" == ""-querysilent""  goto doConf
if ""%1"" == ""-hostid""       goto doConf
if ""%1"" == ""-version""      goto doConf
if ""%1"" == ""-help""         goto doHelp

echo Unrecognized option: %1
echo.

:doHelp
echo Usage: service ^<command^> ^<configuration file^>
echo.
echo replace ^<command^> with one of the following:
echo   -console      Run as a Console application.
echo   -start        Start an NT service.
echo   -pause        Pause a started NT service.
echo   -resume       Resume a paused NT service.
echo   -stop         Stop a running NT service.
echo   -install      Install as an NT service.
echo   -installstart Install and start as an NT service.
echo   -remove       Remove as an NT service.
echo   -dump         Request a thread dump.
echo   -query        Query for the current status of the service.
echo   -querysilent  Silent query for the current status of the service.
echo   -hostid       Prints a list of Host IDs which can be used to license this host.
echo   -version      Prints version information of the wrapper.
echo   -help         Prints this help message.
echo.
echo ^<configuration file^> is the wrapper.conf to use (implicitly ..\configuration\wrapper.conf).
echo Name must be absolute or relative to the location of service.bat file.
goto end

rem
rem Find the wrapper.conf
rem
:doConf
set _WRAPPER_CONF="C:\temp\SAGEM\profiles\SPM\configuration\wrapper.conf"

:execCmd
"%_WRAPPER_EXE%" -%1 %_WRAPPER_CONF%
if errorlevel 0 goto :eof
goto :conditionalPausedEnd

:conditionalPausedEnd
if not "%BATCHMODE%"=="TRUE" pause
goto :eof

:end
