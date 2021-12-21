#include <stdio.h>
#include <stdlib.h>
#include "file_utility.h"

const char* msq_get_file_content(const char* file_path)
{
  FILE* file = fopen(file_path, "r");
  fseek(file, 0, SEEK_END);
  long file_size = ftell(file);
  fseek(file, 0, SEEK_SET);
  
  char* content = malloc(file_size + 1);
  fread(content, file_size, 1, file);
  fclose(file);
  content[file_size] = '\0';
  
  return (const char*)content;
}

void msq_free_file(const char* file_content)
{
  free((void*)file_content);
}
