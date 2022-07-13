//
// Created by Shrimp on 6/14/2022.
//

#include "WorldGenerationShader.h"

WorldGenerationShader::WorldGenerationShader() : ComputeShader("res/shaders/worldGeneration.glsl") {
    chunkPos = getUniformLocation("chunkPos");
}

void WorldGenerationShader::loadChunkPos(Vector3D pos) const {
    load3DVector(chunkPos, pos);
}
