@ECHO OFF
REM -----------------------------------------------------------------------
REM
REM Environment settings for the Common Libraries for OpenSSL 10.7
REM
REM -----------------------------------------------------------------------
REM Copyright (c) 2017-2020 Software AG, Darmstadt, Germany and/or
REM Software AG USA Inc., Reston, VA, USA, and/or its subsidiaries and/or
REM its affiliates and/or their licensors.
REM
REM Use, reproduction, transfer, publication or disclosure is prohibited except
REM as specifically provided for in your License Agreement with Software AG.
REM -----------------------------------------------------------------------
REM If the environment variable TLSDIR is set ensure it points to
REM the root of the installation directory.
REM
REM Otherwise review the setup below before using this script.
REM
REM Then call this script to include the libraries
REM in the current environment's search paths, e.g. like:
REM C:\SoftwareAG> call common\security\openssl\extras\tlsenv.bat
REM
REM Set the environment variable SAGENV_VERBOSE to any non-empty value
REM in order to get verbose output while the script executes.
REM -----------------------------------------------------------------------

CALL :SSLECHO Setting up environment for Common Libraries for OpenSSL 10.7 ...

IF "%TLSDIR%"=="" (
  SET TLSDIR=C:\temp\SAGEM\common\security\openssl32
)
CALL :SSLECHO TLSDIR=%TLSDIR%

IF "%OPENSSL_CONF%"=="" SET OPENSSL_CONF=%TLSDIR%\openssl.cnf
CALL :SSLECHO OPENSSL_CONF=%OPENSSL_CONF%

IF "%SSL_CERT_FILE%"=="" SET SSL_CERT_FILE=%TLSDIR%\cert.pem
CALL :SSLECHO SSL_CERT_FILE=%SSL_CERT_FILE%

ECHO %Path%|FIND /I "%TLSDIR%" >NUL
IF NOT ERRORLEVEL 1 GOTO DONE

SET Path=%TLSDIR%\bin;%Path%

:DONE
CALL :SSLECHO Path=%Path%
CALL :SSLECHO Finished.

REM reset errorlevel
EXIT /B 0

:SSLECHO
IF NOT "%SAGENV_VERBOSE%"=="" ECHO [SSX_TLSENV] %*
