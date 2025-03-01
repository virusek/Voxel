#include "vbo.h"

#include <glad/glad.h>

struct VBO vbo_create(u32 type, bool isDynamic) {
  struct VBO vbo;
  vbo.type = type;
  vbo.isDynamic = isDynamic;

  glGenBuffers(1, &vbo.id);
  glBindBuffer(type, vbo.id);

  return vbo;
}

void vbo_bind(struct VBO *self) { glBindBuffer(self->type, self->id); }
void vbo_destroy(struct VBO *self) { glDeleteBuffers(1, &self->id); }

void vbo_data(struct VBO *self, size_t size, void *data) {
  glBufferData(self->type, size, data,
               self->isDynamic ? GL_DYNAMIC_DRAW : GL_STATIC_DRAW);
}
