#version 450 core

uniform vec2 resolution;

uniform sampler2D colorAttachment;
uniform sampler2D depthAttachment;
uniform sampler2D rayDirAttachment;
uniform sampler2D frameCountAttachment;
uniform sampler2D normalAttachment;
uniform sampler2D lightAttachment;

uniform bool columnCheck;

uniform int scale;
uniform float sigma;

layout (location = 0) out vec3 outColor;

#define maxDistance 500
#define e 2.71828
#define pi 3.14159
#define sqrttwopi 2.50662

float calculateKernel(in float v) {
    return 1 / (sigma * sqrttwopi) * pow(e, -(v * v) / (2 * sigma * sigma));
}

float calculateWeight(in vec3 mainHitPos, in vec3 mainNormal, in vec3 offsetHitPos, in vec3 offsetNormal) {
    vec3 d = mainNormal - offsetNormal;
    if (dot(d, d) > 0.1) {
        return 0;
    }

    vec3 dmPos = (mainHitPos * mainNormal);
    vec3 doPos = (offsetHitPos * offsetNormal);
    d = dmPos - doPos;
    if (dot(d, d) > 1) {
        return 0;
    }

    return 1;
}

void main(void) {
    const vec2 mainPixel = gl_FragCoord.xy / resolution;
    const ivec3 mainNormal = ivec3(texture(normalAttachment, mainPixel).rgb);

    const float mainDepth = texture(depthAttachment, mainPixel).r;
    const vec3 mainRayDir = texture(rayDirAttachment, mainPixel).rgb;

    const vec3 mainHitPos = mainRayDir * (mainDepth * maxDistance);

    float sum = 0;
    vec3 color = vec3(0);
    for (int i = -scale; i <= scale; i++) {
        const vec2 offset = vec2(columnCheck ? 0 : i, columnCheck ? i : 0);
        const vec2 offsetPixel = mainPixel + offset / resolution;

        const ivec3 offsetNormal = ivec3(texture(normalAttachment, offsetPixel).rgb);
        const float offsetDepth = texture(depthAttachment, offsetPixel).r;
        const vec3 offsetRayDir = texture(rayDirAttachment, offsetPixel).rgb;
        const vec3 offsetHitPos = offsetRayDir * (offsetDepth * maxDistance);

        const float weight = calculateWeight(mainHitPos, mainNormal, offsetHitPos, offsetNormal);
        if (weight == 0) {
            continue;
        }

        const float kernel = calculateKernel(i);
        sum += kernel;
        color += texture(colorAttachment, offsetPixel).rgb * kernel;
    }

    if (sum == 0) {
        outColor = vec3(0);
        return;
    }

    outColor = color / sum;
}