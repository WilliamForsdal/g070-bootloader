scons
if %errorlevel% neq 0 exit /b %errorlevel%
ST-LINK_CLI.exe -c UR -P "build\bin.srec" -V -Rst