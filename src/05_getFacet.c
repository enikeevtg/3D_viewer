#include "../obj_viewer.h"

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
  pobject->facets[i].vertices = (int*)calloc(vertices_count, sizeof(int));
  if (pobject->facets[i].vertices == NULL) return RAM_ERROR;

  int error = OK;
  for (int vertex_index = 0; vertex_index < vertices_count && !error;
       vertex_index++) {
    error = getFacetVertex(&line, pobject, i, vertex_index);
  }

  return error;
}

int getFacetVerticesCount(char* line) {
  int vertices_count = 0;
  do {
    line = strpbrk(line, " \r");
    if (line) {
      vertices_count++;
      line += strspn(line, " ");  // if after last number not space?
    }
  } while (*line != '\r');

  return vertices_count;
}

int getFacetVertex(char** line, geometry_info* pobject, int i,
                   int vertex_index) {
  int vertex_id = atoi(*line);
  *line += strspn(*line, " -");
  *line += strspn(*line, "0123456789");
  if (vertex_id == 0 || !(**line == ' ' || **line == '/'))
    return INCORRECT_FILE;

  if (vertex_id < 0) vertex_id += pobject->vertices_count + 1;
  pobject->facets[i].vertices[vertex_index] = vertex_id;
  *line = strpbrk(*line, " ");

  return OK;
}
