#pragma once
#include "imgui.h"
#include <string>
#include <type_traits>
#include <glm/vec3.hpp>
#include <cstring>
#include <unordered_map>
#include <vector>
#include <utility>
#include <algorithm>

// ===================== Configuration (Adjustable) =====================
#define IMGUI_EDIT_LABEL_WIDTH 150.0f           // Fixed label width (same line with controls)
#define IMGUI_EDIT_LABEL_MARGIN 5.0f            // Safe margin between label and controls (prevents overlap)
#define IMGUI_EDIT_CONTROL_MARGIN 10.0f         // Margin for control area (prevents clipping)
#define IMGUI_EDIT_LABEL_TRUNCATE_SUFFIX "...:" // Suffix for truncated labels

// ===================== Type Mapping =====================
template<typename T>
struct ImGuiDataTypeMap
{
    static constexpr ImGuiDataType value = ImGuiDataType_COUNT;
};

template<>
struct ImGuiDataTypeMap<int>
{
    static constexpr ImGuiDataType value = ImGuiDataType_S32;
};

template<>
struct ImGuiDataTypeMap<long>
{
    static constexpr ImGuiDataType value = ImGuiDataType_S64;
};

template<>
struct ImGuiDataTypeMap<float>
{
    static constexpr ImGuiDataType value = ImGuiDataType_Float;
};

template<>
struct ImGuiDataTypeMap<double>
{
    static constexpr ImGuiDataType value = ImGuiDataType_Double;
};

template<>
struct ImGuiDataTypeMap<unsigned int>
{
    static constexpr ImGuiDataType value = ImGuiDataType_U32;
};

template<>
struct ImGuiDataTypeMap<unsigned long>
{
    static constexpr ImGuiDataType value = ImGuiDataType_U32;
};

// ===================== Default Configuration (Extended for Vec3 Reset) =====================
template<typename T, typename = void>
struct DefaultNumConfig
{
    static constexpr T           Speed      = static_cast<T>(1);
    static constexpr T           Min        = static_cast<T>(0);
    static constexpr T           Max        = static_cast<T>(100);
    static constexpr const char* Fmt        = "%f";
    static constexpr T           ResetValue = static_cast<T>(0);
};

template<typename T>
struct DefaultNumConfig<T, std::enable_if_t<std::is_integral_v<T> && !std::is_same_v<T, bool>>>
{
    static constexpr T           Speed      = 1;
    static constexpr T           Min        = 0;
    static constexpr T           Max        = 10000;
    static constexpr const char* Fmt        = "%d";
    static constexpr T           ResetValue = 0;
};

template<typename T>
struct DefaultNumConfig<T, std::enable_if_t<std::is_floating_point_v<T>>>
{
    static constexpr T           Speed      = 0.1f;
    static constexpr T           Min        = 0.0f;
    static constexpr T           Max        = 100.0f;
    static constexpr const char* Fmt        = "%.1f";
    static constexpr T           ResetValue = 0.0f;
};

template<>
struct DefaultNumConfig<glm::vec3>
{
    static constexpr float       Speed      = DefaultNumConfig<float>::Speed;
    static constexpr float       Min        = DefaultNumConfig<float>::Min;
    static constexpr float       Max        = DefaultNumConfig<float>::Max;
    static constexpr const char* Fmt        = "%.2f";
    static constexpr glm::vec3   ResetValue = glm::vec3(0.0f);
};

template<>
struct DefaultNumConfig<bool>
{
    static constexpr int         Speed      = DefaultNumConfig<int>::Speed;
    static constexpr int         Min        = 0;
    static constexpr int         Max        = 1;
    static constexpr const char* Fmt        = DefaultNumConfig<int>::Fmt;
    static constexpr bool        ResetValue = false;
};

// ===================== Enum Hint Configuration Template =====================
template<typename T>
struct EnumHintConfig
{
    static const std::unordered_map<T, const char*> GetHints()
    {
        return {};
    }

    static constexpr bool ShowHint       = false;
    static constexpr bool EnableDropdown = false;
};

// ===================== Utility Functions (Same Line + Tooltip + No Overlap) =====================
inline std::string TruncateLabel(const char* full_label, float max_width)
{
    const float full_label_width = ImGui::CalcTextSize(full_label).x;
    const float colon_width      = ImGui::CalcTextSize(":").x;
    const float suffix_width     = ImGui::CalcTextSize(IMGUI_EDIT_LABEL_TRUNCATE_SUFFIX).x;
    const float available_width  = max_width - colon_width;

    if (full_label_width <= available_width)
    {
        return std::string(full_label) + ":";
    }

    std::string truncated       = full_label;
    float       current_width   = 0.0f;
    int         truncate_length = 0;

    for (truncate_length = 0; truncate_length < (int)truncated.size(); truncate_length++)
    {
        current_width += ImGui::CalcTextSize(&truncated[truncate_length], &truncated[truncate_length + 1]).x;
        if (current_width > (available_width - suffix_width))
        {
            break;
        }
    }

    truncated = truncated.substr(0, truncate_length) + IMGUI_EDIT_LABEL_TRUNCATE_SUFFIX;
    return truncated;
}

inline void RenderLabelInSameLine(const char* full_label)
{
    const std::string display_label = TruncateLabel(full_label, IMGUI_EDIT_LABEL_WIDTH);

    ImGui::Text("%s", display_label.c_str());

    if (display_label != (std::string(full_label) + ":"))
    {
        if (ImGui::IsItemHovered())
        {
            ImGui::SetTooltip("%s", full_label);
        }
    }

    ImGui::SameLine(IMGUI_EDIT_LABEL_WIDTH + IMGUI_EDIT_LABEL_MARGIN);
}

template<typename T>
inline const T* ImGuiSafeAddr(const T& val)
{
    return &val;
}

template<typename T, typename HintConfig>
void RenderEnumHint(const char* base_id, T value, bool use_same_line = false)
{
    if constexpr (HintConfig::ShowHint)
    {
        auto        hints     = HintConfig::GetHints();
        auto        it        = hints.find(value);
        const char* hint_text = (it != hints.end()) ? it->second : "Unknown";

        if (use_same_line)
        {
            if (ImGui::GetCursorPosX() > ImGui::GetWindowContentRegionMin().x)
            {
                ImGui::SameLine();
            }
        }

        ImGui::PushID(base_id);
        ImGui::PushID("hint");
        ImGui::TextDisabled("(%s)", hint_text);
        ImGui::PopID();
        ImGui::PopID();
    }
}

template<typename T, typename HintConfig>
bool RenderEnumDropdown(const char* base_id, T& value)
{
    if constexpr (HintConfig::EnableDropdown)
    {
        auto hints = HintConfig::GetHints();
        if (hints.empty())
            return false;

        std::string                            dropdown_id = std::string(base_id) + "_dropdown";
        std::vector<std::pair<T, const char*>> sorted_hints(hints.begin(), hints.end());

        const char* current_text = "Unknown";
        int         current_idx  = 0;
        for (size_t i = 0; i < sorted_hints.size(); ++i)
        {
            if (sorted_hints[i].first == value)
            {
                current_text = sorted_hints[i].second;
                current_idx  = static_cast<int>(i);
                break;
            }
        }

        ImGui::PushID(dropdown_id.c_str());
        bool updated = false;
        if (ImGui::BeginCombo("##dropdown", current_text))
        {
            for (size_t i = 0; i < sorted_hints.size(); ++i)
            {
                bool is_selected = (current_idx == static_cast<int>(i));
                ImGui::PushID(static_cast<int>(i));
                if (ImGui::Selectable(sorted_hints[i].second, is_selected))
                {
                    value   = sorted_hints[i].first;
                    updated = true;
                }
                ImGui::PopID();

                if (is_selected)
                    ImGui::SetItemDefaultFocus();
            }
            ImGui::EndCombo();
        }
        ImGui::PopID();
        return updated;
    }
    return false;
}

// ===================== Core: Vec3 Render (Strict Same Line) =====================
template<typename Config>
void RenderVec3Control(const void* obj_ptr, const char* label, glm::vec3& value)
{
    ImGui::PushID(obj_ptr);

    RenderLabelInSameLine(label);

    const float total_available_width = ImGui::GetContentRegionAvail().x - IMGUI_EDIT_CONTROL_MARGIN;

    float  font_size       = ImGui::GetFontSize();
    float  frame_padding_y = ImGui::GetStyle().FramePadding.y;
    float  lineHeight      = font_size + frame_padding_y * 2.0f;
    ImVec2 buttonSize      = {lineHeight, lineHeight};

    const float button_spacing     = 2.0f;
    const float drag_spacing       = 2.0f;
    const float total_button_width = 3 * buttonSize.x + 2 * button_spacing;
    const float total_drag_width   = total_available_width - total_button_width - 2 * drag_spacing;
    const float drag_width         = std::max(total_drag_width / 3.0f, 60.0f);

    ImGui::PushStyleVar(ImGuiStyleVar_ItemSpacing, ImVec2 {2.0f, 0.0f});

    ImGui::PushStyleColor(ImGuiCol_Button, ImVec4 {0.8f, 0.1f, 0.15f, 1.0f});
    ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImVec4 {0.9f, 0.2f, 0.2f, 1.0f});
    ImGui::PushStyleColor(ImGuiCol_ButtonActive, ImVec4 {0.8f, 0.1f, 0.15f, 1.0f});
    if (ImGui::Button("X", buttonSize))
        value.x = Config::ResetValue.x;
    ImGui::PopStyleColor(3);

    ImGui::SameLine();
    ImGui::SetNextItemWidth(drag_width);
    ImGui::DragFloat("##X", &value.x, Config::Speed, Config::Min, Config::Max, Config::Fmt);

    ImGui::SameLine();
    ImGui::PushStyleColor(ImGuiCol_Button, ImVec4 {0.2f, 0.45f, 0.2f, 1.0f});
    ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImVec4 {0.3f, 0.55f, 0.3f, 1.0f});
    ImGui::PushStyleColor(ImGuiCol_ButtonActive, ImVec4 {0.2f, 0.45f, 0.2f, 1.0f});
    if (ImGui::Button("Y", buttonSize))
        value.y = Config::ResetValue.y;
    ImGui::PopStyleColor(3);

    ImGui::SameLine();
    ImGui::SetNextItemWidth(drag_width);
    ImGui::DragFloat("##Y", &value.y, Config::Speed, Config::Min, Config::Max, Config::Fmt);

    ImGui::SameLine();
    ImGui::PushStyleColor(ImGuiCol_Button, ImVec4 {0.1f, 0.25f, 0.8f, 1.0f});
    ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImVec4 {0.2f, 0.35f, 0.9f, 1.0f});
    ImGui::PushStyleColor(ImGuiCol_ButtonActive, ImVec4 {0.1f, 0.25f, 0.8f, 1.0f});
    if (ImGui::Button("Z", buttonSize))
        value.z = Config::ResetValue.z;
    ImGui::PopStyleColor(3);

    ImGui::SameLine();
    ImGui::SetNextItemWidth(drag_width);
    ImGui::DragFloat("##Z", &value.z, Config::Speed, Config::Min, Config::Max, Config::Fmt);

    ImGui::PopStyleVar();
    ImGui::PopID();
}

// ===================== Core Logic (Strict Same Line for All Types) =====================
template<typename T>
void DragScalarWithDefault(const void* obj_ptr, const char* id, T& value)
{
    using Config                       = DefaultNumConfig<T>;
    constexpr ImGuiDataType imgui_type = ImGuiDataTypeMap<T>::value;
    const T                 min_val    = Config::Min;
    const T                 max_val    = Config::Max;

    ImGui::PushID(obj_ptr);
    ImGui::PushID(id);
    ImGui::PushID("drag");
    if (imgui_type != ImGuiDataType_COUNT)
    {
        ImGui::DragScalar(
            "##drag", imgui_type, &value, Config::Speed, ImGuiSafeAddr(min_val), ImGuiSafeAddr(max_val), Config::Fmt);
    }
    else
    {
        ImGui::InputScalar("##drag", imgui_type, &value);
    }
    ImGui::PopID();
    ImGui::PopID();
    ImGui::PopID();
}

inline void DragBoolWithIntConfig(const void* obj_ptr, const char* id, bool& value)
{
    using Config      = DefaultNumConfig<bool>;
    int       int_val = static_cast<int>(value);
    const int min_val = Config::Min;
    const int max_val = Config::Max;

    ImGui::PushID(obj_ptr);
    ImGui::PushID(id);
    ImGui::PushID("drag_bool");
    if (ImGui::DragInt("##drag_bool", &int_val, Config::Speed, min_val, max_val, Config::Fmt))
    {
        value = (int_val != 0);
    }
    ImGui::PopID();
    ImGui::PopID();
    ImGui::PopID();
}

template<typename T, typename EnumHint = EnumHintConfig<T>>
void _ImguiEditField(const void* obj_ptr, const char* label, T& value, bool use_drag_for_bool = false)
{
    ImGui::PushID(obj_ptr);

    if constexpr (std::is_same_v<std::remove_cvref_t<T>, glm::vec3>)
    {
        using Config = DefaultNumConfig<glm::vec3>;
        RenderVec3Control<Config>(obj_ptr, label, value);
    }
    else
    {
        RenderLabelInSameLine(label);

        ImGui::SetNextItemWidth(ImGui::GetContentRegionAvail().x - IMGUI_EDIT_CONTROL_MARGIN);

        const std::string base_id = "##" + std::string(label);

        if constexpr (std::is_same_v<T, std::string>)
        {
            ImGui::PushID("string_input");
            char buf[256] = {0};
            if (!value.empty())
                strncpy_s(buf, sizeof(buf), value.c_str(), _TRUNCATE);
            if (ImGui::InputText("##string", buf, sizeof(buf)))
                value = buf;
            ImGui::PopID();
        }
        else if constexpr (std::is_same_v<T, bool>)
        {
            ImGui::PushID("bool_control");
            if (use_drag_for_bool)
                DragBoolWithIntConfig(obj_ptr, base_id.c_str(), value);
            else
                ImGui::Checkbox("##bool", &value);
            ImGui::PopID();
        }
        else if constexpr (std::is_integral_v<T> && !std::is_same_v<T, bool>)
        {
            bool dropdown_updated = false;
            if constexpr (EnumHint::EnableDropdown)
            {
                const float dropdown_width = [&]() {
                    auto  hints     = EnumHint::GetHints();
                    float max_width = 0.0f;
                    for (const auto& pair : hints)
                        max_width = std::max(max_width, ImGui::CalcTextSize(pair.second).x);
                    return max_width + 20.0f;
                }();

                ImGui::SetNextItemWidth(dropdown_width);
                dropdown_updated = RenderEnumDropdown<T, EnumHint>(base_id.c_str(), value);

                ImGui::SameLine();
                ImGui::SetNextItemWidth(ImGui::GetContentRegionAvail().x - IMGUI_EDIT_CONTROL_MARGIN);
            }
            else
            {
                ImGui::SetNextItemWidth(ImGui::GetContentRegionAvail().x - IMGUI_EDIT_CONTROL_MARGIN);
            }

            if (!dropdown_updated)
                DragScalarWithDefault<T>(obj_ptr, base_id.c_str(), value);
            else
            {
                ImGui::BeginDisabled();
                DragScalarWithDefault<T>(obj_ptr, base_id.c_str(), value);
                ImGui::EndDisabled();
            }

            RenderEnumHint<T, EnumHint>(base_id.c_str(), value);
        }
        else if constexpr (std::is_floating_point_v<T>)
        {
            ImGui::PushID("float_drag");
            ImGui::SetNextItemWidth(ImGui::GetContentRegionAvail().x - IMGUI_EDIT_CONTROL_MARGIN);
            DragScalarWithDefault<T>(obj_ptr, base_id.c_str(), value);
            ImGui::PopID();
        }
        else
        {
            ImGui::TextDisabled("%s: [Unsupported Type]", label);
        }
    }

    ImGui::PopID();
    ImGui::Spacing();
}

// ===================== Custom Config Version (Strict Same Line) =====================
template<typename T, typename C>
void DragScalarWithConstom(const void* obj_ptr, const char* id, T& value)
{
    constexpr ImGuiDataType imgui_type = ImGuiDataTypeMap<T>::value;
    const T                 min_val    = C::Min;
    const T                 max_val    = C::Max;

    ImGui::PushID(obj_ptr);
    ImGui::PushID(id);
    ImGui::PushID("custom_drag");
    if (imgui_type != ImGuiDataType_COUNT)
    {
        ImGui::DragScalar(
            "##custom_drag", imgui_type, &value, C::Speed, ImGuiSafeAddr(min_val), ImGuiSafeAddr(max_val), C::Fmt);
    }
    else
    {
        ImGui::InputScalar("##custom_drag", imgui_type, &value);
    }
    ImGui::PopID();
    ImGui::PopID();
    ImGui::PopID();
}

template<typename C>
void DragBoolWithCustomIntConfig(const void* obj_ptr, const char* id, bool& value)
{
    int       int_val = static_cast<int>(value);
    const int min_val = C::Min;
    const int max_val = C::Max;

    ImGui::PushID(obj_ptr);
    ImGui::PushID(id);
    ImGui::PushID("custom_drag_bool");
    if (ImGui::DragInt("##custom_drag_bool", &int_val, C::Speed, min_val, max_val, C::Fmt))
    {
        value = (int_val != 0);
    }
    ImGui::PopID();
    ImGui::PopID();
    ImGui::PopID();
}

template<typename C>
void RenderVec3ControlCustom(const void* obj_ptr, const char* label, glm::vec3& value)
{
    ImGui::PushID(obj_ptr);

    RenderLabelInSameLine(label);

    const float total_available_width = ImGui::GetContentRegionAvail().x - IMGUI_EDIT_CONTROL_MARGIN;
    float       font_size             = ImGui::GetFontSize();
    float       frame_padding_y       = ImGui::GetStyle().FramePadding.y;
    float       lineHeight            = font_size + frame_padding_y * 2.0f;
    ImVec2      buttonSize            = {lineHeight, lineHeight};

    const float button_spacing     = 2.0f;
    const float drag_spacing       = 2.0f;
    const float total_button_width = 3 * buttonSize.x + 2 * button_spacing;
    const float total_drag_width   = total_available_width - total_button_width - 2 * drag_spacing;
    const float drag_width         = std::max(total_drag_width / 3.0f, 60.0f);

    ImGui::PushStyleVar(ImGuiStyleVar_ItemSpacing, ImVec2 {2.0f, 0.0f});

    ImGui::PushStyleColor(ImGuiCol_Button, ImVec4 {0.8f, 0.1f, 0.15f, 1.0f});
    ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImVec4 {0.9f, 0.2f, 0.2f, 1.0f});
    ImGui::PushStyleColor(ImGuiCol_ButtonActive, ImVec4 {0.8f, 0.1f, 0.15f, 1.0f});
    if (ImGui::Button("X", buttonSize))
        value.x = C::ResetValue.x;
    ImGui::PopStyleColor(3);

    ImGui::SameLine();
    ImGui::SetNextItemWidth(drag_width);
    ImGui::DragFloat("##X", &value.x, C::Speed, C::Min, C::Max, C::Fmt);

    ImGui::SameLine();
    ImGui::PushStyleColor(ImGuiCol_Button, ImVec4 {0.2f, 0.45f, 0.2f, 1.0f});
    ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImVec4 {0.3f, 0.55f, 0.3f, 1.0f});
    ImGui::PushStyleColor(ImGuiCol_ButtonActive, ImVec4 {0.2f, 0.45f, 0.2f, 1.0f});
    if (ImGui::Button("Y", buttonSize))
        value.y = C::ResetValue.y;
    ImGui::PopStyleColor(3);

    ImGui::SameLine();
    ImGui::SetNextItemWidth(drag_width);
    ImGui::DragFloat("##Y", &value.y, C::Speed, C::Min, C::Max, C::Fmt);

    ImGui::SameLine();
    ImGui::PushStyleColor(ImGuiCol_Button, ImVec4 {0.1f, 0.25f, 0.8f, 1.0f});
    ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImVec4 {0.2f, 0.35f, 0.9f, 1.0f});
    ImGui::PushStyleColor(ImGuiCol_ButtonActive, ImVec4 {0.1f, 0.25f, 0.8f, 1.0f});
    if (ImGui::Button("Z", buttonSize))
        value.z = C::ResetValue.z;
    ImGui::PopStyleColor(3);

    ImGui::SameLine();
    ImGui::SetNextItemWidth(drag_width);
    ImGui::DragFloat("##Z", &value.z, C::Speed, C::Min, C::Max, C::Fmt);

    ImGui::PopStyleVar();
    ImGui::PopID();
}

template<typename T, typename C, typename EnumHint = EnumHintConfig<T>>
void _ImguiEditFieldConstom(const void* obj_ptr, const char* label, T& value, bool use_drag_for_bool = false)
{
    ImGui::PushID(obj_ptr);

    if constexpr (std::is_same_v<std::remove_cvref_t<T>, glm::vec3>)
    {
        RenderVec3ControlCustom<C>(obj_ptr, label, value);
    }
    else
    {
        RenderLabelInSameLine(label);
        ImGui::SetNextItemWidth(ImGui::GetContentRegionAvail().x - IMGUI_EDIT_CONTROL_MARGIN);

        const std::string base_id = "##" + std::string(label);

        if constexpr (std::is_same_v<T, std::string>)
        {
            ImGui::PushID("custom_string_input");
            char buf[256] = {0};
            if (!value.empty())
                strncpy_s(buf, sizeof(buf), value.c_str(), _TRUNCATE);
            if (ImGui::InputText("##custom_string", buf, sizeof(buf)))
                value = buf;
            ImGui::PopID();
        }
        else if constexpr (std::is_same_v<T, bool>)
        {
            ImGui::PushID("custom_bool_control");
            if (use_drag_for_bool)
                DragBoolWithCustomIntConfig<C>(obj_ptr, base_id.c_str(), value);
            else
                ImGui::Checkbox("##bool", &value);
            ImGui::PopID();
        }
        else if constexpr (std::is_integral_v<T> && !std::is_same_v<T, bool>)
        {
            bool dropdown_updated = false;
            if constexpr (EnumHint::EnableDropdown)
            {
                const float dropdown_width = [&]() {
                    auto  hints     = EnumHint::GetHints();
                    float max_width = 0.0f;
                    for (const auto& pair : hints)
                        max_width = std::max(max_width, ImGui::CalcTextSize(pair.second).x);
                    return max_width + 20.0f;
                }();

                ImGui::SetNextItemWidth(dropdown_width);
                dropdown_updated = RenderEnumDropdown<T, EnumHint>(base_id.c_str(), value);

                ImGui::SameLine();
                ImGui::SetNextItemWidth(ImGui::GetContentRegionAvail().x - IMGUI_EDIT_CONTROL_MARGIN);
            }
            else
            {
                ImGui::SetNextItemWidth(ImGui::GetContentRegionAvail().x - IMGUI_EDIT_CONTROL_MARGIN);
            }

            if (!dropdown_updated)
                DragScalarWithConstom<T, C>(obj_ptr, base_id.c_str(), value);
            else
            {
                ImGui::BeginDisabled();
                DragScalarWithConstom<T, C>(obj_ptr, base_id.c_str(), value);
                ImGui::EndDisabled();
            }

            RenderEnumHint<T, EnumHint>(base_id.c_str(), value);
        }
        else if constexpr (std::is_floating_point_v<T>)
        {
            ImGui::PushID("custom_float_drag");
            ImGui::SetNextItemWidth(ImGui::GetContentRegionAvail().x - IMGUI_EDIT_CONTROL_MARGIN);
            DragScalarWithConstom<T, C>(obj_ptr, base_id.c_str(), value);
            ImGui::PopID();
        }
        else
        {
            ImGui::TextDisabled("%s: [Unsupported Type]", label);
        }
    }

    ImGui::PopID();
    ImGui::Spacing();
}

// ===================== Wrapper Macros =====================
template<typename T, typename EnumHint = EnumHintConfig<T>>
void _ImguiEditMember(const void* obj_ptr, const char* label, T& value, bool use_drag_for_bool = false)
{
    _ImguiEditField<T, EnumHint>(obj_ptr, label, value, use_drag_for_bool);
}

#define IMGUI_EDIT_MEMBER(STRUCT, MEMBER) _ImguiEditMember(&STRUCT, #MEMBER, STRUCT.MEMBER)
#define IMGUI_EDIT_MEMBER_WITH_ENUM(STRUCT, MEMBER, ENUM_CONFIG) \
    _ImguiEditMember<std::remove_cvref_t<decltype(STRUCT.MEMBER)>, ENUM_CONFIG>(&STRUCT, #MEMBER, STRUCT.MEMBER)
#define IMGUI_EDIT_MEMBER_BOOL_AS_INT(STRUCT, MEMBER) _ImguiEditMember(&STRUCT, #MEMBER, STRUCT.MEMBER, true)

template<typename T, typename C, typename EnumHint = EnumHintConfig<T>>
void _ImguiEditMemberConstom(const void* obj_ptr, const char* label, T& value, bool use_drag_for_bool = false)
{
    _ImguiEditFieldConstom<T, C, EnumHint>(obj_ptr, label, value, use_drag_for_bool);
}

#define IMGUI_EDIT_MEMBER_CONSTOM(STRUCT, MEMBER, CONFIG) \
    _ImguiEditMemberConstom<std::remove_cvref_t<decltype(STRUCT.MEMBER)>, CONFIG>(&STRUCT, #MEMBER, STRUCT.MEMBER)
#define IMGUI_EDIT_MEMBER_CONSTOM_WITH_ENUM(STRUCT, MEMBER, CONFIG, ENUM_CONFIG) \
    _ImguiEditMemberConstom<std::remove_cvref_t<decltype(STRUCT.MEMBER)>, CONFIG, ENUM_CONFIG>( \
        &STRUCT, #MEMBER, STRUCT.MEMBER)
#define IMGUI_EDIT_MEMBER_CONSTOM_BOOL_AS_INT(STRUCT, MEMBER, CONFIG) \
    _ImguiEditMemberConstom<std::remove_cvref_t<decltype(STRUCT.MEMBER)>, CONFIG>(&STRUCT, #MEMBER, STRUCT.MEMBER, true)