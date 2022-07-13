//
// Created by Shrimp on 4/16/2022.
//

#include <iostream>
#include "ChunkManager.h"
#include "../../core/GlobalVariables.h"

ChunkManager::ChunkManager(const unsigned int width, const unsigned int height, const unsigned int depth) :
        WIDTH(width), HEIGHT(height), DEPTH(depth), CHUNK_AMOUNT(width * height * depth) {
    voxelBufferIDArray = std::vector<uint64_t>(width * height * depth);
    bitmaskBufferIDArray = std::vector<uint64_t>(width * height * depth);

    chunkList = std::vector<std::optional<Chunk>>(width * height * depth);

    for (int i = 0; i < WIDTH; i++) {
        for (int j = 0; j < HEIGHT; j++) {
            for (int k = 0; k < DEPTH; k++) {
                createChunkChunkSpace(Vector3D(i, j, k));
            }
        }
    }

}

void ChunkManager::updateBuffers() {
    for (int i = 0; i < WIDTH; i++) {
        for (int j = 0; j < HEIGHT; j++) {
            for (int k = 0; k < DEPTH; k++) {
                int idx = getIDX(i, j, k);

                if (!chunkList[idx]) {
                    continue;
                }

                Chunk &chunk = *chunkList[idx];
                if (!chunk.shouldUpdateBuffers()) {
                    continue;
                }

                chunk.updateBuffers();

                const unsigned int voxelID = chunk.testImageTest;
//                const unsigned int voxelID = chunk.getVoxelBuffer().getID();
//                const unsigned int bitmaskID = chunk.getBitmaskBuffer().getID();

                glGenerateTextureMipmap(voxelID);

                voxelBufferIDArray[idx] = glGetTextureHandleARB(voxelID);
//                bitmaskBufferIDArray[idx] = glGetTextureHandleARB(bitmaskID);

                glMakeTextureHandleResidentARB(voxelBufferIDArray[idx]);
//                glMakeTextureHandleResidentARB(bitmaskBufferIDArray[idx]);
            }
        }
    }
}

void ChunkManager::cleanUp() {
    for (auto chunk: chunkList) {
        if (!chunk) {
            return;
        }

        chunk->getVoxelBuffer().cleanUp();
    }
}

Chunk ChunkManager::createChunkChunkSpace(Vector3D chunkPos) {
    const std::string id = chunkPos.toString();
    int idx = getIDX(chunkPos);

    chunkList[idx].emplace((int) chunkPos.x, (int) chunkPos.y, (int) chunkPos.z);

    idToChunk.insert(std::make_pair(id, &*chunkList[idx]));
    chunkUpdateList.push_back(&*chunkList[idx]);
    chunkGenerateList.push_back(&*chunkList[idx]);

    return *chunkList[idx];
}

Vector3D ChunkManager::getChunkPosition(const int x, const int y, const int z) {
    return Vector3D(x, y, z) / Chunk::mapChunkSize;
}

Chunk ChunkManager::getChunkWithId(const std::string &id) {
    if (idToChunk.find(id) == idToChunk.end()) {
        return nullChunk;
    }

    return *idToChunk[id];
}

Chunk ChunkManager::getChunkWorldSpace(Vector3D pos, const bool createIfNull) {
    return getChunkWorldSpace((int) pos.x, (int) pos.y, (int) pos.z, createIfNull);
}

Chunk ChunkManager::getChunkWorldSpace(const int x, const int y, const int z, const bool createIfNull) {
    return getChunkChunkSpace(x / (int) Chunk::mapChunkSize, y / (int) Chunk::mapChunkSize,
                              z / (int) Chunk::mapChunkSize, createIfNull);
}

Chunk ChunkManager::getChunkChunkSpace(const int x, const int y, const int z, const bool createIfNull) {
    Vector3D chunkPos = Vector3D(x, y, z);
    Chunk chunk = getChunkWithId(chunkPos.toString());

    if (chunk != nullChunk) {
        return chunk;
    }

    if (!createIfNull) {
        return nullChunk;
    }

    return createChunkChunkSpace(chunkPos);
}

Element ChunkManager::getElement(const int x, const int y, const int z) {
    Chunk chunk = getChunkWorldSpace(x, y, z, false);
    return chunk != nullChunk ? chunk.getElement(x, y, z) : ElementRegistry::emptyElement;
}

void ChunkManager::setElement(const int x, const int y, const int z, const Element &element) {
    Chunk chunk = getChunkWorldSpace(x, y, z, true);
    if (chunk.getElement(x, y, z) != ElementRegistry::emptyElement) {
        return;
    }

    chunk.setElement(x, y, z, element);
//        chunk.awakeGrid(x, y, z);
}

bool ChunkManager::inBounds(const int x, const int y, const int z) const {
    return !(x < 0 || x >= WIDTH || y < 0 || y >= HEIGHT || z < 0 || z >= DEPTH);
}

int ChunkManager::getIDX(const int x, const int y, const int z) const {
    if (!inBounds(x, y, z)) {
        return OUT_OF_BOUNDS;
    }

    return x + y * (int) WIDTH + z * (int) WIDTH * (int) HEIGHT;
}

int ChunkManager::getIDX(Vector3D pos) const {
    return getIDX((int) pos.x, (int) pos.y, (int) pos.z);
}

const std::vector<uint64_t> &ChunkManager::getVoxelBufferIDArray() const {
    return voxelBufferIDArray;
}

const std::vector<uint64_t> &ChunkManager::getBitmaskBufferIDArray() const {
    return bitmaskBufferIDArray;
}

const std::vector<Chunk *> &ChunkManager::getChunkUpdateList() const {
    return chunkUpdateList;
}

std::vector<Chunk *> &ChunkManager::getChunkGenerateList() {
    return chunkGenerateList;
}

const std::vector<std::optional<Chunk>> &ChunkManager::getChunkList() const {
    return chunkList;
}

Vector3D ChunkManager::getWorldScaleByChunks() const {
    return {WIDTH, HEIGHT, DEPTH};
}
