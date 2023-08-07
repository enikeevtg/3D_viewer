#include "../obj_viewer.h"

void struct_clean(geometry_info* pobject) {
  if (pobject->array_vertex_x != NULL) free(pobject->array_vertex_x);
  if (pobject->array_vertex_y != NULL) free(pobject->array_vertex_y);
  if (pobject->array_vertex_z != NULL) free(pobject->array_vertex_z);
}
