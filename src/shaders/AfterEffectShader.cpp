//
// Created by Shrimp on 4/30/2022.
//

#include "./AfterEffectShader.h"

AfterEffectShader::AfterEffectShader() : BasicShader("res/shaders/afterEffectVertex.glsl",
                                                     "res/shaders/afterEffectFragment.glsl") {
    resolution = getUniformLocation("resolution");
    columnCheck = getUniformLocation("columnCheck");
    scale = getUniformLocation("scale");
    sigma = getUniformLocation("sigma");

    dramaticZoom = getUniformLocation("dramaticZoom");
}

void AfterEffectShader::loadResolution() const {
    load2DVector(resolution, {DisplayManager::WIDTH, DisplayManager::HEIGHT});
}

void AfterEffectShader::loadColumnCheck(bool value) const {
    loadBoolean(columnCheck, value);
}

void AfterEffectShader::loadVariables(int _scale, float _sigma) const {
    loadInt(scale, _scale);
    loadFloat(sigma, _sigma);
}

void AfterEffectShader::doDramaticZoom(bool value) const {
    loadBoolean(dramaticZoom, value);
}

