#include "model_loading.h"

int getFacetVerticesCount(char* line);
int getFacetVertex(char** line, geometry_info* pobject, int i,
                   int vertex_index);

/// @brief
/// @param line
/// @param pobject
/// @param f_index
/// @return
int getFacet(char* line, geometry_info* pobject, int i) {
  line++;
  line += strspn(line, " ");
  int vertices_count = getFacetVerticesCount(line);
  if (vertices_count < 3) return INCORRECT_FILE;

  pobject->facets[i].facet_vertices_count = vertices_count;
  pobject->facets[i].vertices_id = (int*)calloc(vertices_count, sizeof(int));
  if (pobject->facets[i].vertices_id == NULL) return RAM_ERROR;

  int error = OK;
  for (int vertex_index = 0; vertex_index < vertices_count && !error;
       vertex_index++) {
    error = getFacetVertex(&line, pobject, i, vertex_index);
  }

  return error;
}

int getFacetVerticesCount(char* line) {
  int vertices_count = 0;
  while (line && strchr("0123456789", *line)) {
    vertices_count++;
    line = strpbrk(line, " ");
    if (line) line += strspn(line, " ");
  }
  return vertices_count;
}

int getFacetVertex(char** line, geometry_info* pobject, int i,
                   int vertex_index) {
  int vertex_id = atoi(*line);
  if (vertex_id == 0) return INCORRECT_FILE;

  if (vertex_id < 0) vertex_id += pobject->vertices_count + 1;
  pobject->facets[i].vertices_id[vertex_index] = vertex_id;

  *line += strspn(*line, " -");
  *line += strspn(*line, "0123456789");
  *line = strpbrk(*line, " ");

  return OK;
}
