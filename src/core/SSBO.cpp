//
// Created by Shrimp on 4/17/2022.
//

#include "glad/glad.h"
#include "SSBO.h"

SSBO::SSBO(const int index, const int usage) : index(index), usage(usage) {}

void SSBO::create(std::vector<uint64_t> data) {
    if (id != 0) {
        glDeleteBuffers(1, &id);
    }

    glGenBuffers(1, &id);
    glBindBuffer(GL_SHADER_STORAGE_BUFFER, id);
    glBufferData(GL_SHADER_STORAGE_BUFFER, (int) (data.size() * sizeof(uint64_t)), data.data(), usage);
    glBindBufferBase(GL_SHADER_STORAGE_BUFFER, index, id);
    glBindBuffer(GL_SHADER_STORAGE_BUFFER, 0);
}

void SSBO::bind() const {
    glBindBufferBase(GL_SHADER_STORAGE_BUFFER, index, id);
}
