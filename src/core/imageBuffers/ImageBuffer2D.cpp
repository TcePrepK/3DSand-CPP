//
// Created by Shrimp on 4/10/2022.
//

#include "ImageBuffer2D.h"
#include "../TextureManager.h"

ImageBuffer2D::ImageBuffer2D(const int width, const int height, const unsigned int location,
                             const unsigned int offset, const int internalFormat,
                             const unsigned int format, const unsigned int dataType) :
        width(width), height(height), ImageBuffer(location, offset, internalFormat, format, dataType) {}

void ImageBuffer2D::createAttachment(unsigned int pixels[]) {
    create(pixels);
    glFramebufferTexture(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0 + location, id, 0);
}

void ImageBuffer2D::createAttachment() {
    createAttachment(nullptr);
}

void ImageBuffer2D::create(const unsigned int pixels[]) {
    id = TextureManager::create2DTexture(width, height, internalFormat, format, dataType, pixels);
}

void ImageBuffer2D::bind() {
    glActiveTexture(GL_TEXTURE0 + location + offset);
    glBindTexture(GL_TEXTURE_2D, oldID);
}

void ImageBuffer2D::updateResolution(const int _width, const int _height) {
    width = _width;
    height = _height;
}
