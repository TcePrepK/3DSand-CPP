//
// Created by Shrimp on 4/13/2022.
//

#include "Mouse.h"
#include "../GlobalVariables.h"

void Mouse::initialize() {
    GLFWwindow *window = GlobalVariables.displayManager.getWindow();
    glfwSetMouseButtonCallback(window, [](GLFWwindow *window, int button, int action, int mods) {
        if (button >= maxMouseButtons) {
            return;
        }

        if (action == GLFW_PRESS) {
            GlobalVariables.mouse.pressedList[button] = true;

            switch (button) {
                case 0:
                    GlobalVariables.mouse.leftMousePress.dispatch();
                    break;
                case 1:
                    GlobalVariables.mouse.rightMousePress.dispatch();
                    break;
                case 2:
                    GlobalVariables.mouse.middleMousePress.dispatch();
                    break;
                default:
                    break;
            }
        } else if (action == GLFW_RELEASE) {
            GlobalVariables.mouse.pressedList[button] = false;

            switch (button) {
                case 0:
                    GlobalVariables.mouse.leftMouseRelease.dispatch();
                    break;
                case 1:
                    GlobalVariables.mouse.rightMouseRelease.dispatch();
                    break;
                case 2:
                    GlobalVariables.mouse.middleMouseRelease.dispatch();
                    break;
                default:
                    break;
            }
        }
    });

    glfwSetScrollCallback(window, [](GLFWwindow *window, double offX, double offY) {
        GlobalVariables.mouse.mouseScroll.dispatch(offY == 1 ? 1 : -1);
    });
}

void Mouse::update() {
    GLFWwindow *window = GlobalVariables.displayManager.getWindow();
    Vector2D currentPosition = GlobalVariables.mouse.position;

    double xPos;
    double yPos;

    glfwGetCursorPos(window, &xPos, &yPos);

    GlobalVariables.mouse.delta.x = (float) xPos - currentPosition.x;
    GlobalVariables.mouse.delta.y = (float) yPos - currentPosition.y;

    GlobalVariables.mouse.position.x = (float) xPos;
    GlobalVariables.mouse.position.y = (float) yPos;
}

bool Mouse::isButtonDown(const int button) {
    if (button >= maxMouseButtons) {
        return false;
    }

    return pressedList[button];
}

Vector2D Mouse::getPosition() {
    return position;
}

Vector2D Mouse::getDelta() {
    return delta;
}
