# imjson

`imjson` is a small C++ utility that allows theme definition for Dear ImGui through JSON files.

## Features

- Define ImGui style colors and variables using JSON objects.
- Load themes from files, strings, or JSON objects.
- Load fonts from JSON objects.

## Usage

To use `imjson`, include the `imjson.h` and `imjson.cpp` files in your project

Here's an example of how to load a theme from a file:

```cpp
#include "imjson.h"

int main() {
    imjson::load_theme_from_file("my_theme.json");

    // or from a string
    imjson::load_theme_from_string(R"(
		{
			"Colors": {
				"Text": [1.0, 0.0, 0.0, 1.0]
			}
		}
	)");
}
```

## License

`imjson` is distributed under the MIT License.
