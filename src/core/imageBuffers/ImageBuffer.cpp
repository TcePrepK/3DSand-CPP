//
// Created by Shrimp on 4/10/2022.
//

#include "ImageBuffer.h"
#include "glad/glad.h"

ImageBuffer::ImageBuffer(const unsigned int location, const unsigned int offset, const int internalFormat,
                         const unsigned int format, const unsigned int dataType) : location(location), offset(offset),
                                                                                   internalFormat(internalFormat),
                                                                                   format(format), dataType(dataType) {}

void ImageBuffer::update() {
    glDeleteTextures(1, &oldID);
    oldID = id;
}

void ImageBuffer::cleanUp() {
    glDeleteTextures(1, &id);
    glDeleteTextures(1, &oldID);
}

bool ImageBuffer::isEmpty() const {
    return id == 0 && oldID == 0;
}

unsigned int ImageBuffer::getID() const {
    return id;
}

unsigned int ImageBuffer::getOldID() const {
    return oldID;
}

unsigned int ImageBuffer::getPosition() const {
    return location + offset;
}
