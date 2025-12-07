#pragma once
#include "tinyxml2.h"
#include <string>

std::string GetStringAttribute(tinyxml2::XMLElement* elem, const char* attrName, const std::string& defaultValue = "");

int GetIntChild(tinyxml2::XMLElement* parent, const char* childName, int defaultValue = 0);

float GetFloatChild(tinyxml2::XMLElement* parent, const char* childName, float defaultValue);

bool GetBoolChild(tinyxml2::XMLElement* parent, const char* childName, bool defaultValue = false);
