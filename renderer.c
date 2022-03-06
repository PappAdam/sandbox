#include "mapgen.h"
#include "camera.h"
#include "engine.h"
#include "character.h"
#include <SDL2/SDL.h>

unsigned int IMG_S = 64;

SDL_Texture* mapTexture;
SDL_Texture* characterTexture;
SDL_Texture* selectedTileTexture;


void setRenderer(SDL_Renderer* renderer) {
    generateMap();
    mapTexture = loadTexture("base.png", renderer);
    characterTexture = loadTexture("karakter.png", renderer);
    selectedTileTexture = loadTexture("selectedTile.png", renderer);
} 


void gameRenderer(SDL_Renderer *renderer, camera* cam, int win_w, int win_h, character _char) {
    SDL_RenderClear(renderer);
    SDL_Rect dstR = {0, 0, IMG_S, IMG_S};
    SDL_Rect cDstR = {0, 0, IMG_S, IMG_S};
    for (int z = 0; z < 64; z++) {
        for (int x = 0; x < mapSizeX; x++) {
            for (int y = 0; y < mapSizeY; y++) {
                if (map[y][x][z]) {
                    if (map[y][x][z] == 1) {
                        dstR.x = x*dstR.w/2 - y*dstR.h/2 + cam->xoffset;
                        dstR.y = y*dstR.h/4 + x*dstR.w/4 - z*dstR.h/2 + cam->yoffset;
                        if (map[y][x][z+1] == 2) {
                            SDL_RenderCopy(renderer, selectedTileTexture, NULL, &dstR);
                        }
                        else
                            SDL_RenderCopy(renderer, mapTexture, NULL, &dstR);
                    }

                    else if (map[y][x][z] == 2) {
                        cDstR.x = _char.x*cDstR.w/2 - _char.y*cDstR.h/2 + cam->xoffset;
                        cDstR.y = _char.y*cDstR.h/4 + _char.x*cDstR.w/4 - _char.z*cDstR.w/2 + cam->yoffset - cDstR.h/2;
                        SDL_RenderCopy(renderer, characterTexture, NULL, &cDstR);
                    }
                }
            }
        }
    }
    SDL_RenderPresent(renderer);
}
