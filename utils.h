#ifndef UTILS_H
#define UTILS_H
#include "raylib.h"
#include <string>
#include <vector>

char get_current_state(char &state, const char &key);
void get_color(const char &key, Color &color);

struct shape {
  virtual ~shape() {}
  virtual void draw() = 0;
};

struct rectangle : shape {
  Vector2 position;
  Vector2 dimention;
  Color color;
  void draw();
  rectangle(Vector2 start, Vector2 end, Color c) {

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
    position = {start.x, start.y};
    dimention = {changex, changey};
    color = c;
  }
};

struct line : shape {
  Vector2 start;
  Vector2 end;
  Color color;
  void draw();
  line(Vector2 s, Vector2 e, Color c) : start(s), end(e), color(c) {}
};

struct text : shape {
  Vector2 position;
  std::string writing;
  Color color;
  void draw();
  text(Vector2 p, std::string t, Color c) : position(p), writing(t), color(c) {}
};

void undo(const char &key, std::vector<shape *> &shapes);

#endif
