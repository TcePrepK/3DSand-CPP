//
// Created by Shrimp on 6/14/2022.
//

#ifndef INC_3DSAND_WORLDGENERATIONSHADER_H
#define INC_3DSAND_WORLDGENERATIONSHADER_H


#include "ComputeShader.h"

class WorldGenerationShader : public ComputeShader {
private:
    int chunkPos{};
public:
    WorldGenerationShader();

    void loadChunkPos(Vector3D pos) const;
};


#endif //INC_3DSAND_WORLDGENERATIONSHADER_H
