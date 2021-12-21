#include "shader.h"
#include "file_utility.h"
#include <stdio.h>
#include <GL/glew.h>

#define SHADER_ERR_SIZE 1024

// takes as input, a shader, a check function (either glGetShaderiv or glGetProgramiv) and a status type (either GL_COMPILE_STATUS or GL_LINK_STATUS)

void check_shader_error(shader id, void(*check_function)(GLuint,GLenum,GLint*), 
                        GLenum status_type, void(*get_info_log)(GLuint,GLsizei,GLsizei*,GLchar*))
{
  char info[SHADER_ERR_SIZE];
  int success;
  check_function(id, status_type, &success);
  if(!success){
    get_info_log(id, SHADER_ERR_SIZE, NULL, info);
    fprintf(stderr, "Shader compilation error: %s\n", info);
  }
}

shader_program msqge_shader_create(const char* vertex_shader, const char* fragment_shader)
{
  const char* vertex_shader_file_content = msq_get_file_content(vertex_shader);
  const char* fragment_shader_file_content = msq_get_file_content(fragment_shader);
  
  shader vertex = glCreateShader(GL_VERTEX_SHADER);
  glShaderSource(vertex, 1, &vertex_shader_file_content, NULL);
  glCompileShader(vertex);
  check_shader_error(vertex, glGetShaderiv, GL_COMPILE_STATUS, glGetShaderInfoLog);
  
  shader frag = glCreateShader(GL_FRAGMENT_SHADER);
  glShaderSource(frag, 1, &fragment_shader_file_content, NULL);
  glCompileShader(frag);
  check_shader_error(frag, glGetShaderiv, GL_COMPILE_STATUS, glGetShaderInfoLog);
  
  shader_program program = glCreateProgram();
  glAttachShader(program, vertex);
  glAttachShader(program, frag);
  glLinkProgram(program);
  check_shader_error(program, glGetProgramiv, GL_LINK_STATUS, glGetProgramInfoLog);
  glDeleteShader(vertex);
  glDeleteShader(frag);
  
  msq_free_file(vertex_shader_file_content);
  msq_free_file(fragment_shader_file_content);
  return program;
}

void msqge_shader_set_int(shader_program id, const char* int_name, int value)
{
  glUniform1i(glGetUniformLocation(id, int_name), value);
}

void msqge_shader_set_float(shader_program id, const char* float_name, float value)
{
  glUniform1f(glGetUniformLocation(id, float_name), value);
}
