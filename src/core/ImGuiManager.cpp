//
// Created by Shrimp on 4/11/2022.
//

#include "GlobalVariables.h"
#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"
//#include "imgui.h"
//#include "imgui_impl_opengl3.h"
//#include "imgui_impl_glfw.h"
//#include "../../depends/IMGUI/imgui.h"
//#include "../../depends/IMGUI/backends/imgui_impl_opengl3.h"
//#include "../../depends/IMGUI/backends/imgui_impl_glfw.h"

ImGuiManager::ImGuiManager() {
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGui_ImplGlfw_InitForOpenGL(GlobalVariables.displayManager.getWindow(), true);
    ImGui_ImplOpenGL3_Init("#version 450");
}

void ImGuiManager::update() {
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGlfw_NewFrame();
    ImGui::NewFrame();

    ImGui::Begin("Cool Window");

    // FPS
    ImGui::Text("FPS: %f", GlobalVariables.displayManager.getFPS());
    ImGui::Text("Average FPS: %f", GlobalVariables.displayManager.getAverageFPS());
    ImGui::Spacing();
//        ImGui.text("Update time: " + updateTime + "ms");
//        ImGui.text("Binding time: " + renderer.getBindTime() + "ms");
//        ImGui.text("Tracing time: " + renderer.getTraceTime() + "ms");
//        ImGui.text("Other time: " + renderer.getOtherTime() + "ms");
//        ImGui.text("Total time: " + DisplayManager.getDelta() * 1000 + "ms");
    ImGui::Spacing();
    ImGui::Spacing();
    // FPS

    // View Control
    if (ImGui::TreeNode("Output Options")) {
        const std::vector<const char *> options = GlobalVariables.renderer.getAttachmentManager().keys();
        const char *output = GlobalVariables.selectedOutput.c_str();
        int selectedOption = 0;
        for (int i = 0; i < options.size(); i++) {
            if (strcmp(options[i], output) == 0) {
                selectedOption = i;
                break;
            }
        }

        ImGui::ListBox("##Options", &selectedOption, options.data(), (int) options.size(), 5);
        if (selectedOption < options.size()) {
            GlobalVariables.selectedOutput = options[selectedOption];
        }

        ImGui::TreePop();
    }
    ImGui::Spacing();

    ImGui::DragInt("Spatial Scale", &GlobalVariables.spatialScale, 1, 1, 10);
    ImGui::DragFloat("Spatial Sigma", &GlobalVariables.spatialSigma, 0.01, 0.01, 5);

    ImGui::Spacing();
    ImGui::Spacing();
    // View Control

    // Ray Control
    ImGui::Checkbox("Path Tracing", &GlobalVariables.pathTracing);
    ImGui::Checkbox("Render Bitmask Borders", &GlobalVariables.drawBitmaskBorders);

//        if (ImGui.button("Reset Frame Counter")) {
//            renderer.resetFrameCounter = true;
//        }
//
//        final
//        int[]
//        bounceInt = new int[]{lightBounceAmount};
//        if (ImGui.sliderInt("Bounce Amount", bounceInt, 0, 25)) {
//            lightBounceAmount = bounceInt[0];
//        }
//
//        ImGui.spacing();
//
//        if (ImGui.checkbox("Update Sun", updateSun)) {
//            updateSun = !updateSun;
//        }
//
//        ImGui.spacing();
//        ImGui.spacing();
    // Ray Control

    // World Generation
//        if (ImGui.checkbox("Generate World", generateWorld)) {
//            generateWorld = !generateWorld;
//        }
//
//        ImGui.spacing();
//        ImGui.spacing();
    // World Generation

    // World
//        final
//        Point3D worldScale = world.getWorldScale();
//        final
//        ChunkGenerationThread generationThread = (ChunkGenerationThread) threadManager.getThread(
//                "chunkGenerationThread");
//
//        ImGui.text("World: " + worldScale.x + "x" + worldScale.y + "x" + worldScale.z);
//        ImGui.text("World generation percentage: " + generationThread.getGeneratePercentage() + "%");
//        ImGui.text("World generation time: " + generationThread.getThreadAliveTime() + "sec");
//        ImGui.text("Estimated generation time: " + generationThread.getEstimatedTime() + "sec");
//
//        ImGui.spacing();
//        ImGui.spacing();
    // World

    // World Update
//        if (ImGui.checkbox("Update World", updateWorld)) {
//            updateWorld = !updateWorld;
//        }
//
//        ImGui.text("Amount of chunks to update: " + chunkManager.getChunkUpdateList().size());
//        ImGui.text("Chunk update time: " + threadManager.getThread("chunkUpdateThread").getLoopTime() + "ms");
    // World Update

    ImGui::End();
    ImGui::Render();
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}

void ImGuiManager::cleanUp() {
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();
}
