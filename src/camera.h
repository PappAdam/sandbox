#pragma once
#include <SDL2/SDL.h>
#include "engine.h"
#include <stdbool.h>

typedef struct _camera {
    float xoffset, yoffset;
    int speed;
    bool isMoveable;
} camera;

void moveCam(camera *cam, mouse mouse_, int maxX, int maxY, float deltaTime);
