//#include "./src/utils/utils.h"
//#include "./src/elementRegistry.h"

//void eventSDL(SDL_Event event) {
//    switch (event.type) {
//        case SDL_QUIT: {
//            GlobalVariables.gameIsRunning = false;
//            break;
//        }
//        case SDL_MOUSEBUTTONDOWN: {
//            if (event.button.button == SDL_BUTTON_LEFT) {
//                s32 id = testForGUIs();
//                if (id != -1) GlobalVariables.currentMatID = id;
//                else GlobalVariables.holdingLeft = true;
//            } else if (event.button.button == SDL_BUTTON_RIGHT) {
//                // Vector2D tile = mouseToTile(GlobalVariables.mouse);
//                // Vector2D p = {tile.x, tile.y};
//
//                // GlobalVariables.shower.id = GlobalVariables.currentMatID;
//                // GlobalVariables.shower.pos = p;
//            }
//            break;
//        }
//        case SDL_MOUSEBUTTONUP: {
//            GlobalVariables.holdingLeft = false;
//            break;
//        }
//        default:
//            break;
//    }
//}

#include <iostream>
#include "src/core/GlobalVariables.h"
#include "src/elements/ElementRegistry.h"
#include "src/threads/ChunkGenerationThread.h"

int main() {
    GLFWwindow *window = GlobalVariables.displayManager.getWindow();

    Mouse::initialize();
    ElementRegistry::registerElements();

    ChunkGenerationThread thread0 = ChunkGenerationThread(0);
    ChunkGenerationThread thread1 = ChunkGenerationThread(1);
    ChunkGenerationThread thread2 = ChunkGenerationThread(2);
    ChunkGenerationThread thread3 = ChunkGenerationThread(3);

    std::cout << "Starting main loop!" << std::endl;

    thread0.start();
    thread1.start();
    thread2.start();
    thread3.start();
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

    thread0.kill();
    thread1.kill();
    thread2.kill();
    thread3.kill();
    return 0;
}