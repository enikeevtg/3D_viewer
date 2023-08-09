#ifndef _3D_VIEWER_SRC_MODEL_LOADING_H_
#define _3D_VIEWER_SRC_MODEL_LOADING_H_

#include "../3D_viewer.h"

int getGeometryInfo(char* filename, geometry_info* pobject);
void getComponentsCount(FILE* fp, geometry_info* pobject);
int getComponents(FILE* fp, geometry_info* pobject);
int getVertex(char* line, geometry_info* pobject, int ID);
int getFacet(char* line, geometry_info* pobject, int ID);

void structClean(geometry_info* pobject);

#endif  // _3D_VIEWER_SRC_MODEL_LOADING_H_
