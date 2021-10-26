rem ---- SET INITIALLY BY THE INSTALLER ----
rem ############################################################################
rem #
rem # The following parameters must not be modified by users.
rem # 
rem ############################################################################

SET OSGI_INSTALL_AREA=C:\temp\SAGEM\install\profile
SET OSGI_CONFIGURATION_AREA=%OSGI_INSTALL_AREA%\configuration
SET JAVA_BOOT_CLASSPATH=C:\temp\SAGEM\common\runtime\bundles\platform\eclipse\plugins\com.softwareag.platform.jaas.proxy_10.7.0.0000-0635.jar;C:\temp\SAGEM\common\runtime\bundles\platform\eclipse\plugins\com.softwareag.platform.logging.jul.proxy_10.7.0.0000-0635.jar
SET JAVA_SYSTEM_CLASSPATH=C:\temp\SAGEM\common\runtime\bundles\platform\eclipse\plugins\com.softwareag.platform.bootstrap_10.7.0.0000-0635.jar;C:\temp\SAGEM\common\runtime\bundles\platform\eclipse\plugins\org.eclipse.equinox.launcher_1.5.300.v20190213-1655.jar

SET WRAPPER="C:\temp\SAGEM\common\bin\wrapper.exe"
SET WRAPPER_CONF="%OSGI_CONFIGURATION_AREA%\wrapper.conf"

SET LOG4J_PROPS=-Dlog4j2.disable.jmx=true -Djava.util.logging.manager=com.softwareag.platform.jul.proxy.ProxyLogManager -DLog4jContextSelector=org.apache.logging.log4j.core.selector.BasicContextSelector -Dlog4j.configurationFile="%OSGI_INSTALL_AREA%\configuration\logging\log4j2.properties"

rem getting anchor file path from wraper.conf file
set TARGET=wrapper.anchorfile
FOR /F "usebackq tokens=1,2* delims==" %%A IN (%WRAPPER_CONF%) DO IF "%%A"=="%TARGET%" set WRAPPER_ANCHOR="%%B"
rem replace / path separator with \
set WRAPPER_ANCHOR=%WRAPPER_ANCHOR:/=\%

rem we cannot remove quotes because if placeholder is empty then script will start.
rem to return error because we unset not set variable.
if "%WORK_DIR%"=="" (
   SET WORK_DIR=""
)
rem unsets WORK_DIR if it has for value "".
if %WORK_DIR%=="" (
   SET WORK_DIR=
)

SET SERVICE_NAME=sagwis_7.1
SET WINDOW_TITLE=Software AG Provision Application (7)
SET TELNET_CMD=telnet
if "%JAVA_EXEC%"=="" ( 
    SET JAVA_EXEC="C:\temp\SAGEM\jvm\jvm\bin\java"
)
SET PATH="C:\temp\SAGEM\common\security\ssx_64\bin";%PATH%

if "%JAVA_SYSPROPS%"=="" (
  set JAVA_SYSPROPS=-Dosgi.install.area="%OSGI_INSTALL_AREA%" -Dosgi.configuration.area="%OSGI_CONFIGURATION_AREA%" -Declipse.ignoreApp=%ECLIPSE_IGNORE_APP% -Dosgi.noShutdown=true
)
SET JAVA_SYSPROPS=%JAVA_SYSPROPS% %LOG4J_PROPS%

rem After asking platform to stop gracefully wait this much
set SHUTDOWN_TIMEOUT=90
rem If platform does not stop send stop signal to process and wait this much
rem After that kill the process forcefully
set JVM_EXIT_TIMEOUT=90

rem ############################################################################
rem #
rem # The following parameters can be modified by users.
rem # 
rem ############################################################################

if "%JAVA_MIN_MEM%"=="" (
  set JAVA_MIN_MEM=256M
)

if "%JAVA_MAX_MEM%"=="" (
  set JAVA_MAX_MEM=512M
)

if "%RUN_CUSTOM_CONF%"=="" (
  set RUN_CUSTOM_CONF=%~dp0custom_setenv.bat
)

if exist "%RUN_CUSTOM_CONF%" (
  call "%RUN_CUSTOM_CONF%"
)
