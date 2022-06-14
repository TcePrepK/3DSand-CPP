//
// Created by Shrimp on 12/31/2021.
//

#include "../core/GlobalVariables.h"

void debug_callback(GLenum source, GLenum type, GLuint id, GLenum severity, GLsizei length, const GLchar *message,
                    const void *param) {

    std::string sourceStr;
    std::string typeStr;
    std::string severityStr;

    switch (source) {
        case GL_DEBUG_SOURCE_API:
            sourceStr = "GL_DEBUG_SOURCE_API";
            break;
        case GL_DEBUG_SOURCE_THIRD_PARTY:
            sourceStr = "GL_DEBUG_SOURCE_THIRD_PARTY";
            break;
        case GL_DEBUG_SOURCE_APPLICATION:
            sourceStr = "GL_DEBUG_SOURCE_APPLICATION";
            break;
        case GL_DEBUG_SOURCE_OTHER:
            sourceStr = "GL_DEBUG_SOURCE_OTHER";
            break;
        default:
            sourceStr = "unknown error";
            break;
    }

    switch (type) {
        case GL_DEBUG_TYPE_ERROR:
            typeStr = "GL_DEBUG_TYPE_ERROR";
            break;
        case GL_DEBUG_TYPE_DEPRECATED_BEHAVIOR:
            typeStr = "GL_DEBUG_TYPE_DEPRECATED_BEHAVIOR";
            break;
        case GL_DEBUG_TYPE_UNDEFINED_BEHAVIOR:
            typeStr = "GL_DEBUG_TYPE_UNDEFINED_BEHAVIOR";
            break;
        case GL_DEBUG_TYPE_PERFORMANCE:
            typeStr = "GL_DEBUG_TYPE_PERFORMANCE";
            break;
        case GL_DEBUG_TYPE_MARKER:
            typeStr = "GL_DEBUG_TYPE_MARKER";
            break;
        case GL_DEBUG_TYPE_PUSH_GROUP:
            typeStr = "GL_DEBUG_TYPE_PUSH_GROUP";
            break;
        case GL_DEBUG_TYPE_POP_GROUP:
            typeStr = "GL_DEBUG_TYPE_POP_GROUP";
            break;
        case GL_DEBUG_TYPE_OTHER:
            typeStr = "GL_DEBUG_TYPE_OTHER";
            break;
        default:
            typeStr = "unknown error";
            break;
    }

    switch (severity) {
        case GL_DEBUG_SEVERITY_HIGH:
            severityStr = "GL_DEBUG_SEVERITY_HIGH";
            break;
        case GL_DEBUG_SEVERITY_MEDIUM:
            severityStr = "GL_DEBUG_SEVERITY_MEDIUM";
            break;
        case GL_DEBUG_SEVERITY_LOW:
            severityStr = "GL_DEBUG_SEVERITY_LOW";
            break;
        case GL_DEBUG_SEVERITY_NOTIFICATION:
            severityStr = "GL_DEBUG_SEVERITY_NOTIFICATION";
            break;
        default:
            severityStr = "unknown error";
            break;
    }

    printf("%s:%s[%s](%d): %s\n", sourceStr.c_str(), typeStr.c_str(), severityStr.c_str(), id, message);
}

void error_callback(int error, const char *description) {
    fprintf(stderr, "Error: %s\n", description);
}

DisplayManager::DisplayManager() {
    glfwSetErrorCallback(error_callback);

    if (!glfwInit()) {
        std::cout << "Failed to initialize GLFW!" << std::endl;
        return;
    }

    window = glfwCreateWindow(WIDTH, HEIGHT, "Game",
                              nullptr,
                              nullptr);
    if (!window) {
        glfwTerminate();
        return;
    }

    const GLFWvidmode *mode = glfwGetVideoMode(glfwGetPrimaryMonitor());
    glfwSetWindowPos(window, (mode->width - (int) WIDTH) / 2, (mode->height - (int) HEIGHT) / 2);

    glfwMakeContextCurrent(window);

    if (!gladLoadGLLoader((GLADloadproc) glfwGetProcAddress)) {
        std::cout << "Failed to initialize Glad!" << std::endl;
        return;
    }

    if (!gladLoadGL()) {
        std::cout << "Failed to initialize Glad!" << std::endl;
        return;
    }

    // DEBUG
    glfwWindowHint(GLFW_OPENGL_DEBUG_CONTEXT, GL_TRUE);
    glEnable(GL_DEBUG_OUTPUT);
    glDebugMessageCallback(debug_callback, nullptr);
    // DEBUG
}

void DisplayManager::updateDisplay() {
    double time = glfwGetTime();
    FPS = 1 / (time - lastTime);
    lastTime = time;
    averageFPS = ((averageFPS * (GlobalVariables.currentFrame - 1)) + FPS) / GlobalVariables.currentFrame;
}

void DisplayManager::cleanUp() {
    glfwTerminate();
}

GLFWwindow *DisplayManager::getWindow() const {
    return window;
}

double DisplayManager::getFPS() const {
    return FPS;
}

double DisplayManager::getAverageFPS() const {
    return averageFPS;
}
