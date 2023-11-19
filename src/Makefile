CC1 = fltk-config
CC2 = g++
CFLAGS1 = --compile
CFLAGS2 = -std=c++17 -Wall -Wextra -Wpedantic -Wshadow -lSDL2 -lSDL2_mixer

gui:
	$(CC1) $(CFLAGS1) ui.cpp
play:
	$(CC2) -o play play_music.cpp $(CFLAGS2)
