typedef unsigned int shader;
typedef unsigned int shader_program;

shader_program msqge_shader_create(const char *vertex_shader_path, const char *frag_shader_path);

void msqge_shader_set_int(shader_program id, const char *int_name, int value);
void msqge_shader_set_float(shader_program id, const char *float_name, float value);

