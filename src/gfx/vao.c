#include "vao.h"

#include "vbo.h"
#include <glad/glad.h>

struct VAO vao_create() {
  struct VAO vao;

  glGenVertexArrays(1, &vao.id);
  glBindVertexArray(vao.id);

  return vao;
}

void vao_bind(struct VAO *self) { glBindVertexArray(self->id); }
void vao_destroy(struct VAO *self) { glDeleteVertexArrays(1, &self->id); }

void vao_attr(struct VAO self, struct VBO *vbo, u32 index, i32 size, u32 type,
              i32 stride, size_t offset) {
  vao_bind(&self);
  vbo_bind(vbo);

  switch (type) {
  case GL_BYTE:
  case GL_UNSIGNED_BYTE:
  case GL_SHORT:
  case GL_UNSIGNED_SHORT:
  case GL_INT:
  case GL_UNSIGNED_INT:
  case GL_INT_2_10_10_10_REV:
  case GL_UNSIGNED_INT_2_10_10_10_REV:
    glVertexAttribIPointer(index, size, type, stride, (void *)offset);
    break;
  default:
    glVertexAttribPointer(index, size, type, GL_FALSE, stride, (void *)offset);
    break;
  }
  glEnableVertexAttribArray(index);
}
