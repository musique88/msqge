#include <stdio.h>
#include "engine.h"
#include "shader.h"
#include <math.h>
#include "file_utility.h"
#include "model.h"
#include <stdlib.h>
#include "msqglm/vec.h"

struct data_struct{
	struct msqge_model model;
	shader_program shader_program;
};

void init(struct msqge_engine* engine)
{
	unsigned int *indices;
    msqglm_vec3 *vertices;
    unsigned int indices_size;
    unsigned int vertices_size;
    msqge_parse_obj("res/default_cube.obj", &vertices, &vertices_size, &indices, &indices_size);
    engine->data = malloc(sizeof(struct data_struct));
	struct data_struct* data = (struct data_struct*)engine->data; 
	data->shader_program = msqge_shader_create("res/shader.vs", "res/shader.fs");
	data->model = msqge_init_model((float*)vertices, vertices_size * 3, indices, indices_size);
}

void draw(struct msqge_engine* engine)
{
	struct data_struct* data = (struct data_struct*)engine->data; 
	glUseProgram(data->shader_program);
	glUniform4f(glGetUniformLocation(data->shader_program, "color"), sin(glfwGetTime()) / 2.f + 0.5f, 0.f, 0.f, 1.f);
	msqge_draw_model(data->model);
}

void end(struct msqge_engine* engine)
{
	free(engine->data);
}

int main()
{
	struct msqge_engine* engine = msqge_constr_default_engine();
	engine->init_callback = init;
	engine->draw_callback = draw;
	engine->end_callback = end;
	engine->loop(engine);
}
