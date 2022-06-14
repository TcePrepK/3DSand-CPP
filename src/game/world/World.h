//
// Created by Shrimp on 1/3/2022.
//

#ifndef INC_2DSAND_WORLD_H
#define INC_2DSAND_WORLD_H


#include <unordered_map>
#include "Chunk.h"
#include "../../utils/Pair_Hash.h"
#include "../../elements/Element.h"

struct World {
public:
//    static std::unordered_map<std::pair<int, int>, std::shared_ptr<Chunk>, pair_hash> chunks;
//    static std::vector<std::shared_ptr<Chunk>> chunkList;
//
//    static Vector2D worldResolution;
//    static float *worldBuffer;
//
//    static bool inBounds(std::pair<int, int> location);
//
//    static std::pair<int, int> getChunkLocation(int x, int y);
//
//    static std::shared_ptr<Chunk> createChunk(std::pair<int, int> location);
//
//    static std::shared_ptr<Chunk> getChunkDirect(std::pair<int, int> location);
//
//    static std::shared_ptr<Chunk> getChunkDirect(int x, int y);
//
//    static std::shared_ptr<Chunk> getChunk(std::pair<int, int> location);
//
//    static std::shared_ptr<Chunk> getChunk(int x, int y);
//
//    static std::shared_ptr<Element> getElement(int x, int y);
//
//    static std::shared_ptr<Element> getElementDirect(int x, int y);
//
//    static void setElement(int x, int y, const std::shared_ptr<Element> &element);
//
//    static void colorizeGrid(unsigned int x, unsigned int y, Vector3D color);
};


#endif //INC_2DSAND_WORLD_H
