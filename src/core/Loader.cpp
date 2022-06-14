//
// Created by Shrimp on 4/10/2022.
//

#include "Loader.h"

RawModel *Loader::loadToVAO(const std::vector<float> &positions, const int dimensions) {
    const unsigned int vaoID = createVAO();

    storeDataInAttributeList(0, dimensions, positions);

    unbindVAO();

    auto *rawModel = new RawModel(vaoID, (int) (positions.size() / dimensions));
    rawModels.push_back(rawModel);

    return rawModel;
}

RawModel *Loader::loadToVAO(const std::vector<float> &positions, const std::vector<int> &indices) {
    const unsigned int vaoID = createVAO();

    bindIndicesBuffer(indices);

    storeDataInAttributeList(0, 3, positions);

    unbindVAO();

    auto *rawModel = new RawModel(vaoID, (int) indices.size());
    rawModels.push_back(rawModel);

    return rawModel;
}

void Loader::cleanUp() {
    for (unsigned int vao: vaos) {
        glDeleteVertexArrays(1, &vao);
    }

    for (unsigned int vbo: vbos) {
        glDeleteBuffers(1, &vbo);
    }

    for (unsigned int texture: textures) {
        glDeleteTextures(1, &texture);
    }

    for (RawModel *rawModel: rawModels) {
        delete rawModel;
    }
}

unsigned int Loader::createVAO() {
    unsigned int vaoID;
    glGenVertexArrays(1, &vaoID);
    glBindVertexArray(vaoID);

    vaos.push_back(vaoID);

    return vaoID;
}

void
Loader::storeDataInAttributeList(const int attributeNumber, const int coordinateSize, const std::vector<float> &data) {
    unsigned int vboID;
    glGenBuffers(1, &vboID);
    glBindBuffer(GL_ARRAY_BUFFER, vboID);
    glBufferData(GL_ARRAY_BUFFER, (long long) (data.size() * sizeof(float)), data.data(), GL_STATIC_DRAW);
    glVertexAttribPointer(attributeNumber, coordinateSize, GL_FLOAT, false, 0, nullptr);
    glBindBuffer(GL_ARRAY_BUFFER, 0);;

    vbos.push_back(vboID);
}

void Loader::unbindVAO() {
    glBindVertexArray(0);
}

void Loader::bindIndicesBuffer(const std::vector<int> &indices) {
    unsigned int vboID;
    glGenBuffers(1, &vboID);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, vboID);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, (long long) (indices.size() * sizeof(int)), indices.data(), GL_STATIC_DRAW);

    vbos.push_back(vboID);
}
