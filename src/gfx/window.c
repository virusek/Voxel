#include "window.h"

struct Window window;

static void _key_callback(GLFWwindow *window, i32 key, i32 scancode, i32 action,
                          i32 mods) {
  if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS) {
    glfwSetWindowShouldClose(window, true);
  }
}

static void _framebuffer_size_callback(GLFWwindow *window, int width,
                                       int height) {
  glViewport(0, 0, width, height);
}

void window_create(u32 width, u32 height, const char *title, FWindow init,
                   FWindow update, FWindow render) {
  window.width = width;
  window.height = height;
  window.init = init;
  window.update = update;
  window.render = render;

  if (!glfwInit()) {
    printf("Error: Couldn't initialize GLFW\n");
  }

  window.handle = glfwCreateWindow(1280, 720, "Voxel", NULL, NULL);
  if (!window.handle) {
    printf("Error: Couldn't create a window!\n");
  }

  glfwMakeContextCurrent(window.handle);
  glfwSwapInterval(1); // TODO: Change for FPS limiting instead of VSync

  // Callbacks
  glfwSetKeyCallback(window.handle, _key_callback);
  glfwSetFramebufferSizeCallback(window.handle, _framebuffer_size_callback);

  // Init OpenGL
  if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
    printf("Failed to initialize GLAD");
  }

  glViewport(0, 0, 1280, 720);
}

void window_destroy() {
  glfwDestroyWindow(window.handle);
  glfwTerminate();
}

static void _init() { window.init(); }
static void _update() { window.update(); }
static void _render() {
  window.render();

  glfwPollEvents();
  glfwSwapBuffers(window.handle);
}

void window_loop() {
  _init();

  while (!glfwWindowShouldClose(window.handle)) {
    _update();
    _render();
  }

  window_destroy();
}
