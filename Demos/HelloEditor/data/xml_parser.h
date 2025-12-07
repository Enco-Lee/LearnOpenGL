#pragma once
#include "data_parser.h"
#include "tinyxml2.h"

class SceneDataXMLParser : public SceneDataParser
{
public:
    virtual bool loadFromFile(const std::string& fileName, SceneData& outData) override;
    virtual bool saveToFile(const std::string& fileName, const SceneData& inData) override;

private:
    AppConfig  ParseAppConfig(tinyxml2::XMLElement* configNode);
    PlayerData ParsePlayerData(tinyxml2::XMLElement* playerNode);

    tinyxml2::XMLElement* SerializeAppConfig(tinyxml2::XMLDocument& doc, const AppConfig& config);
    tinyxml2::XMLElement* SerializePlayerData(tinyxml2::XMLDocument& doc, const PlayerData& player);
};
