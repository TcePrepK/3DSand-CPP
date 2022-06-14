//
// Created by Shrimp on 4/15/2022.
//

#ifndef INC_2DSAND_IMAGEBUFFER3D_H
#define INC_2DSAND_IMAGEBUFFER3D_H


#include "ImageBuffer.h"
#include "../../utils/Vector3D.h"

class ImageBuffer3D : public ImageBuffer {
private:
    int width, height, depth;

public:
    ImageBuffer3D(int width, int height, int depth, unsigned int location, unsigned int offset,
                  int internalFormat, unsigned int format, unsigned int dataType);

    ImageBuffer3D(Vector3D scale, unsigned int location, unsigned int offset,
                  int internalFormat, unsigned int format, unsigned int dataType);

    void create(const uint8_t pixels[]);

    void bind() override;
};


#endif //INC_2DSAND_IMAGEBUFFER3D_H
