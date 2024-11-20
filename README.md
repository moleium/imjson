# imjson

`imjson` is a small C++ utility that allows theme definition for Dear ImGui through JSON files.

## Features

- Define ImGui style colors and variables using JSON objects
- Load themes from files, strings, or JSON objects
- Load fonts from JSON objects
- Proper style stack management

## Dependencies

- [Dear ImGui](https://github.com/ocornut/imgui)
- [nlohmann/json](https://github.com/nlohmann/json)

## Usage

Include `imjson.h` and `imjson.cpp` in your project:

```cpp
#include "imjson.h"

int main() {
  imjson::load_file("my_theme.json");  

  // Or from a string
  imjson::load_string(R"(
  {
    "Colors": {
      "Text": [1.0, 0.0, 0.0, 1.0]
    },
    "Rounding": {
      "WindowRounding": 8.0,
      "FrameRounding": 4.0
    },
    "WindowPadding": [8, 8]
  }
  )");  
  
  imjson::pop_colors();
  imjson::pop_vars();
}
```

## Example

A complete example is provided in the `example/` directory. To build it:

```bash
mkdir build && cd build
cmake ..
cmake --build .
```

## Theme Format

```json
{
  "Colors": {
    "Text": [0.9, 0.9, 0.9, 1.0],
    "WindowBg": [0.1, 0.1, 0.1, 1.0]
  },
  "Rounding": {
    "WindowRounding": 4.0,
    "FrameRounding": 2.0
  },
  "WindowPadding": [8, 8]
}
```