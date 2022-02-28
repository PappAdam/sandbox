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
#include "character.h"


//=========================================================================== GAME VARIABLES =================================================================//


#define win_width 1920
#define win_height 1080

SDL_Window *window = NULL;
SDL_Renderer *renderer = NULL;
camera mainCamera = {.speed = 2, .xoffset = 0, .yoffset = 0, .isMoveable=true};
mouse mouse_;

character character_ = {.move = false, .x = 62, .y = 40, .z = 3, .speed = .01f};

const unsigned int timePerFrame = 1000 / 1000;
const float deltaTimeRatio = 1000 / 500;

bool run = true;

//========================================================================== INIT ============================================================================//


void init() {
    srand(time(NULL));
    SDL_Init( SDL_INIT_VIDEO );
    IMG_Init(IMG_INIT_PNG);

    window = SDL_CreateWindow( "Try", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, win_width, win_height, SDL_WINDOW_FULLSCREEN_DESKTOP );
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

    SDL_SetRenderDrawColor(renderer, 0x00, 0x00, 0x00, 0xFF);
}


//========================================================================== CLOSE ===========================================================================//


void Close_() {
    SDL_DestroyWindow( window );

    SDL_DestroyRenderer( renderer);


    SDL_Quit();
    IMG_Quit();
}

//=========================================================================== EVENT HANDLER ==================================================================//


void eventHandler(SDL_Event event) {
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
                        character_.direction = forward;
                        character_.move = true;
                        break;
                    case SDLK_s:
                        character_.move = true;
                        character_.direction = backwards;
                        break;
                    case SDLK_a:
                        character_.move = true;
                        character_.direction = left;
                        break;
                    case SDLK_d:
                        character_.move = true;
                        character_.direction = right;
                        break;
                    
                    default:
                        break;
                }
                break;
                case SDL_KEYUP:
                    switch(event.key.keysym.sym) {
                        case SDLK_w:
                            character_.direction = forward;
                            character_.move = false;
                            break;
                        case SDLK_s:
                            character_.move = false;
                            character_.direction = backwards;
                            break;
                        case SDLK_a:
                            character_.move = false;
                            character_.direction = left;
                            break;
                        case SDLK_d:
                            character_.move = false;
                            character_.direction = right;
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


    while (run) {
        frameStart = SDL_GetTicks();

        // Game

        gameRenderer(renderer, &mainCamera, win_width, win_height, character_);
        eventHandler(event);
        moveCam(&mainCamera, mouse_, win_width, win_height, deltaTime);
        moveCharacter(&character_, deltaTime);


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


