#include "entity.h"
#include "entity_manager.h"
#include "snake_entity.h"
#include "gameboard_utils.h"
#include <cstdio>
#include <iostream>
#include <memory>
#include <stdexcept>

extern "C" {
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <GL/gl.h>
}


#define DEFAULT_WINDOW_WIDTH 800
#define DEFAULT_WINDOW_HEIGHT 800

void framebuffer_size_callback(GLFWwindow* window, int width, int height) {
    glViewport(0, 0, width, height);
}

void process_input(GLFWwindow* window) {
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
        glfwSetWindowShouldClose(window, true);
    }
}

int main() {
    glfwInitHint(GLFW_PLATFORM, GLFW_PLATFORM_WAYLAND);
    if (!glfwInit()) {
        const char* description;
        int code = glfwGetError(&description);
        throw std::runtime_error(std::string("Failed to initilze glfw: ") + std::string(description));
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    GLFWwindow* window = glfwCreateWindow(DEFAULT_WINDOW_WIDTH , DEFAULT_WINDOW_HEIGHT, "OpenGL Template", NULL, NULL);
    if (window == NULL) {
        glfwTerminate();
        throw std::runtime_error("Failed to create a window");
    }
    glfwMakeContextCurrent(window);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        glfwTerminate();
        throw std::runtime_error("Failed to load glad");
    }

    glViewport(0, 0, DEFAULT_WINDOW_WIDTH , DEFAULT_WINDOW_HEIGHT);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    EntityManager entityManager = EntityManager();
    GameBoardPos squareOnePos{0, 0, 0};
    MovVector movVector{1, 1, 0};

    std::unique_ptr<Snake> snake = std::dynamic_pointer_cast<Snake>(entityManager.spawnEntity(EntityType::SnakeType, squareOnePos));

    long framecount = 0;
    while(!glfwWindowShouldClose(window))
    {
        std::cout << "frameCount: " << framecount++ << "\n";

        snake->move();

        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        snake->draw();

        glfwSwapBuffers(window);
        glfwPollEvents();    
    }
    
    //CleanUp
    {
        glfwTerminate();
    }
    std::cout << "Done\n";
    return 0;
}

