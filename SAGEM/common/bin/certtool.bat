@echo off

setlocal

SET CLASSPATH=.

rem Set default values
SET DEFAULT_PATH=C:\temp\SAGEM\common\conf
SET KEYTOOL_PATH=C:\temp\SAGEM\jvm\jvm\bin\keytool

SET KEYSTORE_KEY_ALIAS=default
SET KEYSTORE_FILE=%DEFAULT_PATH%\%KEYSTORE_KEY_ALIAS%.jks
SET KEYSTORE_TYPE=jks
SET KEYSTORE_PASSWORD=manage

SET TRUSTED_CERT_ALIAS=default
SET TRUSTSTORE_FILE=%DEFAULT_PATH%\%TRUSTED_CERT_ALIAS%_truststore.jks
SET TRUSTSTORE_TYPE=jks
SET TRUSTSTORE_PASSWORD=manage

SET X509_FILE=%DEFAULT_PATH%\%KEYSTORE_KEY_ALIAS%.cer

SET VALIDITY=1826
SET KEY_ALGORITHM=RSA
SET SIG_ALGORITHM=SHA512withRSA
SET KEY_SIZE=1024

SET OU=ssos

if "%1" == "-usage" (
	echo.
	echo Available commands are:
	echo.
	echo -listkeystore	Lists the entries in the keystore. Default is default.jks.
	echo -listtruststore	Lists the entries in the truststore. Default is default_truststore.jks.
	echo -add		Adds a trusted certificate to the truststore. Default_truststore.jks is used, if other is not specified.
	echo -delete		Deletes a trusted certificate from the truststore. Default_truststore.jks is used, if other is not specified.
	echo -generate	Generates a key pair and exports the public information as .cer file. Defaults are default.jks and default.cer file.
	echo -usage		Prints available commands.
	echo.
	goto end
)

if "%1" == "-listkeystore" goto listkeystore

if "%1" == "-listtruststore" goto listtruststore

if "%1" == "-add" goto addtrustedcert

if "%1" == "-delete" goto deletetrustedcert

if "%1" == "-generate" goto generatecert

goto err

:listkeystore
	SET /P USER_KEYSTORE_FILE=Please enter the keystore file path for listing the keys:
	SET /P USER_KEYSTORE_PASSWORD= Please enter the keystore password:
	
	if "%USER_KEYSTORE_FILE%"=="" (
		set USER_KEYSTORE_FILE=%KEYSTORE_FILE%
	)
	
	if "%USER_KEYSTORE_PASSWORD%"=="" (
		set USER_KEYSTORE_PASSWORD="%KEYSTORE_PASSWORD%"
	)
	
	%KEYTOOL_PATH% -list -v -keystore %USER_KEYSTORE_FILE% -storepass %USER_KEYSTORE_PASSWORD%
	
	goto end

:listtruststore
	SET /P USER_TRUSTSTORE_FILE=Please enter the truststore file path for listing the keys:
	SET /P USER_TRUSTSTORE_PASSWORD= Please enter the truststore password:
	
	if "%USER_TRUSTSTORE_FILE%"=="" (
		set USER_TRUSTSTORE_FILE=%TRUSTSTORE_FILE%
	)
	
	if "%USER_TRUSTSTORE_PASSWORD%"=="" (
		set USER_TRUSTSTORE_PASSWORD="%TRUSTSTORE_PASSWORD%"
	)
	
	%KEYTOOL_PATH% -list -v -keystore %USER_TRUSTSTORE_FILE% -storepass %USER_TRUSTSTORE_PASSWORD%
	
	goto end

:addtrustedcert

	SET /P USER_TRUSTED_CERT_ALIAS=Please enter the alias of the certificate to be added [otherwise default %TRUSTED_CERT_ALIAS% will be used]:
	SET /P USER_X509_FILE= Please enter the path to the certificate file to be added:
	SET /P USER_TRUSTSTORE_FILE=Please enter the truststore file path to add the certificate:
	SET /P USER_TRUSTSTORE_PASSWORD= Please enter the truststore password:
	SET /P USER_TRUSTSTORE_TYPE= Please enter the truststore type:
	
	if "%USER_TRUSTED_CERT_ALIAS%"=="" (
		set USER_TRUSTED_CERT_ALIAS=%TRUSTED_CERT_ALIAS%
	)
	
	if "%USER_X509_FILE%"=="" (
		set USER_X509_FILE=%X509_FILE%
	)
	
	if "%USER_TRUSTSTORE_FILE%"=="" (
		set USER_TRUSTSTORE_FILE=%TRUSTSTORE_FILE%
	)
	
	if "%USER_TRUSTSTORE_PASSWORD%"=="" (
		set USER_TRUSTSTORE_PASSWORD=%TRUSTSTORE_PASSWORD%
	)
	
	if "%USER_TRUSTSTORE_TYPE%"=="" (
		set USER_TRUSTSTORE_TYPE=%TRUSTSTORE_TYPE%
	)

	%KEYTOOL_PATH% -importcert -alias %USER_TRUSTED_CERT_ALIAS% -file %USER_X509_FILE% -keystore %USER_TRUSTSTORE_FILE% -storepass %USER_TRUSTSTORE_PASSWORD% -storetype %USER_TRUSTSTORE_TYPE%
	
	echo Note. You should update your SSOS configuration for the changes to take place.
	
	goto end
	
:deletetrustedcert

	SET /P USER_TRUSTED_CERT_ALIAS=Please enter the alias of the certificate to be deleted [required]:
	
	if "%USER_TRUSTED_CERT_ALIAS%"=="" (
		echo.
		echo Incorrect syntax. Alias is required.
		goto end
	)
	
	SET /P USER_TRUSTSTORE_FILE=Please enter the truststore file path to delete the certificate from:
	SET /P USER_TRUSTSTORE_PASSWORD= Please enter the truststore password:
	SET /P USER_TRUSTSTORE_TYPE= Please enter the truststore type:
	
	if "%USER_TRUSTSTORE_FILE%"=="" (
		set USER_TRUSTSTORE_FILE=%TRUSTSTORE_FILE%
	)
	
	if "%USER_TRUSTSTORE_PASSWORD%"=="" (
		set USER_TRUSTSTORE_PASSWORD=%TRUSTSTORE_PASSWORD%
	)
	
	if "%USER_TRUSTSTORE_TYPE%"=="" (
		set USER_TRUSTSTORE_TYPE=%TRUSTSTORE_TYPE%
	)

	%KEYTOOL_PATH% -delete -alias %USER_TRUSTED_CERT_ALIAS% -keystore %USER_TRUSTSTORE_FILE% -storepass %USER_TRUSTSTORE_PASSWORD% -storetype %USER_TRUSTSTORE_TYPE%

	goto end
	
:generatecert

	SET /P USER_KEYSTORE_KEY_ALIAS=Please enter the alias for the generated key pair:
	SET /P USER_KEYSTORE_FILE=Please enter the keystore file path for generating the key pair:
	SET /P USER_KEYSTORE_PASSWORD= Please enter the keystore password:
	SET /P USER_KEYSTORE_TYPE= Please enter the keystore type:

	SET /P USER_CN=Please enter the common name of the client you want to create a Cert for [required]:
	
	if "%USER_CN%"=="" (
		echo.
		echo Incorrect syntax. Common name is required.
		goto end
	)
	
	SET /P USER_OU=Please enter your organizational unit:
	SET /P USER_O=Please enter your organization name:
	SET /P USER_L=Please enter City or location:
	SET /P USER_C=Please enter a two letter country code for your location:

	
	if "%USER_OU%"=="" (
		set DNAME="CN=%USER_CN%, OU=%OU%
	) else (
		set DNAME="CN=%USER_CN%, OU=%USER_OU%
	)
	
	if not "%USER_O%"=="" (
		set DNAME=%DNAME%, O=%USER_O%
	)
	
	if not "%USER_L%"=="" (
		set DNAME=%DNAME%, L=%USER_L%
	)
	
	if not "%USER_C%"=="" (
		set DNAME=%DNAME%, C=%USER_C%
	)
	
	set DNAME=%DNAME%"
	
	if "%USER_KEYSTORE_KEY_ALIAS%"=="" (
		set USER_KEYSTORE_KEY_ALIAS=%KEYSTORE_KEY_ALIAS%
	)
	
	if "%USER_KEYSTORE_FILE%"=="" (
		set USER_KEYSTORE_FILE=%KEYSTORE_FILE%
	)
	
	if "%USER_KEYSTORE_PASSWORD%"=="" (
		set USER_KEYSTORE_PASSWORD="%KEYSTORE_PASSWORD%"
	)
		
	REM ***********************************************************************************
	REM * RGHOGI-5586 - we will use the same password for the key due to SSOS limitation. *
	REM ***********************************************************************************
	set USER_KEYSTORE_KEY_PASSWORD="%USER_KEYSTORE_PASSWORD%"
	
	if "%USER_KEYSTORE_TYPE%"=="" (
		set USER_KEYSTORE_TYPE="%KEYSTORE_TYPE%"
	)
	
	if exist "%USER_KEYSTORE_FILE%" (
		goto deletefile 
	) else (
		goto generatekeys
	)
	
:deletefile
		echo File %USER_KEYSTORE_FILE% exists and will be deleted!
		SET /P DELETE_FILE=Please enter q if you want to quit:

		if NOT "%DELETE_FILE%" == "q" set del1=y
		if NOT "%DELETE_FILE%" == "Q" set del2=y
		 
		if NOT "%del1%%del2%" == "y" (
			del %USER_KEYSTORE_FILE%
			goto generatekeys
		) else (
			goto notexecuted
		)
	
:generatekeys
	%KEYTOOL_PATH% -genkeypair -alias %USER_KEYSTORE_KEY_ALIAS% -keystore %USER_KEYSTORE_FILE% -storepass %USER_KEYSTORE_PASSWORD% -validity %VALIDITY% -keypass %USER_KEYSTORE_KEY_PASSWORD% -keyalg %KEY_ALGORITHM% -keysize %KEY_SIZE% -sigalg %SIG_ALGORITHM% -dname %DNAME% -storetype %USER_KEYSTORE_TYPE% 
	rem export the created certificate
	SET /P USER_X509_FILE=Please enter file name and location for saving the public part of the certificate [otherwise default is %DEFAULT_PATH%\%USER_KEYSTORE_KEY_ALIAS%.cer]:"

	if "%USER_X509_FILE%"=="" (
		set USER_X509_FILE=%X509_FILE%
	)
	
	%KEYTOOL_PATH% -exportcert -alias %USER_KEYSTORE_KEY_ALIAS% -file %USER_X509_FILE% -keystore %USER_KEYSTORE_FILE% -storepass %USER_KEYSTORE_PASSWORD% -storetype %USER_KEYSTORE_TYPE%
	
	echo Note. You should update your SSOS configuration for the changes to take place.
	
	goto end
	
:err
	echo Unavailable command.
	goto end
	
:notexecuted
	echo Quit operation.
	goto end
	
:end
	echo Command %1% executed.
	
endlocal
