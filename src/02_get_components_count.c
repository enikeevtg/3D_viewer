#include "../obj_viewer.h"

/// @brief 
/// @param fp 
/// @param pobject 
void get_components_count(FILE* fp, geometry_info* pobject) {
  char* line = NULL;
  size_t line_len = 0;

  while (getline(&line, &line_len, fp) != -1) {
    if (line[0] == 'v' && line[1] == ' ') pobject->v_count++;
    if (line[0] == 'f' && line[1] == ' ') pobject->f_count++;
  }
  if (line) free(line);

  fseek(fp, 0, SEEK_SET);
}
