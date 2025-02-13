@echo off
set path=%1
start /b node ./nanasm/index.js %path%
start /b ./build/bin/nanvm.exe ./nanasm/temp.nb
