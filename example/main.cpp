#include <iostream>

#include <imgui/imgui.h>
#include <imgui/imgui_impl_opengl3.h>
#include <imgui/imgui_impl_glfw.h>
#include <GLFW/glfw3.h>

#include "../imjson.h"

int main() {
    GLFWwindow* window;

    glfwInit();
    window = glfwCreateWindow(1280, 720, ">w<", NULL, NULL);
    glfwMakeContextCurrent(window);

    ImGui::CreateContext();

    // use imjson to load the theme from a string
    imjson::load_theme_from_string(R"(
    {
        "Colors": {
            "Text": [1.0, 1.0, 1.0, 1.0],
            "TextDisabled": [0.5, 0.5, 0.5, 1.0],
            "WindowBg": [0.0, 0.0, 0.0, 1.0],
            "ChildBg": [0.0, 0.0, 0.0, 0.0],
            "PopupBg": [0.05, 0.05, 0.10, 0.9]
        },
        "Rounding": {
            "WindowRounding": 8.0,
            "FrameRounding": 4.0,
            "ScrollbarRounding": 0.0
        },
        "Fonts": {
            "Default": {
                "Path": "C:\\Windows\\Fonts\\segoeui.ttf",
                "SizePixels": 18
            }
        },
        "WindowPadding": [10, 10],
        "FramePadding": [5, 5]
    }
    )");


    ImGui_ImplGlfw_InitForOpenGL(window, true);
    ImGui_ImplOpenGL3_Init("#version 130");
    glClearColor(0.15f, 0.15f, 0.15f, 1.0f);

    while (!glfwWindowShouldClose(window)) {
        glfwPollEvents();
        glClear(GL_COLOR_BUFFER_BIT);

        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();

        ImGui::NewFrame();

        ImGui::SetNextWindowPos(ImVec2(0, 0));
        ImGui::SetNextWindowSize(ImGui::GetIO().DisplaySize);
        ImGui::Begin("Background", nullptr, ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoBackground | ImGuiWindowFlags_NoBringToFrontOnFocus);

        ImGui::Begin("Style Editor");
        ImGui::ShowStyleEditor();
        ImGui::End();

        ImGui::End();

        ImGui::Render();
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

        glfwSwapBuffers(window);
    }


    return 0;
}
