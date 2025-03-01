#include "shader.h"
#include "cglm/types-struct.h"

#include <glad/glad.h>
#include <stdio.h>
#include <stdlib.h>

static char *_read_file(const char *filename, size_t *out_size) {
  FILE *file = fopen(filename, "rb");
  if (!file) {
    perror("Failed to open file");
    return NULL;
  }

  fseek(file, 0, SEEK_END);
  long file_size = ftell(file);
  rewind(file);

  if (file_size < 0) {
    perror("Failed to determine file size");
    fclose(file);
    return NULL;
  }

  char *buffer = (char *)malloc(file_size + 1);
  if (!buffer) {
    perror("Failed to allocate memory");
    fclose(file);
    return NULL;
  }

  size_t read_size = fread(buffer, 1, file_size, file);
  fclose(file);

  if (read_size != file_size) {
    perror("File read error");
    free(buffer);
    return NULL;
  }

  buffer[file_size] = '\0';

  if (out_size) {
    *out_size = file_size;
  }

  return buffer;
}

u32 _compileShader(const char *src, GLenum type) {
  static int success;
  static char infoLog[512];

  u32 shaderId = glCreateShader(type);
  glShaderSource(shaderId, 1, &src, NULL);
  glCompileShader(shaderId);

  glGetShaderiv(shaderId, GL_COMPILE_STATUS, &success);
  if (!success) {
    glGetShaderInfoLog(shaderId, 512, NULL, infoLog);
    printf("Couldn't compile shader: %s", infoLog);
  }

  return shaderId;
}

struct Shader shader_create(const char *vertexPath, const char *fragmentPath) {
  const char *vertexSrc = _read_file(vertexPath, NULL);
  const char *fragSrc = _read_file(fragmentPath, NULL);

  u32 vertexShader = _compileShader(vertexSrc, GL_VERTEX_SHADER);
  u32 fragShader = _compileShader(fragSrc, GL_FRAGMENT_SHADER);

  struct Shader shader;

  shader.id = glCreateProgram();
  glAttachShader(shader.id, vertexShader);
  glAttachShader(shader.id, fragShader);
  glLinkProgram(shader.id);
  glUseProgram(shader.id);

  glDeleteShader(vertexShader);
  glDeleteShader(fragShader);

  free((void *)vertexSrc);
  free((void *)fragSrc);

  return shader;
}

void shader_bind(struct Shader *self) { glUseProgram(self->id); }

// UNIFORM FUNCTIONS

// TODO: Add location cache
i32 _getUniformLocation(struct Shader *self, const char *name) {
  return glGetUniformLocation(self->id, name);
}

void shader_setFloat(struct Shader *self, const char *name, float value) {
  glUniform1f(_getUniformLocation(self, name), value);
}

void shader_setMatrix4x4(struct Shader *self, const char *name, mat4s value) {
  glUniformMatrix4fv(_getUniformLocation(self, name), 1, GL_FALSE,
                     (const GLfloat *)&value.raw);
}
