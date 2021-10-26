@echo off
setlocal

goto check

:startSUM
rem first try to update
"%~dp0..\jvm\jre\bin\java.exe" %JAVA_OPTIONS% %JAVA_OPTIONS_SUM_V11% -jar "%~dp0SUMlauncher.jar" -sumHome "%~dp0.." -updateOnly -debug true %*
set EL=%ERRORLEVEL%
if "%EL%" == "16" (
  rem update started
  set UPDATING=yes
  echo Updating Launcher Components...
  goto wait
) else if "%EL%" == "17" (
  goto positive_exit
) else if "%EL%" == "18" (
  goto negative_exit
) else if "%EL%" == "0" (
  goto done
) else if "%EL%" == "170" (
  goto done
) else (
  exit /b %EL%
)

:wait
if exist "%~dps0.lock" (
  ping -n 5 -w 1 0.0.0.1 >nul 2>&1
  goto wait
)

rem wait for file system
ping -n 10 -w 1 0.0.0.1 >nul 2>&1
:wait_exit
rem read exit status
if exist "%~dps0exit_code.txt" (
  for /f "tokens=1,2*" %%i in (%~dps0exit_code.txt) do (
    if "%%i" == "16" (
      ping -n 5 -w 1 0.0.0.1 >nul 2>&1
      goto wait_exit
    ) else if "%%i" == "170" (
      del "%~dps0exit_code.txt"
      goto done
    ) else if "%%i" == "0" (
      del "%~dps0exit_code.txt"
      goto done
    )
    echo Failed: %%j
    endlocal & exit /b %%i
  )
) else (
  goto wait
)

:done
if "%UPDATING%" == "yes" (
  echo Done
)

:startSUM2
"%~dp0..\jvm\jre\bin\java.exe" %JAVA_OPTIONS% %JAVA_OPTIONS_SUM_V11% -jar "%~dp0SUMlauncher.jar" -sumHome "%~dp0.." -debug true %*
set EL=%ERRORLEVEL%
endlocal & exit /b %EL%

:positive_exit
endlocal & exit /b 0

:negative_exit
endlocal & exit /b 1

:check
if "%1" == "" goto startSUM2
if "%1" == "-withoutUI" goto startSUM
if "%1" == "-guiUpdateCheck" goto startSUM

set p=%1
set p=%p:"=%
if "%p%" == "-sum" shift & goto startSUM
goto startSUM2
