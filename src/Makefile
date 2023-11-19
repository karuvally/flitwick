CC = g++
CC1 = fltk-config
CC2 = g++

CFLAGS	= -std=c++17 -L/usr/local/lib -lfltk -lXrender -lXcursor -lXfixes -lXext -lXinerama -lpthread -lm -lX11 -lSDL2 -lSDL2_mixer
CFLAGS1 = --compile
CFLAGS2 = -std=c++17 -Wall -Wextra -Wpedantic -Wshadow -lSDL2 -lSDL2_mixer

all:
	$(CC) -o flitwick ui.cpp $(CFLAGS)
gui:
	$(CC1) $(CFLAGS1) ui.cpp
play:
	$(CC2) -o play play_music.cpp $(CFLAGS2)