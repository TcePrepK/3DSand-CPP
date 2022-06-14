//
// Created by Shrimp on 12/30/2021.
//

#ifndef INC_2DSAND_TEXTUREMANAGER_H
#define INC_2DSAND_TEXTUREMANAGER_H


#include "glad/glad.h"

struct TextureManager {
public:
    // 2D
    static unsigned int
    create2DTexture(int width, int height, int internalFormat, unsigned int format, unsigned int dataType,
                    const unsigned int pixels[]);
    // 2D

    // 3D
    static unsigned int
    create3DTexture(int width, int height, int depth, int internalFormat, unsigned int format, unsigned int dataType,
                    const uint8_t pixels[]);
    // 3D
};


#endif //INC_2DSAND_TEXTUREMANAGER_H
