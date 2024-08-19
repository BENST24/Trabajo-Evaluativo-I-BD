@echo off

if not exist "bin" (
    mkdir "bin"
)

g++ -Iinclude -Llib -o bin\app.exe src\Database.cpp src\Game.cpp src\GameMapper.cpp src\Menu.cpp src\User.cpp src\UserGameAssociation.cpp src\UserMapper.cpp main.cpp -lsqlite3

if %ERRORLEVEL% NEQ 0 (
    echo Compilation failed.
) else (
    echo Compilation succeeded.
)