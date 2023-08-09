#include "model_loading.h"

/// @brief getting geometric object parameters from .obj file
/// @param fp .obj file pointer
/// @param pobject geometric object pointer
/// @return error code
int getGeometryInfo(FILE* fp, geometry_info* pobject) {
  getComponentsCount(fp, pobject);
  if (pobject->vertices_count < 3 || pobject->facets_count < 1)
    return INCORRECT_FILE;

  int error = getComponents(fp, pobject);

  return error;
}
