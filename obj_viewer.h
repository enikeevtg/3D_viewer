#ifndef OBJ_VIEWER_OBJ_VIEWER_H_
#define OBJ_VIEWER_OBJ_VIEWER_H_

#define _GNU_SOURCE
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

enum error_codes { OK, NO_SUCH_FILE_OR_DIRECTORY, INCORRECT_FILE, RAM_ERROR };

typedef struct Vertex {
  double x;
  double y;
  double z;
  // void printCoords();
} vertex_t;

typedef struct Facet {
  int* vertices;
  int facet_vertices_count;
} facet_t;

typedef struct Geometry {
  int vertices_count;
  int facets_count;
  vertex_t* vertices;
  facet_t* facets;
} geometry_info;

int getGeometryInfo(FILE* fp, geometry_info* pobject);
void getComponentsCount(FILE* fp, geometry_info* pobject);
int getComponents(FILE* fp, geometry_info* pobject);
int getVertex(char* line, geometry_info* pobject, int i);
int getFacet(char* line, geometry_info* pobject, int i);

void structClean(geometry_info* pobject);



#endif  // OBJ_VIEWER_OBJ_VIEWER_H_
