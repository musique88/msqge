#include <GL/glew.h>
#include <GLFW/glfw3.h>

#define DEFAULT_WINDOW_WIDTH 1024
#define DEFAULT_WINDOW_HEIGHT 720

struct msqge_engine {
  GLFWwindow *window;
  // will be called when resizing the window
  void (*resize_callback)(GLFWwindow*, int, int);
  // will be callde when resizing the window
  void (*onresize_callback)(struct msqge_engine*);
  // used for initialisation of any library used
  void (*preinit_callback)(struct msqge_engine*);
  // used to initialise data
  void (*init_callback)(struct msqge_engine*);
  // will be called on every frame before draw_callback
  void (*predraw_callback)(struct msqge_engine*);
  // will be called on every frame
  void (*draw_callback)(struct msqge_engine*);
  // used to free data
  void (*end_callback)(struct msqge_engine*);
  // used for deinitialising libraries
  void (*postend_callback)(struct msqge_engine*);
  void (*loop)(struct msqge_engine*);
  void *data;

  const char *game_name;
};

struct msqge_engine* msqge_constr_default_engine();

void msqge_resize_default_engine(GLFWwindow*, int, int);
void msqge_onresize_default_engine(struct msqge_engine*);
void msqge_preinit_default_engine(struct msqge_engine*);
void msqge_init_default_engine(struct msqge_engine*);
void msqge_predraw_default_engine(struct msqge_engine*);
void msqge_draw_default_engine(struct msqge_engine*);
void msqge_end_default_engine(struct msqge_engine*);
void msqge_postend_default_engine(struct msqge_engine*);

void msqge_loop_default_engine(struct msqge_engine*);

void msqge_set_active_engine(struct msqge_engine*);
struct msqge_engine* msqge_get_engine();
