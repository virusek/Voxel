#ifndef VAO_H
#define VAO_H

#include "../util/util.h"

struct VBO;

struct VAO {
  u32 id;
};

struct VAO vao_create();
void vao_bind(struct VAO *self);
void vao_destroy(struct VAO *self);

void vao_attr(struct VAO self, struct VBO *vbo, u32 index, i32 size, u32 type,
              i32 stride, size_t offset);

#endif // !VAO_H
