//
// Created by Shrimp on 4/10/2022.
//

#ifndef INC_2DSAND_IMAGEBUFFER2D_H
#define INC_2DSAND_IMAGEBUFFER2D_H


#include "ImageBuffer.h"

class ImageBuffer2D : public ImageBuffer {
private:
    int width, height;

public:
    ImageBuffer2D(int width, int height, unsigned int location, unsigned int offset,
                  int internalFormat, unsigned int format, unsigned int dataType);

    void createAttachment(unsigned int pixels[]);

    void createAttachment();

    void create(const unsigned int pixels[]);

    void bind() override;

    void updateResolution(int width, int height);
};


#endif //INC_2DSAND_IMAGEBUFFER2D_H
