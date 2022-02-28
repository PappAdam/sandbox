#include "engine.h"
#include <stdbool.h>

typedef struct _camera {
    float xoffset, yoffset;
    int speed;
    bool isMoveable;
} camera;

void moveCam(camera *cam, mouse mouse_, int maxX, int maxY, float deltaTime) {
    if (cam->isMoveable) {
        if (mouse_.x >= maxX-20) {
            cam->xoffset -= cam->speed*deltaTime;
        } else if (mouse_.x <= 20) {
            cam->xoffset += cam->speed*deltaTime;
        }

        if (mouse_.y >= maxY-20) {
            cam->yoffset -= cam->speed*deltaTime;

        } else if (mouse_.y <= 20) {
            cam->yoffset += cam->speed*deltaTime;
        }
    }

    // printf("%lf, %lf, %lf\n", cam->xoffset, cam->yoffset, deltaTime);
}
