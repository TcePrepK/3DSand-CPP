//
// Created by Shrimp on 1/7/2022.
//

#include <algorithm>
#include "ElementUpdater.h"
#include "../game/world/World.h"

//void ElementUpdater::prepareUpdate() {
//    for (const std::shared_ptr<Chunk> &chunk: World::chunkList) {
//        if (chunk->filledPixelAmount != 0) continue;
//
//        std::pair<int, int> location = World::getChunkLocation(chunk->chunkX, chunk->chunkY);
//        // chunks.erase(location);
//        // chunkList.erase(chunkList.begin() + i);
//        // i--;
//
//        // delete chunk;
//    }
//}
//
//void ElementUpdater::update() {
////    prepareUpdate();
//    for (const std::shared_ptr<Chunk> &chunk: World::chunkList) {
//        for (int offX = 0; offX < Chunk::width; offX++) {
//            for (int offY = 0; offY < Chunk::height; offY++) {
//                std::shared_ptr<Element> e = chunk->getElement(offX, offY);
//                if (e == nullptr) {
//                    continue;
//                }
//
//                Vector2D pos = chunk->getChunkToWorldIndex(offX, offY);
//                Vector2D newPos = e->update((int) pos.x, (int) pos.y);
//                if (newPos.x == pos.x && newPos.y == pos.y) {
//                    continue;
//                }
//
//                std::shared_ptr<Chunk> toChunk = World::getChunk((int) newPos.x, (int) newPos.y);
//                if (toChunk == nullptr) {
//                    continue;
//                }
//
//                if (toChunk != chunk) {
//                    awakeChunk(toChunk);
//                }
//
//                Vector2D from = {offX, offY};
//                Vector2D to = newPos - Vector2D(toChunk->tileX, toChunk->tileY);
//
//                chunk->moveElement(toChunk, from, to);
//            }
//        }
//    }
//
//    for (const std::shared_ptr<Chunk> &chunk: World::chunkList) {
//        chunk->updateChanges();
//    }
//}
//
//void ElementUpdater::awakeChunkDirect(const std::shared_ptr<Chunk> &chunk) {
//    World::chunkList.push_back(chunk);
//}
//
//void ElementUpdater::awakeChunk(const std::shared_ptr<Chunk> &chunk) {
//    if (std::find(World::chunkList.begin(), World::chunkList.end(), chunk) != World::chunkList.end()) {
//        return;
//    }
//
//    awakeChunkDirect(chunk);
//}
