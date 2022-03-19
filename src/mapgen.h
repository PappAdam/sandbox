#pragma once
#include <SDL2/SDL.h>
#include "gameobj.h"

#define mapSize 100

gameobj map[mapSize][mapSize][64];

void generateMap();