#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <stdio.h>
#include <stdbool.h>


SDL_Texture* loadTexture(const char* filename, SDL_Renderer* renderer) {
    SDL_Texture* newTexture = NULL;
    SDL_Surface* loadedSurface = NULL;

    loadedSurface = IMG_Load(filename);
    if (loadedSurface == NULL) {
        printf("Error loading texture, SDL error: %s\n", SDL_GetError());
        return -1;
    }

    newTexture = SDL_CreateTextureFromSurface(renderer, loadedSurface);
    if (newTexture == NULL) {
        printf("Error loading texture, SDL error: %s\n", SDL_GetError());
        return -1;
    }

    SDL_FreeSurface(loadedSurface);
    return newTexture;
}
