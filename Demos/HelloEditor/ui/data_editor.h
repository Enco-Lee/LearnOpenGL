#pragma once
#include <memory>
#include "object_edit_ui.hpp"
#include "data/xml_parser.h"
#include <chrono>

class DataEditorUI
{
public:
    void render();

    bool loadData(const std::string& fileName);
    bool saveData(const std::string& fileName);

private:
    std::string _selectedFile;
    SceneData   _sceneData;

    std::unique_ptr<SceneDataParser> _dataParser;

    std::string _statesMessage;

    std::chrono::time_point<std::chrono::steady_clock> _lastMessageTime;
};
