//
// Created by Shrimp on 12/30/2021.
//

#ifndef INC_2DSAND_GLOBALVARIABLES_H
#define INC_2DSAND_GLOBALVARIABLES_H


#include "RNG.h"
#include "../renderers/MasterRenderer.h"
#include "../game/Camera.h"
#include "Loader.h"
#include "ImGuiManager.h"
#include "inputs/Mouse.h"
#include "../game/world/ChunkManager.h"

struct GlobalVariables_ {
public:
    unsigned int currentFrame = 0;

    RNG rand;

    Mouse mouse;
    Camera camera;

    bool pathTracing = false;
    bool drawBitmaskBorders = false;

    // View
    std::string selectedOutput = "color";

    int spatialScale = 1; // 3
    float spatialSigma = 0.01; // 0.85

    bool dramaticZoom = false;
    // View

    // World
    int maxViewDistance = 5000; // 500

    const unsigned int chunkViewDistance = 4;
    ChunkManager chunkManager = ChunkManager(16 * chunkViewDistance, 2 * chunkViewDistance, 16 * chunkViewDistance);
    // World

    Loader loader;
    DisplayManager displayManager;
    ImGuiManager imGuiManager;
    MasterRenderer renderer;
};

extern GlobalVariables_ GlobalVariables;


#endif //INC_2DSAND_GLOBALVARIABLES_H
