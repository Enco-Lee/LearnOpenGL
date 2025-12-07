#pragma once
#include "member_edit_ui.hpp"
#include "data/data_define.h"

void ImGuiEdit(AppConfig& config);


void ImGuiEdit(std::vector<AppConfig>& configs);


void ImGuiEdit(PlayerData& player);


void ImGuiEdit(std::vector<PlayerData>& players);


void ImGuiEdit(SceneData& sceneData);

