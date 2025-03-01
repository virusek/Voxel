#ifndef VBO_H
#define VBO_H

#include "../util/util.h"

struct VBO {
  u32 id;
  u32 type;
  bool isDynamic;
};

struct VBO vbo_create(u32 type, bool isDynamic);

void vbo_bind(struct VBO *self);
void vbo_destroy(struct VBO *self);

void vbo_data(struct VBO *self, size_t size, void *data);

#endif // !VBO_H
