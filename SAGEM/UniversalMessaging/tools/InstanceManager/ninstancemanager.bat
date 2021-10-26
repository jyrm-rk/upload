@echo off
TITLE UM Instance Manager

set INSTALL_DIR=%~dp0..\..\..
set UM_HOME_DIR=%INSTALL_DIR%\UniversalMessaging
set IM_HOME_DIR=%~dp0

set JAVA_EXEC="%INSTALL_DIR%\jvm\jvm\bin\java"
set PATH="%IM_HOME_DIR%";"%INSTALL_DIR%\jvm\jvm\lib";%PATH%

set JAVA_CLASSPATH="%UM_HOME_DIR%\lib\ninstancemanager.jar;%UM_HOME_DIR%\lib\nClient.jar;%UM_HOME_DIR%\lib\activation-api-1.2.0.jar;%UM_HOME_DIR%\lib\jaxb-api-2.3.0.jar;%UM_HOME_DIR%\lib\jaxb-core-2.3.0.jar;%UM_HOME_DIR%\lib\jaxb-impl-2.3.0.jar;%UM_HOME_DIR%\lib\jaxb-xjc-2.3.0.jar;%UM_HOME_DIR%\lib\nServer.jar;%INSTALL_DIR%\install\jars\InstallerUtils-ALL-Any.jar;%INSTALL_DIR%\install\jars\DistMan.jar;%INSTALL_DIR%\install\jars\CustomInstall-ALL-Any.jar;%INSTALL_DIR%\install\jars\CustomInstall-W32-Any.jar;%INSTALL_DIR%\install\jars\CustomInstall-W64-Any.jar;%INSTALL_DIR%\install\jars\wMInstToolsAPI-ALL-Any.jar;%INSTALL_DIR%\install\jars\wMInstTools-ALL-Any.jar;%INSTALL_DIR%\install\jars\OSGiProfilesAPI-ALL-Any.jar;%INSTALL_DIR%\install\jars\OSGiProfiles-ALL-Any.jar;%INSTALL_DIR%\install\jars\NUMInstallMessages-ALL-Any.jar"
set JAVA_OPTS=-Djava.library.path="%UM_HOME_DIR%\tools\InstanceManager;%INSTALL_DIR%\jvm\jvm\lib" -DCREATE_SHORTCUTS=true -DWORKING_DIR="%IM_HOME_DIR%/"

%JAVA_EXEC% -cp %JAVA_CLASSPATH% %JAVA_OPTS% com.pcbsys.foundation.utils.fInstanceManager %*
