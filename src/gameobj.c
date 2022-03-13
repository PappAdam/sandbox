#include "gameobj.h"
#include "hitbox.h"
#include "mapgen.h"

staticGameobj createStaticGameObj(int width, int height, int lenght, int x, int y, int z) {
    staticGameobj newSttcGObj;
    hitbox newSttcGObj_hitbox;

    newSttcGObj_hitbox.w = width;
    newSttcGObj_hitbox.l = lenght;
    newSttcGObj_hitbox.h = height;
    newSttcGObj.hitbox = newSttcGObj_hitbox;
    newSttcGObj.x = x; newSttcGObj.mapx = x;
    newSttcGObj.y = y; newSttcGObj.mapy = y;
    newSttcGObj.z = z; newSttcGObj.mapz = z;
    
    
    return newSttcGObj;
}

dinamicGameobj createDinamicGameObj(int width, int height, int lenght, int x, int y, int z, float speed) {
    dinamicGameobj newDnmcGObj;
    hitbox newDnmcGObj_hitbox;

    newDnmcGObj_hitbox.w = width;
    newDnmcGObj_hitbox.l = lenght;
    newDnmcGObj_hitbox.h = height;
    newDnmcGObj.hitbox = newDnmcGObj_hitbox;
    newDnmcGObj.x = x; newDnmcGObj.mapx = x;
    newDnmcGObj.y = y; newDnmcGObj.mapy = y;
    newDnmcGObj.z = z; newDnmcGObj.mapz = z;
    newDnmcGObj.speed = speed;
    newDnmcGObj.isJump = false;
    newDnmcGObj.move = false;


    return newDnmcGObj;
}

static void clearDnmcGobjPrevPos(dinamicGameobj* gObj) {
    map[(int)gObj->y][(int)gObj->x][(int)gObj->z] = 0;
}

static void setDmncGobjPos(dinamicGameobj* gObj) {
    map[(int)gObj->y][(int)gObj->x][(int)gObj->z] = 2;
    map[(int)gObj->y-1][(int)gObj->x-1][(int)gObj->z] = 1;
}

void moveGameObj(dinamicGameobj* gObj, float deltaTime) {
    clearDnmcGobjPrevPos(gObj);
    if (gObj->move) {
        switch (gObj->dir)
        {
            case left:
                if (!gObj->hitbox.colDir.left) gObj->x -= gObj->speed*deltaTime;
                break;
            case right:
                if (!gObj->hitbox.colDir.right) gObj->x += gObj->speed*deltaTime;
                break;
            case forward:
                if (!gObj->hitbox.colDir.forward) gObj->y -= gObj->speed*deltaTime;
                break;
            case backwards:
                if (!gObj->hitbox.colDir.backwards) gObj->y += gObj->speed*deltaTime;
                break;
            
            default:
                break;
        }
    }
    
    if (gObj->isJump) {
        gObj->zSpeed = -0.03f;
    }
    if (!gObj->hitbox.colDir.down) {
        gObj->zSpeed += 0.0003;
        gObj->isJump = false;
    }
    else if (gObj->hitbox.colDir.down && !gObj->isJump) {gObj->zSpeed = 0;}
    
    gObj->z -= gObj->zSpeed*deltaTime;

    setDmncGobjPos(gObj);
}