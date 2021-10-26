@echo off
rem  ###########################################################################
rem                                                                            #
rem  migrate.bat : Migrate Software AG Common Platform data            		   #
rem                                                                            #
rem  This script is designed to work with Java VM's that conform to the        #
rem  command-line conventions of Sun Microsystems (TM) Java Development Kit    #
rem  or Java Runtime Environment.                                              #
rem                                                                            #
rem  (c) Software AG 2017                                                      #
rem                                                                            #
rem  ###########################################################################

SETLOCAL

SET _DIR=%~dp0
SET OSGI_DIR=%_DIR%..

set PRODUCT_DATA_PROVIDER=com.softwareag.platform.migration.dataprovider.PlatformMigratorAppDataProviderImpl
set MIGRATOR_PRODUCT_NAME="Software AG Common Platform"

rem ##### Following variable is used for locating Java #####
set JAVA_DIR=%OSGI_DIR%\..\..\..\jvm\jvm

echo JAVA_DIR is %JAVA_DIR%

if "%1" == "-help" (
	goto usage
)

rem  ################################

SET JAVA_HOME=%JAVA_DIR%
echo JAVA_HOME is %JAVA_HOME%

set JAVA_MIN_MEM=256M
set JAVA_MAX_MEM=1024M
set JAVA_MAX_PERM_SIZE=256M
set JAVA_EXE="%JAVA_HOME%\bin\java.exe"

set SAVED_CP=%CLASSPATH%

set CLASSPATH="%OSGI_DIR%\..\..\lib\ext\log4j\log4j-12api.jar"
set CLASSPATH=%CLASSPATH%;"%OSGI_DIR%\..\..\lib\ext\log4j\log4j-api.jar"
set CLASSPATH=%CLASSPATH%;"%OSGI_DIR%\..\..\lib\ext\log4j\log4j-core.jar"
set CLASSPATH=%CLASSPATH%;"%OSGI_DIR%\..\..\lib\ext\log4j\log4j-jcl.jar"
set CLASSPATH=%CLASSPATH%;"%OSGI_DIR%\..\..\lib\wm-is-migration-framework.jar"
set CLASSPATH=%CLASSPATH%;"%OSGI_DIR%\..\..\lib\wm-isclient.jar"

set CLASSPATH=%CLASSPATH%;"%OSGI_DIR%\..\..\lib\migrate\*"
set CLASSPATH=%CLASSPATH%;"%OSGI_DIR%\..\..\..\install\jars\DistMan.jar"

set CLASSPATH=%CLASSPATH%;"%OSGI_DIR%\bin\platform-migration.jar"
set CLASSPATH=%CLASSPATH%;"%OSGI_DIR%\lib\*"

title Software AG Common Platform Migration Utility

%JAVA_EXE% -Dwatt.migrate.product.dataProvider=%PRODUCT_DATA_PROVIDER% ^
		   -Dwatt.migrate.product.name=%MIGRATOR_PRODUCT_NAME% ^
		   -Dwatt.installer.migrate.destDir="%OSGI_DIR%\..\..\.." ^
           -Dlog4j.configurationFile="%_DIR%\log4j2.properties" ^
           -ms%JAVA_MIN_MEM% -mx%JAVA_MAX_MEM% -classpath %CLASSPATH% ^
            com.wm.app.b2b.server.migrate.cmd.CmdLineToolMigrationDriver %*
           
set RETURN_VALUE=%ERRORLEVEL%

rem 
rem restore original classpath 
rem
set CLASSPATH=%SAVED_CP%
GOTO :done

:usage
echo  Usage: migrate.bat [options]
echo  options
echo        -srcDir	        Full path to root directory of old Software AG installation.
echo        -srcFile         Full path to ZIP file containing old product installation.
echo        -importFile      migrate^<old_release^>sbs.dat file containing default migration settings.
echo        -silent true    Runs the migration utility without prompting for user input.
GOTO :done

:done

exit /b %RETURN_VALUE%
ENDLOCAL
