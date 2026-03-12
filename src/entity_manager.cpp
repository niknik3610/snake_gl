#include "entity_manager.h"
#include "entity.h"
#include "snake_entity.h"
#include "vao_wrapper.h"
#include <memory>

EntityManager::EntityManager() : currentEntity(0) {
    this->vertices = std::make_shared<std::vector<float>>(std::vector<float>{
        0.5f,  0.5f, 0.0f,  // top right
        0.5f, -0.5f, 0.0f,  // bottom right
        -0.5f, -0.5f, 0.0f,  // bottom left
        -0.5f,  0.5f, 0.0f   // top left 
    });

    this->indices = std::make_shared<std::vector<unsigned int>>(std::vector<unsigned int>{        
        0, 1, 3,   // first triangle
        1, 2, 3    // second triangle
    }); 

    this->vao = std::make_shared<VaoWrapper>(vertices, indices);
    this->shader = std::make_shared<Shader>(VERTEX_SHADER_PATH, FRAG_SHADER_PATH); 
}


EntityManager::~EntityManager() {
}


//TODO figure out traits and make this template <typename T>, where T implements Entity. Then this is easy clap
std::unique_ptr<Entity> EntityManager::spawnEntity(EntityType type, GameBoardPos spawnPos)
{
    std::unique_ptr<Entity> entity;
    switch (type) {
        case SnakeType:
            entity = std::make_unique<Snake>(std::move(spawnPos), this->vao, this->shader);
            break;
    }

    return std::move(entity);
}

                      
