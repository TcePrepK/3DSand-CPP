//
// Created by Shrimp on 1/1/2022.
//

#ifndef INC_2DSAND_DISPLAYSHADER_H
#define INC_2DSAND_DISPLAYSHADER_H


#include "BasicShader.h"

class DisplayShader : public BasicShader {
private:
    int resolution{};

public:
    DisplayShader();

    void loadResolution() const;
};


#endif //INC_2DSAND_DISPLAYSHADER_H
