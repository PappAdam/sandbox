#pragma once
#include "hitbox.h"
#include <stdbool.h>

typedef enum dir {
    left,
    right,
    forward,
    backwards
} direction;

typedef enum gobjType {
    dnmc = 1,
    sttc
} gobjType;

typedef struct dnmcGameobj
{
    float zSpeed;
    float speed;
    direction dir;
    bool isJump;
    bool move;
} dinamicGameobj;

typedef struct gameobj
{
    hitbox hitbox;
    float x, y, z;
    int mapx, mapy, mapz;
    gobjType type;
    dinamicGameobj dinamic;
} gameobj;

//functions

gameobj createDinamicGameObj(int width, int height, int lenght, int x, int y, int z, float speed);
gameobj createStaticGameObj(int width, int height, int lenght, int x, int y, int z);
gameobj createNoneTypeGameObj();

void moveGameObj(gameobj* gObj, float deltaTime);