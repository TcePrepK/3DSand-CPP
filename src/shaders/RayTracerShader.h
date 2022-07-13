//
// Created by Shrimp on 4/10/2022.
//

#ifndef INC_2DSAND_RAYTRACERSHADER_H
#define INC_2DSAND_RAYTRACERSHADER_H


#include "BasicShader.h"

class RayTracerShader : public BasicShader {
private:
    int viewMatrix{};
    int displayRes{};
    int viewportRes{};
    int lookFrom{};
    int lookTo{};

    int oldMVPMatrix{};
    int oldViewMatrix{};
    int oldCameraPos{};

    int randVector2D{};
    int sunPosition{};
    int textureScale{};

    int isPathTracing{};
    int isRenderingBitmask{};
    int bitmaskSize{};
    int lightBounceAmount{};

    int maxDistance{};
    int chunkScale{};

public:
    RayTracerShader();

    void loadResolutions() const;

    void loadCameraVariables() const;

    void loadMaxDistance(int num) const;

    void loadChunkScale() const;

    void loadOldVariables() const;

    void loadPathTracingSetting() const;

    void loadBitmaskBorderSetting() const;

    void loadLightBounceAmount() const;

    void loadRandomVector() const;

    void loadSunPosition(float angle) const;
};


#endif //INC_2DSAND_RAYTRACERSHADER_H
