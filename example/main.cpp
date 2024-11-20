#include <GLFW/glfw3.h>
#include <imgui/imgui.h>
#include <imgui/imgui_impl_glfw.h>
#include <imgui/imgui_impl_opengl3.h>

#include <iostream>
#include <imjson.h>

static void glfw_error_callback(int error, const char *description) {
  fprintf(stderr, "GLFW Error %d: %s\n", error, description);
}

int main() {

  glfwSetErrorCallback(glfw_error_callback);
  if (!glfwInit()) {
    std::cerr << "Failed to initialize GLFW" << std::endl;
    return 1;
  }

  const char *glsl_version = "#version 130";
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

  GLFWwindow *window =
      glfwCreateWindow(1280, 720, "ImJson Demo", nullptr, nullptr);
  if (!window) {
    std::cerr << "Failed to create GLFW window" << std::endl;
    glfwTerminate();
    return 1;
  }
  glfwMakeContextCurrent(window);
  glfwSwapInterval(1);

  IMGUI_CHECKVERSION();
  ImGui::CreateContext();
  ImGuiIO &io = ImGui::GetIO();
  io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;

  ImGui_ImplGlfw_InitForOpenGL(window, true);
  ImGui_ImplOpenGL3_Init(glsl_version);

  const char *theme_json = R"(
  {
    "Colors": {
      "Text": [0.95, 0.95, 0.95, 1.0],
      "TextDisabled": [0.5, 0.5, 0.5, 1.0],
      "WindowBg": [0.12, 0.12, 0.12, 1.0],
      "PopupBg": [0.08, 0.08, 0.08, 0.94],
      "Border": [0.43, 0.43, 0.50, 0.5],
      "FrameBg": [0.25, 0.25, 0.25, 0.54],
      "FrameBgHovered": [0.33, 0.33, 0.33, 0.54],
      "FrameBgActive": [0.42, 0.42, 0.42, 0.54],
      "TitleBg": [0.15, 0.15, 0.15, 1.0],
      "TitleBgActive": [0.15, 0.15, 0.15, 1.0],
      "MenuBarBg": [0.14, 0.14, 0.14, 1.0],
      "ScrollbarBg": [0.02, 0.02, 0.02, 0.53],
      "ScrollbarGrab": [0.31, 0.31, 0.31, 1.0],
      "ScrollbarGrabHovered": [0.41, 0.41, 0.41, 1.0],
      "ScrollbarGrabActive": [0.51, 0.51, 0.51, 1.0],
      "CheckMark": [0.86, 0.86, 0.86, 1.0],
      "Button": [0.29, 0.29, 0.29, 0.54],
      "ButtonHovered": [0.35, 0.35, 0.35, 0.54],
      "ButtonActive": [0.42, 0.42, 0.42, 0.54],
      "Header": [0.35, 0.35, 0.35, 0.54],
      "HeaderHovered": [0.39, 0.39, 0.39, 0.54],
      "HeaderActive": [0.47, 0.47, 0.47, 0.54]
    },
    "Rounding": {
      "WindowRounding": 4.0,
      "FrameRounding": 2.0,
      "ScrollbarRounding": 3.0,
      "GrabRounding": 2.0,
      "TabRounding": 2.0
    },
    "WindowPadding": [8, 8],
    "FramePadding": [4, 3],
    "ItemSpacing": [8, 4],
    "ScrollbarSize": 14.0,
    "GrabMinSize": 10.0
  })";

  imjson::load_string(theme_json);

  while (!glfwWindowShouldClose(window)) {
    glfwPollEvents();

    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGlfw_NewFrame();
    ImGui::NewFrame();

    {
      ImGui::Begin("Theme Demo");

      if (ImGui::CollapsingHeader("Basic Controls")) {
        static float f = 0.0f;
        ImGui::SliderFloat("Float", &f, 0.0f, 1.0f);

        static int counter = 0;
        if (ImGui::Button("Button"))
          counter++;
        ImGui::SameLine();
        ImGui::Text("Counter = %d", counter);

        static bool checkbox = false;
        ImGui::Checkbox("Checkbox", &checkbox);
      }

      if (ImGui::CollapsingHeader("Style Editor")) {
        ImGui::ShowStyleEditor();
      }

      ImGui::End();
    }

    ImGui::Render();
    int display_w, display_h;
    glfwGetFramebufferSize(window, &display_w, &display_h);
    glViewport(0, 0, display_w, display_h);
    glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

    glfwSwapBuffers(window);
  }

  imjson::pop_colors();
  imjson::pop_vars();

  ImGui_ImplOpenGL3_Shutdown();
  ImGui_ImplGlfw_Shutdown();
  ImGui::DestroyContext();

  glfwDestroyWindow(window);
  glfwTerminate();

  return 0;
}
