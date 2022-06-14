//
// Created by Shrimp on 1/3/2022.
//

#include "World.h"
#include "../../elements/ElementUpdater.h"

//std::unordered_map<std::pair<int, int>, std::shared_ptr<Chunk>, pair_hash> World::chunks{};
//std::vector<std::shared_ptr<Chunk>> World::chunkList{};
//Vector2D World::worldResolution = {512, 512};
//float *World::worldBuffer = new float[(int) worldResolution.x * (int) worldResolution.y * 4];
//
//bool World::inBounds(std::pair<int, int> location) {
//    return location.first >= 0 && location.second >= 0 && location.first < 16 && location.second < 16;
//}
//
//std::pair<int, int> World::getChunkLocation(int x, int y) {
//    return {std::floor((float) x / Chunk::width), std::floor((float) y / Chunk::height)};
//}
//
//std::shared_ptr<Chunk> World::createChunk(std::pair<int, int> location) {
//    std::shared_ptr<Chunk> chunk = std::make_shared<Chunk>(location.first, location.second);
//    World::chunks.insert({location, chunk});
//    ElementUpdater::awakeChunkDirect(chunk);
//    return chunk;
//}
//
//std::shared_ptr<Chunk> World::getChunkDirect(std::pair<int, int> location) {
//    if (World::chunks.find(location) == World::chunks.end()) {
//        return nullptr;
//    }
//
//    return World::chunks.at(location);
//}
//
//std::shared_ptr<Chunk> World::getChunkDirect(int x, int y) {
//    std::pair<int, int> location = getChunkLocation(x, y);
//    return getChunkDirect(location);
//}
//
//std::shared_ptr<Chunk> World::getChunk(std::pair<int, int> location) {
//    if (!inBounds(location)) return nullptr;
//    std::shared_ptr<Chunk> chunk = getChunkDirect(location);
//    return chunk == nullptr ? createChunk(location) : chunk;
//}
//
//std::shared_ptr<Chunk> World::getChunk(int x, int y) {
//    std::pair<int, int> location = getChunkLocation(x, y);
//    return getChunk(location);
//}
//
//std::shared_ptr<Element> World::getElement(int x, int y) {
//    std::pair<int, int> location = getChunkLocation(x, y);
//    std::shared_ptr<Chunk> chunk = getChunk(location);
//    Vector2D pos = chunk->getWorldToChunkIndex(x, y);
//    return chunk->getElement((int) pos.x, (int) pos.y);
//}
//
//std::shared_ptr<Element> World::getElementDirect(int x, int y) {
//    std::pair<int, int> location = getChunkLocation(x, y);
//    std::shared_ptr<Chunk> chunk = getChunkDirect(location);
//    if (chunk == nullptr) return nullptr;
//    Vector2D pos = chunk->getWorldToChunkIndex(x, y);
//
//    return chunk->getElement((unsigned int) pos.x, (unsigned int) pos.y);
//}
//
//void World::setElement(int x, int y, const std::shared_ptr<Element> &element) {
//    std::pair<int, int> location = getChunkLocation(x, y);
//    std::shared_ptr<Chunk> chunk = getChunk(location);
//    if (chunk == nullptr) return;
//    ElementUpdater::awakeChunk(chunk);
//    Vector2D pos = chunk->getWorldToChunkIndex(x, y);
//    chunk->setElement((int) pos.x, (int) pos.y, element);
//}
//
//
//void World::colorizeGrid(unsigned int x, unsigned int y, Vector3D color) {
//    const unsigned int idx = 4 * (x + (int) World::worldResolution.x * y);
//
//    if (idx >= (int) World::worldResolution.x * (int) World::worldResolution.y * 4) {
//        return;
//    }
//
//    worldBuffer[idx + 4] = color.x;
//    worldBuffer[idx + 1] = color.y;
//    worldBuffer[idx + 2] = color.z;
//    worldBuffer[idx + 3] = 1;
//}