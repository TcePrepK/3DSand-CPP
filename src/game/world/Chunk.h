//
// Created by Shrimp on 1/3/2022.
//

#ifndef INC_2DSAND_CHUNK_H
#define INC_2DSAND_CHUNK_H


#include <vector>
#include <tuple>
#include <memory>
#include "../../elements/Element.h"
#include "../../utils/Maths.h"
#include "../../core/imageBuffers/ImageBuffer3D.h"
#include "glad/glad.h"
#include "../../elements/ElementRegistry.h"
//#include "ChunkBuilder.h"

class Chunk {
private:
    Vector3D chunkPos;

    Vector3D chunkScale = Vector3D((float) mapChunkSize);
    Vector3D bitmaskScale = Vector3D((float) mapChunkSize / mapBitmaskSize);

    ImageBuffer3D voxelImageBuffer = ImageBuffer3D(chunkScale, 0, 0, GL_R8, GL_RED, GL_UNSIGNED_BYTE);
    ImageBuffer3D bitmaskImageBuffer = ImageBuffer3D(bitmaskScale, 0, 0, GL_R8, GL_RED, GL_UNSIGNED_BYTE);
public:
    unsigned int totalElementAmount = 0;
    bool isBuild = false;
    bool updateAllBuffers = false;
    static const unsigned int mapChunkSize = 32;
    static const unsigned int mapBitmaskSize = 4;

    uint8_t grid[mapChunkSize * mapChunkSize * mapChunkSize]{};
    uint8_t bitGrid[mapChunkSize / mapBitmaskSize * mapChunkSize / mapBitmaskSize * mapChunkSize / mapBitmaskSize]{};

    Chunk();

    Chunk(int x, int y, int z);

    void buildTheChunk();

    void updateBuffers();

    void setElement(int x, int y, int z, const Element &element);

    void setElement(Vector3D pos, const Element &e);

    [[nodiscard]] Element getElement(int x, int y, int z);

    Element getElement(Vector3D pos);

    [[nodiscard]] bool isEmpty() const;

    [[nodiscard]] unsigned int getIDXRelativeToChunk(int x, int y, int z) const;

    [[nodiscard]] static unsigned int getIDX(int x, int y, int z);

    [[nodiscard]] unsigned int getBitmaskIDXRelativeToChunk(int x, int y, int z) const;

    [[nodiscard]] unsigned int getBitmaskIDX(int x, int y, int z) const;

    [[nodiscard]] bool outBounds(int x, int y, int z) const;

    [[nodiscard]] ImageBuffer3D &getVoxelBuffer();

    [[nodiscard]] ImageBuffer3D &getBitmaskBuffer();

    [[nodiscard]] bool shouldUpdateBuffers() const;

    [[nodiscard]] const Vector3D &getChunkPos() const;

    bool operator==(const Chunk &chunk) const;

    bool operator==(Chunk &chunk) const;

    bool operator!=(const Chunk &chunk) const;

    bool operator!=(Chunk &chunk) const;
};


#endif //INC_2DSAND_CHUNK_H
