#include <iostream>
#include "src/core/GlobalVariables.h"
#include "src/elements/ElementRegistry.h"
#include "src/threads/ChunkGenerationThread.h"

int main() {
    GLFWwindow *window = GlobalVariables.displayManager.getWindow();

    Mouse::initialize();
    ElementRegistry::registerElements();

//    ChunkGenerationThread thread0 = ChunkGenerationThread(0);
//    ChunkGenerationThread thread1 = ChunkGenerationThread(1);
//    ChunkGenerationThread thread2 = ChunkGenerationThread(2);
//    ChunkGenerationThread thread3 = ChunkGenerationThread(3);

    std::cout << "Starting main loop!" << std::endl;

//    thread0.start();
//    thread1.start();
//    thread2.start();
//    thread3.start();
    while (!glfwWindowShouldClose(window)) {
        GlobalVariables.currentFrame++;

        Mouse::update();
        GlobalVariables.camera.update();

        GlobalVariables.renderer.render();
        ImGuiManager::update();
        MasterRenderer::finishRendering(window);

        GlobalVariables.renderer.loadOldCameraVariables();

        GlobalVariables.displayManager.updateDisplay();
    }

    GlobalVariables.loader.cleanUp();
    GlobalVariables.renderer.cleanUp();
    ImGuiManager::cleanUp();
    DisplayManager::cleanUp();

//    thread0.kill();
//    thread1.kill();
//    thread2.kill();
//    thread3.kill();
    return 0;
}