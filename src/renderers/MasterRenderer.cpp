//
// Created by Shrimp on 4/10/2022.
//

#include "MasterRenderer.h"
#include "../core/GlobalVariables.h"

MasterRenderer::MasterRenderer() {
    std::vector<float> positions{-1, 1, -1, -1, 1, 1, 1, -1};

    quad = GlobalVariables.loader.loadToVAO(positions, 2);

    displayShader.start();
    displayShader.loadResolution();
    DisplayShader::stop();

    renderShader.start();
    renderShader.loadResolutions();
    renderShader.loadChunkScale();

    attachmentManager.add("color", 0, GL_RGB32F, GL_RGB, GL_UNSIGNED_BYTE);
    attachmentManager.add("depth", 0, GL_R8, GL_RED, GL_UNSIGNED_BYTE);
    attachmentManager.add("rayDir", 0, GL_RGB32F, GL_RGB, GL_UNSIGNED_BYTE);
    attachmentManager.add("frameCount", 0, GL_R8, GL_RED, GL_UNSIGNED_BYTE);
    attachmentManager.add("normal", 0, GL_RGB32F, GL_RGB, GL_UNSIGNED_BYTE);
    attachmentManager.add("light", 0, GL_RGB32F, GL_RGB, GL_UNSIGNED_BYTE);

    for (const std::string key: attachmentManager.keys()) {
        renderShader.loadTexture(key + "Attachment", attachmentManager.get(key).getPosition());
    }
    RayTracerShader::stop();

    afterEffectShader.start();
    afterEffectShader.loadResolution();

    afterEffectAttachmentManager.add("color", 0, GL_RGB32F, GL_RGB, GL_UNSIGNED_BYTE);

    for (const std::string key: attachmentManager.keys()) {
        afterEffectShader.loadTexture(key + "Attachment", attachmentManager.get(key).getPosition());
    }

    AfterEffectShader::stop();

    displayBufferID = createDisplayBuffer();
    afterEffectBufferID = createAfterEffectBuffer();

//        screenSizeChange.add(()->
//        {
//            renderShader.start();
//            renderShader.loadResolutions();
//            BaseShader.stop();
//
//            displayShader.start();
//            displayShader.loadResolution();
//            BaseShader.stop();
//
//            attachmentManager.updateResolutions(WIDTH, HEIGHT);
//        });
}

void MasterRenderer::render() {
//        // Binding Timer
//        mainTimer.startTimer();
//        // Binding Timer

    // Update Buffers
    GlobalVariables.chunkManager.updateBuffers();
    // Update Buffers

    // Start Renderer
    renderShader.start();
    // Start Renderer

    // Load Variables
    renderShader.loadResolutions();
    renderShader.loadCameraVariables();

//        if (reloadResolutions) {
//            renderShader.loadResolutions();
//            reloadResolutions = false;
//        }

//        if (loadCameraVariables) {
//            renderShader.loadCameraVariables();
//            loadCameraVariables = false;
//        }

//        if (resetFrameCounter) {
//            attachmentManager.get("frameCount").create(null);
//            attachmentManager.get("frameCount").update();
//            resetFrameCounter = false;
//        }

    renderShader.loadRandomVector();
    renderShader.loadSunPosition(angle++);
    renderShader.loadPathTracingSetting();
    renderShader.loadBitmaskBorderSetting();
    renderShader.loadLightBounceAmount();
    // Load Variables

    // Bind Texture Buffer
    bindFrameBuffer(displayBufferID);
    // Bind Texture Buffer

    // Attachments
    attachmentManager.createAttachments();

    chunkBuffer.create(GlobalVariables.chunkManager.getVoxelBufferIDArray());
    bitmaskBuffer.create(GlobalVariables.chunkManager.getBitmaskBufferIDArray());

    attachmentManager.bind();

    chunkBuffer.bind();
    bitmaskBuffer.bind();
    // Attachments

//        // Binding Timer
//        bindTime = (float) mainTimer.stopTimer() * 1000;
//        // Binding Timer

//        // Timer For Others
//        mainTimer.startTimer();
//        // Timer For Others

    drawQuad();

    // Unbind Texture Buffer
    unbindFrameBuffer();
    RayTracerShader::stop();
    // Unbind Texture Buffer

    // After Effect
    afterEffectShader.start();
    bindFrameBuffer(afterEffectBufferID);

    afterEffectShader.loadVariables(GlobalVariables.spatialScale, GlobalVariables.spatialSigma);

    afterEffectAttachmentManager.createAttachments();
    attachmentManager.bind();
    afterEffectShader.loadColumnCheck(false);
    drawQuad();

    afterEffectAttachmentManager.update();
    afterEffectAttachmentManager.createAttachments();
    attachmentManager.bind();
    afterEffectAttachmentManager.get("color").bind();


    afterEffectShader.loadColumnCheck(true);
    drawQuad();

    unbindFrameBuffer();
    AfterEffectShader::stop();
    // After Effect

    // Start Display
    displayShader.start();
    // Start Display

    // Render Texture To Screen
    glActiveTexture(GL_TEXTURE0);
    if (afterEffectAttachmentManager.has(GlobalVariables.selectedOutput)) {
        glBindTexture(GL_TEXTURE_2D, afterEffectAttachmentManager.get(GlobalVariables.selectedOutput).getID());
    } else {
        glBindTexture(GL_TEXTURE_2D, attachmentManager.get(GlobalVariables.selectedOutput).getID());
    }
    // Render Texture To Screen

    drawQuad();

    DisplayShader::stop();

    attachmentManager.update();
    afterEffectAttachmentManager.update();

//        // Timer For Others
//        otherTime = (float) mainTimer.stopTimer() * 1000;
//        // Timer For Others
}

void MasterRenderer::drawQuad() {
    glBindVertexArray(quad->getVaoID());
    glEnableVertexAttribArray(0);
    glDrawArrays(GL_TRIANGLE_STRIP, 0, quad->getVertexCount());
    glDisableVertexAttribArray(0);
    glBindVertexArray(0);
}

void MasterRenderer::finishRendering(GLFWwindow *window) {
//        mainTimer.startTimer();

    glfwSwapBuffers(window);
    glfwPollEvents();

//        traceTime = (float) mainTimer.stopTimer() * 1000;
}

void MasterRenderer::loadOldCameraVariables() {
    renderShader.start();
    renderShader.loadOldVariables();
    RayTracerShader::stop();
}

void MasterRenderer::bindFrameBuffer(const unsigned int bufferID) {
    glBindFramebuffer(GL_FRAMEBUFFER, bufferID);
//        glViewport(0, 0, WIDTH, HEIGHT);
}

void MasterRenderer::unbindFrameBuffer() {
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
//        glViewport(0, 0, WIDTH, HEIGHT);
}

unsigned int MasterRenderer::createDisplayBuffer() {
    unsigned int frameBuffer;
    glGenFramebuffers(1, &frameBuffer);
    glBindFramebuffer(GL_FRAMEBUFFER, frameBuffer);

    const int size = (int) attachmentManager.size();
    std::vector<unsigned int> attachments(size);

    for (int i = 0; i < size; i++) {
        attachments[i] = GL_COLOR_ATTACHMENT0 + i;
    }

    glDrawBuffers(size, attachments.data());
    unbindFrameBuffer();

    return frameBuffer;
}

unsigned int MasterRenderer::createAfterEffectBuffer() {
    unsigned int frameBuffer;
    glGenFramebuffers(1, &frameBuffer);
    glBindFramebuffer(GL_FRAMEBUFFER, frameBuffer);

    const int size = (int) afterEffectAttachmentManager.size();
    std::vector<unsigned int> attachments(size);

    for (int i = 0; i < size; i++) {
        attachments[i] = GL_COLOR_ATTACHMENT0 + i;
    }

    glDrawBuffers(size, attachments.data());
    unbindFrameBuffer();

    return frameBuffer;
}

void MasterRenderer::cleanUp() {
    renderShader.cleanUp();
    displayShader.cleanUp();
    afterEffectShader.cleanUp();
    attachmentManager.cleanUp();
    afterEffectAttachmentManager.cleanUp();
//        chunkManager.cleanUp();

    glDeleteBuffers(1, &displayBufferID);
    glDeleteBuffers(1, &afterEffectBufferID);
}

AttachmentManager MasterRenderer::getAttachmentManager() {
    return attachmentManager;
}
