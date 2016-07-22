@echo off
REM    gcc -Wall -Werror main.c -s -m32 -o game.exe
cproto -DPROTO_H -e -p -v -o proto.h *.c 
gcc *.c -pg -static -m32 -std=c11 -Wall -o game[profile].exe -DDEBUG

if not %errorlevel%==0 (
echo [ERROR]gcc error code:%errorlevel%
pause
exit
)

echo generating gmon.out..

game[profile].exe

echo gmon.out generated

echo generating analysis.txt..
gprof game[profile].exe gmon.out > analysis.txt

echo done!
pause