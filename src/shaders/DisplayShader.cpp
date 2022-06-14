//
// Created by Shrimp on 1/1/2022.
//

#include "DisplayShader.h"
#include "../display/DisplayManager.h"

DisplayShader::DisplayShader() : BasicShader("res/shaders/displayVertex.glsl",
                                             "res/shaders/displayFragment.glsl") {
    resolution = getUniformLocation("resolution");
}

void DisplayShader::loadResolution() const {
    load2DVector(resolution, {DisplayManager::WIDTH, DisplayManager::HEIGHT});
}
