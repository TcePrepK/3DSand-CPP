//
// Created by Shrimp on 4/23/2022.
//

#ifndef INC_2DSAND_BASICTHREAD_H
#define INC_2DSAND_BASICTHREAD_H


#include <atomic>
#include <thread>

#include <iostream>
#include <utility>
#include "../core/GlobalVariables.h"

class BasicThread {
protected:
    explicit BasicThread(std::string name) : name(std::move(name)) {}

private:
    std::thread thread;
    std::atomic<bool> isDead = true;
    std::string name;

    void run() {
        std::cout << "Starting " << name << "!" << std::endl;
        while (!isDead) {
            loop();
            breath();
        }
    }

    virtual void loop() {
        std::cout << "Undefined thread function" << std::endl;
        kill();
    }

    static void breath() {
        std::this_thread::sleep_for(std::chrono::milliseconds(1));
    }

public:
    void start() {
        isDead = false;
        thread = std::thread(&BasicThread::run, this);
    }

    void kill() {
        if (isDead) {
            return;
        }

        isDead = true;

        unsigned int elements = 0;

        auto chunkList = GlobalVariables.chunkManager.getChunkList();
        for (auto &i: chunkList) {
            if (!i) {
                continue;
            }

            elements += (*i).totalElementAmount;
        }

        const Vector3D worldScale = Vector3D(2 * (int) GlobalVariables.chunkViewDistance * (int) Chunk::mapChunkSize);
        std::cout <<
                  (float) elements /
                  (worldScale.x * worldScale.y * worldScale.z) * 100
                  << "%\n";
    }

};


#endif //INC_2DSAND_BASICTHREAD_H
