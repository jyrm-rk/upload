@echo off

setlocal

for /f "tokens=*" %%i in ('dir C:\temp\SAGEM\common\runtime\bundles\platform\eclipse\plugins\com.softwareag.security.sin.utils_10.*.jar /b') DO (
  set SIN_UTILS=%%i
)
for /f "tokens=*" %%i in ('dir C:\temp\SAGEM\common\runtime\bundles\platform\eclipse\plugins\com.softwareag.security.sin.common_10.*.jar /b') DO (
  set SIN_COMMON=%%i
)

SET CLASSPATH=.;C:\temp\SAGEM\common\runtime\bundles\platform\eclipse\plugins\%SIN_COMMON%;C:\temp\SAGEM\common\runtime\bundles\platform\eclipse\plugins\%SIN_UTILS%
C:\temp\SAGEM\jvm\jvm\bin\java com.softwareag.security.tools.internaluserrepo.InternalUsersRepoTool %*

endlocal
