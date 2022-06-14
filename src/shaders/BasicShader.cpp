//
// Created by Shrimp on 1/1/2022.
//

#include <iostream>
#include <filesystem>
#include <fstream>
#include <regex>
#include "BasicShader.h"
#include "glad/glad.h"

BasicShader::BasicShader(const char *vertexFile, const char *fragmentFile) {
    std::cout << "Creating a shader!" << std::endl;

    vertexShaderID = loadShader(vertexFile, GL_VERTEX_SHADER);
    fragmentShaderID = loadShader(fragmentFile, GL_FRAGMENT_SHADER);

    programID = glCreateProgram();
    glAttachShader(programID, vertexShaderID);
    glAttachShader(programID, fragmentShaderID);
    glLinkProgram(programID);
    glValidateProgram(programID);
}

void BasicShader::start() const {
    glUseProgram(programID);
}

void BasicShader::stop() {
    glUseProgram(0);
}

void BasicShader::cleanUp() const {
    stop();
    glDetachShader(programID, vertexShaderID);
    glDetachShader(programID, fragmentShaderID);
    glDeleteShader(vertexShaderID);
    glDeleteShader(fragmentShaderID);
    glDeleteProgram(programID);
}

unsigned int BasicShader::loadShader(const char *filePath, const unsigned int type) {
    std::string shaderSourceStr{};
    std::vector<std::string> includeList{};
    shaderReader(shaderSourceStr, filePath, includeList);
    const char *shaderSource = shaderSourceStr.c_str();

    const unsigned int shaderID = glCreateShader(type);
    glShaderSource(shaderID, 1, &shaderSource, nullptr);
    glCompileShader(shaderID);

    int result;
    glGetShaderiv(shaderID, GL_COMPILE_STATUS, &result);
    if (result == GL_FALSE) {
        int logLength;
        glGetShaderiv(shaderID, GL_INFO_LOG_LENGTH, &logLength);

        std::vector<GLchar> errorLog(logLength);
        glGetShaderInfoLog(shaderID, logLength, &logLength, errorLog.data());
        std::cout << "Failed to compile " << (type == GL_VERTEX_SHADER ? "Vertex" : "Fragment") << " Shader!"
                  << std::endl;
        std::cout << errorLog.data() << std::endl;

        glDeleteShader(shaderID);
        return 0;
    }

    return shaderID;
}

std::string BasicShader::shaderReader(std::string &baseContent, const std::string &filePath,
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

int BasicShader::getUniformLocation(const char *uniformName) const {
    return glGetUniformLocation(programID, uniformName);
}

void BasicShader::loadFloat(const int location, const float value) {
    glUniform1f(location, value);
}

void BasicShader::loadInt(const int location, const int value) {
    glUniform1i(location, value);
}

void BasicShader::load2DVector(const int location, const Vector2D vec) {
    glUniform2f(location, vec.x, vec.y);
}

void BasicShader::load3DVector(const int location, const Vector3D vector) {
    glUniform3f(location, vector.x, vector.y, vector.z);
}

void BasicShader::load3DIVector(const int location, const Vector3D vector) {
    glUniform3i(location, (int) vector.x, (int) vector.y, (int) vector.z);
}

void BasicShader::loadBoolean(const int location, const bool value) {
    glUniform1f(location, value ? 1 : 0);
}

void BasicShader::loadMatrix(const int location, glm::mat4 matrix) {
    glUniformMatrix4fv(location, 1, false, glm::value_ptr(matrix));
}

void BasicShader::loadTexture(const std::string &id, const unsigned int pos) const {
    loadInt(getUniformLocation(id.c_str()), (int) pos);
}
