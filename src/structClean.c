#include "../obj_viewer.h"

void structClean(geometry_info* pobject) {
  if (pobject->vertices != NULL) free(pobject->vertices);
}
