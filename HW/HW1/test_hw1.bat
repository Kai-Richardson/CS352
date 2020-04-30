REM Tests student submission for hw1; requires Egg and student submission built and g++ installed

g++ -std=c++14 -o test_hw1 test_hw1.cpp 
if %errorlevel% neq 0 exit /b %errorlevel%
.\test_hw1.exe