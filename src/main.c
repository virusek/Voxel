#include "glad/glad.h"
#include "util/util.h"

#include "gfx/shader.h"
#include "gfx/texture.h"
#include "gfx/window.h"

#include "gfx/vao.h"
#include "gfx/vbo.h"

#include "state.h"

struct State state;

struct VAO vao;
struct VBO vbo, ibo;

struct Shader shader;
struct Texture texture;
// TEST

void init() {
  state.window = &window;

  // Quad Setup

  f32 vertices[] = {
      // positions        // colors         // UVs
      0.5f,  0.5f,  0.0f, 1.0f, 0.0f, 0.0f, 1.0f, 1.0f, // top right
      0.5f,  -0.5f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f, // bottom right
      -0.5f, -0.5f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, // bottom left
      -0.5f, 0.5f,  0.0f, 0.5f, 0.5f, 1.0f, 0.0f, 1.0f  // top left
  };

  u32 indices[] = {
      // note that we start from 0!
      0, 1, 3, // first triangle
      1, 2, 3  // second triangle
  };

  texture = texture_loadFromPath("res/wall.jpg");
  texture_bind(&texture);

  vao = vao_create();
  vao_bind(&vao);

  vbo = vbo_create(GL_ARRAY_BUFFER, false);
  vbo_bind(&vbo);
  vbo_data(&vbo, sizeof(vertices), vertices);

  ibo = vbo_create(GL_ELEMENT_ARRAY_BUFFER, false);
  vbo_bind(&ibo);
  vbo_data(&ibo, sizeof(indices), indices);

  vao_attr(vao, &vbo, 0, 3, GL_FLOAT, 8 * sizeof(f32), 0);
  vao_attr(vao, &vbo, 1, 3, GL_FLOAT, 8 * sizeof(f32), 3 * sizeof(f32));
  vao_attr(vao, &vbo, 2, 2, GL_FLOAT, 8 * sizeof(f32), 6 * sizeof(f32));

  shader = shader_create("res/simple.vert.glsl", "res/simple.frag.glsl");
  shader_bind(&shader);
}

void update() {}

void render() {
  glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
  glClear(GL_COLOR_BUFFER_BIT);

  glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
}

int main(void) {
  window_create(1280, 720, "Voxel", init, update, render);
  window_loop();

  return 0;
}
