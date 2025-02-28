#include "util/util.h"

#include <glad/glad.h>
#include <stdio.h>
#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>

int main(void) {
  if (!glfwInit()) {
    printf("Error: Couldn't initialize GLFW\n");

    const char *description;
    i32 code = glfwGetError(&description);

    printf("GLFW Error code: %d, %s\n", code, description);

    return -1;
  }

  void *window = glfwCreateWindow(640, 480, "Voxel", NULL, NULL);
  if (!window) {
    printf("Error: Couldn't create a window!\n");
    return -1;
  }
  glfwMakeContextCurrent(window);

  while (!glfwWindowShouldClose(window)) {
    // Inf loop
  }

  glfwDestroyWindow(window);
  glfwTerminate();

  return 0;
}
