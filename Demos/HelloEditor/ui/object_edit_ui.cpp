#include "object_edit_ui.hpp"


void ImGuiEdit(AppConfig& config)
{
    IMGUI_EDIT_MEMBER(config, app_name);
    IMGUI_EDIT_MEMBER(config, window_width);
    IMGUI_EDIT_MEMBER(config, window_height);
    IMGUI_EDIT_MEMBER(config, fullscreen);
    IMGUI_EDIT_MEMBER(config, volume);
}

void ImGuiEdit(std::vector<AppConfig>& configs)
{
    for (size_t i = 0; i < configs.size(); ++i)
    {
        std::string header = "Config " + std::to_string(i);
        if (ImGui::CollapsingHeader(header.c_str()))
        {
            ImGui::Indent(15.0f);
            ImGuiEdit(configs[i]);
            ImGui::Unindent(15.0f);
            ImGui::Separator();
        }
    }
    if (ImGui::Button("Add Config"))
    {
        configs.emplace_back();
    }
}

void ImGuiEdit(PlayerData& player)
{
    IMGUI_EDIT_MEMBER(player, name);
    IMGUI_EDIT_MEMBER_CONSTOM_WITH_ENUM(player, level, LevelConfig, LevelEnumConfig);
    IMGUI_EDIT_MEMBER(player, health);
    IMGUI_EDIT_MEMBER(player, position);
}

void ImGuiEdit(std::vector<PlayerData>& players)
{
    for (size_t i = 0; i < players.size(); ++i)
    {
        std::string header = "Player " + std::to_string(i);
        if (ImGui::CollapsingHeader(header.c_str()))
        {
            ImGui::Indent(15.0f);
            ImGuiEdit(players[i]);
            ImGui::Unindent(15.0f);
            ImGui::Separator();
        }
    }
    if (ImGui::Button("Add Player"))
    {
        players.emplace_back();
    }
}

void ImGuiEdit(SceneData& sceneData)
{
    if (ImGui::CollapsingHeader("App Config", ImGuiTreeNodeFlags_DefaultOpen))
    {
        ImGui::Indent(15.0f);
        ImGuiEdit(sceneData.configs);
        ImGui::Unindent(15.0f);
        ImGui::Separator();
    }

    if (ImGui::CollapsingHeader("Player Data"))
    {
        ImGui::Indent(15.0f);
        ImGuiEdit(sceneData.players);
        ImGui::Unindent(15.0f);
        ImGui::Separator();
    }
}
