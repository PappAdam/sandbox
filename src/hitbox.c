#include "hitbox.h"
#include "gameobj.h"
#include "mapgen.h"

void isCollide(gameobj* gObj, float deltaTime) { //TODO create hitbox system
    gObj->hitbox.colDir.down = false;
    gObj->hitbox.colDir.top = false;
    gObj->hitbox.colDir.right = false;
    gObj->hitbox.colDir.left = false;
    gObj->hitbox.colDir.forward = false;
    gObj->hitbox.colDir.backwards = false;

    if (map[(int)gObj->y][(int)gObj->x][(int)gObj->z-1].type != NULL && gObj->z*32-(gObj->dinamic.zSpeed*32 + 0.0003f*deltaTime*32) <= ((int)gObj->z-1)*32+32+16) {
        gObj->hitbox.colDir.down = true;
    }
    if (map[(int)gObj->y][(int)gObj->x-1][(int)gObj->z].type != NULL && gObj->x*32-(gObj->dinamic.speed*32)-16 <= ((int)gObj->x-1)*32+32+1) gObj->hitbox.colDir.left = true;
    if (map[(int)gObj->y][(int)gObj->x+1][(int)gObj->z].type != NULL && gObj->x*32+(gObj->dinamic.speed*32) >= ((int)gObj->x+1)*32-1) gObj->hitbox.colDir.right = true;
    if (map[(int)gObj->y-1][(int)gObj->x][(int)gObj->z].type != NULL && gObj->y*32-(gObj->dinamic.speed*32)-16 <= ((int)gObj->y-1)*32+32+1) gObj->hitbox.colDir.forward = true;
    if (map[(int)gObj->y+1][(int)gObj->x][(int)gObj->z].type != NULL && gObj->y*32+(gObj->dinamic.speed*32) >= ((int)gObj->y+1)*32-1) gObj->hitbox.colDir.backwards = true;
}   

