//
// Created by Shrimp on 4/10/2022.
//

#include "RawModel.h"

RawModel::RawModel(const unsigned int vaoID, const int vertexCount) : vaoID(vaoID), vertexCount(vertexCount) {}

unsigned int RawModel::getVaoID() const {
    return vaoID;
}

int RawModel::getVertexCount() const {
    return vertexCount;
}
