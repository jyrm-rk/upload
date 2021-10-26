rem ---- SET INITIALLY BY THE INSTALLER ----
rem ###########################################################
rem #                                                         #
rem # The following parameters must not be modified by users. #
rem #                                                         #
rem ###########################################################
SET OSGI_INSTALL_AREA=C:\temp\SAGEM\install\profile
SET OSGI_CONFIGURATION_AREA=%OSGI_INSTALL_AREA%\configuration

rem ########################################################################
rem # The environment variable USE_WRAPPER changes the way profile instance 
rem # is started. 
rem # Values:
rem #     no    - profile instance is started by pure Java call
rem #     yes   - Tanuki Wrapper is used to launch the profile instance
if "%USE_WRAPPER%"=="" (
	SET USE_WRAPPER=no
)

rem #########################################################################
rem # The environment variable STARTUP_MODE changes the default startup mode
rem # of this profile instance if it is installed as a system service.
rem # Values:
rem #     service    - start the service, if any
rem #     console    - start as a regular process, but only if
rem #                  the service is not already running
if "%STARTUP_MODE%"=="" (
   SET STARTUP_MODE=service
)

rem ###############################################################################
rem # The environment variable BLOCKING_SCRIPT changes behaviour of startup script
rem # when STARTUP_MODE is set to "console" or wrapper is used
rem # Values:
rem #     no    - startup script is non-blocking
rem #     yes   - startup script is blocking
if "%BLOCKING_SCRIPT%"=="" (
   SET BLOCKING_SCRIPT=no
)
rem # set eclipse ignore application property, default value is true
set ECLIPSE_IGNORE_APP=true