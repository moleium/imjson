#pragma once

#if __has_include(<imgui/imgui.h>)
#include <imgui/imgui.h>
#elif __has_include("imgui/imgui.h")
#include "imgui/imgui.h"
#else
#error "imgui/imgui.h not found, specify include path for imgui"
#endif

#include <nlohmann/json.hpp>
#include "bindings.h"

namespace imjson {
/**
 * @brief Load theme from a file.
 */
void load_file(const std::string &filename);

/**
 * @brief Load theme from a string.
 */
void load_string(const std::string &json_str);

/**
 * @brief Load theme from a JSON object.
 */
void load(const json &j);

/**
 * @brief Pop all previously pushed colors
 */
void pop_colors();

/**
 * @brief Pop all previously pushed style variables
 */
void pop_vars();
}