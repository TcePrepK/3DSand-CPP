//
// Created by Shrimp on 4/10/2022.
//

#include "RayTracerShader.h"
#include "../core/GlobalVariables.h"

RayTracerShader::RayTracerShader() : BasicShader("res/shaders/mainVertex.glsl",
                                                 "res/shaders/mainFragment.glsl") {
    viewMatrix = getUniformLocation("viewMatrix");
    displayRes = getUniformLocation("displayRes");
    viewportRes = getUniformLocation("viewportRes");
    lookFrom = getUniformLocation("lookFrom");
    lookTo = getUniformLocation("lookTo");

    oldMVPMatrix = getUniformLocation("oldMVPMatrix");
    oldViewMatrix = getUniformLocation("oldViewMatrix");
    oldCameraPos = getUniformLocation("oldCameraPos");

    randVector2D = getUniformLocation("randVector2D");
    sunPosition = getUniformLocation("sunPosition");
    textureScale = getUniformLocation("textureScale");

    isPathTracing = getUniformLocation("isPathTracing");
    isRenderingBitmask = getUniformLocation("isRenderingBitmask");
    bitmaskSize = getUniformLocation("bitmaskSize");
    lightBounceAmount = getUniformLocation("lightBounceAmount");

    chunkScale = getUniformLocation("chunkScale");
}

void RayTracerShader::loadResolutions() const {
    load2DVector(displayRes, {DisplayManager::WIDTH, DisplayManager::HEIGHT});
    load2DVector(viewportRes, GlobalVariables.camera.getViewportResolution());
    loadInt(bitmaskSize, Chunk::mapBitmaskSize);
}

void RayTracerShader::loadCameraVariables() const {
    const Vector3D worldScale = Vector3D(2 * (int) GlobalVariables.chunkViewDistance * (int) Chunk::mapChunkSize);
    loadMatrix(viewMatrix, GlobalVariables.camera.getViewMatrix());
    load3DVector(lookFrom, GlobalVariables.camera.getPosition());
    load3DVector(lookTo, worldScale / 2);
    load3DVector(textureScale, worldScale);
}

void RayTracerShader::loadChunkScale() const {
    load3DIVector(chunkScale, Vector3D((int) GlobalVariables.chunkViewDistance * 2));
}

void RayTracerShader::loadOldVariables() const {
    load3DVector(oldCameraPos, GlobalVariables.camera.getPosition());
    loadMatrix(oldMVPMatrix, GlobalVariables.camera.getProjectionViewMatrix());
    loadMatrix(oldViewMatrix, GlobalVariables.camera.getViewMatrix());
}

void RayTracerShader::loadPathTracingSetting() const {
    loadBoolean(isPathTracing, GlobalVariables.pathTracing);
}

void RayTracerShader::loadBitmaskBorderSetting() const {
    loadBoolean(isRenderingBitmask, GlobalVariables.drawBitmaskBorders);
}

void RayTracerShader::loadLightBounceAmount() const {
//    loadInt(lightBounceAmount, GlobalVariables.lightBounceAmount);
    loadInt(lightBounceAmount, 3);
}

void RayTracerShader::loadRandomVector() const {
    load2DVector(randVector2D, {RNG::randomFloat(-1, 1), RNG::randomFloat(-1, 1)});
}

void RayTracerShader::loadSunPosition(const float angle) const {
    const float a = glm::radians(angle);
    const Vector3D origin = Vector3D((float) glm::cos(a), (float) glm::sin(a), 0.f);

//    load3DVector(sunPosition, sun.getPosition());
    load3DVector(sunPosition, origin);

}
