//
// Created by Shrimp on 4/10/2022.
//

#ifndef INC_2DSAND_LOADER_H
#define INC_2DSAND_LOADER_H


#include <vector>
#include "RawModel.h"
#include "glad/glad.h"

class Loader {
private:
    std::vector<unsigned int> vaos = std::vector<unsigned int>();
    std::vector<unsigned int> vbos = std::vector<unsigned int>();
    std::vector<unsigned int> textures = std::vector<unsigned int>();
    std::vector<RawModel *> rawModels = std::vector<RawModel *>();

public:
    RawModel *loadToVAO(const std::vector<float> &positions, int dimensions);

    RawModel *loadToVAO(const std::vector<float> &positions, const std::vector<int> &indices);

    void cleanUp();

private:
    unsigned int createVAO();

    void storeDataInAttributeList(int attributeNumber, int coordinateSize, const std::vector<float> &data);

    static void unbindVAO();

    void bindIndicesBuffer(const std::vector<int> &indices);
};


#endif //INC_2DSAND_LOADER_H
