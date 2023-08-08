#include "../obj_viewer.h"

/// @brief
/// @param fp
/// @param pobject
/// @return
int getGeometryInfo(FILE* fp, geometry_info* pobject) {
  getComponentsCount(fp, pobject);
  if (pobject->vertices_count < 3 || pobject->facets_count < 1)
    return INCORRECT_FILE;

  int error = getComponents(fp, pobject);

  // printf("vertices number is %d\n", pobject->vertices_count);
  // printf("faces number is %d\n", pobject->facets_count);
  // char str[11] = {0};
  // printf("first line is: \"%s\"", fgets(str, 10, fp));

  return error;
}
