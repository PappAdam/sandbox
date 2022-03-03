#include "character.h"
#include "mapgen.h"
#include "engine.h"

void clearCharacterPrevPos(character character) {
    map[(int)character.y][(int)character.x][(int)character.z] = 0;
}

void setCharacterPos(character character) {
    map[(int)character.y][(int)character.x][(int)character.z] = 2;
}

void moveCharacter(character* character, float deltaTime) {
    clearCharacterPrevPos(*character);
    if (character->move) {
        switch (character->direction)
        {
            case left:
                if (!character->collisioDir.left) character->x -= character->speed*deltaTime;
                break;
            case right:
                if (!character->collisioDir.right) character->x += character->speed*deltaTime;
                break;
            case forward:
                if (!character->collisioDir.forward) character->y -= character->speed*deltaTime;
                break;
            case backwards:
                if (!character->collisioDir.backwards) character->y += character->speed*deltaTime;
                break;
            
            default:
                break;
        }
    }
    
    if (character->isJump) {
        character->zSpeed = -0.03f;
    }
    if (!character->collisioDir.down) {
        character->zSpeed += 0.0003;
        character->isJump = false;
    }
    else if (character->collisioDir.down && !character->isJump) {character->zSpeed = 0;}
    
    character->z -= character->zSpeed;
    setCharacterPos(*character);
}

void isCollide(character* character) { //TODO create hitbox system
    character->collisioDir.down = false;
    character->collisioDir.top = false;
    character->collisioDir.right = false;
    character->collisioDir.left = false;
    character->collisioDir.forward = false;
    character->collisioDir.backwards = false;

    if (map[(int)character->y][(int)character->x][(int)character->z-1] != 0 && character->z*32-.1-(character->zSpeed*32) <= ((int)character->z-1)*32+32) character->collisioDir.down = true;
    if (map[(int)character->y][(int)character->x-1][(int)character->z] != 0 && character->x*32-(character->speed*32)-16 <= ((int)character->x-1)*32+32) character->collisioDir.left = true;
    if (map[(int)character->y][(int)character->x+1][(int)character->z] != 0 && character->x*32+(character->speed*32) >= ((int)character->x+1)*32) character->collisioDir.right = true;
    if (map[(int)character->y-1][(int)character->x][(int)character->z] != 0 && character->y*32-(character->speed*32)-16 <= ((int)character->y-1)*32+32) character->collisioDir.forward = true;
    if (map[(int)character->y+1][(int)character->x][(int)character->z] != 0 && character->y*32+(character->speed*32) >= ((int)character->y+1)*32) character->collisioDir.backwards = true;
}