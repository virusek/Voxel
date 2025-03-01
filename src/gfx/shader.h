#ifndef SHADER_H
#define SHADER_H

#include "../util/util.h"

struct Shader {
  u32 id;
};

struct Shader shader_create(const char *vertexPath, const char *fragmentPath);

void shader_bind(struct Shader *self);

// Uniform functions
void shader_setFloat(struct Shader *self, const char *name, float value);
void shader_setMatrix4x4(struct Shader *self, const char *name, mat4s value);

#endif // !SHADER_H
