#pragma once
#include <SDL2/SDL.h>
#include "camera.h"
#include "character.h"

void setRenderer(SDL_Renderer* renderer);
void gameRenderer(SDL_Renderer *renderer, camera* cam, int win_w, int win_h, character _char);