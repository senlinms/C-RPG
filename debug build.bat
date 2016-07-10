@echo off
REM    gcc -Wall -Werror main.c -s -m32 -o game.exe
gcc *.c -g -static -m32 -std=c11 -w -o debug_game.exe -DDEBUG
pause