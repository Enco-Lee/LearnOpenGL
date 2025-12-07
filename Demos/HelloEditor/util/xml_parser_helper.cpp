#include "xml_parser_helper.h"

std::string GetStringAttribute(tinyxml2::XMLElement* elem, const char* attrName, const std::string& defaultValue)
{
    if (!elem)
        return defaultValue;
    const char* value = elem->Attribute(attrName);
    return value ? value : defaultValue;
}

int GetIntChild(tinyxml2::XMLElement* parent, const char* childName, int defaultValue)
{
    if (!parent)
        return defaultValue;
    tinyxml2::XMLElement* child = parent->FirstChildElement(childName);
    if (!child)
        return defaultValue;
    int value = defaultValue;
    child->QueryIntText(&value);
    return value;
}

float GetFloatChild(tinyxml2::XMLElement* parent, const char* childName, float defaultValue)
{
    if (!parent)
        return defaultValue;
    tinyxml2::XMLElement* child = parent->FirstChildElement(childName);
    if (!child)
        return defaultValue;
    float value = defaultValue;
    child->QueryFloatText(&value);
    return value;
}

bool GetBoolChild(tinyxml2::XMLElement* parent, const char* childName, bool defaultValue)
{
    if (!parent)
        return defaultValue;
    tinyxml2::XMLElement* child = parent->FirstChildElement(childName);
    if (!child)
        return defaultValue;
    const char* text = child->GetText();
    if (!text)
        return defaultValue;
    return (strcmp(text, "true") == 0 || strcmp(text, "1") == 0);
}
