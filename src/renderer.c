#include "mapgen.h"
#include "camera.h"
#include "engine.h"
#include "renderer.h"
#include "gameobj.h"
#include <SDL2/SDL.h>
#include <stdio.h>
#include <stdbool.h>

unsigned int IMG_S = 64;

static bool isRenderable = true;

void setRenderer(SDL_Renderer* renderer) {
    dstR.w = IMG_S; dstR.h = IMG_S;
    cDstR.w = IMG_S; cDstR.h = IMG_S;
    generateMap();
    mapTexture = loadTexture("imgs/base.png", renderer);
    characterTexture = loadTexture("imgs/karakter.png", renderer);
    selectedTileTexture = loadTexture("imgs/selectedTile.png", renderer);
} 

void gameRenderer(SDL_Renderer *renderer, camera* cam, dinamicGameobj gObj) {
    SDL_RenderClear(renderer);
    isRenderable = true;
    for (int z = 0; z < 64; z++) {
        for (int y = 1; y < mapSize-1; y++) {
            for (int x = 1; x < mapSize-1; x++) {
                if (map[y][x][z] == 1) {
                    dstR.x = x*dstR.w/2 - y*dstR.h/2 + cam->xoffset;
                    dstR.y = y*dstR.h/4 + x*dstR.w/4 - z*dstR.h/2 + cam->yoffset;
                    if (map[y][x][z+1] == 2) {
                        SDL_RenderCopy(renderer, selectedTileTexture, NULL, &dstR);
                    }
                    else {
                        if (map[y][x-1][z] == 0 && map[y+1][x-1][z] == 2) {
                            cDstR.x = gObj.x*cDstR.w/2 - gObj.y*cDstR.h/2 + cam->xoffset;
                            cDstR.y = gObj.y*cDstR.h/4 + gObj.x*cDstR.w/4 - gObj.z*cDstR.w/2 + cam->yoffset - cDstR.h/2;
                            SDL_RenderCopy(renderer, characterTexture, NULL, &cDstR);
                            isRenderable = false;
                        }

                        SDL_RenderCopy(renderer, mapTexture, NULL, &dstR);

                    }
                }

                if (isRenderable && map[y][x][z] == 2) {
                    cDstR.x = gObj.x*cDstR.w/2 - gObj.y*cDstR.h/2 + cam->xoffset;
                    cDstR.y = gObj.y*cDstR.h/4 + gObj.x*cDstR.w/4 - gObj.z*cDstR.w/2 + cam->yoffset - cDstR.h/2;
                    SDL_RenderCopy(renderer, characterTexture, NULL, &cDstR);
                    isRenderable = false;
                }
            }
        }
    }
    SDL_RenderPresent(renderer);
}
