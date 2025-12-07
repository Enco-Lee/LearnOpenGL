#pragma once
#include <string>
#include <vector>
#include <unordered_map>
#include <glm/glm.hpp>

struct AppConfig
{
    std::string id            = "-1";
    std::string app_name      = "MyApp";
    int         window_width  = 1280;
    int         window_height = 720;
    bool        fullscreen    = false;
    float       volume        = 0.8f;
};

struct PlayerData
{
    std::string id       = "-1";
    std::string name     = "Player1";
    int         level    = 1;
    float       health   = 100.0f;
    glm::vec3   position = {0, 0, 0};
};

struct LevelConfig
{
    static constexpr int         Speed = 1;
    static constexpr int         Min   = 0;
    static constexpr int         Max   = 4;
    static constexpr const char* Fmt   = "%d";
};

// Example: Level enum config
struct LevelEnumConfig
{
    static const std::unordered_map<int, const char*> GetHints()
    {
        static const std::unordered_map<int, const char*> hints = {
            {0, "Novice"}, {1, "Advanced"}, {2, "Veteran"}, {3, "Master"}, {4, "Legend"}};
        return hints;
    }

    static constexpr bool ShowHint       = true;
    static constexpr bool EnableDropdown = false;
};

// Example: Job enum config
struct JobEnumConfig
{
    static const std::unordered_map<int, const char*> GetHints()
    {
        static const std::unordered_map<int, const char*> hints = {
            {1, "Warrior"}, {2, "Mage"}, {3, "Priest"}, {4, "Rogue"}};
        return hints;
    }

    static constexpr bool ShowHint       = true;
    static constexpr bool EnableDropdown = true;
};

struct SceneData
{
    std::vector<PlayerData> players;
    std::vector<AppConfig>  configs;
};
