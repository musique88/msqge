#include "engine.h"
#include <stdlib.h>
#include <assert.h>
#include <stdio.h>

struct msqge_engine* active_engine = NULL;

const char* default_name = "game_engine";
 void msqge_set_active_engine(struct msqge_engine *engine)
{
  active_engine = engine;
}

struct msqge_engine *msqge_get_engine()
{
  return active_engine;
}

struct msqge_engine *msqge_constr_default_engine()
{
  struct msqge_engine *engine = malloc(sizeof(*engine));
  engine->window = NULL;
  engine->data = NULL;
  engine->preinit_callback = msqge_preinit_default_engine;
  engine->init_callback = msqge_init_default_engine;
  engine->predraw_callback = msqge_predraw_default_engine;
  engine->draw_callback = msqge_draw_default_engine;
  engine->resize_callback = msqge_resize_default_engine;
  engine->onresize_callback = msqge_onresize_default_engine;
  engine->end_callback = msqge_end_default_engine;
  engine->postend_callback = msqge_postend_default_engine;
  
  engine->loop = msqge_loop_default_engine;
  
  msqge_set_active_engine(engine);
  
  return engine;
}

void msqge_resize_default_engine(GLFWwindow* window, int width, int height)
{
  glViewport(0,0,width,height);
  struct msqge_engine* engine = msqge_get_engine();
  engine->onresize_callback(engine);
}

void msqge_onresize_default_engine(struct msqge_engine* engine)
{
  
}

void msqge_preinit_default_engine(struct msqge_engine* engine)
{
  // glfw shenanigans

  glfwInit();
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
  engine->window = glfwCreateWindow(DEFAULT_WINDOW_WIDTH, DEFAULT_WINDOW_HEIGHT, default_name, NULL, NULL);
  if(!engine->window){
    fprintf(stderr, "Unable to create window!\n");
    glfwTerminate();
    exit(1);
  }
  glfwMakeContextCurrent(engine->window);
  
  // glew shenanigans
  glewExperimental = GL_TRUE;
  GLenum glew_error = glewInit();
  if(glew_error){
    fprintf(stderr, "Unable to initialise glew: %s\n", glewGetErrorString(glew_error));
    glfwTerminate();
    exit(1);
  }

  glViewport(0, 0, DEFAULT_WINDOW_WIDTH, DEFAULT_WINDOW_HEIGHT);
  glfwSetFramebufferSizeCallback(engine->window, engine->resize_callback);
}

void msqge_init_default_engine(struct msqge_engine* engine)
{

}

void msqge_predraw_default_engine(struct msqge_engine* engine)
{
  glfwSwapBuffers(engine->window);
  glfwPollEvents();
  glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
  glClear(GL_COLOR_BUFFER_BIT);
}

void msqge_draw_default_engine(struct msqge_engine* engine)
{

}

void msqge_end_default_engine(struct msqge_engine* engine)
{

}

void msqge_postend_default_engine(struct msqge_engine* engine)
{
   glfwTerminate();
}

void msqge_loop_default_engine(struct msqge_engine* engine)
{
  engine->preinit_callback(engine);
  engine->init_callback(engine);
  while(!glfwWindowShouldClose(engine->window)){
    engine->predraw_callback(engine);
    engine->draw_callback(engine);
  }
  engine->end_callback(engine);
  engine->postend_callback(engine);
}
