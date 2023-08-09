#ifndef _3D_VIEWER_3D_VIEWER_H_
#define _3D_VIEWER_3D_VIEWER_H_

#define _GNU_SOURCE
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

enum error_codes { OK, NO_SUCH_FILE_OR_DIRECTORY, INCORRECT_FILE, RAM_ERROR };

typedef struct Vertex {
  double x;
  double y;
  double z;
} vertex_t;

typedef struct Facet {
  int* vertex_IDs;
  int facet_vertices_count;
} facet_t;

typedef struct Geometry {
  int vertices_count;
  int facets_count;
  vertex_t* vertices;
  facet_t* facets;
} geometry_info;

#endif  // _3D_VIEWER_3D_VIEWER_H_
