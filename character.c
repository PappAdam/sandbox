#include <stdbool.h>
#include "character.h"
#include "mapgen.h"

void clearCharacterPrevPos(character character) {
    map[(int)character.y][(int)character.x][(int)character.z] = 0;
}

void setCharacterPos(character character) {
    map[(int)character.y][(int)character.x][(int)character.z] = 2;
}

void moveCharacter(character* character, float deltaTime) {
    if (character->move) {
        clearCharacterPrevPos(*character);
        switch (character->direction)
        {
            case left:
                character->x -= character->speed*deltaTime;
                break;
            case right:
                character->x += character->speed*deltaTime;
                break;
            case forward:
                character->y -= character->speed*deltaTime;
                break;
            case backwards:
                character->y += character->speed*deltaTime;
                break;
            
            default:
                break;
        }
        setCharacterPos(*character);
    }
}