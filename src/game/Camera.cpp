//
// Created by Shrimp on 4/10/2022.
//

#include <glm/gtc/matrix_transform.hpp>
#include "Camera.h"
#include "../core/GlobalVariables.h"

void printLn(glm::mat4 matrix) {
    std::cout << matrix[0][0] << " " << matrix[1][0] << " " << matrix[2][0] << " "
              << matrix[3][0] << std::endl;
    std::cout << matrix[0][1] << " " << matrix[1][1] << " " << matrix[2][1] << " "
              << matrix[3][1] << std::endl;
    std::cout << matrix[0][2] << " " << matrix[1][2] << " " << matrix[2][2] << " "
              << matrix[3][2] << std::endl;
    std::cout << matrix[0][3] << " " << matrix[1][3] << " " << matrix[2][3] << " "
              << matrix[3][3] << std::endl;
}

Camera::Camera() {
    createProjectionMatrix();

    GlobalVariables.mouse.mouseScroll.add(calculateZoom);
//        matrixWatcher.add(()->
//        {
//            renderer.loadCameraVariablesNextFrame();
//        });
//
//        screenSizeChange.add(this
//        ::screenResize);
}

void Camera::update() {
    updateZoom();

    if (GlobalVariables.mouse.isButtonDown(1)) {
        calculateAngleAroundPlayer(0.3f);
        calculatePitch();
    }

    if (GlobalVariables.dramaticZoom) {
        desiredZoomLevel = glm::max(0.f, zoomLevel - 10);
    }

    calculatePosition();
    calculateMatrices();
}

void Camera::screenResize() {
    cameraAspectRatio = DisplayManager::WIDTH / (float) DisplayManager::HEIGHT;
    viewportWidth = 2 * (float) glm::tan(glm::radians(Camera::FOV) / 2.0);
    viewportHeight = viewportWidth / cameraAspectRatio;

    createProjectionMatrix();
}

void Camera::calculateMatrices() {
    // ViewMatrix
    viewMatrix = glm::mat4(1);
    viewMatrix = glm::rotate(viewMatrix, glm::radians(pitch), glm::vec3(1, 0, 0));
    viewMatrix = glm::rotate(viewMatrix, glm::radians(yaw), glm::vec3(0, 1, 0));
//    viewMatrix = glm::rotate(viewMatrix, glm::radians(roll), glm::vec3(0, 0, 1));
    viewMatrix = glm::translate(viewMatrix, glm::vec3(-position.x, -position.y, -position.z));

    // ProjectionViewMatrix
    projectionViewMatrix = projectionMatrix * viewMatrix;
}

void Camera::createProjectionMatrix() {
//    const float y_scale = 1 / (viewportWidth / 2) * cameraAspectRatio;
    const float y_scale = ((1 / glm::tan(glm::radians(FOV / 2))) * cameraAspectRatio);
    const float x_scale = y_scale / cameraAspectRatio;
    const float frustum_length = Camera::FAR_PLANE - Camera::NEAR_PLANE;

    projectionMatrix[0][0] = x_scale;
    projectionMatrix[1][1] = y_scale;
    projectionMatrix[2][2] = -((Camera::FAR_PLANE + Camera::NEAR_PLANE) / frustum_length);
    projectionMatrix[2][3] = -1;
    projectionMatrix[3][2] = -((2 * Camera::NEAR_PLANE * Camera::FAR_PLANE) / frustum_length);
    projectionMatrix[3][3] = 0;
}

void Camera::calculatePosition() {
    yaw = 180 - angleAroundPlayer;

    const Vector3D center = GlobalVariables.chunkManager.getWorldScaleByChunks() * (int) Chunk::mapChunkSize / 2;

    const float horizontalDistance = calculateHorizontalDistance();
    const double theta = glm::radians(angleAroundPlayer);
    const auto offsetX = (float) (horizontalDistance * glm::sin(theta));
    const auto offsetZ = (float) (horizontalDistance * glm::cos(theta));

    const float verticalDistance = calculateVerticalDistance();
    position.x = center.x - offsetX;
    position.y = center.y + verticalDistance;
    position.z = center.z - offsetZ;
}

float Camera::calculateHorizontalDistance() const {
    return (float) (glm::cos(glm::radians(pitch)) * zoomLevel);
}

float Camera::calculateVerticalDistance() const {
    return (float) (glm::sin(glm::radians(pitch)) * zoomLevel);
}

void Camera::calculateZoom(int delta) {
    GlobalVariables.camera.desiredZoomLevel *= 1 - (float) delta / 100 * 5;
//        clampDesiredZoomLevel();
}

void Camera::updateZoom() {
    const float deltaZoom = desiredZoomLevel - zoomLevel;
    if (glm::abs(deltaZoom) < 0.5) {
        zoomLevel = desiredZoomLevel;
        return;
    }

//        const float dt = DisplayManager.getFrameTimeSeconds();
    const float dt = 1;
    zoomLevel += deltaZoom * dt * 10;

    if ((deltaZoom > 0 && zoomLevel > desiredZoomLevel) || (deltaZoom < 0 && zoomLevel < desiredZoomLevel)) {
        zoomLevel = desiredZoomLevel;
    }
}

void Camera::calculateAngleAroundPlayer(const float m) {
    float angleChange;
//        if (mouseLocked) {
//            angleChange = (Mouse.x() - DisplayManager.WIDTH / 2f) * m;
//        } else {
    angleChange = GlobalVariables.mouse.getDelta().x * m;
//        }

    angleAroundPlayer -= angleChange;

    angleAroundPlayer += 360.f * (angleAroundPlayer < 0.f ? 1.f : (angleAroundPlayer > 360) ? -1.f : 0.f);
//        clampAngleAroundPlayer();
}

void Camera::calculatePitch() {
    float pitchChange;
//        if (mouseLocked) {
//            pitchChange = (Mouse.y() - DisplayManager.HEIGHT / 2f) * 0.1f;
//        } else {
    pitchChange = GlobalVariables.mouse.getDelta().y * 0.1f;
//        }

    pitch += pitchChange;

    pitch = glm::clamp(pitch, MIN_PITCH, MAX_PITCH);

//        clampPitch();
}

Vector3D Camera::getPosition() {
    return position;
}

glm::mat4 Camera::getViewMatrix() {
    return viewMatrix;
}

Vector2D Camera::getViewportResolution() const {
    return {viewportWidth, viewportHeight};
}

const glm::mat4 &Camera::getProjectionViewMatrix() const {
    return projectionViewMatrix;
}
