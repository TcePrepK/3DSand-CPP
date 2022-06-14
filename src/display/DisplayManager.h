//
// Created by Shrimp on 12/31/2021.
//

#ifndef INC_2DSAND_DISPLAYMANAGER_H
#define INC_2DSAND_DISPLAYMANAGER_H


#include "glad/glad.h"
#include "GLFW/glfw3.h"

class DisplayManager {
private:
    GLFWwindow *window{};

    double lastTime{};
    double FPS{};
    double averageFPS{};
public:
    static const unsigned int WIDTH = 1280;
    static const unsigned int HEIGHT = 720;

    DisplayManager();

    void updateDisplay();

    static void cleanUp();

    [[nodiscard]] GLFWwindow *getWindow() const;

    [[nodiscard]] double getFPS() const;

    [[nodiscard]] double getAverageFPS() const;
};


#endif //INC_2DSAND_DISPLAYMANAGER_H
