#include "raylib.h"
#include "utils.h"
#include <iostream>
#include <optional>
#include <string> 
#include <vector>

char state{'L'};
Color color{WHITE};
std::vector<shape *> shapes;
std::optional<shape *> preview;
std::optional<std::string> label;
std::optional<Vector2> temp_value;

int main() {

  SetConfigFlags(FLAG_WINDOW_RESIZABLE); // Window configuration flags
  InitWindow(2000, 1000, "Window title");
  SetTargetFPS(60);
  while (!WindowShouldClose()) {

    Vector2 pos = GetMousePosition();
    int key = GetKeyPressed();
    char keyin = GetCharPressed();
    bool mouse = IsMouseButtonPressed(MOUSE_BUTTON_LEFT);

    switch (state) {
    case 'N':
      state = get_current_state(state, key);
      get_color(key, color);
      undo(key, shapes);
      break;
    case 'T':
      if (!label) {
        if (mouse) {
          temp_value = pos;
          label = "";
        }
        state = get_current_state(state, key);
        get_color(key, color);
        undo(key, shapes);
      } else {
        if (key) {

          switch (key) {
          case KEY_ENTER:
            shapes.push_back(
                new text(temp_value.value(), label.value(), color));
            temp_value.reset();
            label.reset();
            preview.reset();
            break;
          case KEY_BACKSPACE:
            label.value().pop_back();
            preview = new text(temp_value.value(), label.value(), color);
            break;
          default: {
            label.value() += key;
            preview = new text(temp_value.value(), label.value(), color);
          };
          }
        }
      }
      break;
    case 'L':
      if (mouse) {
        if (temp_value.has_value()) {
          line *myLine = new line(pos, temp_value.value(), color);
          shapes.push_back(myLine);
          temp_value.reset();
          preview.reset();
        } else {
          {
            temp_value = pos;
            preview = new line(temp_value.value(), pos, color);
          }
        }
      }
      if (preview.has_value())
        preview.emplace() = new line(temp_value.value(), pos, color);

      state = get_current_state(state, key);
      get_color(key, color);
      undo(key, shapes);
      break;
    case 'R':
      state = get_current_state(state, key);
      get_color(key, color);
      undo(key, shapes);
      if (mouse) {
        if (temp_value.has_value()) {
          shapes.push_back(new rectangle(temp_value.value(), pos, color));
          temp_value.reset();
          preview.reset();
        } else {
          temp_value = pos;
          preview = new rectangle(temp_value.value(), pos, color);
        }
      }
      if (preview)
        preview = new rectangle(temp_value.value(), pos, color);
      break;
    }

    BeginDrawing();
    ClearBackground(BLACK);

    for (shape *my_shape : shapes) {
      my_shape->draw();
    }

    if (preview) {
      preview.value()->draw();
    }

    EndDrawing();
  }

  CloseWindow();

  return 0;
}
