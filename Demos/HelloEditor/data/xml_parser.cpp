#include "xml_parser.h"
#include "util/xml_parser_helper.h"

bool SceneDataXMLParser::loadFromFile(const std::string& fileName, SceneData& outData)
{
    tinyxml2::XMLDocument doc;
    tinyxml2::XMLError    err = doc.LoadFile(fileName.c_str());

    if (err != tinyxml2::XML_SUCCESS)
    {
        // TODO: add logging here
        return false;
    }

    tinyxml2::XMLElement* root = doc.FirstChildElement("scene");
    if (!root)
    {
        // TODO: add logging here
        return false;
    }

    outData.configs.clear();
    outData.players.clear();

    tinyxml2::XMLElement* configNode = root->FirstChildElement("app_config");
    while (configNode)
    {
        outData.configs.push_back(ParseAppConfig(configNode));
        configNode = configNode->NextSiblingElement("app_config");
    }

    tinyxml2::XMLElement* playerNode = root->FirstChildElement("player_data");
    while (playerNode)
    {
        outData.players.push_back(ParsePlayerData(playerNode));
        playerNode = playerNode->NextSiblingElement("player_data");
    }

    return true;
}

bool SceneDataXMLParser::saveToFile(const std::string& fileName, const SceneData& inData)
{
    tinyxml2::XMLDocument doc;

    tinyxml2::XMLDeclaration* decl = doc.NewDeclaration();
    doc.InsertFirstChild(decl);

    tinyxml2::XMLElement* root = doc.NewElement("scene");
    doc.InsertEndChild(root);

    for (const auto& config : inData.configs)
    {
        root->InsertEndChild(SerializeAppConfig(doc, config));
    }

    for (const auto& player : inData.players)
    {
        root->InsertEndChild(SerializePlayerData(doc, player));
    }

    tinyxml2::XMLError err = doc.SaveFile(fileName.c_str());
    if (err != tinyxml2::XML_SUCCESS)
    {
        // TODO: add logging here
        return false;
    }

    return true;
}

AppConfig SceneDataXMLParser::ParseAppConfig(tinyxml2::XMLElement* configNode)
{
    AppConfig config;
    if (!configNode)
        return config;

    config.id = GetStringAttribute(configNode, "id", "config_default");

    config.app_name = GetStringAttribute(configNode->FirstChildElement("app_name"), "value", config.app_name);
    if (config.app_name.empty())
    {
        const char* text = configNode->FirstChildElement("app_name")->GetText();
        if (text)
            config.app_name = text;
    }

    config.window_width  = GetIntChild(configNode, "window_width", config.window_width);
    config.window_height = GetIntChild(configNode, "window_height", config.window_height);
    config.fullscreen    = GetBoolChild(configNode, "fullscreen", config.fullscreen);
    config.volume        = GetFloatChild(configNode, "volume", config.volume);

    return config;
}

PlayerData SceneDataXMLParser::ParsePlayerData(tinyxml2::XMLElement* playerNode)
{
    PlayerData player;
    if (!playerNode)
        return player;

    player.id = GetStringAttribute(playerNode, "id", "player_default");

    const char* nameText = playerNode->FirstChildElement("name")->GetText();
    if (nameText)
        player.name = nameText;

    player.level  = GetIntChild(playerNode, "level", player.level);
    player.health = GetFloatChild(playerNode, "health", player.health);

    tinyxml2::XMLElement* posNode = playerNode->FirstChildElement("position");
    if (posNode)
    {
        player.position.x = GetFloatChild(posNode, "x", player.position.x);
        player.position.y = GetFloatChild(posNode, "y", player.position.y);
        player.position.z = GetFloatChild(posNode, "z", player.position.z);
        posNode->QueryFloatAttribute("x", &player.position.x);
        posNode->QueryFloatAttribute("y", &player.position.y);
        posNode->QueryFloatAttribute("z", &player.position.z);
    }

    return player;
}

tinyxml2::XMLElement* SceneDataXMLParser::SerializeAppConfig(tinyxml2::XMLDocument& doc, const AppConfig& config)
{
    tinyxml2::XMLElement* configNode = doc.NewElement("app_config");
    configNode->SetAttribute("id", config.id.c_str());

    tinyxml2::XMLElement* appNameNode = doc.NewElement("app_name");
    appNameNode->SetText(config.app_name.c_str());
    configNode->InsertEndChild(appNameNode);

    tinyxml2::XMLElement* widthNode = doc.NewElement("window_width");
    widthNode->SetText(config.window_width);
    configNode->InsertEndChild(widthNode);

    tinyxml2::XMLElement* heightNode = doc.NewElement("window_height");
    heightNode->SetText(config.window_height);
    configNode->InsertEndChild(heightNode);

    tinyxml2::XMLElement* fullscreenNode = doc.NewElement("fullscreen");
    fullscreenNode->SetText(config.fullscreen ? "true" : "false");
    configNode->InsertEndChild(fullscreenNode);

    tinyxml2::XMLElement* volumeNode = doc.NewElement("volume");
    volumeNode->SetText(config.volume);
    configNode->InsertEndChild(volumeNode);

    return configNode;
}

tinyxml2::XMLElement* SceneDataXMLParser::SerializePlayerData(tinyxml2::XMLDocument& doc, const PlayerData& player)
{
    tinyxml2::XMLElement* playerNode = doc.NewElement("player_data");
    playerNode->SetAttribute("id", player.id.c_str());

    tinyxml2::XMLElement* nameNode = doc.NewElement("name");
    nameNode->SetText(player.name.c_str());
    playerNode->InsertEndChild(nameNode);

    tinyxml2::XMLElement* levelNode = doc.NewElement("level");
    levelNode->SetText(player.level);
    playerNode->InsertEndChild(levelNode);

    tinyxml2::XMLElement* healthNode = doc.NewElement("health");
    healthNode->SetText(player.health);
    playerNode->InsertEndChild(healthNode);

    tinyxml2::XMLElement* posNode = doc.NewElement("position");
    posNode->SetAttribute("x", player.position.x);
    posNode->SetAttribute("y", player.position.y);
    posNode->SetAttribute("z", player.position.z);
    playerNode->InsertEndChild(posNode);

    return playerNode;
}
