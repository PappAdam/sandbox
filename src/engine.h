#pragma once
#include <SDL2/SDL.h>

SDL_Texture* loadTexture(const char* filename, SDL_Renderer* renderer);

typedef struct _mouse {
    int x, y;
} mouse;
