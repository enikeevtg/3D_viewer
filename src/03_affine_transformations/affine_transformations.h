#ifndef _3D_VIEWER_SRC_03_AFFINE_TRANSFORMATIONS_AFFINE_TRANSFORMATIONS_H_
#define _3D_VIEWER_SRC_03_AFFINE_TRANSFORMATIONS_AFFINE_TRANSFORMATIONS_H_

#include "../3D_viewer.h"

void translationAllDirections(geometry_info* pobject, vertex_t* delta);
void translationXDirection(geometry_info* pobject, double dx);
void translationYDirection(geometry_info* pobject, double dy);
void translationZDirection(geometry_info* pobject, double dz);

void scaleModel(geometry_info* pobject, double scale);

#endif  // _3D_VIEWER_SRC_03_AFFINE_TRANSFORMATIONS_AFFINE_TRANSFORMATIONS_H_
