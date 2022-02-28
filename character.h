#pragma once
#include <stdbool.h>
#include <SDL2/SDL.h>

typedef struct _character
{
    float x, y, z;
    bool move;
    float speed;
    enum dir {
        left,
        right,
        forward,
        backwards
    } direction;

} character;

void moveCharacter(character* character, float deltaTime);