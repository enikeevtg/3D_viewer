#include "model_loading.h"

/// @brief
/// @param fp
/// @param pobject
/// @return
int getComponents(FILE* fp, geometry_info* pobject) {
  pobject->vertices =
      (vertex_t*)calloc(pobject->vertices_count + 1, sizeof(vertex_t));
  pobject->facets =
      (facet_t*)calloc(pobject->facets_count + 1, sizeof(facet_t));

  int error = OK;
  if (pobject->vertices == NULL || pobject->facets == NULL) {
    error = RAM_ERROR;
  } else {
    ssize_t read_bytes = 0;
    char* line = NULL;
    size_t line_len = 0;
    int vertex_index = 1;
    int facet_index = 1;
    while ((read_bytes = getline(&line, &line_len, fp)) != -1 && !error) {
      line[read_bytes - 1] = '\0';
      if (line[0] == 'v' && line[1] == ' ') {  // strncmp()
        error = getVertex(line, pobject, vertex_index);
        vertex_index++;
      } else if (line[0] == 'f' && line[1] == ' ') {  // strncmp()
        error = getFacet(line, pobject, facet_index);
        facet_index++;
      }
    }
    if (line) free(line);
  }
  return error;
}
