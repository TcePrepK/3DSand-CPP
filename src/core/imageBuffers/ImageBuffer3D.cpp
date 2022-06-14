//
// Created by Shrimp on 4/15/2022.
//

#include "ImageBuffer3D.h"
#include "glad/glad.h"
#include "../TextureManager.h"

ImageBuffer3D::ImageBuffer3D(const int width, const int height, const int depth,
                             const unsigned int location, const unsigned int offset, const int internalFormat,
                             const unsigned int format, const unsigned int dataType) :
        width(width), height(height), depth(depth),
        ImageBuffer(location, offset, internalFormat, format, dataType) {}

ImageBuffer3D::ImageBuffer3D(Vector3D scale, unsigned int location, unsigned int offset, int internalFormat,
                             unsigned int format, unsigned int dataType) :
        width((int) scale.x), height((int) scale.y), depth((int) scale.z),
        ImageBuffer(location, offset, internalFormat, format, dataType) {}


void ImageBuffer3D::create(const uint8_t pixels[]) {
    id = TextureManager::create3DTexture(width, height, depth, internalFormat, format, dataType, pixels);
}

void ImageBuffer3D::bind() {
    glActiveTexture(GL_TEXTURE0 + location + offset);
    glBindTexture(GL_TEXTURE_3D, oldID);
}