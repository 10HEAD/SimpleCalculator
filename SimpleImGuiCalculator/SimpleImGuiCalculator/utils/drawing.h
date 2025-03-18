namespace linus {
	namespace drawing {
        namespace utils {
            bool showCalculator = true;

            float buttonSize = 60.0f;
            float spacing = 5.0f;
            float displayHeight = 40.0f;
            float windowPadding = 10.0f;

            float totalHeight = displayHeight + (buttonSize * 4) + (spacing * 3) + (2 * windowPadding);
        }

        void drawCalculatorUI() {
            if (!utils::showCalculator) {
                glfwSetWindowShouldClose(setup::g_window, true);
                return;
            }

            ImGui::SetNextWindowSize(ImVec2(300, utils::totalHeight));

            ImGui::Begin("Calculator", &utils::showCalculator,
                ImGuiWindowFlags_NoCollapse |
                ImGuiWindowFlags_NoResize |
                ImGuiWindowFlags_NoScrollbar);

            static std::string displayInput = "0";
            static bool operatorPressed = false;

            ImGui::SetWindowFontScale(1.5f);
            ImGui::Text("%s", displayInput.c_str());

            const char* buttons[4][4] = {
                {"7", "8", "9", "/"},
                {"4", "5", "6", "*"},
                {"1", "2", "3", "-"},
                {"0", "C", "=", "+"}
            };

            for (int row = 0; row < 4; ++row) {
                ImGui::Columns(4, NULL, false);
                for (int col = 0; col < 4; ++col) {
                    if (ImGui::Button(buttons[row][col], ImVec2(utils::buttonSize, utils::buttonSize))) {
                        std::string btn = buttons[row][col];

                        if (btn == "C") {
                            calculator::input = "0";
                            displayInput = "0";
                            calculator::lastOp = 0;
                            calculator::result = 0.0;
                            calculator::newInput = true;
                            operatorPressed = false;
                        }
                        else if (btn == "=") {
                            calculator::calculate('=');
                            displayInput = calculator::input;
                            calculator::newInput = true;
                            operatorPressed = false;
                        }
                        else if (btn == "+" || btn == "-" || btn == "*" || btn == "/") {
                            if (!calculator::newInput) {
                                calculator::calculate(btn[0]);
                            }
                            displayInput += " " + btn + " ";
                            calculator::newInput = true;
                            operatorPressed = true;
                        }
                        else {
                            if (calculator::newInput) {
                                if (operatorPressed) {
                                    calculator::input = btn;
                                    displayInput += btn;
                                }
                                else {
                                    calculator::input = btn;
                                    displayInput = btn;
                                }
                            }
                            else {
                                calculator::input += btn;
                                displayInput += btn;
                            }
                            calculator::newInput = false;
                            operatorPressed = false;
                        }
                    }
                    ImGui::NextColumn();
                }
                ImGui::Columns(1);
            }

            ImGui::End();
        }



        void runRenderTick() {
            while (!glfwWindowShouldClose(linus::setup::g_window)) {
                glfwPollEvents();
                ImGui_ImplOpenGL3_NewFrame();
                ImGui_ImplGlfw_NewFrame();
                ImGui::NewFrame();

                drawCalculatorUI();

                ImGui::Render();
                int display_w, display_h;
                glfwGetFramebufferSize(linus::setup::g_window, &display_w, &display_h);
                glViewport(0, 0, display_w, display_h);
                glClear(GL_COLOR_BUFFER_BIT);
                ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

                glfwSwapBuffers(linus::setup::g_window);
            }
        }
	}
}