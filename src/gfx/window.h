#ifndef WINDOW_H
#define WINDOW_H

#include "../util/util.h"

#include <glad/glad.h>
#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>

typedef void (*FWindow)();

struct Window {
  GLFWwindow *handle;
  u32 width, height;

  FWindow init, update, render;
};

extern struct Window window;

void window_create(u32 width, u32 height, const char *title, FWindow init,
                   FWindow update, FWindow render);
void window_destroy();
void window_loop();

#endif // !WINDOW_H
