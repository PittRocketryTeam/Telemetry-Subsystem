@echo off

IF "%1"=="" GOTO Build
IF "%1"=="clean" GOTO Clean

:Build
javac *.java
GOTO End

:Clean
del *.class
GOTO End

:End
