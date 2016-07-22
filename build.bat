@echo off
del game[release].exe
REM    gcc -Wall -Werror main.c -s -m32 -o game.exe
indent -linux *.c
cproto -DPROTO_H -e -p -v -o proto.h *.c 


gcc *.c -static -m32 -std=c11 -w -o game[release].exe
pause