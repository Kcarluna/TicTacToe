#!/bin/sh

std="-std=c++17"

CFLAGS=`pkg-config SDL2 --cflags`
LIBS=`pkg-config SDL2 SDL2_ttf --libs`

MODS="Scene.cpp Game.cpp Board.cpp Tile.cpp"
COMP="-o2"

set -xe

clang++ $COMP $std $CFLAGS $LIBS $MODS main.cpp -o TicTacToe
