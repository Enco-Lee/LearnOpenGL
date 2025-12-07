#include "application.h"

#include "imgui.h"
#include "backends/imgui_impl_glfw.h"
#include "backends/imgui_impl_opengl3.h"

#include <vector>
#include <string>

#include "ui/data_editor.h"

void SetupImGuiStyle()
{
    ImGuiStyle& style  = ImGui::GetStyle();
    ImVec4*     colors = style.Colors;

    colors[ImGuiCol_WindowBg]       = ImVec4(0.12f, 0.12f, 0.12f, 0.95f);
    colors[ImGuiCol_ChildBg]        = ImVec4(0.10f, 0.10f, 0.10f, 1.00f);
    colors[ImGuiCol_FrameBg]        = ImVec4(0.18f, 0.18f, 0.18f, 0.54f);
    colors[ImGuiCol_FrameBgHovered] = ImVec4(0.25f, 0.25f, 0.25f, 0.80f);
    colors[ImGuiCol_FrameBgActive]  = ImVec4(0.30f, 0.30f, 0.30f, 1.00f);
    colors[ImGuiCol_Button]         = ImVec4(0.22f, 0.45f, 0.70f, 0.60f);
    colors[ImGuiCol_ButtonHovered]  = ImVec4(0.25f, 0.50f, 0.80f, 0.80f);
    colors[ImGuiCol_ButtonActive]   = ImVec4(0.18f, 0.40f, 0.65f, 1.00f);
    colors[ImGuiCol_Text]           = ImVec4(0.95f, 0.95f, 0.95f, 1.00f);
    colors[ImGuiCol_TextDisabled]   = ImVec4(0.50f, 0.50f, 0.50f, 1.00f);
    colors[ImGuiCol_Separator]      = ImVec4(0.20f, 0.20f, 0.20f, 1.00f);
    colors[ImGuiCol_Tab]            = ImVec4(0.18f, 0.18f, 0.18f, 0.86f);
    colors[ImGuiCol_TabHovered]     = ImVec4(0.25f, 0.25f, 0.25f, 0.80f);
    colors[ImGuiCol_TabActive]      = ImVec4(0.22f, 0.45f, 0.70f, 1.00f);


    style.WindowPadding     = ImVec2(12.0f, 10.0f);
    style.FramePadding      = ImVec2(8.0f, 6.0f);
    style.CellPadding       = ImVec2(6.0f, 4.0f);
    style.ItemSpacing       = ImVec2(10.0f, 8.0f);
    style.ItemInnerSpacing  = ImVec2(6.0f, 6.0f);
    style.WindowRounding    = 8.0f;
    style.FrameRounding     = 4.0f;
    style.TabRounding       = 6.0f;
    style.ScrollbarRounding = 8.0f;
    style.GrabRounding      = 4.0f;
    style.FrameBorderSize   = 1.0f;
    style.WindowBorderSize  = 1.0f;
    style.ScrollbarSize     = 12.0f;
   
    ImGuiIO& io = ImGui::GetIO();

    io.Fonts->AddFontDefault();
    io.Fonts->Fonts[0]->Scale = 1.05f; 
}



namespace Hub
{
	class HelloApp :public Application
	{
	public:
		void initData()
		{
            IMGUI_CHECKVERSION();
            ImGui::CreateContext();
            ImGuiIO& io = ImGui::GetIO();
            (void)io;
            io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard; // Enable Keyboard Controls
            io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;  // Enable Gamepad Controls

            const char* glsl_version = "#version 330 core";
            ImGui_ImplGlfw_InitForOpenGL(_currentWindow->getNativeHandle(), true);

            ImGui_ImplOpenGL3_Init(glsl_version);

            SetupImGuiStyle();
            _dataEditorUI = DataEditorUI();
		}

		void update()
		{
		}

		void render()
		{
            if (glfwGetWindowAttrib(_currentWindow->getNativeHandle(), GLFW_ICONIFIED) != 0)
            {
                ImGui_ImplGlfw_Sleep(10);
                return;
            }

            // Start the Dear ImGui frame
            ImGui_ImplOpenGL3_NewFrame();
            ImGui_ImplGlfw_NewFrame();
            ImGui::NewFrame();
            
            // pass
            _dataEditorUI.render();

            ImGui::Render();
			glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
			glClear(GL_COLOR_BUFFER_BIT);

           
			// Draw
            ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
        }

        void destory()
        {
            // Cleanup
            ImGui_ImplOpenGL3_Shutdown();
            ImGui_ImplGlfw_Shutdown();
            ImGui::DestroyContext();
        }

    private:
        DataEditorUI _dataEditorUI;
	};
}

int main()
{
	using namespace Hub;
	HelloApp app;
	app.run();
	return 0;
}
