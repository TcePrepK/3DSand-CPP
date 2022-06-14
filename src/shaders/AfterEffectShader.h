//
// Created by Shrimp on 4/30/2022.
//

#ifndef INC_2DSAND_AFTEREFFECTSHADER_H
#define INC_2DSAND_AFTEREFFECTSHADER_H

#include "BasicShader.h"
#include "../display/DisplayManager.h"

class AfterEffectShader : public BasicShader {
private:
    int resolution{};
    int columnCheck{};
    int scale{};
    int sigma{};

public:
    AfterEffectShader();

    void loadResolution() const;

    void loadColumnCheck(bool value) const;

    void loadVariables(int _scale, float _sigma) const;
};

#endif //INC_2DSAND_AFTEREFFECTSHADER_H
