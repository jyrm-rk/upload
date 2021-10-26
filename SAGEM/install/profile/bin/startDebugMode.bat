@echo off
setlocal
rem ###########################################################################
rem #                                                                         #
rem # Debug script that start profile in debug mode listening on default      #
rem # port 10033 and waiting for debugger to attach                           #
rem #                                                                         #
rem # Custom debug port can be set with command line argument address <port>  #
rem # Suspend mode can be set with command line argument suspend <y/n>        #
rem #                                                                         #
rem # For example: 'startDebugMode.bat address 8787 suspend n'                #
rem ###########################################################################

rem ##########################################################################
rem # The environment variable DEBUG_PORT set port on which profile instance #
rem # is listening for debugger to attach. This environment variable can be  #
rem # overridden from command line argument 'address <port>'                 #
rem ##########################################################################
set DEBUG_PORT=10033

rem ##########################################################################
rem # The environment variable SUSPEND_MODE set if JVM should wait for       #
rem # debugger to attach. This environment variable can be overridden from   #
rem # command line argument 'suspend <y/n>'                                  #
rem ##########################################################################
set SUSPEND_MODE=y

if "%RUN_CUSTOM_CONF%"=="" (
  set RUN_CUSTOM_CONF=%~dp0custom_setenv.bat
)

if exist "%RUN_CUSTOM_CONF%" (
    call "%RUN_CUSTOM_CONF%"
)

if not "%ADD_ARGS%"=="" (
  set ADD_ARGS=
)

rem ##########################################################################
rem # Store the current working directory.  The shift command from the arg   #
rem # parsing loop destroys the original value                               #
rem ##########################################################################
set _WD=%~dp0

:loop
if not "%1"=="" (
  if "%1"=="address" (
     if not "%SKIP_PORT%"=="y" (
        if not "%2"=="" (
           set DEBUG_PORT=%2
        )
        shift
        set SKIP_PORT=y
        goto end_loop
     )
  )
  
  if "%1"=="suspend" (
     if not "%SKIP_SUSPEND%"=="y" (
        if not "%2"=="" (
           set SUSPEND_MODE=%2
        )
        shift
        set SKIP_SUSPEND=y
        goto end_loop
     )
  )  

  if "%ADD_ARGS%"=="" (
      set ADD_ARGS=%1
  ) else (
      set ADD_ARGS=%ADD_ARGS% %1
  )
  
  :end_loop
  shift  
  goto loop
)

rem if wrapper is used we pass debug parameter as environment variable
if "%USE_WRAPPER%"=="yes" (
   set TANUKI_ARGS=wrapper.java.additional.500=-Xdebug wrapper.java.additional.501=-Xrunjdwp:transport=dt_socket,server=y,suspend=%SUSPEND_MODE%,address=%DEBUG_PORT%
   rem On windows profile should be always started as regular process for debugging
   set STARTUP_MODE=console
) else (
   set DEBUG_ARG=-Xdebug -Xrunjdwp:transport=dt_socket,server=y,suspend=%SUSPEND_MODE%,address=%DEBUG_PORT%
)

call "%_WD%startup.bat" %ADD_ARGS%

set EL=%ERRORLEVEL%
endlocal & set EL=%EL%
exit /b %EL%
