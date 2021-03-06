//
// Created by Shrimp on 6/14/2022.
//

#include <iostream>
#include <fstream>
#include <regex>
#include "ComputeShader.h"
#include "glad/glad.h"

ComputeShader::ComputeShader(const char *computeFile) {
    std::cout << "Creating a shader!" << std::endl;

    computeShaderID = loadShader(computeFile);

    programID = glCreateProgram();
    glAttachShader(programID, computeShaderID);
    glLinkProgram(programID);
    glValidateProgram(programID);
}

void ComputeShader::start() const {
    glUseProgram(programID);
}

void ComputeShader::stop() {
    glUseProgram(0);
}

void ComputeShader::cleanUp() const {
    stop();
    glDetachShader(programID, computeShaderID);
    glDeleteShader(computeShaderID);
    glDeleteProgram(programID);
}

unsigned int ComputeShader::loadShader(const char *filePath) {
    std::string shaderSourceStr{};
    std::vector<std::string> includeList{};
    shaderReader(shaderSourceStr, filePath, includeList);
    const char *shaderSource = shaderSourceStr.c_str();

    const unsigned int shaderID = glCreateShader(GL_COMPUTE_SHADER);
    glShaderSource(shaderID, 1, &shaderSource, nullptr);
    glCompileShader(shaderID);

    int result;
    glGetShaderiv(shaderID, GL_COMPILE_STATUS, &result);
    if (result == GL_FALSE) {
        int logLength;
        glGetShaderiv(shaderID, GL_INFO_LOG_LENGTH, &logLength);

        std::vector<GLchar> errorLog(logLength);
        glGetShaderInfoLog(shaderID, logLength, &logLength, errorLog.data());
        std::cout << "Failed to compile Compute Shader!"
                  << std::endl;
        std::cout << errorLog.data() << std::endl;

        glDeleteShader(shaderID);
        return 0;
    }

    return shaderID;
}

std::string ComputeShader::shaderReader(std::string &baseContent, const std::string &filePath,
                                        std::vector<std::string> &includeList) {
    std::ifstream fileStream("../" + filePath, std::ios::in);

    if (!fileStream.is_open()) {
        std::cerr << "Could not read file " << filePath << ". File does not exist." << std::endl;
        return "";
    }

    std::string line;
    while (!fileStream.eof()) {
        std::getline(fileStream, line);

        if (line.empty()) {
            continue;
        }

        std::regex commentPattern(R"(\/\/)");
        if (std::regex_search(line, commentPattern)) {
            continue;
        }

        std::smatch colorMatch;
        std::regex includePattern("(#include )([/\\w.]+)");
        if (!std::regex_search(line, colorMatch, includePattern)) {
            baseContent.append(line + "\n");
            continue;
        }

        std::string newPath = colorMatch[2];
        if (std::find(includeList.begin(), includeList.end(), newPath) != includeList.end()) {
            continue;
        }

        includeList.push_back(newPath);
        shaderReader(baseContent, newPath, includeList);
    }

    fileStream.close();
    return baseContent;
}

int ComputeShader::getUniformLocation(const char *uniformName) const {
    return glGetUniformLocation(programID, uniformName);
}

void ComputeShader::loadFloat(const int location, const float value) {
    glUniform1f(location, value);
}

void ComputeShader::loadInt(const int location, const int value) {
    glUniform1i(location, value);
}

void ComputeShader::load2DVector(const int location, const Vector2D vec) {
    glUniform2f(location, vec.x, vec.y);
}

void ComputeShader::load3DVector(const int location, const Vector3D vector) {
    glUniform3f(location, vector.x, vector.y, vector.z);
}

void ComputeShader::load3DIVector(const int location, const Vector3D vector) {
    glUniform3i(location, (int) vector.x, (int) vector.y, (int) vector.z);
}

void ComputeShader::loadBoolean(const int location, const bool value) {
    glUniform1f(location, value ? 1 : 0);
}

void ComputeShader::loadMatrix(const int location, glm::mat4 matrix) {
    glUniformMatrix4fv(location, 1, false, glm::value_ptr(matrix));
}

void ComputeShader::loadTexture(const std::string &id, const unsigned int pos) const {
    loadInt(getUniformLocation(id.c_str()), (int) pos);
}
