#pragma once
#include <stdbool.h>

typedef struct collisionDir
{
    bool left;
    bool right;
    bool forward;
    bool backwards;
    bool top;
    bool down;
} collisionDir;

typedef struct hitbox
{
    int w, l, h;
    collisionDir colDir;
} hitbox;
