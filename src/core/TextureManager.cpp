//
// Created by Shrimp on 12/30/2021.
//

#include "TextureManager.h"

unsigned int
TextureManager::create2DTexture(const int width, const int height, const int internalFormat, const unsigned int format,
                                const unsigned int dataType, const unsigned int pixels[]) {
    unsigned int texture;
    glGenTextures(1, &texture);

    glBindTexture(GL_TEXTURE_2D, texture);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);

    glTexImage2D(GL_TEXTURE_2D, 0, internalFormat, width, height, 0, format, dataType, pixels);
    glBindTexture(GL_TEXTURE_2D, 0);

    return texture;
}

unsigned int
TextureManager::create3DTexture(const int width, const int height, const int depth, const int internalFormat,
                                const unsigned int format, const unsigned int dataType, const uint8_t pixels[]) {
    unsigned int texture;
    glGenTextures(1, &texture);

    glBindTexture(GL_TEXTURE_3D, texture);

    glTexParameteri(GL_TEXTURE_3D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_3D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_3D, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);

    glTexParameteri(GL_TEXTURE_3D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_3D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);

    glTexImage3D(GL_TEXTURE_3D, 0, internalFormat, width, height, depth, 0, format, dataType, pixels);
    glBindTexture(GL_TEXTURE_3D, 0);

    return texture;
}
