@echo off

echo Copying data...
mkdir release
cd release
mkdir data
cd ..

robocopy data release/data /E

pause