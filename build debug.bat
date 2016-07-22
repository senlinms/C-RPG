@echo off
REM    gcc -Wall -Werror main.c -s -m32 -o game.exe
cproto -DPROTO_H -e -p -v -o proto.h *.c 

gcc *.c -g -static -m32 -std=c11 -Wall -o game[debug].exe -DDEBUG
pause