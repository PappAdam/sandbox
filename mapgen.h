#pragma once
#include <SDL2/SDL.h>

#define mapSizeX 100
#define mapSizeY 100

int map[mapSizeY][mapSizeX][64];

void generateMap();