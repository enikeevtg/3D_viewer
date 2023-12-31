#include "model_loading.h"

/// @brief getting geometric object vertices and facets info from .obj file
/// @param fp .obj file pointer
/// @param pobject geometric object pointer
/// @return error code
int getComponents(FILE* fp, geometry_info* pobject) {
  pobject->vertices =
      (vertex_t*)calloc(pobject->vertices_count, sizeof(vertex_t));
  pobject->facets = (facet_t*)calloc(pobject->facets_count, sizeof(facet_t));

  int error = OK;
  if (pobject->vertices == NULL || pobject->facets == NULL) {
    error = RAM_ERROR;
  } else {
    char* line = NULL;
    size_t line_len = 0;
    int vertex_id = 0;
    int facet_id = 0;
    int vertex_id_start = 0;
    int vertex_id_end = 0;
    while (getline(&line, &line_len, fp) != -1 && !error) {
      if (strncmp(line, "v ", 2) == 0) {
        error = getVertex(line, pobject, vertex_id);
        vertex_id_end = vertex_id;  // hard ducktape if any groups
        vertex_id++;
      } else if (strncmp(line, "f ", 2) == 0) {
        error =
            getFacet(line, pobject, facet_id, vertex_id_start, vertex_id_end);
        facet_id++;
      } else if (strncmp(line, "g ", 2) == 0 && vertex_id_start != 0) {
        vertex_id_start = vertex_id + 1;  // hard ducktape if any groups
      }
    }
    if (line) free(line);
  }
  return error;
}
