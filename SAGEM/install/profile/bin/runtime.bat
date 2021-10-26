@echo off

setlocal

if "%RUN_CONF%"=="" (
  set RUN_CONF=%~dp0setenv.bat
)

if exist "%RUN_CONF%" (
  call "%RUN_CONF%"
)

set JAVA_MEMSET=-Xms%JAVA_MIN_MEM% -Xmx%JAVA_MAX_MEM%
set JAVA_RUN=%JAVA_EXEC% %JAVA_MEMSET% -server
set APP_DAEMON_PIDFILE_TMP=%OSGI_INSTALL_AREA%\bin\pid.tmp

if "%USE_WRAPPER%"=="no" (
  SET TERM=ansi
)

:checkParams
if "%1"=="-start" (
  rem Remove the following variable set after services are ready
  rem SET NO_SERVICE=yes
  goto init
)
if "%1"=="-console" (
  SET NO_SERVICE=yes
  goto init
)
if "%1"=="-stop" (
  goto init
)
if "%1"=="-status" (
  goto init
)

:init
SET LOCK_FILE="%~dp0.lock"
SET STAT_FILE="%~dp0.stat"
SET LOCK_FILE_OSGI="%OSGI_INSTALL_AREA%\workspace\temp\cleanupBatch.bat"
SET SHUTDOWN_ANCHOR="%~dp0shutdown.anchor"

if [%WORK_DIR%]==[] (
  goto skip_work_dir
)

rem switch to work directory (if not empty)
if exist %WORK_DIR% (
  echo Changing working directory to %WORK_DIR%
  cd /d %WORK_DIR%
)

:skip_work_dir
rem check if it is a newer Windows version
for /f "tokens=2* delims=[]" %%a in ('ver') do (
  for /f "tokens=2" %%v in ("%%a") do (
    set WINVER_FULL=%%v
    echo Windows version is %%v
  )
)

for /f "tokens=1 delims=." %%m in ("%WINVER_FULL%") do (
  set WINVER_MAJOR=%%m
)

if "%1"=="-start" goto start
if "%1"=="-console" goto start
if "%1"=="-stop" goto stop
if "%1"=="-status" goto status

:help
echo.
echo Usage: runtime.bat ^<command^>
echo replace ^<command^> with one of the following:
echo    -start      ^- Starts the runtime as a service if it is installed, or
echo              as a regular process if it is not installed.
echo    -console    ^- Starts as a regular process even if installed as a
echo              service. This has no effect if it is already running as a service. 
echo    -stop       ^- Stops the runtime.
echo    -status     ^- Checks the runtime status (RUNNING or STOPPED).
echo    -help       ^- Displays this message.
echo.
pause
goto end

:start
rem =================================== Start ===================================
rem Check is it empty otherwise it will return error level 1 that variable is not set but we try to unset it.
if not "%CMD_ARGS%"=="" (
  set CMD_ARGS=
)

rem skip first argument as it denotes startup mode
:loop
if not "%2"=="" (
  if "%CMD_ARGS%"=="" (
    set CMD_ARGS=%2
  ) else (
    set CMD_ARGS=%CMD_ARGS% %2
  )
  shift /2
  goto loop
)

rem Check if shutdown anchor file exist and if exist delete it.
rem this indicates that previous shutdown command failed due to some reason
if exist "%SHUTDOWN_ANCHOR%" (
  del /q %SHUTDOWN_ANCHOR%
)

rem Check if there is a service installed
if "%SERVICE_NAME%"=="" (
  goto start_noService
)

rem Get service state
rem Check is it empty otherwise it will return error level 1 that variable is not set but we try to unset it.
if not "%SERVICE_STATE%"=="" (
  set SERVICE_STATE=
)

rem Workaround for: Any command set in the following registry:
rem HKEY_CURRENT_USER\Software\Microsoft\Command Processor\Autorun 
rem will write its output as a result to the "for" cycle.
rem We detect such situations by searching for a process we are sure
rem does not exist and if PID is set to anything than nul, then this is the case

set RESULT_COUNT=0
set "FAKE_SERVICE_NAME=%SERVICE_NAME%_%random%_%random%"
for /f "tokens=3,4*" %%i in ('%WINDIR%\System32\sc query %FAKE_SERVICE_NAME% ^| %WINDIR%\System32\FINDSTR "STATE"') do (
  set /A RESULT_COUNT=RESULT_COUNT+1
)
set RESULT_COUNT_2=0
for /f "tokens=3,4*" %%i in ('%WINDIR%\System32\sc query %SERVICE_NAME% ^| %WINDIR%\System32\FINDSTR "STATE"') do (
  set TEMP_VAR=%%i
  set SERVICE_STATE=%%j
  set /A RESULT_COUNT_2=RESULT_COUNT_2+1
)
if %RESULT_COUNT% == %RESULT_COUNT_2% (
  rem No service found
  goto start_noService
)

if "%SERVICE_STATE%"=="" (
  goto start_noService
)

if not "%SERVICE_STATE%"=="RUNNING" (
  rem The service is not running
  goto start_cmdService
)

rem Check if the service is already running
for /f "tokens=3*" %%i in ('%WINDIR%\System32\sc queryex %SERVICE_NAME% ^| %WINDIR%\System32\findstr PID') do (
  set PID=%%i
  echo RUNNING %PID%
  goto end
)

:start_cmdService
if "%NO_SERVICE%"=="yes" (
  goto start_noService
)
%WRAPPER% -t %WRAPPER_CONF% %TANUKI_ARGS% -- %CMD_ARGS% >nul
rem sc start %SERVICE_NAME% >nul
goto end

:start_noService
rem Check if already running

if "%USE_WRAPPER%"=="yes" (
  rem Checking for anchor file %WRAPPER_ANCHOR%
  if exist %WRAPPER_ANCHOR% (
    for /F "usebackq" %%i in (%WRAPPER_ANCHOR%) do (
      set PID=%%i
    )
    goto check_is_running_wrapper
  )
  rem platform is not started - continue with start.
  goto start_continue
)
goto check_is_running

rem check does process with PID is running
:check_is_running_wrapper
wmic process where "ProcessID = %PID%" get processid 2> %APP_DAEMON_PIDFILE_TMP% > NUL
set /P STDERR=<%APP_DAEMON_PIDFILE_TMP%
 
for /f %%i in ("%APP_DAEMON_PIDFILE_TMP%") do set size=%%~zi
if not defined size set size=0
del /q %APP_DAEMON_PIDFILE_TMP%
if "%size%" == "0" goto start_alreadyRunning

rem delete old wrapper.anchor file
if exist %WRAPPER_ANCHOR% (
  del /q %WRAPPER_ANCHOR%
)

:check_is_running
rem Parameter to skip Windows title check for IS
if "%DO_NOT_CHECK_FOR_DUPLICATE_INSTANCE_WITH_TITLE%"=="true" (
  goto start_continue
)

rem Workaround for: Any command set in the following registry:
rem HKEY_CURRENT_USER\Software\Microsoft\Command Processor\Autorun 
rem will write its output as a result to the "for" cycle.
rem We detect such situations by searching for a process we are sure
rem does not exist and if PID is set to anything than nul, then this is the case

for /f "skip=1" %%i in ('wmic process where "Name like 'java.exe'" get ProcessId') do (
  for /f "tokens=2" %%j in ('TASKLIST /NH /V /FI "PID eq %%i" /FI "WINDOWTITLE eq %WINDOW_TITLE%" 2^>nul ^| %WINDIR%\System32\FINDSTR "%WINDOW_TITLE%"') do (
    set PID=%%i
  )
)

if NOT "%PID%"=="" (
  rem A running instance was found
  goto start_alreadyRunning
)

if not %WINVER_MAJOR% GTR 5 (
  rem There is really no such process
  goto start_continue
)
rem Windows major version is greater than 5. It may be a 2008...
for /f "skip=1" %%i in ('wmic process where "Name like 'java.exe'" get ProcessId') do (
  for /f "tokens=2" %%j in ('TASKLIST /NH /V /FI "PID eq %%i" 2^>nul ^| %WINDIR%\System32\FIND "%WINDOW_TITLE%"') do (
    set PID=%%i
  )
)
if NOT "%PID%"=="" (
  rem A running instance was found
  goto start_alreadyRunning
)

:start_continue
rem Not running - release the lock
if exist %LOCK_FILE% (
  del /q %LOCK_FILE%
)
rem remove the status file
if exist %STAT_FILE% (
  del /q %STAT_FILE%
)

:start_cmd
rem Get the lock
echo. >%LOCK_FILE%

title %WINDOW_TITLE%
if "%USE_WRAPPER%"=="yes" (
  goto use_wrapper
)
echo Starting as an application using Java.

set JAVA_SYSPROPS=%JAVA_SYSPROPS% -Dcom.softwareag.platform.bootstrap.anchor=%WRAPPER_ANCHOR%

if "%BLOCKING_SCRIPT%"=="yes" (
  %JAVA_RUN% %DEBUG_ARG% -Xbootclasspath/a:"%JAVA_BOOT_CLASSPATH%" -cp "%JAVA_SYSTEM_CLASSPATH%" %JAVA_OPTS% %JAVA_SYSPROPS% com.softwareag.platform.bootstrap.Bootstrap startup %CMD_ARGS%
) else (
  start "%WINDOW_TITLE%" %JAVA_RUN% %DEBUG_ARG% -Xbootclasspath/a:"%JAVA_BOOT_CLASSPATH%" -cp "%JAVA_SYSTEM_CLASSPATH%" %JAVA_OPTS% %JAVA_SYSPROPS% com.softwareag.platform.bootstrap.Bootstrap startup %CMD_ARGS%
)
goto end_start_cmd

:use_wrapper
echo Starting as an application using Tanuki Wrapper
if "%BLOCKING_SCRIPT%"=="yes" (
  %WRAPPER% -c %WRAPPER_CONF% %TANUKI_ARGS% -- %CMD_ARGS%
) else (
  start "%WINDOW_TITLE%" %WRAPPER% -c %WRAPPER_CONF% %TANUKI_ARGS% -- %CMD_ARGS%
)

:end_start_cmd
set EL=%ERRORLEVEL%
echo %EL% >%STAT_FILE%

if not "%BLOCKING_SCRIPT%"=="yes" (
  goto end
)

rem Release the lock
rem if exist %LOCK_FILE% (
rem   del /q %LOCK_FILE%
rem )
goto stop_clean
rem goto end

:start_alreadyRunning
echo RUNNING %PID%
goto end

:stop
rem =================================== Stop ===================================
if exist %WRAPPER_ANCHOR% (
  copy %WRAPPER_ANCHOR% %SHUTDOWN_ANCHOR% >nul
)

rem Check if there is a service installed
if "%SERVICE_NAME%"=="" (
  goto stop_noService
)

rem Get service state
rem Check is it empty otherwise it will return error level 1 that variable is not set but we try to unset it.  
if not "%SERVICE_STATE%"=="" (
  set SERVICE_STATE=
)

for /f "tokens=3,4*" %%i in ('%WINDIR%\System32\sc query %SERVICE_NAME% ^| %WINDIR%\System32\FIND "STATE"') do (
  rem set in temp variable first result because it will be returned as error level 1
  set TEMP_VAR=%%i
  set SERVICE_STATE=%%j
)
if "%SERVICE_STATE%"=="" (
  goto stop_noService
)

rem Check if the service is already running
if not "%SERVICE_STATE%"=="RUNNING" (
  rem The service is not running
  rem Now check if started as a normal process
  goto stop_noService
)

:stop_cmdService
%WRAPPER% -p %WRAPPER_CONF% >nul
rem sc stop %SERVICE_NAME% >nul
goto end

:stop_cmd
:stop_noService

:stop_checkRunning
rem Check if running
if exist %WRAPPER_ANCHOR% (
  for /F "usebackq" %%i in (%WRAPPER_ANCHOR%) do (
    set PID=%%i
    goto checkAnchorPID
  )
  :deleteAnchor
  echo Anchor file found. Deleting it to stop platform...
  del /q %WRAPPER_ANCHOR%
  set ANCHOR_DELETE=yes
  goto stop_waitStatus

  :checkAnchorPID
  wmic process where "ProcessID = %PID%" get processid 2> %APP_DAEMON_PIDFILE_TMP% > NUL
  set /P STDERR=<%APP_DAEMON_PIDFILE_TMP%
  for /f %%i in ("%APP_DAEMON_PIDFILE_TMP%") do set size=%%~zi
  if not defined size set size=0
  del /q %APP_DAEMON_PIDFILE_TMP%
  if "%size%" == "0" goto deleteAnchor
  @echo Process is stopped.
)

:checkWindow
for /f "skip=1" %%i in ('wmic process where "Name like 'java.exe'" get ProcessId') do (
  for /f "tokens=2" %%j in ('TASKLIST /NH /V /FI "PID eq %%i" /FI "WINDOWTITLE eq %WINDOW_TITLE%" 2^>nul ^| %WINDIR%\System32\FINDSTR "%WINDOW_TITLE%"') do (
    set PID=%%i
  )
)

if NOT "%PID%"=="" (
  rem A running instance was found
  goto stop_waitStatus
)

if not %WINVER_MAJOR% GTR 5 (
  rem There is really no such process
  goto stop_continue
)
rem Windows major version is greater than 5. It may be a 2008...
for /f "skip=1" %%i in ('wmic process where "Name like 'java.exe'" get ProcessId') do (
  for /f "tokens=2" %%j in ('TASKLIST /NH /V /FI "PID eq %%i" 2^>nul ^| %WINDIR%\System32\FIND "%WINDOW_TITLE%"') do (
    set PID=%%i
  )
)
if NOT "%PID%"=="" (
  rem A running instance was found
  goto stop_waitStatus
)

:stop_continue
goto stop_clean

:stop_waitStatus
rem Will wait for status about 60 seconds
rem Check is it empty otherwise it will return error level 1 that variable is not set but we try to unset it.  
if not "%WAITING%"=="" (
  set WAITING=
)

:stop_waitingLoop
if not "%WAITING%"=="........................................................................................................................" (
  goto stop_checkStatus
)

if not "%TRIED_GRACEFUL%"=="yes" (
  goto stop_graceful
)
if "%TRIED_GRACEFUL%"=="yes" (
  echo Waited to shutdown for 30 seconds. Stopping it now.
  goto stop_kill
)

:stop_checkStatus
set RESULT_COUNT=0
set FAKE_PID="%random%_%random%_%random%"
for /f "tokens=2" %%i in ('TASKLIST /NH /V /FI "PID eq %FAKE_PID%" 2^>nul ^| %WINDIR%\System32\FINDSTR "%FAKE_PID%"') do (
  set /A RESULT_COUNT=RESULT_COUNT+1
)
set RESULT_COUNT_2=0
for /f "tokens=2" %%i in ('TASKLIST /NH /V /FI "PID eq %PID%" 2^>nul ^| %WINDIR%\System32\FINDSTR "%PID%"') do (
  set /A RESULT_COUNT_2=RESULT_COUNT_2+1
)

if exist %STAT_FILE% (
  if "%ANCHOR_DELETE%"=="yes" (
    if NOT "%RESULT_COUNT%"=="%RESULT_COUNT_2%" (
      rem A running instance was found
      if not "%WAITING%"=="........................................................................................................................" (
        echo|set /p=.
        goto wait
      )
      set ANCHOR_DELETE=no
      goto checkWindow
    )
    if exist %STAT_FILE% (
      del /q %STAT_FILE%
    )
    @echo Process is stopped.
    goto end
  )
  rem Ensure cmd.exe is stopped
  goto stop_kill
)

set RESULT_COUNT=0
set FAKE_PID="%random%_%random%_%random%"
for /f "tokens=2" %%i in ('TASKLIST /NH /V /FI "PID eq %FAKE_PID%" 2^>nul ^| %WINDIR%\System32\FINDSTR "%FAKE_PID%"') do (
  set /A RESULT_COUNT=RESULT_COUNT+1
)
echo step 1
set RESULT_COUNT_2=0
for /f "tokens=2" %%i in ('TASKLIST /NH /V /FI "PID eq %PID%" 2^>nul ^| %WINDIR%\System32\FINDSTR "%PID%"') do (
  set /A RESULT_COUNT_2=RESULT_COUNT_2+1
)

if not "%PID%"=="" (
  if "%ANCHOR_DELETE%"=="yes" (
    @echo Checking Tanuki Wrapper PID...

    if NOT "%RESULT_COUNT%"=="%RESULT_COUNT_2%" (
      rem A running instance was found
      goto wait
    )

    @echo Process is stopped.
    goto end
  )
)

if "%PID%"=="" (
  @echo PID is empty. Process is stopped.
  goto end
)

rem Wait one more second
:wait
ping -n 5 -w 1 0.0.0.1 >nul 2>&1
set WAITING=%WAITING%.
goto stop_waitingLoop

:stop_graceful
echo Trying to stop it gracefully...
TASKKILL /T /PID %PID%
set TRIED_GRACEFUL=yes
goto stop_waitStatus

:stop_kill
echo Killing the process...
TASKKILL /F /T /PID %PID%

:stop_getStatus
for /f "tokens=1" %%i in ('type %STAT_FILE%') do (
  set EL=%%i
)

:stop_clean
if exist %LOCK_FILE% (
  del /q %LOCK_FILE%
)
if exist %STAT_FILE% (
  del /q %STAT_FILE%
)
goto end

:status
rem =================================== Status ===================================

rem Check if there is a service installed
if "%SERVICE_NAME%"=="" (
  goto status_noService
)

rem Get service state
rem Check is it empty otherwise it will return error level 1 that variable is not set but we try to unset it.
if not "%SERVICE_STATE%"=="" (
  set SERVICE_STATE=
)

for /f "tokens=3,4*" %%i in ('%WINDIR%\System32\sc query %SERVICE_NAME% ^| %WINDIR%\System32\FIND "STATE"') do (
  rem set in temp variable first result because it will be returned as error level 1
  set TEMP_VAR=%%i
  set SERVICE_STATE=%%j
)
if "%SERVICE_STATE%"=="" (
  goto status_noService
)

rem Check if the service is already running
if not "%SERVICE_STATE%"=="RUNNING" (
  rem The service is not running
  rem Now check if running as a normal process
  goto status_noService
)

goto status_running

:status_noService
if exist %LOCK_FILE_OSGI% (
  goto status_running
)
if not exist %LOCK_FILE% (
  goto status_stopped
)

rem check for anchor file
if "%USE_WRAPPER%"=="yes" (
  if exist %WRAPPER_ANCHOR% (
    for /F "usebackq" %%i in (%WRAPPER_ANCHOR%) do (
      set /A PID=%%i
      goto status_is_running
    )
  )
  rem it is stopped
  goto status_stopped
)

rem Workaround for: Any command set in the following registry:
rem HKEY_CURRENT_USER\Software\Microsoft\Command Processor\Autorun 
rem will write its output as a result to the "for" cycle.
rem We detect such situations by searching for a process we are sure
rem does not exist and if PID is set to anything than nul, then this is the case

for /f "skip=1" %%i in ('wmic process where "Name like 'java.exe'" get ProcessId') do (
  for /f "tokens=2" %%j in ('TASKLIST /NH /V /FI "PID eq %%i" /FI "WINDOWTITLE eq %WINDOW_TITLE%" 2^>nul ^| %WINDIR%\System32\FINDSTR "%WINDOW_TITLE%"') do (
    set PID=%%i
  )
)

if NOT "%PID%"=="" (
  rem A running instance was found
  goto status_running
)
if not %WINVER_MAJOR% GTR 5 (
  rem There is really no such process
  goto status_stopped
)
rem Windows major version is greater than 5. It may be a 2008...
for /f "skip=1" %%i in ('wmic process where "Name like 'java.exe'" get ProcessId') do (
  for /f "tokens=2" %%j in ('TASKLIST /NH /V /FI "PID eq %%i" 2^>nul ^| %WINDIR%\System32\FIND "%WINDOW_TITLE%"') do (
    set PID=%%i
  )
)
if NOT "%PID%"=="" (
  rem A running instance was found
  goto status_running
)

rem check does process with PID is running
:status_is_running
wmic process where "ProcessID = %PID%" get processid 2> %APP_DAEMON_PIDFILE_TMP% > NUL
set /P STDERR=<%APP_DAEMON_PIDFILE_TMP%
 
for /f %%i in ("%APP_DAEMON_PIDFILE_TMP%") do set size=%%~zi
if not defined size set size=0
del %APP_DAEMON_PIDFILE_TMP%
if "%size%" == "0" goto status_running

:status_stopped
echo STOPPED
rem delete old wrapper.anchor file
if exist %WRAPPER_ANCHOR% (
  del /q %WRAPPER_ANCHOR%
)
if exist %LOCK_FILE% (
  del /q %LOCK_FILE%
)
if exist %STAT_FILE% (
  del /q %STAT_FILE%
)
set EL=1
goto end

:status_running
if "%PID%"=="" (
  goto status_running_no_pid
) else (
  goto status_running_with_pid
)

:status_running_with_pid
echo RUNNING %WINDOW_TITLE% with pid %PID%
set EL=0
goto end

:status_running_no_pid
echo RUNNING %WINDOW_TITLE%
set EL=0
goto end

:end
if exist %LOCK_FILE_OSGI% (
  ping -n 5 -w 1 0.0.0.1 >nul 2>&1
  goto end
)
if exist %SHUTDOWN_ANCHOR% (
   del /q %SHUTDOWN_ANCHOR%
)

rem restore the window title
title "Command Prompt"
if not "%EL%"=="" (
   exit /b %EL%
)
endlocal
