#ifndef OBJ_VIEWER_SRC_MODEL_LOADING_H_
#define OBJ_VIEWER_SRC_MODEL_LOADING_H_

#include "../3D_viewer.h"

int getGeometryInfo(FILE* fp, geometry_info* pobject);
void getComponentsCount(FILE* fp, geometry_info* pobject);
int getComponents(FILE* fp, geometry_info* pobject);
int getVertex(char* line, geometry_info* pobject, int i);
int getFacet(char* line, geometry_info* pobject, int i);

void structClean(geometry_info* pobject);

#endif  // OBJ_VIEWER_SRC_MODEL_LOADING_H_
