#ifndef SNAKE_ENTITY_H
#define SNAKE_ENTITY_H

#include "color.h"
#include "gameboard_utils.h"
#include "square.h"
#include "vao_wrapper.h"
#include "entity.h"
#include <memory>

enum MovementDirection {
    Up,
    Down,
    Left,
    Right
};

class Snake : public Entity {
    private:
        static constexpr int MAX_SQUARES = 512;
        static constexpr Color COLR = Color(2, 212, 48);
        static constexpr MovementDirection DEFAULT_MOV_DIR = Right;

    public:

        int squareCount;
        Square* renderSquares[MAX_SQUARES];  
        GameBoardPos squarePositions[MAX_SQUARES];

        Snake(GameBoardPos spawnPos, std::shared_ptr<VaoWrapper> vao, std::shared_ptr<Shader> shader);
        ~Snake();

        virtual void draw() override;
        virtual GameBoardPos getPos() override;

    private:
        Square* makeSquare(GameBoardPos pos);
        std::shared_ptr<VaoWrapper> vao;
        std::shared_ptr<Shader> shader;

        MovementDirection currMovDirection;
        GameBoardPos currHeadPos;
};


#endif
