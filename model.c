#include "model.h"
#include <GL/glew.h>

struct msqge_model msqge_init_model(float* vertices, unsigned int vertices_count, unsigned int* indices, unsigned int indices_count)
{
  struct msqge_model model;
  glGenVertexArrays(1, &model.vao);
  glGenBuffers(1, &model.vbo);
  glGenBuffers(1, &model.ebo);
  model.indices_count = indices_count;  
  glBindVertexArray(model.vao);
  
  glBindBuffer(GL_ARRAY_BUFFER, model.vbo);
  glBufferData(GL_ARRAY_BUFFER, vertices_count * sizeof(*vertices), vertices, GL_STATIC_DRAW);

  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, model.ebo);
  glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices_count * sizeof(*indices), indices, GL_STATIC_DRAW);
  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(*vertices), (void*)0);
  glEnableVertexAttribArray(0);

  glBindBuffer(GL_ARRAY_BUFFER, 0);
  glBindVertexArray(0);
  return model;
}

void msqge_draw_model(struct msqge_model model)
{
  glBindVertexArray(model.vao);
  glDrawElements(GL_TRIANGLES, model.indices_count, GL_UNSIGNED_INT, 0);
}