namespace linus {
	namespace setup {
        GLFWwindow* g_window;
        int g_width = 400, g_height = 500;

        static void glfwErrorCallback(int error, const char* description) {
            std::cerr << "GLFW Error " << error << ": " << description << std::endl;
        }

        void setupWindow() {
            glfwSetErrorCallback(glfwErrorCallback);
            if (!glfwInit()) {
                std::cerr << "glfwInit failed!\n";
                return;
            }

            glfwWindowHint(GLFW_DECORATED, false);
            glfwWindowHint(GLFW_RESIZABLE, false);
            glfwWindowHint(GLFW_TRANSPARENT_FRAMEBUFFER, true);
            glfwWindowHint(GLFW_FLOATING, true);

            g_window = glfwCreateWindow(g_width, g_height, "", NULL, NULL);
            if (!g_window) {
                std::cerr << "Could not create window.\n";
                glfwTerminate();
                return;
            }

            glfwMakeContextCurrent(g_window);
            glfwSwapInterval(1);

            if (glewInit() != GLEW_OK) {
                std::cerr << "Failed to initialize OpenGL loader!\n";
                return;
            }

            IMGUI_CHECKVERSION();
            ImGui::CreateContext();
            ImGuiIO& io = ImGui::GetIO(); (void)io;

            ImGui::StyleColorsDark();
            ImGui_ImplGlfw_InitForOpenGL(g_window, true);
            ImGui_ImplOpenGL3_Init("#version 130");
        }

        void cleanupWindow() {
            ImGui_ImplOpenGL3_Shutdown();
            ImGui_ImplGlfw_Shutdown();
            ImGui::DestroyContext();
            glfwDestroyWindow(g_window);
            glfwTerminate();
        }
	}
}