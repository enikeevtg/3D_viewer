#include "model_loading.h"

void structClean(geometry_info* pobject) {
  if (pobject->vertices != NULL) free(pobject->vertices);

  if (pobject->facets != NULL) {
    for (int i = 0; i < pobject->facets_count + 1; i++) {
      if (pobject->facets[i].vertices_id != NULL) {
        free(pobject->facets[i].vertices_id);
      }
    }  // for
    free(pobject->facets);
  }
}
