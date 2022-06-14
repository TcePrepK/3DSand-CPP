//
// Created by Shrimp on 4/23/2022.
//

#ifndef INC_2DSAND_CHUNKGENERATIONTHREAD_H
#define INC_2DSAND_CHUNKGENERATIONTHREAD_H


#include <iostream>
#include <stack>
#include "BasicThread.h"
#include "../core/GlobalVariables.h"

class ChunkGenerationThread : public BasicThread {
public:
    explicit ChunkGenerationThread(unsigned int threadNum) : threadNum(threadNum), lastIDX(threadNum),
                                                             BasicThread("chunkGeneration") {}

private:
    unsigned int threadNum;
    unsigned int lastIDX;

    std::vector<Chunk *> *generateList = &GlobalVariables.chunkManager.getChunkGenerateList();

    void loop() override {
        if (lastIDX >= generateList->size()) {
            kill();
            return;
        }

        generateList->at(lastIDX)->buildTheChunk();
        lastIDX += 4;
    }
};


#endif //INC_2DSAND_CHUNKGENERATIONTHREAD_H
