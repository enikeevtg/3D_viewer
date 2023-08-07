#include "../obj_viewer.h"

/// @brief
/// @param fp
/// @param pobject
/// @return
int getObjectInfo(FILE* fp, geometry_info* pobject) {
  getComponentsCount(fp, pobject);
  if (pobject->v_count < 3 || pobject->f_count < 1) return INCORRECT_FILE;

  int error = getComponents(fp, pobject);

  // printf("vertices number is %d\n", pobject->v_count);
  // printf("faces number is %d\n", pobject->f_count);
  // char str[11] = {0};
  // printf("first line is: \"%s\"", fgets(str, 10, fp));

  for (int i = 0; i < 3; i++) {
    double x = pobject->array_vertex_x[i];
    double y = pobject->array_vertex_y[i];
    double z = pobject->array_vertex_z[i];
    printf("#%d:\n x = %lf\n y = %lf\n z = %lf\n", i, x, y, z);
  }
  return error;
}
