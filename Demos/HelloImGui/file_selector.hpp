#pragma once

#include "imgui.h"

#include <filesystem>
#include <vector>
#include <string>

namespace fs = std::filesystem;

#include "ImGuiFileDialog.h" // Make sure this is in your include path

void ShowFileSelectDemo()
{
    static std::string selectedFile;

    if (ImGui::Button("Select File"))
    {
        IGFD::FileDialogConfig config;
        config.path = ".";
        ImGuiFileDialog::Instance()->OpenDialog("ChooseFileDlg", "Choose a File", ".*", config);
    }

    // Rendering dialog
    if (ImGuiFileDialog::Instance()->Display("ChooseFileDlg"))
    {
        // If user selects a file and presses OK
        if (ImGuiFileDialog::Instance()->IsOk())
        {
            selectedFile = ImGuiFileDialog::Instance()->GetFilePathName();
        }
        ImGuiFileDialog::Instance()->Close();
    }

    if (!selectedFile.empty())
    {
        ImGui::Text("Selected file: %s", selectedFile.c_str());
    }
}

// Helper function to get filenames in a directory
std::vector<std::string> GetFilesInDirectory(const std::string& directoryPath)
{
    std::vector<std::string> files;
    for (const auto& entry : fs::directory_iterator(directoryPath))
    {
        if (!fs::is_directory(entry.status()))
            files.push_back(entry.path().filename().string());
    }
    return files;
}

// The custom file selector ImGui widget
void ShowSimpleFileSelector(const char* directory = ".")
{
    static std::string              selectedFile;
    static bool                     open = false;
    static std::vector<std::string> files;

    if (ImGui::Button("Select File"))
    {
        files = GetFilesInDirectory(directory); // reload file list
        open  = true;
    }

    if (open)
    {
        ImGui::Begin("Select a File", &open);

        // List files
        for (int i = 0; i < files.size(); ++i)
        {
            if (ImGui::Selectable(files[i].c_str()))
            {
                selectedFile = files[i];
                open         = false;
            }
        }

        ImGui::End();
    }

    if (!selectedFile.empty())
    {
        ImGui::Text("Selected file: %s", selectedFile.c_str());
    }
}
