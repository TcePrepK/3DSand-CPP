//
// Created by Shrimp on 6/14/2022.
//

#ifndef INC_3DSAND_COMPUTESHADERS_H
#define INC_3DSAND_COMPUTESHADERS_H


#include <string>
#include <vector>
#include "../utils/Vector2D.h"
#include "../utils/Vector3D.h"
#include "glm/gtc/type_ptr.hpp"

class ComputeShaders {
private:
    unsigned int programID;

    unsigned int computeShaderID;

public:
    explicit ComputeShaders(const char *computeFile);

    void start() const;

    static void stop();

    void cleanUp() const;

    void loadTexture(const std::string &, unsigned int pos) const;

private:
    static unsigned int loadShader(const char *filePath, unsigned int type);

    static std::string
    shaderReader(std::string &baseContent, const std::string &filePath, std::vector<std::string> &includeList);

protected:
    int getUniformLocation(const char *uniformName) const;

    static void loadFloat(int location, float value);

    static void loadInt(int location, int value);

    static void load2DVector(int location, Vector2D vec);

    static void load3DVector(int location, Vector3D vector);

    static void load3DIVector(int location, Vector3D vector);

    static void loadBoolean(int location, bool value);

    static void loadMatrix(int location, glm::mat4 matrix);
};


#endif //INC_3DSAND_COMPUTESHADERS_H
