//
// Created by Shrimp on 1/3/2022.
//

#include <cmath>
#include <iostream>
#include "Chunk.h"
#include "../../core/GlobalVariables.h"

Chunk::Chunk() {
    chunkPos = Vector3D(-1) * mapChunkSize;
}

Chunk::Chunk(int x, int y, int z) {
    chunkPos = Vector3D(x, y, z) * mapChunkSize;
}

void generateMandelBulb(Chunk &chunk) {
    Element &light = ElementRegistry::getElementByName("Light");
    Element &dirt = ElementRegistry::getElementByName("Dirt");
    Element &glass = ElementRegistry::getElementByName("Glass");

    auto worldScale = Vector3D(2 * (int) GlobalVariables.chunkViewDistance * (int) Chunk::mapChunkSize);
//    const float scale = 2;
    const float scale = 1.75;
    const float n = 8;
    const unsigned int l = 10;
    for (int offX = 0; offX < Chunk::mapChunkSize; offX++) {
        for (int offY = 0; offY < Chunk::mapChunkSize; offY++) {
            for (int offZ = 0; offZ < Chunk::mapChunkSize; offZ++) {
                Vector3D voxelPos = chunk.getChunkPos() + Vector3D(offX, offY, offZ);
                Vector3D centered = voxelPos - worldScale / 2;
                Vector3D pos = centered / (worldScale * scale / 2) * 2;

                auto Z = Vector3D(pos);
                bool hit = true;
                for (int i = 0; i < l; i++) {
                    const float cr = Z.length();
                    if (cr >= 2) {
                        hit = false;
                        break;
                    }

                    const float a1 = glm::atan(Z.y, Z.x) * n;
                    const float a2 = glm::atan(Z.z, glm::sqrt(Z.x * Z.x + Z.y * Z.y)) * n;
                    const auto r = (float) glm::pow(cr, n);

                    Z.x = (float) (r * glm::cos(a2) * glm::cos(a1));
                    Z.y = (float) (r * glm::cos(a2) * glm::sin(a1));
                    Z.z = (float) (r * glm::sin(a2));
                    Z += pos;
                }

                if (!hit) {
                    continue;
                }

                if (RNG::randomFloat(0, 1) < 0.9) {
                    chunk.setElement(voxelPos, glass);
                } else {
                    chunk.setElement(voxelPos, glass);
//                    chunk.setElement(voxelPos, dirt);
                }
            }
        }
    }
}

void generatePlatform(Chunk &chunk) {
    if (chunk.getChunkPos().y > 0) {
        return;
    }

    Element &light = ElementRegistry::getElementByName("Light");
    Element &dirt = ElementRegistry::getElementByName("Dirt");

    const Vector3D pos = chunk.getChunkPos();
    for (int offX = 0; offX < Chunk::mapChunkSize; offX++) {
        for (int offZ = 0; offZ < Chunk::mapChunkSize; offZ++) {
            if (RNG::randomFloat(0, 1) < 0.01) {
                chunk.setElement((int) pos.x + offX, (int) pos.y, (int) pos.z + offZ, light);
            } else {
                chunk.setElement((int) pos.x + offX, (int) pos.y, (int) pos.z + offZ, dirt);
            }
        }
    }
}

void generateSponge(Chunk &chunk) {
    generatePlatform(chunk);

    Element &light = ElementRegistry::getElementByName("Light");
    Element &dirt = ElementRegistry::getElementByName("Dirt");

    const float scale = 0.5f;
    const Vector3D worldScale = Vector3D(2 * (int) GlobalVariables.chunkViewDistance * (int) Chunk::mapChunkSize);
    const Vector3D newSize = worldScale * scale;
    const Vector3D center = (worldScale - newSize) / 2 * Vector3D(1, 0, 1) + Vector3D(0, 2, 0);
    const Vector3D pos = chunk.getChunkPos();

    for (int offX = 0; offX < Chunk::mapChunkSize; offX++) {
        for (int offY = 0; offY < Chunk::mapChunkSize; offY++) {
            for (int offZ = 0; offZ < Chunk::mapChunkSize; offZ++) {
                const Vector3D offset = Vector3D(offX, offY, offZ) + pos;
                const Vector3D scaledOffset = (offset - center) / scale;
                const Vector3D normPos = scaledOffset / worldScale;

                Vector3D voxel = (normPos * 3 - 1).floor();
                Vector3D absVoxel = voxel.abs();
                if (absVoxel.x > 1 || absVoxel.y > 1 || absVoxel.z > 1) {
                    continue;
                }

                int iter = 0;
                bool hit = true;
                while (iter <= 4) {
                    absVoxel = voxel.abs();
                    if (absVoxel.x + absVoxel.y + absVoxel.z <= 1) {
                        hit = false;
                        break;
                    }

                    iter++;

                    const auto power = (float) glm::pow(3, iter);
                    const Vector3D location = normPos * power;
                    voxel = (location % 3) - 1;
                }

                if (hit) {
                    chunk.setElement((int) pos.x + offX, (int) pos.y + offY, (int) pos.z + offZ, dirt);
                }
            }
        }
    }
}

void Chunk::buildTheChunk() {
    if (isBuild) {
        return;
    }

    isBuild = true;
    updateAllBuffers = true;

    testImageTest = TextureManager::create3DTexture(
            mapChunkSize, mapChunkSize, mapChunkSize,
            GL_R8, GL_RED, GL_UNSIGNED_BYTE, nullptr);

//    generateSponge(*this);
//    generateMandelBulb(*this);
}

void Chunk::updateBuffers() {
    if (!isBuild || !updateAllBuffers) {
        return;
    }

    updateAllBuffers = false;

//    const unsigned int voxelID = voxelImageBuffer.getID();
//    const unsigned int bitmaskID = bitmaskImageBuffer.getID();
//    glDeleteTextures(1, &voxelID);
//    glDeleteTextures(1, &bitmaskID);

    if (isEmpty()) {
        return;
    }

//    voxelImageBuffer.create(grid);
//    bitmaskImageBuffer.create(bitGrid);
}

void Chunk::setElement(const int x, const int y, const int z, const Element &element) {
    if (outBounds(x, y, z)) {
        return;
    }

//        awakeGrid(x, y, z);

    const unsigned int idx = getIDXRelativeToChunk(x, y, z);

    const unsigned int id = element.getID();
    const unsigned int previousID = grid[idx];
    if (id == previousID) {
        return;
    }

    grid[idx] = id;
    updateAllBuffers = true;

    if (id != ElementRegistry::emptyID && previousID != ElementRegistry::emptyID) {
        return;
    }

    const int counterDelta = id == ElementRegistry::emptyID ? -1 : 1;
    const unsigned int bitmaskIDX = getBitmaskIDXRelativeToChunk(x, y, z);

    totalElementAmount += counterDelta;
    bitGrid[bitmaskIDX] += counterDelta;
}

void Chunk::setElement(Vector3D pos, const Element &e) {
    setElement((int) pos.x, (int) pos.y, (int) pos.z, e);
}

Element Chunk::getElement(const int x, const int y, const int z) {
    if (outBounds(x, y, z)) {
        return ElementRegistry::emptyElement;
    }

    const unsigned int id = grid[getIDXRelativeToChunk(x, y, z)];
    return ElementRegistry::getElementByID(id);
}

Element Chunk::getElement(Vector3D pos) {
    return getElement((int) pos.x, (int) pos.y, (int) pos.z);
}

bool Chunk::isEmpty() const {
    return totalElementAmount == 0;
}

unsigned int Chunk::getIDXRelativeToChunk(const int x, const int y, const int z) const {
    return Chunk::getIDX(x - (int) chunkPos.x, y - (int) chunkPos.y, z - (int) chunkPos.z);
}

unsigned int Chunk::getIDX(const int x, const int y, const int z) {
    return x + (y * mapChunkSize) + (z * mapChunkSize * mapChunkSize);
}

unsigned int Chunk::getBitmaskIDXRelativeToChunk(int x, int y, int z) const {
    return Chunk::getBitmaskIDX(x - (int) chunkPos.x, y - (int) chunkPos.y, z - (int) chunkPos.z);
}

unsigned int Chunk::getBitmaskIDX(const int x, const int y, const int z) const {
    const unsigned int bitX = x / mapBitmaskSize;
    const unsigned int bitY = y / mapBitmaskSize;
    const unsigned int bitZ = z / mapBitmaskSize;
    return bitX + bitY * (int) bitmaskScale.x + bitZ * (int) bitmaskScale.x * (int) bitmaskScale.y;
}

bool Chunk::outBounds(const int x, const int y, const int z) const {
    return (x < chunkPos.x || x >= chunkPos.x + mapChunkSize || y < chunkPos.y || y >= chunkPos.y + mapChunkSize ||
            z < chunkPos.z ||
            z >= chunkPos.z + mapChunkSize);
}

ImageBuffer3D &Chunk::getVoxelBuffer() {
    return voxelImageBuffer;
}

ImageBuffer3D &Chunk::getBitmaskBuffer() {
    return bitmaskImageBuffer;
}

bool Chunk::shouldUpdateBuffers() const {
    return updateAllBuffers;
}

const Vector3D &Chunk::getChunkPos() const {
    return chunkPos;
}

bool Chunk::operator==(const Chunk &chunk) const {
    return chunkPos == chunk.chunkPos;
}

bool Chunk::operator==(Chunk &chunk) const {
    return chunkPos == chunk.chunkPos;
}

bool Chunk::operator!=(const Chunk &chunk) const {
    return chunkPos != chunk.chunkPos;
}

bool Chunk::operator!=(Chunk &chunk) const {
    return chunkPos != chunk.chunkPos;
}
