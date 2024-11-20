#include "imjson.h"

#include <fstream>
#include <iostream>

namespace imjson {

static int pushed_colors = 0;
static int pushed_vars = 0;

void set_style_colors(const json &j) {
  pushed_colors = 0; // Reset counter
  try {
    for (auto it = j.begin(); it != j.end(); ++it) {
      const std::string &name = it.key();
      const json &color = it.value();
      if (color.is_array()) {
        if (color.size() != 4) {
          std::cerr << "Warning: Color '" << name
                    << "' must have exactly 4 components" << std::endl;
          continue;
        }
        if (!std::all_of(color.begin(), color.end(),
                         [](const json &v) { return v.is_number(); })) {
          std::cerr << "Warning: Color '" << name
                    << "' contains non-numeric values" << std::endl;
          continue;
        }
        ImVec4 col(color[0], color[1], color[2], color[3]);
        auto color_it = color_map.find(name);
        if (color_it != color_map.end()) {
          ImGui::PushStyleColor(color_it->second, col);
          pushed_colors++;
        }
      }
    }
  } catch (const std::exception &e) {
    std::cerr << "Error setting style colors: " << e.what() << std::endl;
  }
}

void set_style_vars(const json &j) {
  pushed_vars = 0; // Reset counter
  try {
    for (auto it = j.begin(); it != j.end(); ++it) {
      const std::string &name = it.key();
      const json &value = it.value();
      auto style_it = style_map.find(name);
      if (style_it != style_map.end()) {
        if (value.is_number()) {
          ImGui::PushStyleVar(style_it->second, value.get<float>());
          pushed_vars++;
        } else if (value.is_array() && value.size() == 2) {
          ImGui::PushStyleVar(style_it->second, ImVec2(value[0], value[1]));
          pushed_vars++;
        }
      }
    }
  } catch (const std::exception &e) {
    std::cerr << "Error setting style variables: " << e.what() << std::endl;
  }
}

void load_fonts(const json &j) {
  try {
    if (j.contains("Default") && j["Default"].is_object()) {
      const json &default_font = j["Default"];
      if (default_font.contains("Path") && default_font["Path"].is_string() &&
          default_font.contains("SizePixels") &&
          default_font["SizePixels"].is_number()) {
        std::string path = default_font["Path"];
        float size_pixels = default_font["SizePixels"];
        ImGuiIO &io = ImGui::GetIO();
        io.Fonts->AddFontFromFileTTF(path.c_str(), size_pixels);
      }
    }
  } catch (const std::exception &e) {
    std::cerr << "Error loading fonts: " << e.what() << std::endl;
  }
}

void load_file(const std::string &filename) {
  try {
    std::ifstream file(filename);
    if (file.is_open()) {
      json j;
      file >> j;
      load(j);
    }
  } catch (const nlohmann::detail::parse_error &e) {
    std::cerr << "Error loading theme from file: " << e.what() << '\n';
    std::cerr << "Exception id: " << e.id << '\n';
    std::cerr << "Byte position of error: " << e.byte << '\n';
  } catch (const std::exception &e) {
    std::cerr << "Error loading theme from file: " << e.what() << '\n';
  }
}

void load_string(const std::string &json_str) {
  try {
    json j = json::parse(json_str);
    load(j);
  } catch (const nlohmann::detail::parse_error &e) {
    // output exception information
    std::cerr << "Error loading theme from string: " << e.what() << '\n';
    std::cerr << "Exception id: " << e.id << '\n';
    std::cerr << "Byte position of error: " << e.byte << '\n';
  } catch (const std::exception &e) {
    std::cerr << "Error loading theme from string: " << e.what() << '\n';
  }
}

void load(const json &j) {
  try {
    for (auto it = j.begin(); it != j.end(); ++it) {
      const std::string &name = it.key();
      const json &value = it.value();
      if (name == "Colors" && value.is_object()) {
        set_style_colors(value);
      } else if (name == "Fonts" && value.is_object()) {
        load_fonts(value);
      } else if (name == "Rounding" && value.is_object()) {
        set_style_vars(value);
      } else if (style_map.find(name) != style_map.end()) {
        json style_values = json::object();
        style_values[name] = value;
        set_style_vars(style_values);
      }
    }
  } catch (const std::exception &e) {
    std::cerr << "Error loading theme from json: " << e.what() << std::endl;
  }
}

void pop_colors() {
  if (pushed_colors > 0) {
    ImGui::PopStyleColor(pushed_colors);
    pushed_colors = 0;
  }
}

void pop_vars() {
  if (pushed_vars > 0) {
    ImGui::PopStyleVar(pushed_vars);
    pushed_vars = 0;
  }
}
} // namespace imjson