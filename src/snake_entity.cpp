#include "gameboard_utils.h"
#include "square.h"
#include "vao_wrapper.h"
#include <memory>
#include "snake_entity.h"

Snake::Snake(GameBoardPos spawnPos, std::shared_ptr<VaoWrapper> vao, std::shared_ptr<Shader> shader) : 
    squareCount(0), vao(vao), shader(shader), currMovDirection(DEFAULT_MOV_DIR)
{
    auto square = this->makeSquare(spawnPos);
    this->renderSquares[squareCount] = std::move(square);
    this->squarePositions[squareCount] = std::move(spawnPos);
    squareCount++;
}

std::unique_ptr<Square> Snake::makeSquare(GameBoardPos pos) {
    GLPos glPos = GameBoardUtils::translateBoardCoordsToGL(pos);
    auto square = std::make_unique<Square>(this->vao, this->shader, COLR.getPrepared(), glPos);
    return square;
}

void Snake::draw() {
    for (int i = 0; i < squareCount; i++) {
        this->renderSquares[i]->draw();
    }
}

GameBoardPos Snake::move(MovVector movVec) {
    for (int i = 0; i < squareCount; i++) {
        auto& square = this->renderSquares[i];
        auto& oldPos = this->squarePositions[i];
        auto newPos = oldPos + movVec;
        this->squarePositions[i] = newPos;
        square->setPos(GameBoardUtils::translateBoardCoordsToGL(newPos));
    }

    this->currHeadPos = this->squarePositions[0];
    return this->currHeadPos;
}

GameBoardPos Snake::getPos() {
    return this->currHeadPos;
}
