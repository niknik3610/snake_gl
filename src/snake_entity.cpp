#include "gameboard_utils.h"
#include "square.h"
#include "vao_wrapper.h"
#include <memory>
#include "snake_entity.h"

Snake::Snake(GameBoardPos spawnPos, std::shared_ptr<VaoWrapper> vao, std::shared_ptr<Shader> shader) : Entity(), squareCount(0), vao(vao), shader(shader), currMovDirection(DEFAULT_MOV_DIR)
{}

Snake::~Snake() {
    for (int i = 0; i < squareCount; i++) {
        delete renderSquares[i];
    }
}

Square* Snake::makeSquare(GameBoardPos pos) {
    GLPos glPos = GameBoardUtils::translateBoardCoordsToGL(pos);
    Square* square = new Square(this->vao, this->shader, COLR.getPrepared(), glPos);
    return square;
}

void Snake::draw() {
    //TODO:
}

GameBoardPos Snake::getPos() {
    return this->currHeadPos;
}
