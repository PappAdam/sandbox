#pragma once
#include <stdbool.h>
#include <SDL2/SDL.h>


typedef struct collisionDir
{
    bool left;
    bool right;
    bool forward;
    bool backwards;
    bool top;
    bool down;
} collisionDir_;

typedef enum dir {
        left,
        right,
        forward,
        backwards
} dir;


typedef struct _character
{
    float zSpeed;
    float x, y, z;
    int mapCX, mapCY, mapCZ;
    bool isJump;
    bool move;
    float speed;
    dir direction;
    collisionDir_ collisioDir;

} character;

void moveCharacter(character* character, float deltaTime);

void isCollide(character* character);