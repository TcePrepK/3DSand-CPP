//
// Created by Shrimp on 4/10/2022.
//

#ifndef INC_2DSAND_IMAGEBUFFER_H
#define INC_2DSAND_IMAGEBUFFER_H


#include <cstdint>

class ImageBuffer {
protected:
    const unsigned int location;
    const unsigned int offset;
    const int internalFormat;
    const unsigned int format, dataType;
    unsigned int id{}, oldID{};

public:
    ImageBuffer(unsigned int location, unsigned int offset, int internalFormat,
                unsigned int format, unsigned int dataType);

    void update();

    void cleanUp();

    virtual void bind() = 0;

    [[nodiscard]] bool isEmpty() const;

    [[nodiscard]] unsigned int getID() const;

    [[nodiscard]] unsigned int getOldID() const;

    [[nodiscard]] unsigned int getPosition() const;
};


#endif //INC_2DSAND_IMAGEBUFFER_H
