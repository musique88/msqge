#include <stdio.h>

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "shader.h"
#include <math.h>
#include "file_utility.h"
#include "model.h"

#define WINDOW_WIDTH 1024
#define WINDOW_HEIGHT 720

void resize_callback(GLFWwindow *window, int width, int height)
{
	glViewport(0,0,width,height);
}

int main()
{
	// glfw shenanigans
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	GLFWwindow* window = glfwCreateWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "game_engine", NULL, NULL);
	if(!window){
		fprintf(stderr, "Unable to create window!\n");
		glfwTerminate();
		return 1;
	}
	glfwMakeContextCurrent(window);
	
	// glew shenanigans
	glewExperimental = GL_TRUE;
	GLenum glew_error = glewInit();
	if(glew_error){
		fprintf(stderr, "Unable to initialise glew: %s\n", glewGetErrorString(glew_error));
		return 1;
	}
	
	// testing
	float triangle_vertices[] = {
		-0.5f, -0.5f, 0.f,
		0.5f, -0.5f, 0.f,
		-0.5f, 0.5f, 0.f,
		0.5f, 0.5f, 0.f
	};

	unsigned int indices[] = {
		0, 1, 2,
		2, 1, 3
	};

	glViewport(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT);
	glfwSetFramebufferSizeCallback(window, &resize_callback);

	shader_program program = msqge_shader_create("res/shader.vs", "res/shader.fs");
	struct msqge_model model = msqge_init_model(triangle_vertices, 12, indices, 6);
	while(!glfwWindowShouldClose(window)){
		glClearColor(0.0f, 1.0f, 0.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);
		
		glUseProgram(program);
		glUniform4f(glGetUniformLocation(program, "color"), sin(glfwGetTime()) / 2.f + 0.5f, 0.f, 0.f, 1.f);
		msqge_draw_model(model);

		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	glfwTerminate();
}
