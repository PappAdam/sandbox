#include "gameobj.h"
#include "hitbox.h"
#include "mapgen.h"


static const gameobj noneObj;

gameobj createDinamicGameObj(int width, int height, int lenght, int x, int y, int z, float speed) {
    gameobj newDnmcGObj;
    hitbox newDnmcGObj_hitbox;

    newDnmcGObj_hitbox.w = width;
    newDnmcGObj_hitbox.l = lenght;
    newDnmcGObj_hitbox.h = height;
    newDnmcGObj.hitbox = newDnmcGObj_hitbox;
    newDnmcGObj.x = x; newDnmcGObj.mapx = x;
    newDnmcGObj.y = y; newDnmcGObj.mapy = y;
    newDnmcGObj.z = z; newDnmcGObj.mapz = z;
    newDnmcGObj.type = dnmc;
    newDnmcGObj.dinamic.speed = speed;
    newDnmcGObj.dinamic.isJump = false;
    newDnmcGObj.dinamic.move = false;
    newDnmcGObj.dinamic.zSpeed = 0;

    return newDnmcGObj;
}

gameobj createStaticGameObj(int width, int height, int lenght, int x, int y, int z) {
    gameobj newDnmcGObj;
    hitbox newDnmcGObj_hitbox;

    newDnmcGObj_hitbox.w = width;
    newDnmcGObj_hitbox.l = lenght;
    newDnmcGObj_hitbox.h = height;
    newDnmcGObj.hitbox = newDnmcGObj_hitbox;
    newDnmcGObj.x = x; newDnmcGObj.mapx = x;
    newDnmcGObj.y = y; newDnmcGObj.mapy = y;
    newDnmcGObj.z = z; newDnmcGObj.mapz = z;
    newDnmcGObj.type = sttc;

    return newDnmcGObj;

}

gameobj createNoneTypeGameObj() {
    return noneObj;

}

static void clearDnmcGobjPrevPos(gameobj* gObj) {
    map[(int)gObj->y][(int)gObj->x][(int)gObj->z] = noneObj;

}

static void setDmncGobjPos(gameobj* gObj) {
    map[(int)gObj->y][(int)gObj->x][(int)gObj->z] = *gObj;

}

void moveGameObj(gameobj* gObj, float deltaTime) {
    clearDnmcGobjPrevPos(gObj);
    if (gObj->dinamic.move) {
        switch (gObj->dinamic.dir)
        {
            case left:
                if (!gObj->hitbox.colDir.left) gObj->x -= gObj->dinamic.speed*deltaTime;
                break;
            case right:
                if (!gObj->hitbox.colDir.right) gObj->x += gObj->dinamic.speed*deltaTime;
                break;
            case forward:
                if (!gObj->hitbox.colDir.forward) gObj->y -= gObj->dinamic.speed*deltaTime;
                break;
            case backwards:
                if (!gObj->hitbox.colDir.backwards) gObj->y += gObj->dinamic.speed*deltaTime;
                break;
            
            default:
                break;
        }
    }
    
    if (gObj->dinamic.isJump) {
        gObj->dinamic.zSpeed = -0.03f;
    }
    if (!gObj->hitbox.colDir.down) {
        gObj->dinamic.zSpeed += 0.0003f*deltaTime;
        gObj->dinamic.isJump = false;
    }
    else if (gObj->hitbox.colDir.down && !gObj->dinamic.isJump) {gObj->dinamic.zSpeed = 0;}
    
    gObj->z -= gObj->dinamic.zSpeed*deltaTime;

    setDmncGobjPos(gObj);
}
