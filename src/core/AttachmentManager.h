//
// Created by Shrimp on 4/10/2022.
//

#ifndef INC_2DSAND_ATTACHMENTMANAGER_H
#define INC_2DSAND_ATTACHMENTMANAGER_H


#include <unordered_map>
#include <vector>
#include "imageBuffers/ImageBuffer2D.h"
#include "../utils/Pair_Hash.h"

class AttachmentManager {
private:
    int width, height;
    std::unordered_map<std::string, ImageBuffer2D> imageBufferList;

public:
    AttachmentManager(int width, int height);

    void update();

    void createAttachments();

    void bind();

    void updateResolutions(int newWidth, int newHeight);

    void
    add(const std::string &id, unsigned int offset, int internalFormat, unsigned int format, unsigned int dataType);

    void add(const std::string &id, ImageBuffer2D &image);

    ImageBuffer2D &get(const std::string &id);

    bool has(const std::string &id);

    void remove(const char *id);

    void cleanUp();

    unsigned int size();

    std::vector<const char *> keys();

    const std::unordered_map<std::string, ImageBuffer2D> &getImageBufferList() const;
};


#endif //INC_2DSAND_ATTACHMENTMANAGER_H
