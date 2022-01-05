#include "model.h"
#include <GL/glew.h>
#include "file_utility.h"
#include "msqglm/vec.h"
#include "msqutils/msq.h"
#include <stdio.h>
#include <stdlib.h>

// TODO update to use msqglm datastructures
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

void msqge_parse_obj(const char* filepath, msqglm_vec3** vertices, unsigned int* vertices_size, unsigned int** faces, unsigned int* faces_size)
{
    const char* fc = msq_get_file_content(filepath);
    unsigned int pos = 0;
    char line[128];
    unsigned int pos_in_line;
    msq_vector* vertices_list = v_create(10); 
    msq_vector* faces_list = v_create(10);
    msqglm_vec3* vector; 
    unsigned int* i1_face;
    unsigned int* i2_face;
    unsigned int* i3_face;
    int throwaway;
    while(fc[pos]){
        pos_in_line = 0;
        do {
            line[pos_in_line++] = fc[pos];
        } while (fc[pos++] != '\n');
        line[pos_in_line] = '\0';
        switch(line[0]){
            case 'v':
                if(line[1] != 'n'){
                    vector = malloc(sizeof(*vector));
                    sscanf(line, "v %f %f %f", &(*vector)[0], &(*vector)[1], &(*vector)[2]);
                    v_append(vertices_list, (void*)vector);
                }
                break;
            case 'f':
                //this is garbage
                i1_face = malloc(sizeof(*i1_face)); 
                i2_face = malloc(sizeof(*i2_face)); 
                i3_face = malloc(sizeof(*i3_face)); 
                sscanf(line, "f %d//%d %d//%d %d//%d ",i1_face,&throwaway,i2_face,&throwaway,i3_face,&throwaway);
                v_append(faces_list, (void*)i1_face);
                v_append(faces_list, (void*)i2_face);
                v_append(faces_list, (void*)i3_face);
                break;
            default:
                break;
        }
    }
    *vertices = malloc(sizeof(**vertices) * vertices_list->s);
    *vertices_size = vertices_list->s;
    unsigned int i; 
    for(i = 0; i < vertices_list->s; i++){
        (*vertices)[i][0] = (*(msqglm_vec3*)vertices_list->o[i])[0];
        (*vertices)[i][1] = (*(msqglm_vec3*)vertices_list->o[i])[1];
        (*vertices)[i][2] = (*(msqglm_vec3*)vertices_list->o[i])[2];
    }
    *faces = malloc(sizeof(**faces) * faces_list->s);
    *faces_size = faces_list->s; 
    for(i = 0; i < faces_list->s; i++)
        (*faces)[i] = *(unsigned int*)faces_list->o[i];
    v_free(vertices_list);
    v_free(faces_list);
}
