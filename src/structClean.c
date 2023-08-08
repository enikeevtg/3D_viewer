#include "../obj_viewer.h"

void structClean(geometry_info* pobject) {
  if (pobject->vertices != NULL) free(pobject->vertices);

  if (pobject->facets != NULL) {
    for (int i = 0; i < pobject->facets_count; i++) {
      if (pobject->facets[i].vertices != NULL) {
        free(pobject->facets[i].vertices);
      }
    }  // for
    free(pobject->facets);
  }
}
