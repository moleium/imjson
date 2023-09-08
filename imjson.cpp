//===-- imjson/imjson.cpp - imjson library implementation ------*- C++ -*-===//
//
// Part of the imjson project
//
//===----------------------------------------------------------------------===//
//
// This file contains the implementation of the imjson library, which allows
// theme definition for imgui through JSON files.
//
//===----------------------------------------------------------------------===//

#include "imjson.h"

#include <fstream>
#include <iostream>

namespace imjson {

	void set_style_colors(const json& j) {
		try {
			for (auto it = j.begin(); it != j.end(); ++it) {
				const std::string& name = it.key();
				const json& color = it.value();
				if (color.is_array() && color.size() == 4) {
					ImVec4 col(color[0], color[1], color[2], color[3]);
					auto color_it = color_map.find(name);
					if (color_it != color_map.end()) {
						ImGui::PushStyleColor(color_it->second, col);
					}
				}
			}
		}
		catch (const std::exception& e) {
			std::cerr << "Error setting style colors: " << e.what() << std::endl;
		}
	}

	void set_style_vars(const json& j) {
		try {
			for (auto it = j.begin(); it != j.end(); ++it) {
				const std::string& name = it.key();
				const json& value = it.value();
				auto style_it = style_map.find(name);
				if (style_it != style_map.end()) {
					ImGui::PushStyleVar(style_it->second, value);
				}
			}
		}
		catch (const std::exception& e) {
			std::cerr << "Error setting style variables: " << e.what() << std::endl;
		}
	}

	void load_fonts(const json& j) {
		try {
			if (j.contains("Default") && j["Default"].is_object()) {
				const json& default_font = j["Default"];
				if (default_font.contains("Path") && default_font["Path"].is_string() &&
					default_font.contains("SizePixels") && default_font["SizePixels"].is_number()) {
					std::string path = default_font["Path"];
					float size_pixels = default_font["SizePixels"];
					ImGuiIO& io = ImGui::GetIO();
					io.Fonts->AddFontFromFileTTF(path.c_str(), size_pixels);
				}
			}
		}
		catch (const std::exception& e) {
			std::cerr << "Error loading fonts: " << e.what() << std::endl;
		}
	}

	void load_theme_from_file(const std::string& filename) {
		try {
			std::ifstream file(filename);
			if (file.is_open()) {
				json j;
				file >> j;
				load_theme_from_json(j);
			}
		}
		catch (const nlohmann::detail::parse_error& e) {
			std::cerr << "Error loading theme from file: " << e.what() << '\n';
			std::cerr << "Exception id: " << e.id << '\n';
			std::cerr << "Byte position of error: " << e.byte << '\n';
		}
		catch (const std::exception& e) {
			std::cerr << "Error loading theme from file: " << e.what() << '\n';
		}
	}

	void load_theme_from_string(const std::string& json_str) {
		try {
			json j = json::parse(json_str);
			load_theme_from_json(j);
		}
		catch (const nlohmann::detail::parse_error& e) {
			// output exception information
			std::cerr << "Error loading theme from string: " << e.what() << '\n';
			std::cerr << "Exception id: " << e.id << '\n';
			std::cerr << "Byte position of error: " << e.byte << '\n';
		}
		catch (const std::exception& e) {
			std::cerr << "Error loading theme from string: " << e.what() << '\n';
		}
	}

	void load_theme_from_json(const json& j) {
		try {
			for (auto it = j.begin(); it != j.end(); ++it) {
				const std::string& name = it.key();
				const json& value = it.value();
				if (name == "Colors" && value.is_object()) {
					set_style_colors(value);
				}
				else if (name == "Fonts" && value.is_object()) {
					load_fonts(value);
				}
				else if (name == "Rounding" && value.is_object()) {
					set_style_vars(value);
				}
				else if (style_map.find(name) != style_map.end() && value.is_array()) {
					ImGui::PushStyleVar(style_map.at(name), ImVec2(value[0], value[1]));
				}
			}
		}
		catch (const std::exception& e) {
			std::cerr << "Error loading theme from json: " << e.what() << std::endl;
		}
	}
}
