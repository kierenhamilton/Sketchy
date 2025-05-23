#include "utils.h"
#include "raylib.h"

char get_current_state(char &state, const char &key) {
  if (!key)
    return state;
  if (key == KEY_L || key == KEY_N || key == KEY_R || key == KEY_T)
    return key;
  return state;
}

void get_color(const char &key, Color &color) {
  if (!key)
    return;
  switch (key) {
  case 'W':
    color = WHITE;
    return;
  case 'B':
    color = BLUE;
    return;
  case 'P':
    color = PINK;
    return;
  case 'G':
    color = GREEN;
    return;
  case 'O':
    color = RED;
    return;
  }
  return;
}

void line::draw() { DrawLine(start.x, start.y, end.x, end.y, color); }

void rectangle::draw() {
  DrawRectangle(position.x, position.y, dimention.x, dimention.y, color);
}

rectangle *set_rectangle(Vector2 start, Vector2 end, Color color) {

  float changex = end.x - start.x;
  float changey = end.y - start.y;

  if (changex < 0) {
    start.x += changex;
    changex *= -1;
  }
  if (changey < 0) {
    start.y += changey;
    changey *= -1;
  }
  Vector2 dimention{changex, changey};

  return new rectangle(start, dimention, color);
}
void undo(const char &key, std::vector<shape *> &shapes) {
  if (key == 'Z')
    shapes.pop_back();
  if (key == 'C')
    shapes.clear();
}

void text::draw(){
  DrawText(writing.c_str(), position.x, position.y, 30, color);
}
