#ifndef ENTITY_MANAGER_H
#define ENTITY_MANAGER_H

#include "entity.h"
#include "gameboard_utils.h"
#include "shader.h"
#include "vao_wrapper.h"
#include <memory>

#define VERTEX_SHADER_PATH "../src/shaders/shader.vert"
#define FRAG_SHADER_PATH "../src/shaders/shader.frag"

enum EntityType {
    SnakeType
};

class EntityManager {
    private:
        static constexpr int MAX_ENTITY_COUNT = 512;

    public:
        EntityManager();
        ~EntityManager();

        std::unique_ptr<Entity> spawnEntity(EntityType type, GameBoardPos spawnPos);

    private:
        std::shared_ptr<VaoWrapper> vao;

        int currentEntity;

        //TODO: change this to a std::array
        std::shared_ptr<std::vector<float>> vertices;
        std::shared_ptr<std::vector<unsigned int>> indices;

        std::shared_ptr<Shader> shader;
};

#endif
