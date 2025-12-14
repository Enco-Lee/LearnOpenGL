#include "data_editor.h"
#include "ImGuiFileDialog.h"

void FileSelect(std::string& selectedFile)
{
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
}

void DataEditorUI::init(std::shared_ptr<zmq::context_t> zmqContext)
{
    _publisher = zmq::socket_t(*zmqContext, zmq::socket_type::pub);
    _publisher.bind("ipc:///tmp/zmq_ipc_demo");
}

void DataEditorUI::render()
{
    std::string windowName = "Data Editor";
    // clear _statesMessage after 3s
    auto nowTime = std::chrono::steady_clock::now();
    if (nowTime - _lastMessageTime > std::chrono::seconds(3))
    {
        _statesMessage.clear();
    }
    ImGui::Begin(windowName.c_str());
    // File selection UI
    FileSelect(_selectedFile);

    ImGui::SameLine();

    // Load data button
    if (ImGui::Button("Load Data"))
    {
        bool ok          = loadData(_selectedFile);
        _statesMessage   = ok ? "Data loaded successfully." : "Failed to load data.";
        _lastMessageTime = std::chrono::steady_clock::now();
        _publisher.send(zmq::message_t("A"), zmq::send_flags::sndmore);
        _publisher.send(zmq::message_t(_selectedFile), zmq::send_flags::sndmore);
        _publisher.send(zmq::message_t(_statesMessage));
    }
    ImGui::SameLine();
    // Save data button
    if (ImGui::Button("Save Data"))
    {
        bool ok          = saveData(_selectedFile);
        _statesMessage   = ok ? "Data saved successfully." : "Failed to save data.";
        _lastMessageTime = std::chrono::steady_clock::now();
        _publisher.send(zmq::message_t("B"), zmq::send_flags::sndmore);
        _publisher.send(zmq::message_t(_selectedFile), zmq::send_flags::sndmore);
        _publisher.send(zmq::message_t(_statesMessage));
    }
    if (!_selectedFile.empty() || !_statesMessage.empty())
    {
        ImGui::Text("File: %s. %s", _selectedFile.c_str(), _statesMessage.c_str());
    }
    // Render scene data editor UI
    ImGuiEdit(_sceneData);
    ImGui::End();
}

bool DataEditorUI::loadData(const std::string& fileName)
{
    if (fileName.empty())
    {
        return false;
    }
    if (fileName.find(".xml") != std::string::npos)
    {
        _dataParser = std::make_unique<SceneDataXMLParser>();
    }
    else
    {
        // Handle other formats or show error
        return false;
    }
    return _dataParser->loadFromFile(fileName, _sceneData);
}

bool DataEditorUI::saveData(const std::string& fileName)
{
    if (fileName.empty())
    {
        return false;
    }
    if (_dataParser != nullptr)
    {
        return _dataParser->saveToFile(fileName, _sceneData);
    }
    return false;
}
