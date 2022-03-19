#pragma once
#include <SDL2/SDL.h>
#include "camera.h"
#include "gameobj.h"

SDL_Texture* mapTexture;
SDL_Texture* characterTexture;
SDL_Texture* selectedTileTexture;
SDL_Rect dstR;
SDL_Rect cDstR;

void setRenderer(SDL_Renderer* renderer);
void gameRenderer(SDL_Renderer *renderer, camera* cam, gameobj gObj);