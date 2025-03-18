#include <Windows.h>
#include <iostream>
#include <string>

#include "GL/glew.h"
#include <GLFW/glfw3.h>
#include <GLFW/glfw3native.h>

#include "imgui/imgui.h"
#include "imgui/imgui_impl_glfw.h"
#include "imgui/imgui_impl_opengl3.h"

#include "calculator/calculator.h"
#include "utils/setup.h"
#include "utils/utils.h"
#include "utils/drawing.h"

int main() {
    linus::utils::hideConsole();

    linus::setup::setupWindow();
    if (!linus::setup::g_window) {
        std::cerr << "Window setup failed!\n";
        return 1;
    }

    linus::drawing::runRenderTick();
    linus::setup::cleanupWindow();

    return 0;
}
