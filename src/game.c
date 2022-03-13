#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <time.h>
#include "engine.h"
#include "renderer.h"
#include "mapgen.h"
#include "camera.h"
#include "gameobj.h"


//=========================================================================== GAME VARIABLES =================================================================//


#define win_width 1920
#define win_height 1080

SDL_Window *window = NULL;
SDL_Renderer *renderer = NULL;
camera mainCamera = {.speed = 2, .xoffset = 0, .yoffset = 0, .isMoveable=true};
mouse mouse_;

const unsigned int timePerFrame = 1000 / 1000;
const float deltaTimeRatio = 1000 / 500;

bool run = true;

//========================================================================== INIT ============================================================================//


static void init() {
    srand(time(NULL));
    SDL_Init( SDL_INIT_VIDEO );
    IMG_Init(IMG_INIT_PNG);

    window = SDL_CreateWindow( "Try", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, win_width, win_height, SDL_WINDOW_FULLSCREEN_DESKTOP );
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

    SDL_SetRenderDrawColor(renderer, 0x00, 0x00, 0x00, 0xFF);
}


//========================================================================== CLOSE ===========================================================================//


static void Close_() { //TODO destor images created in renderer.c
    SDL_DestroyWindow( window );

    SDL_DestroyTexture(mapTexture);
    SDL_DestroyTexture(selectedTileTexture);
    SDL_DestroyTexture(characterTexture);

    SDL_DestroyRenderer( renderer);


    SDL_Quit();
    IMG_Quit();
}

//=========================================================================== EVENT HANDLER ==================================================================//


static void eventHandler(SDL_Event event, dinamicGameobj* character) { //TODO add controller support
    while (SDL_PollEvent(&event)) {
        switch(event.type){
            case SDL_QUIT:
                run = false;
                break;
            case SDL_KEYDOWN:
                switch(event.key.keysym.sym) {
                    case SDLK_ESCAPE:
                        run = false;
                        break;
                    case SDLK_w:
                        character->dir = forward;
                        character->move = true;
                        break;
                    case SDLK_s:
                        character->move = true;
                        character->dir = backwards;
                        break;
                    case SDLK_a:
                        character->move = true;
                        character->dir = left;
                        break;
                    case SDLK_d:
                        character->move = true;
                        character->dir = right;
                        break;
                    case SDLK_SPACE:
                        if (character->hitbox.colDir.down) {
                            character->isJump = true;
                        }
                        break;
                    
                    default:
                        break;
                }
                break;
                case SDL_KEYUP:
                    switch(event.key.keysym.sym) {
                        case SDLK_w:
                            character->dir = forward;
                            character->move = false;
                            break;
                        case SDLK_s:
                            character->move = false;
                            character->dir = backwards;
                            break;
                        case SDLK_a:
                            character->move = false;
                            character->dir = left;
                            break;
                        case SDLK_d:
                            character->move = false;
                            character->dir = right;
                            break;
                        
                        default:
                            break;
                }
                break;

            case SDL_MOUSEMOTION:
                mouse_.x = event.motion.x;
                mouse_.y = event.motion.y;
                break;

            default:
                break;
        }
    }
}

//=========================================================================== GAME ===========================================================================//


void runGame() {
    init();
    setRenderer(renderer);

    SDL_Event event;

    Uint32 frameStart;
    Uint32 frameEnd;
    Uint32 frameTime;

    float deltaTime;

    dinamicGameobj character = createDinamicGameObj(16, 20, 16, 50, 50, 20, .01);


    while (run) {
        frameStart = SDL_GetTicks();

        // Game

        gameRenderer(renderer, &mainCamera, character);
        eventHandler(event, &character);
        moveCam(&mainCamera, mouse_, win_width, win_height, deltaTime);
        moveGameObj(&character, deltaTime);
        isCollide(&character);


        // Game

        frameEnd = SDL_GetTicks();
        frameTime = frameEnd - frameStart;

        if (frameTime < timePerFrame) {
            SDL_Delay(timePerFrame - frameTime);
            frameTime = timePerFrame;
        }

        deltaTime = (float)(frameTime / deltaTimeRatio);
    }

    Close_();
}


