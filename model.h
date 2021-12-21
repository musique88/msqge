
typedef unsigned int msqge_vao;
typedef unsigned int msqge_vbo;
typedef unsigned int msqge_ebo;

struct msqge_model{
  msqge_vao vao;
  msqge_vbo vbo;
  msqge_ebo ebo;
  unsigned int indices_count;
};

struct msqge_model msqge_init_model(float* vertices, unsigned int vertices_count, unsigned int* indices, unsigned int indices_count);
void msqge_draw_model(struct msqge_model model);
