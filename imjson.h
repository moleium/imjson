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
 *
 * @param filename The name of the file containing the theme information in JSON
 * format.
 */
void load_theme_from_file(const std::string &filename);

/**
 * @brief Load theme from a string.
 *
 * @param json_str The string containing the theme information in JSON format.
 */
void load_theme_from_string(const std::string &json_str);

/**
 * @brief Load theme from a JSON object.
 *
 * @param j The JSON object containing the theme information.
 */
void load_theme_from_json(const json &j);
}