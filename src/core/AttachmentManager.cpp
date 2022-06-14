//
// Created by Shrimp on 4/10/2022.
//

#include "AttachmentManager.h"

AttachmentManager::AttachmentManager(const int width, const int height) : width(width), height(height) {}

void AttachmentManager::update() {
    for (auto &pair: imageBufferList) {
        pair.second.update();
    }
}

void AttachmentManager::createAttachments() {
    for (auto &pair: imageBufferList) {
        pair.second.createAttachment();
    }
}

void AttachmentManager::bind() {
    for (auto &pair: imageBufferList) {
        pair.second.bind();
    }
}

void AttachmentManager::updateResolutions(const int newWidth, const int newHeight) {
    width = newWidth;
    height = newHeight;

    for (auto &pair: imageBufferList) {
        pair.second.updateResolution(newWidth, newHeight);
    }
}

void
AttachmentManager::add(const std::string &id, const unsigned int offset, const int internalFormat,
                       const unsigned int format,
                       const unsigned int dataType) {
    const ImageBuffer2D image = ImageBuffer2D(width, height, imageBufferList.size(), offset, internalFormat, format,
                                              dataType);
    imageBufferList.insert(std::make_pair(id, image));
}

void AttachmentManager::add(const std::string &id, ImageBuffer2D &image) {
    imageBufferList.insert(std::make_pair(id, image));
}

ImageBuffer2D &AttachmentManager::get(const std::string &id) {
    if (has(id)) {
        return imageBufferList.at(id);
    }

    return imageBufferList.begin()->second;
}

bool AttachmentManager::has(const std::string &id) {
    return imageBufferList.find(id) != imageBufferList.end();
}

void AttachmentManager::remove(const char *id) {
    imageBufferList.erase(id);
}

void AttachmentManager::cleanUp() {
    for (auto &pair: imageBufferList) {
        pair.second.cleanUp();
    }
}

unsigned int AttachmentManager::size() {
    return imageBufferList.size();
}

std::vector<const char *> AttachmentManager::keys() {
    std::vector<const char *> keys;

    for (auto &pair: imageBufferList) {
        keys.push_back(pair.first.c_str());
    }

    return keys;
}

const std::unordered_map<std::string, ImageBuffer2D> &AttachmentManager::getImageBufferList() const {
    return imageBufferList;
}
