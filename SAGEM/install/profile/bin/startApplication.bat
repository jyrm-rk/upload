@echo off
setlocal

if "%RUN_CONF%"=="" (
  set RUN_CONF=%~dp0setenv.bat
)

if exist "%RUN_CONF%" (
    call "%RUN_CONF%"
)

rem call :toAbsolutePath "%DIRNAME%\.." ABS_PATH
rem set TARGET_PROFILE=%ABS_PATH%

set APP_NAME=com.softwareag.plm.sd.provision.app

set COMMAND=%*

rem echo %JAVA_BOOT_CLASSPATH%
rem echo %JAVA_SYSTEM_CLASSPATH%

if "%SAG_INSTALLER_TMPDIR%" == "" (
  %JAVA_EXEC% -Xbootclasspath/a:"%JAVA_BOOT_CLASSPATH%" %LOG4J_PROPS% -cp "%JAVA_SYSTEM_CLASSPATH%" com.softwareag.platform.bootstrap.Bootstrap startup -install "%OSGI_INSTALL_AREA%" -consolelog -configuration "%OSGI_INSTALL_AREA%/configuration" -application %APP_NAME% %COMMAND% -vmArgs -Dosgi.noShutdown=false -Dosgi.startLevel=10
) else (
  %JAVA_EXEC% -Djava.io.tmpdir="%SAG_INSTALLER_TMPDIR%" -Xbootclasspath/a:"%JAVA_BOOT_CLASSPATH%" %LOG4J_PROPS% -cp "%JAVA_SYSTEM_CLASSPATH%" com.softwareag.platform.bootstrap.Bootstrap startup -install "%OSGI_INSTALL_AREA%" -consolelog -configuration "%OSGI_INSTALL_AREA%/configuration" -application %APP_NAME% %COMMAND% -vmArgs -Dosgi.noShutdown=false -Dosgi.startLevel=10
)

exit /b %ERRORLEVEL%

endlocal&GOTO :eof

:toAbsolutePath
SETLOCAL ENABLEEXTENSIONS
pushd .
cd /D %1
SET ABSOLUTE_PATH=%CD%
popd
ENDLOCAL&set %2=%ABSOLUTE_PATH%&GOTO :eof
