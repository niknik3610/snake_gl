#ifndef ENTITY_H
#define ENTITY_H

#include "gameboard_utils.h"
class Entity {
    public:
        virtual void draw() = 0;
        virtual GameBoardPos getPos() = 0;

        virtual ~Entity() = default;
};

#endif 
