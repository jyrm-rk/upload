@echo off
for /f "tokens=1*" %%i in ('call "%~dp0runtime.bat" -status') do (
  if "%%i"=="RUNNING" (
    echo.
    echo %%j is running.
	echo.
    goto end
  )
  if "%%i"=="STOPPED" (
    echo.
    echo The runtime is not running.
	echo.
    goto end
  )
)

:end
pause
