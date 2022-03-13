#pragma once
#include "hitbox.h"
#include <stdbool.h>

typedef enum dir {
    left,
    right,
    forward,
    backwards
} direction;

typedef struct sttcGameobj
{
    hitbox hitbox;
    float x, y, z;
    int mapx, mapy, mapz;

} staticGameobj;

typedef struct dnmcGameobj
{
    hitbox hitbox;
    float x, y, z;
    int mapx, mapy, mapz;
    float zSpeed;
    float speed;
    direction dir;
    bool isJump;
    bool move;

} dinamicGameobj;

//functions

staticGameobj createStaticGameObj(int width, int height, int lenght, int x, int y, int z);
dinamicGameobj createDinamicGameObj(int width, int height, int lenght, int x, int y, int z, float speed);

void moveGameObj(dinamicGameobj* gObj, float deltaTime);