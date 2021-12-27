rmdir /s /q obj
rmdir /s /q bin

mkdir obj
mkdir bin

C:\Gameboy\gbdk\bin\lcc -debug -c -o obj\hero_spr.o res\hero_spr.c

C:\Gameboy\gbdk\bin\lcc -debug -c -o obj\global.o src\global.c
C:\Gameboy\gbdk\bin\lcc -debug -c -o obj\hero.o src\hero.c
C:\Gameboy\gbdk\bin\lcc -debug -c -o obj\level.o src\level.c
C:\Gameboy\gbdk\bin\lcc -debug -c -o obj\main.o src\main.c

C:\Gameboy\gbdk\bin\lcc -debug -Wm-yn"TreasureSweeper" -o bin\TreasureSweeper.gb^
 obj\hero_spr.o^
 obj\global.o^
 obj\hero.o^
 obj\level.o^
 obj\main.o^