//
// Created by Shrimp on 4/10/2022.
//

#ifndef INC_2DSAND_CAMERA_H
#define INC_2DSAND_CAMERA_H


#include <glm/glm.hpp>
#include "../display/DisplayManager.h"
#include "../utils/Vector2D.h"
#include "../utils/Vector3D.h"

class Camera {
public:
    static constexpr float FOV = 90;
    static constexpr float NEAR_PLANE = 1;
    static constexpr float FAR_PLANE = 1000;
private:
    const float MAX_PITCH = 90;
    const float MIN_PITCH = -90;
    const float MAX_ZOOMLEVEL = 300;
    const float MIN_ZOOMLEVEL = 20;

    glm::mat4 viewMatrix{};
    glm::mat4 projectionMatrix{};
    glm::mat4 projectionViewMatrix{};

    float cameraAspectRatio = DisplayManager::WIDTH / (float) DisplayManager::HEIGHT;
    float viewportWidth = 2 * (float) glm::tan(glm::radians(Camera::FOV) / 2);
    float viewportHeight = viewportWidth / cameraAspectRatio;

//    Vector3D topLeftCorner;
//    Vector3D xIncrement;
//    Vector3D yIncrement;

    Vector3D position = Vector3D();
    float angleAroundPlayer = 211;
    float zoomLevel = 200;
    float desiredZoomLevel = zoomLevel;
    float pitch = 25;
    float yaw = 331;
    float roll = 0;

public:
    Camera();

    void update();

    void screenResize();

private:
    void calculatePosition();

    [[nodiscard]] float calculateHorizontalDistance() const;

    [[nodiscard]] float calculateVerticalDistance() const;

    static void calculateZoom(int delta);

    void updateZoom();

    void calculateAngleAroundPlayer(float m);

    void calculatePitch();

public:
    void calculateMatrices();

    void createProjectionMatrix();

//    void clampYaw() {
//        yaw = (yaw + 360) % 360;
//    }

//    void clampPitch() {
//        pitch = clamp(pitch, MIN_PITCH, MAX_PITCH);
//    }

//    void clampZoomLevel() {
//        zoomLevel = clamp(zoomLevel, MIN_ZOOMLEVEL, MAX_ZOOMLEVEL);
//    }

//    void clampDesiredZoomLevel() {
//        desiredZoomLevel = clamp(desiredZoomLevel, MIN_ZOOMLEVEL, MAX_ZOOMLEVEL);
//    }

//    void clampAngleAroundPlayer() {
//        angleAroundPlayer = angleAroundPlayer % 360;
//    }

//    void setYaw(final float yaw) {
//        this.yaw = yaw;
//        clampYaw();
//    }

    Vector3D getPosition();

//    float getAngleAroundPlayer() {
//        return angleAroundPlayer;
//    }

    glm::mat4 getViewMatrix();

//    glm::mat4 getProjectionMatrix() {
//        return projectionMatrix;
//    }

//    glm::mat4 getProjectionViewMatrix() {
//        return projectionViewMatrix;
//    }

    [[nodiscard]] Vector2D getViewportResolution() const;

    [[nodiscard]] const glm::mat4 &getProjectionViewMatrix() const;
};


#endif //INC_2DSAND_CAMERA_H
