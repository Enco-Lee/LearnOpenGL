#pragma once
#include <string>
#include "data_define.h"

class SceneDataParser
{
public:
    virtual bool loadFromFile(const std::string& fileName, SceneData& outData)    = 0;
    virtual bool saveToFile(const std::string& fileName, const SceneData& inData) = 0;
};
