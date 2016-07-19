@echo off
del game[release].exe
REM    gcc -Wall -Werror main.c -s -m32 -o game.exe

cproto *.c > proto.h
gcc *.c -static -m32 -std=c11 -w -o game[release].exe
pause