REM Builds student submission for hw1; requires Egg built and g++ installed

.\egg.exe compile hw1.egg hw1.hpp
if %errorlevel% neq 0 exit /b %errorlevel%
g++ -std=c++14 -o hw1 hw1.cpp
