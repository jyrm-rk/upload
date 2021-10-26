@echo off
SETLOCAL ENABLEEXTENSIONS EnableDelayedExpansion

REM Update Manager Bootstrap Installer
REM Version @VERSION@

REM This .bat file is used from the .exe file bootstrapper on Windows. It is packaged
REM in a ZIP Fusion archive under .exe file.

REM defaults
set DEFAULT_SUM_HOME=C:\SAGUpdateManager

REM initial values
set SUM_HOME=%DEFAULT_SUM_HOME%
set SUM_USERNAME=
set SUM_PASSWORD=
set SUM_SERVER=
set WORKDIR=%~dps0
set JAVA=java
set ACCEPT_LICENSE=0
set THIS_SCRIPT=%WORKDIR%%0
set IMAGE_FILE=
set DEBUG=true
set REPO=
set PUBLISHED_REPO=
set SOURCE_DIR=
set PROXY_HOST=
set PROXY_PORT=
set PROXY_USERNAME=
set PROXY_PASSWORD=
set NON_PROXY_HOSTS=
set PROXY_PROTOCOL=
set IMAGE_FILE_WRITE=
set IMAGE_PLATFORM=
set AUTO_DETECT_PROXY=

echo.
echo Software AG Update Manager installation
echo.

if [%1] == [] goto check

:processOptions
set VALID=0
set p=%1
set p=%p:"=%
if "%p%" == "--help" goto usage
if "%p%" == "-h" goto usage
if "%p%" == "--accept-license" set ACCEPT_LICENSE=1& set VALID=1
if "%p%" == "-d" set SUM_HOME=%2& shift& set VALID=1
if "%p%" == "-u" set SUM_USERNAME=%2& shift& set VALID=1
if "%p%" == "-p" set SUM_PASSWORD=%2& shift& set VALID=1
if "%p%" == "-sumServer" set SUM_SERVER=%2& shift& set VALID=1
if "%p%" == "-i" set IMAGE_FILE=%2& shift& set VALID=1
if "%p%" == "-debug" set DEBUG=true& set VALID=1
if "%p%" == "-repo" set REPO=%2& shift& set VALID=1
if "%p%" == "-installFromRepo" set PUBLISHED_REPO=%2& shift& set VALID=1
if "%p%" == "-installFromSourceDir" set SOURCE_DIR=%2& shift& set VALID=1
if "%p%" == "-proxyHost" set PROXY_HOST=%2& shift& set VALID=1
if "%p%" == "-proxyPort" set PROXY_PORT=%2& shift& set VALID=1
if "%p%" == "-proxyUsername" set PROXY_USERNAME=%2& shift& set VALID=1
if "%p%" == "-proxyPassword" set PROXY_PASSWORD=%2& shift& set VALID=1
if "%p%" == "-proxyProtocol" set PROXY_PROTOCOL=%2& shift& set VALID=1
if "%p%" == "-nonProxyHosts" set NON_PROXY_HOSTS=%2& shift& set VALID=1
if "%p%" == "-createImageOnly" set IMAGE_FILE_WRITE=%2& shift& set VALID=1
if "%p%" == "-imagePlatform" set IMAGE_PLATFORM=%2& shift& set VALID=1
if "%p%" == "-createImage" set IMAGE_FILE_WRITE=%2& shift& set VALID=1& set FULL_IMAGE=yes
if "%p%" == "-autoDetectProxy" set AUTO_DETECT_PROXY=%2& shift& set VALID=1

if %VALID% == 0 if not "%p%" == "" (
  echo ERROR: Invalid option %p%
  goto usage
)
shift
if not "%1" == "" goto processOptions

:check
rem check parameters
rem check license agreement
if %ACCEPT_LICENSE% == 0 (
    echo.
    echo You must accept license agreement with --accept-license switch
    echo.
    goto usage
)

rem remove double quotes
set SUM_HOME=%SUM_HOME:"=%
rem remove trailing slash to allow installation into the current dir
if  %SUM_HOME:~-1%==\ set SUM_HOME=%SUM_HOME:~0,-1%
if  %WORKDIR:~-1%==\ set WORKDIR=%WORKDIR:~0,-1%

if exist "%SUM_HOME%" (
  for /f %%i in ('dir /b "%SUM_HOME%"') do (
    if not "%%i" == "" (
      if not "%%i" == "logs" (
        echo.
        echo ERROR: Target directory is not empty: "%SUM_HOME%"
        echo.
        goto usage
      )
    )
  )
)

set JRE_HOME=%WORKDIR%\jre

:checkJava

echo Checking java

if exist "%JRE_HOME%\bin\java.exe" (
  echo Found bootstrap java: !JRE_HOME!

  set JAVA="!JRE_HOME!\bin\java.exe"
) else (
  echo Will try local java
)

if not [%SOURCE_DIR%] == [] (
  set SOURCE_DIR=%SOURCE_DIR:"=%
  if not [!SOURCE_DIR!] == [] (
    if exist "!SOURCE_DIR!\components\jvm\jre\bin\java.exe" (
      set JAVA="!SOURCE_DIR!\components\jvm\jre\bin\java.exe"
    )
  )
)

%JAVA% -version && (
  echo Done checking java
) || (
  echo ERROR: No valid java found
  echo Install java and try again
  endlocal & exit /B 1
)

:install

if not exist "%WORKDIR%\SUMlauncher.jar" (
  echo ERROR: SUMlauncher.jar is not found
  endlocal & exit /B 2
)

set COMMAND=%JAVA% %JAVA_OPTIONS% -jar "%WORKDIR%\SUMlauncher.jar" -sumHome "%SUM_HOME%"

if not [%SUM_SERVER%] == [] (
  set SUM_SERVER=%SUM_SERVER:"=%
  if not [!SUM_SERVER!] == [] (
    set COMMAND=%COMMAND% -sumServer !SUM_SERVER!
  )
)

if not [%SUM_USERNAME%] == [] (
  set SUM_USERNAME=%SUM_USERNAME:"=%
  if not [!SUM_USERNAME!] == [] (
    if not [%SUM_PASSWORD%] == [] (
      set SUM_PASSWORD=%SUM_PASSWORD:"=%
      if not [!SUM_PASSWORD!] == [] (
        set COMMAND=%COMMAND% -username !SUM_USERNAME! -password !SUM_PASSWORD!
      )
    )
  )
)

if not [%IMAGE_FILE%] == [] (
  set IMAGE_FILE=%IMAGE_FILE:"=%
  if not [!IMAGE_FILE!] == [] (
    set COMMAND=%COMMAND% -installFromImage %IMAGE_FILE%
  )
)

if not [%IMAGE_FILE_WRITE%] == [] (
  set IMAGE_FILE_WRITE=%IMAGE_FILE_WRITE:"=%
  if not [!IMAGE_FILE_WRITE!] == [] (
    if not [!FULL_IMAGE!] == [] (
      set COMMAND=%COMMAND% -createImage %IMAGE_FILE_WRITE%
    ) else (
      set COMMAND=%COMMAND% -createImageOnly %IMAGE_FILE_WRITE%
    )
  )
)

if not [%IMAGE_PLATFORM%] == [] (
  set IMAGE_PLATFORM=%IMAGE_PLATFORM:"=%
  if not [!IMAGE_PLATFORM!] == [] (
    set COMMAND=%COMMAND% -imagePlatform "!IMAGE_PLATFORM!"
  )
)

if not [%DEBUG%] == [] (
  set DEBUG=%DEBUG:"=%
  if not [!DEBUG!] == [] (
    set COMMAND=%COMMAND% -debug true
  )
)

if not [%REPO%] == [] (
  set REPO=%REPO:"=%
  if not [!REPO!] == [] (
    set COMMAND=%COMMAND% -repo !REPO!
  )
)

if not [%PUBLISHED_REPO%] == [] (
  set PUBLISHED_REPO=%PUBLISHED_REPO:"=%
  if not [!PUBLISHED_REPO!] == [] (
    set COMMAND=%COMMAND% -installFromRepo !PUBLISHED_REPO!
  )
)

if not ["%SOURCE_DIR%"] == [""] (
  set SOURCE_DIR=%SOURCE_DIR:"=%
  if not [!SOURCE_DIR!] == [] (
    set COMMAND=%COMMAND% -installFromSourceDir "!SOURCE_DIR!"
  )
)

if not [%PROXY_HOST%] == [] (
  set PROXY_HOST=%PROXY_HOST:"=%
  if not [!PROXY_HOST!] == [] (
    set COMMAND=%COMMAND% -proxyHost "!PROXY_HOST!"
  )
)

if not [%PROXY_PORT%] == [] (
  set PROXY_PORT=%PROXY_PORT:"=%
  if not [!PROXY_PORT!] == [] (
    set COMMAND=%COMMAND% -proxyPort "!PROXY_PORT!"
  )
)

if not [%PROXY_USERNAME%] == [] (
  set PROXY_USERNAME=%PROXY_USERNAME:"=%
  if not [!PROXY_USERNAME!] == [] (
    set COMMAND=%COMMAND% -proxyUsername "!PROXY_USERNAME!"
  )
)

if not [%PROXY_PASSWORD%] == [] (
  set PROXY_PASSWORD=%PROXY_PASSWORD:"=%
  if not [!PROXY_PASSWORD!] == [] (
    set COMMAND=%COMMAND% -proxyPassword "!PROXY_PASSWORD!"
  )
)

if not [%PROXY_PROTOCOL%] == [] (
  set PROXY_PROTOCOL=%PROXY_PROTOCOL:"=%
  if not [!PROXY_PROTOCOL!] == [] (
    set COMMAND=%COMMAND% -proxyProtocol "!PROXY_PROTOCOL!"
  )
)

if not [%NON_PROXY_HOSTS%] == [] (
  set NON_PROXY_HOSTS=%NON_PROXY_HOSTS:"=%
  if not [!NON_PROXY_HOSTS!] == [] (
    set COMMAND=%COMMAND% -nonProxyHosts "!NON_PROXY_HOSTS!"
  )
)

if not [%AUTO_DETECT_PROXY%] == [] (
  set AUTO_DETECT_PROXY=%AUTO_DETECT_PROXY:"=%
  if not [!AUTO_DETECT_PROXY!] == [] (
    set COMMAND=%COMMAND% -autoDetectProxy %AUTO_DETECT_PROXY%
  )
)

if NOT EXIST "%SUM_HOME%" (
  echo "%SUM_HOME%" does not exist
  mkdir "%SUM_HOME%"
  set EL=%ERRORLEVEL%
  if "!EL!" neq "0" (
    echo Cannot create target directory "%SUM_HOME%"
    endlocal & exit /b !EL!
  )
)

echo Installing into "%SUM_HOME%"

set COMMAND=%COMMAND% -withoutUI
%COMMAND%

set EL=%ERRORLEVEL%
if "%EL%" == "16" (
  goto wait_launcher
)

if "%EL%" neq "0" (
  if "%EL%" neq "170" (
      echo ERROR: Installation failed
      echo Please check Update Manager installer log "%SUM_HOME%\logs\launcher.log"
      endlocal & exit /B %EL%
  )
)

:wait_launcher
pushd "%SUM_HOME%\bin"
:wait
echo Installing SUM bundles...
if exist .\.lock (
  ping -n 5 -w 1 0.0.0.1 >nul 2>&1
  goto wait
)

:wait_exit
if exist .\exit_code.txt (
  for /f "tokens=1,2*" %%i in (.\exit_code.txt) do (
    if "%%i" == "16" (
      ping -n 5 -w 1 0.0.0.1 >nul 2>&1
      goto wait_exit
    ) else if "%%i" == "170" (
      del .\exit_code.txt
      goto done
    ) else if "%%i" == "0" (
      del .\exit_code.txt
      goto done
    )
    echo Failed: %%j
    endlocal & popd & exit /b %%i
  )
) else (
  goto wait
)

:done
popd

echo.
echo ####
echo #### Installation of Update Manager completed
echo ####
echo.

:cleanup
if exist "%WORKDIR%\jre" (
    rmdir /S /Q "%WORKDIR%\jre" 2>&1 >nul
)
endlocal & exit /B 0

:usage
echo Usage: %~n0 [options...]
echo    --accept-license   Accept license agreement
echo    http://documentation.softwareag.com/legal/general_license.txt
echo.
echo Options:
echo    -h,--help                    This usage help
echo    -d C:\install\dir            Target installation directory
echo                                 (default %DEFAULT_SUM_HOME%)
echo    -i image-file                Path to Update Manager image
echo    -proxyHost host              proxy host, if using proxy
echo    -proxyPort port              proxy host, if using proxy
echo    -proxyUsername username      proxy username, if using proxy
echo    -proxyPassword password      proxy password, if using proxy
echo    -proxyProtocol protocol      HTTP or SOCKS
echo    -autoDetectProxy true        Autodetection of system proxies
echo.
echo Examples:
echo.
echo %THIS_SCRIPT% --accept-license -d C:\SUM
echo.
echo %THIS_SCRIPT% --accept-license -d C:\SUM -i C:\SUMimage.zip
echo.
echo %THIS_SCRIPT% --accept-license -d C:\SUM -proxyHost 192.168.0.1 -proxyPort 8000 -proxyUsername user -proxyPassword pass -proxyProtocol HTTP
echo.
echo %THIS_SCRIPT% --accept-license -d C:\SUM -autoDetectProxy true
echo.

endlocal & exit /B 1

if ERRORLEVEL 1 exit /B %ERRORLEVEL%
endlocal & exit /B 0
