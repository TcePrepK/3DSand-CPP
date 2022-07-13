//
// Created by Shrimp on 4/16/2022.
//

#ifndef INC_2DSAND_CHUNKMANAGER_H
#define INC_2DSAND_CHUNKMANAGER_H


#include <optional>
#include <queue>
#include "Chunk.h"

class ChunkManager {
private:
    std::unordered_map<std::string, Chunk *> idToChunk{};
    std::vector<std::optional<Chunk>> chunkList{};
    std::vector<Chunk *> chunkUpdateList{};
    std::vector<Chunk *> chunkGenerateList{};

    const int OUT_OF_BOUNDS = -1;
    Chunk nullChunk = Chunk();

    std::vector<uint64_t> voxelBufferIDArray;
    std::vector<uint64_t> bitmaskBufferIDArray;
public:
    const unsigned int WIDTH, HEIGHT, DEPTH;
    const unsigned int CHUNK_AMOUNT;

    ChunkManager(unsigned int width, unsigned int height, unsigned int depth);

    void updateBuffers();

    void cleanUp();

    Chunk createChunkChunkSpace(Vector3D chunkPos);

    static Vector3D getChunkPosition(int x, int y, int z);

    Chunk getChunkWithId(const std::string &id);

    Chunk getChunkWorldSpace(Vector3D pos, bool createIfNull);

    Chunk getChunkWorldSpace(int x, int y, int z, bool createIfNull);

    Chunk getChunkChunkSpace(int x, int y, int z, bool createIfNull);

    Element getElement(int x, int y, int z);

    void setElement(int x, int y, int z, const Element &element);

    bool inBounds(int x, int y, int z) const;

    int getIDX(int x, int y, int z) const;

    int getIDX(Vector3D pos) const;

    const std::vector<uint64_t> &getVoxelBufferIDArray() const;

    const std::vector<uint64_t> &getBitmaskBufferIDArray() const;

    const std::vector<Chunk *> &getChunkUpdateList() const;

    std::vector<Chunk *> &getChunkGenerateList();

    const std::vector<std::optional<Chunk>> &getChunkList() const;

    Vector3D getWorldScaleByChunks() const;
};


#endif //INC_2DSAND_CHUNKMANAGER_H
