//
// Created by Shrimp on 4/10/2022.
//

#ifndef INC_2DSAND_MASTERRENDERER_H
#define INC_2DSAND_MASTERRENDERER_H


#include "../core/RawModel.h"
#include "../core/AttachmentManager.h"
#include "../shaders/RayTracerShader.h"
#include "../shaders/DisplayShader.h"
#include "../display/DisplayManager.h"
#include "../core/SSBO.h"
#include "../shaders/AfterEffectShader.h"

class MasterRenderer {
private:
    float angle = 0;

    RawModel *quad;

    const RayTracerShader renderShader = RayTracerShader();
    const AfterEffectShader afterEffectShader = AfterEffectShader();
    const DisplayShader displayShader = DisplayShader();

    unsigned int displayBufferID;
    unsigned int afterEffectBufferID;

    AttachmentManager attachmentManager = AttachmentManager(DisplayManager::WIDTH, DisplayManager::HEIGHT);
    AttachmentManager afterEffectAttachmentManager = AttachmentManager(DisplayManager::WIDTH, DisplayManager::HEIGHT);
    SSBO chunkBuffer = SSBO(0, GL_DYNAMIC_READ);
    SSBO bitmaskBuffer = SSBO(1, GL_DYNAMIC_READ);

//    final Timer
//    mainTimer = new Timer();
//    float bindTime;
//    float traceTime;
//    float otherTime;

//    boolean loadCameraVariables = false;
//    boolean reloadResolutions = false;
//    boolean resetFrameCounter = false;
public :
    MasterRenderer();

    void render();

    void drawQuad();

    static void finishRendering(GLFWwindow *window);

    void loadOldCameraVariables();

    static void bindFrameBuffer(unsigned int bufferID);

    static void unbindFrameBuffer();

    unsigned int createDisplayBuffer();

    unsigned int createAfterEffectBuffer();

    void cleanUp();

    AttachmentManager getAttachmentManager();

//    float getBindTime() {
//        return bindTime;
//    }

//    float getTraceTime() {
//        return traceTime;
//    }

//    float getOtherTime() {
//        return otherTime;
//    }
};


#endif //INC_2DSAND_MASTERRENDERER_H
