cmake_minimum_required(VERSION 3.16.3)

project(3DSand CXX C)
set(CMAKE_CXX_STANDARD 17)

set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
set(CMAKE_EXE_LINKER_FLAGS "-static")

add_executable(3DSand
        Main.cpp
        src/core/GlobalVariables.cpp src/utils/Vector3D.cpp
        src/display/DisplayManager.cpp src/elements/Element.cpp
        src/elements/ElementRegistry.cpp src/shaders/BasicShader.cpp
        src/shaders/DisplayShader.cpp src/core/TextureManager.cpp
        src/game/world/World.cpp src/core/ImGuiManager.h
        src/game/world/Chunk.cpp src/core/RNG.cpp
        src/elements/ElementUpdater.cpp src/renderers/MasterRenderer.cpp
        src/renderers/MasterRenderer.h src/core/AttachmentManager.cpp
        src/core/AttachmentManager.h src/core/imageBuffers/ImageBuffer.cpp
        src/core/imageBuffers/ImageBuffer.h src/core/imageBuffers/ImageBuffer2D.cpp
        src/core/imageBuffers/ImageBuffer2D.h src/core/RawModel.cpp
        src/core/RawModel.h src/shaders/RayTracerShader.cpp
        src/shaders/RayTracerShader.h src/game/Camera.cpp
        src/game/Camera.h src/utils/Vector2D.cpp
        src/utils/Vector2D.h src/core/Loader.cpp
        src/core/Loader.h src/core/ImGuiManager.cpp
        src/core/inputs/Mouse.cpp src/core/inputs/Mouse.h src/core/Signal.h src/core/imageBuffers/ImageBuffer3D.cpp src/core/imageBuffers/ImageBuffer3D.h src/elements/weirds/Any.h src/elements/weirds/Empty.h src/elements/solids/moveables/Light.h src/game/world/ChunkManager.cpp src/game/world/ChunkManager.h src/core/SSBO.cpp src/core/SSBO.h src/threads/BasicThread.cpp src/threads/BasicThread.h src/threads/ChunkGenerationThread.cpp src/threads/ChunkGenerationThread.h src/elements/solids/moveables/Dirt.h src/shaders/AfterEffectShader.h src/shaders/AfterEffectShader.cpp src/elements/solids/moveables/Glass.h src/shaders/ComputeShader.cpp src/shaders/ComputeShader.h src/shaders/WorldGenerationShader.cpp src/shaders/WorldGenerationShader.h)

include(FetchContent)

#FetchContent_Declare(glad
#        GIT_REPOSITORY https://github.com/Dav1dde/glad
#        GIT_TAG v0.1.36
#        )

FetchContent_Declare(glfw
        GIT_REPOSITORY https://github.com/glfw/glfw
        GIT_TAG 3.3.7
        )

FetchContent_Declare(glm
        GIT_REPOSITORY https://github.com/g-truc/glm
        GIT_TAG 0.9.9.8
        )

FetchContent_Declare(imgui
        GIT_REPOSITORY https://github.com/ocornut/imgui
        GIT_TAG v1.84.2
        )

FetchContent_MakeAvailable(glm glfw)
target_link_libraries(3DSand glm glfw)

FetchContent_GetProperties(imgui)
if (NOT imgui_POPULATED)
    FetchContent_Populate(imgui)

    add_library(lib_imgui
            ${imgui_SOURCE_DIR}/imgui.cpp
            ${imgui_SOURCE_DIR}/imgui_draw.cpp
            ${imgui_SOURCE_DIR}/imgui_widgets.cpp
            ${imgui_SOURCE_DIR}/imgui_tables.cpp
            ${imgui_SOURCE_DIR}/backends/imgui_impl_opengl3.cpp
            ${imgui_SOURCE_DIR}/backends/imgui_impl_glfw.cpp)

    target_include_directories(lib_imgui PUBLIC
            ${imgui_SOURCE_DIR}
            ${imgui_SOURCE_DIR}/backends
            ${glfw_SOURCE_DIR}/include)
endif ()
target_link_libraries(3DSand lib_imgui)

include_directories(depends/glad/include)
add_library(glad STATIC depends/glad/src/glad.c)
target_link_libraries(3DSand glad)

find_package(OpenGL REQUIRED)
target_link_libraries(3DSand OpenGL::GL)
