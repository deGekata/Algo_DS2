@echo off
cmake -S . -B Build -G "MinGW Makefiles"
cd .\Build\
make all
cd ..