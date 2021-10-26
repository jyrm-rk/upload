@echo off
setlocal EnableDelayedExpansion

set SETENV_SCRIPT="%~dp0..\..\..\install\bin\setenv.bat"
if exist %SETENV_SCRIPT% (
	call %SETENV_SCRIPT%
)

if defined JAVA_HOME (
	set JAVA="%JAVA_HOME%\bin\java"
) else (
	where java > NUL 2>&1 && set JAVA=java
	if not defined JAVA (
		echo Java not found!
		exit /b 1
	)
)

REM make sure CLASSPATH never comes from the environment
set CLASSPATH=
for  %%i in ("%~dp0..\lib\*.jar" "%~dp0..\..\..\common\lib\ext\log4j\*.jar" "%~dp0..\..\..\common\lib\wm-is-migration-framework.jar" "%~dp0..\..\..\common\lib\wm-isclient.jar" "%~dp0..\..\..\common\lib\ext\enttoolkit.jar" "%~dp0..\..\..\common\lib\wm-scg-core.jar" "%~dp0..\..\..\common\lib\wm-scg-security.jar" "%~dp0..\..\..\common\lib\wm-g11nutils.jar" "%~dp0..\..\..\common\lib\migrate\*" "%~dp0..\..\..\install\jars\DistMan.jar") do (
	if defined CLASSPATH (
		set CLASSPATH=!CLASSPATH!;"%%i"
	) else (
		set CLASSPATH="%%i"
	)
)

if "%~1" == "-help" (
	goto usage
) 

set MIGRATE_OPTS=-Dlog4j.configurationFile="%~dp0.\log4j2.properties" -Dwatt.migrate.product.name="Platform Manager" -Dwatt.migrate.product.bundle.name=com.softwareag.plm.spm.migrator.messages -Dwatt.migrate.product.migrators.file=migrators.cnf -Dwatt.migrate.product.dataProvider=com.softwareag.plm.spm.migrator.cmd.SPMAppDataProvider -Dwatt.installer.migrate.destDir=..\..\..

%JAVA% %MIGRATE_OPTS% -classpath %CLASSPATH% com.softwareag.plm.spm.migrator.cmd.SPMCmdLineToolMigrationDriver %*
exit /b %ERRORLEVEL%

:usage
echo  Usage: migrate.bat [options]
echo  options
echo		-srcDir		Root directory of the Platform Manager you are migrating from.
echo		-destDir	Destination directory of the Platform Manager you are migrating to.
echo		-srcVersion	Version of the source Platform Manager. 
echo            		Supported values are true or false.		
echo		-silent		Specifies whether migration will be executed in the silent mode.
echo            		Supported values are true or false.		
echo		-importFile	Specifies file path containing migration settings.
echo		-srcFile	Specifies archive file path containing configuration and packages of the source Platform Manager.