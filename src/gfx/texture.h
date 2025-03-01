#ifndef TEXTURE_H
#define TEXTURE_H

#include "../util/util.h"

struct Texture {
  u32 id;
};

struct Texture texture_loadFromPath(const char *path);

void texture_bind(struct Texture *self);
void texture_destroy(struct Texture *self);

#endif // !TEXTURE_H
