struct Ray {
    vec3 pos;
    vec3 dir;
    vec3 color;
};

struct HitRecord {
    vec3 position;
    uvec3 hitVoxel;
    vec3 normal;
    float distance;
    bool light;
    int id;
};

float map(float n, float start1, float stop1, float start2, float stop2) {
    const float newval = (n - start1) / (stop1 - start1) * (stop2 - start2) + start2;
    if (start2 < stop2) {
        return clamp(newval, start2, stop2);
    } else {
        return clamp(newval, stop2, start2);
    }
}

vec3 at(vec3 pos, vec3 dir, float time) {
    return pos + dir * time;
}

vec3 at(Ray ray, float time) {
    return ray.pos + ray.dir * time;
}

bool closeEnough(float n, float v, float e) {
    return abs(n - v) < e;
}

vec2 randState = gl_FragCoord.xy * randVector2D;
vec2 rand2D() {
    randState.x = fract(sin(dot(randState.xy, vec2(12.9898, 78.233))) * 43758.5453);
    randState.y = fract(sin(dot(randState.xy, vec2(12.9898, 78.233))) * 43758.5453);

    return randState * 2.0 - 1.0;
}

//ivec2 intTexture(sampler2D image, vec2 position) {
//    return ivec2(texture(image, position) * 255);
//}
//
//ivec3 intTexture(sampler3D image, vec3 position) {
//    return ivec3(texture(image, position) * 255);
//}

bool inBounds(vec3 v, vec3 s) {
    return !(v.x < 0 || v.x >= s.x || v.y < 0 || v.y >= s.y || v.z < 0 || v.z >= s.z);
}

vec3 getSkyColor(vec3 dir) {
    const vec3 skyColor = vec3(0.5, 0.7, 1);
    const vec3 sunColor = vec3(1);
    const vec3 moonColor = vec3(0);

    //    return moonColor;

    float product = dot(dir, sunPosition) * 2 - 1;
    if (product > 0) {
        float factor = max(0, product);
        factor = min(0.99, factor) + 0.01;
        factor = pow(factor, 100);

        return mix(skyColor, sunColor, factor);
    }

    float factor = max(0, -product / 3);
    factor = min(0.9999, factor) + 0.0001;
    factor = pow(factor, 1);

    return mix(skyColor, moonColor, factor);
}

vec3 randomizeNormal(vec3 normal) {
    return normalize(vec3(normal.xy + rand2D(), normal.z));
}

vec3 getNewDirection() {
    vec2 rng = rand2D();
    float v = rng.x;
    float u = rng.y;

    float r = sqrt(1 - u * u);
    float phi = 2 * 3.1415 * v;

    vec3 result = vec3(cos(phi) * r, sin(phi) * r, u);

    if (result.x == 0) {
        result.x = 0.001;
    }
    if (result.y == 0) {
        result.y = 0.001;
    }
    if (result.z == 0) {
        result.z = 0.001;
    }

    return normalize(result);
}

vec2 AABB(vec3 rayPos, vec3 rayDir, vec3 boxMin, vec3 boxMax) {
    vec3 tMin = (boxMin - rayPos) / rayDir;
    vec3 tMax = (boxMax - rayPos) / rayDir;
    vec3 t1 = min(tMin, tMax);
    vec3 t2 = max(tMin, tMax);
    float tNear = max(max(t1.x, t1.y), t1.z);
    float tFar = min(min(t2.x, t2.y), t2.z);
    return vec2(tNear, tFar);
}

bool testForBorder(Ray ray, float distance, vec3 size) {
    const vec3 pos = fract(at(ray, distance) / size);
    const float e = pow(distance, 0.5) / 500;
    const bool closeX = closeEnough(pos.x, 0, e);
    const bool closeY = closeEnough(pos.y, 0, e);
    const bool closeZ = closeEnough(pos.z, 0, e);
    return ((closeX && closeY) || (closeX && closeZ) || (closeY && closeZ));
}

void DDAStep(ivec3 stepDir, vec3 tS, inout uvec3 gridCoords, inout vec3 tV, out float dist, out int idx) {
    dist = min(min(tV.x, tV.y), tV.z);
    idx = dist == tV.x ? 0 : dist == tV.y ? 1 : 2;

    if (idx == 0) {
        gridCoords.x += stepDir.x;
        tV.x += tS.x;
    } else if (idx == 1) {
        gridCoords.y += stepDir.y;
        tV.y += tS.y;
    } else {
        gridCoords.z += stepDir.z;
        tV.z += tS.z;
    }
}

void DDA(inout Ray ray, inout HitRecord record) {
    const float off = 0.001;

    const bvec3 dirSign = greaterThanEqual(ray.dir, vec3(0));

    const ivec3 stepDir = mix(ivec3(-1), ivec3(1), dirSign);
    const ivec3 voxExit = mix(ivec3(0), ivec3(1), dirSign);
    const vec3 rayInverse = 1 / ray.dir;

    // Calculating world
    vec3 tMin = (0 - ray.pos) / ray.dir;
    vec3 tMax = (textureScale - ray.pos) / ray.dir;
    vec3 t1 = min(tMin, tMax);
    vec3 t2 = max(tMin, tMax);
    float realClosestTime = max(max(t1.x, t1.y), t1.z);
    float realFartestTime = min(min(t2.x, t2.y), t2.z);
    int idx = realClosestTime == t1.x ? 0 : realClosestTime == t1.y ? 1 : 2;

    float closestTime = realClosestTime;
    float fartestTime = realFartestTime;

    ray.color = vec3(1);

    if (closestTime < fartestTime) {
        ray.color = vec3(0.9);
    }

    if (closestTime < 0) {
        closestTime = 0;
    }

    if (fartestTime <= closestTime) {
        fartestTime = closestTime = maxDistance;
    }

    //    if (fartestTime - closestTime > maxDistance) {
    //        fartestTime = closestTime + maxDistance;
    //    }

    record.distance = closestTime;

    uvec3 gridCoords = uvec3(floor(at(ray, record.distance + off)));

    vec3 tV = rayInverse * (vec3(gridCoords + voxExit) - ray.pos);
    vec3 tS = rayInverse * vec3(stepDir);

    int hitId = 0;
    while (record.distance < fartestTime - off && record.distance < maxDistance) {
        ivec3 chunkPos = ivec3(gridCoords / 32);
        uint chunkIDX = chunkPos.x + (chunkPos.y * chunkScale.x) + (chunkPos.z * chunkScale.x * chunkScale.y);
        vec3 chunkOffset = gridCoords % 32 / 32.0;

        bool jumpChunk = chunkBuffer.textures[chunkIDX] == uvec2(0);

        int jumpAmount = jumpChunk ? 32 : bitmaskSize;
        int bitmask = int(texture(sampler3D(bitmaskBuffer.textures[chunkIDX]), chunkOffset).r * 255);
        if (false && (jumpChunk || bitmask == 0)) {
            if (isRenderingBitmask) {
                if (testForBorder(ray, record.distance, stepDir * jumpAmount)) {
                    ray.color *= vec3(0.6);
                } else if (ray.color == vec3(1)) {
                    ray.color = vec3(0.1, 2, 0.1);
                }
            }

            vec3 currPos = at(ray, record.distance);
            const vec3 distToBorder = rayInverse * (voxExit * jumpAmount - (fract(currPos) + (gridCoords % jumpAmount)));
            const float time = min(min(distToBorder.x, distToBorder.y), distToBorder.z);
            idx = time == distToBorder.x ? 0 : time == distToBorder.y ? 1 : 2;

            record.distance += time + off;
            currPos = at(ray, record.distance);
            gridCoords = ivec3(floor(currPos));
            tV = record.distance + rayInverse * (voxExit - fract(currPos));
        } else {
            const int currentID = int(texture(sampler3D(chunkBuffer.textures[chunkIDX]), chunkOffset).r * 255);
            if (currentID == 3 && hitId != 3) {
                ray.color *= abs(gridCoords / textureScale - 0.5) * 2 * 2;
                //                ray.color *= vec3(1, 0.7, 0.7);
            }

            hitId = currentID;

            if (hitId != 0) {
                if (hitId == 1) {
                    record.light = true;
                }

                if (hitId != 3) {
                    break;
                }
            }

            DDAStep(stepDir, tS, gridCoords, tV, record.distance, idx);
        }

        if (isRenderingBitmask) {
            if (testForBorder(ray, record.distance, stepDir * jumpAmount * 2)) {
                ray.color *= vec3(0.6);
            } else if (ray.color == vec3(1)) {
                ray.color = vec3(0.1, 2, 0.1);
            }
        }

        //        int bitmask = int(texture(bitmaskTexture, texturePos).r * 255);
        //        if (bitmask == 0) {
        //            if (isRenderingBitmask) {
        //                if (testForBorder(ray, record.distance, stepDir * 4)) {
        //                    ray.color = vec3(0);
        //                } else if (ray.color != vec3(0)) {
        //                    ray.color = vec3(0.1, 2, 0.1);
        //                }
        //            }
        //
        //            vec3 currPos = at(ray, record.distance);
        //            const vec3 distToBorder = rayInverse * (voxExit * 4 - (fract(currPos) + (gridCoords % 4)));
        //            const float time = min(min(distToBorder.x, distToBorder.y), distToBorder.z);
        //            idx = time == distToBorder.x ? 0 : time == distToBorder.y ? 1 : 2;
        //
        //            record.distance += time + off;
        //            currPos = at(ray, record.distance);
        //            gridCoords = ivec3(floor(currPos));
        //            tV = record.distance + rayInverse * (voxExit - fract(currPos));
        //        } else {
        //            if (isRenderingBitmask && testForBorder(ray, record.distance, stepDir * 4)) {
        //                ray.color = vec3(0);
        //            }
        //
        //            hitId = int(texture(worldTexture, texturePos).r * 255);
        //            if (hitId != 0) {
        //                if (hitId == 1) {
        //                    record.light = true;
        //                }
        //
        //                break;
        //            }
        //
        //            DDAStep(stepDir, tS, gridCoords, tV, record.distance, idx);
        //        }
    }

    if (hitId != 0 && hitId != 3) {
        if (idx == 0) {
            record.normal.x = -stepDir.x;
        } else if (idx == 1) {
            record.normal.y = -stepDir.y;
        } else {
            record.normal.z = -stepDir.z;
        }
    }

    record.position = at(ray, record.distance);
    record.hitVoxel = gridCoords;

    const vec3 skyColor = getSkyColor(ray.dir);
    if (hitId == 0 || hitId == 3) {
        ray.color *= skyColor;
        record.light = true;
    } else {
        vec3 cubeColor = vec3(0);
        if (hitId == 2) {
            //            cubeColor = vec3(0.65, 0.4, 0.3);
            cubeColor = vec3(0.5, 0.2, 0.5);
        } else {
            //            cubeColor = vec3(1);
            //            cubeColor = abs(gridCoords / textureScale - 0.5) * 2;
            cubeColor = vec3(10);

        }

        ray.color *= cubeColor;
    }
}

HitRecord PrimaryDDA(inout Ray ray) {
    HitRecord record = HitRecord(vec3(0), ivec3(0), vec3(0), 0, false, 0);
    DDA(ray, record);

    outDepth = record.distance / maxDistance;

    return record;
}

HitRecord FinderDDA(inout Ray ray) {
    HitRecord record = HitRecord(vec3(0), ivec3(0), vec3(0), 0, false, 0);
    DDA(ray, record);

    return record;
}

bool LightDDA(inout Ray ray, inout HitRecord record) {
    DDA(ray, record);
    return record.light;
}

vec3 calculateHitColor(Ray ray, int depth) {
    float mult = 1;
    while (depth-- > 0) {
        HitRecord record = HitRecord(ray.pos, uvec3(0), vec3(0), 0, false, 0);
        DDA(ray, record);

        if (!record.light) {
            vec3 newDir = getNewDirection();
            if (dot(newDir + record.normal * 0.01, record.normal) < 0) {
                newDir *= -1;
            }

            ray = Ray(record.position, newDir, vec3(0));
            mult *= 0.5;
            continue;
        }

        return ray.color * mult;
    }

    return vec3(0);
}

float traceShadowCone(const vec3 pos, const vec3 dir, const float lightDist) {
    const float aperture = pi / 18;
    const float halfAperture = aperture / 2;
    const float tanHalfAperture = tan(halfAperture);
    const float sinHalfAperture = sin(halfAperture);

    float acc = 0;
    float distance = 1;
    while (distance < lightDist && acc < 1) {
        const float diameter = tanHalfAperture * distance;
        const float lodLevel = log2(sinHalfAperture * distance);

        const ivec3 voxelPos = ivec3(pos + distance * dir);
        if (!inBounds(voxelPos / textureScale, vec3(1))) {
            break;
        }

        const ivec3 chunkPos = ivec3(voxelPos / 32);
        const uint chunkIDX = chunkPos.x + (chunkPos.y * chunkScale.x) + (chunkPos.z * chunkScale.x * chunkScale.y);
        const vec3 chunkOffset = voxelPos % 32 / 32.0;
        const float voxel = textureLod(sampler3D(chunkBuffer.textures[chunkIDX]), chunkOffset, lodLevel).r;

        acc += (1 - acc) * voxel;
        distance += diameter * 2;
    }

    return 1 - pow(acc * 2, 0.2);
}

vec3 traceVoxelCone(const vec3 pos, const vec3 dir) {
    const float aperture = pi / 3;
    const float halfAperture = aperture / 2;
    const float tanHalfAperture = tan(halfAperture);
    const float sinHalfAperture = sin(halfAperture);

    vec4 color = vec4(0);
    float distance = 0.01;
    while (distance < maxDistance) {
        const float diameter = tanHalfAperture * distance;
        const float lodLevel = log2(sinHalfAperture * distance);

        const ivec3 voxelPos = ivec3(pos + distance * dir);
        if (!inBounds(voxelPos / textureScale, vec3(1))) {
            break;
        }

        const ivec3 chunkPos = ivec3(voxelPos / 32);
        const uint chunkIDX = chunkPos.x + (chunkPos.y * chunkScale.x) + (chunkPos.z * chunkScale.x * chunkScale.y);
        const vec3 chunkOffset = voxelPos % 32 / 32.0;
        const float voxel = textureLod(sampler3D(chunkBuffer.textures[chunkIDX]), chunkOffset, lodLevel).r;

        color += voxel;
        distance += diameter * 2;

        if (color.a >= 1) {
            break;
        }
    }

    return 1 - min(vec3(1), max(vec3(0), pow(color.rgb * 2, vec3(0.2))));
}

vec3 calculateOrthogonal(vec3 u) {
    u = normalize(u);
    vec3 v = vec3(0.99146, 0.11664, 0.05832);
    return abs(dot(u, v)) > 0.99999f ? cross(u, vec3(0, 1, 0)) : cross(u, v);
}

HitRecord ColorDDA(inout Ray ray) {
    HitRecord record = PrimaryDDA(ray);
    if (record.light) {
        //        outLight = ray.color;
        return record;
    }

    if (!isPathTracing) {
        ray.color = abs(record.hitVoxel / textureScale - 0.5) * 2;
        return record;
    }

    if (lightBounceAmount == 0) {
        return record;
    }

    // Light Bounces
    //    vec3 bouncePosition = record.position + record.normal * 0.001;
    //    vec3 bounceDirection = getNewDirection();
    //    float product = dot(bounceDirection, record.normal);
    //    if (product < 0) {
    //        bounceDirection *= -1;
    //        product *= -1;
    //    }

    vec3 randomDir = getNewDirection();
    float product = dot(randomDir, record.normal);
    if (product < 0) {
        randomDir *= -1;
    }

    vec3 lightColor = calculateHitColor(Ray(record.position + record.normal * 0.01, randomDir, vec3(0)), lightBounceAmount);
    ray.color *= lightColor;

    //    const vec3 normal = record.normal;
    //
    //    const vec3 ortho = normalize(calculateOrthogonal(normal));
    //    const vec3 orthoCross = normalize(cross(ortho, normal));
    //
    //    const vec3 corner = (ortho + orthoCross) / 2;
    //    const vec3 orthoCorner = (ortho - orthoCross) / 2;
    //
    //    const vec3 s1 = mix(normal, ortho, 0.5);
    //    const vec3 s2 = mix(normal, -ortho, 0.5);
    //    const vec3 s3 = mix(normal, orthoCross, 0.5);
    //    const vec3 s4 = mix(normal, -orthoCross, 0.5);
    //
    //    const vec3 c1 = mix(normal, corner, 0.5);
    //    const vec3 c2 = mix(normal, -corner, 0.5);
    //    const vec3 c3 = mix(normal, orthoCorner, 0.5);
    //    const vec3 c4 = mix(normal, -orthoCorner, 0.5);
    //
    //    const vec3 p = record.position;
    //    const vec3 coneColor = (
    //    traceVoxelCone(p, normal) +
    //    traceVoxelCone(p, s1) +
    //    traceVoxelCone(p, s2) +
    //    traceVoxelCone(p, s3) +
    //    traceVoxelCone(p, s4) +
    //    traceVoxelCone(p, c1) +
    //    traceVoxelCone(p, c2) +
    //    traceVoxelCone(p, c3) +
    //    traceVoxelCone(p, c4)
    //    ) / 9;

    //    const vec3 coneColor =
    //    traceVoxelCone(p, normal) *
    //    traceVoxelCone(p, s1) *
    //    traceVoxelCone(p, s2) *
    //    traceVoxelCone(p, s3) *
    //    traceVoxelCone(p, s4) *
    //    traceVoxelCone(p, c1) *
    //    traceVoxelCone(p, c2) *
    //    traceVoxelCone(p, c3) *
    //    traceVoxelCone(p, c4);

    //    ray.color *= coneColor;
    //
    //    const vec3 lightPosition = sunPosition * 1000;
    //    vec3 lightDir = lightPosition - p;
    //    const float distToLight = length(lightDir);
    //    lightDir /= distToLight;
    //
    //    const float shadow = traceShadowCone(p, lightDir, distToLight);
    //
    //    ray.color *= shadow;

    return record;
    // Light Bounces

    //    HitRecord lightRecord = HitRecord(vec3(0), ivec3(0), vec3(0), 0, false, 0);
    //    Ray lightRay = Ray(offHitPoint, randDir, vec3(0));
    //    if (LightDDA(lightRay, lightRecord)) {
    //        ray.color *= getSkyColor(randDir);
    //
    //        return record;
    //    }
    //
    //    ray.color = vec3(0);
    //    return record;
}
