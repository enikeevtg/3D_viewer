#include "./02_model_loading/model_loading.h"

int main(int argc, char** argv) {
  (void)argc;
  int error = OK;
  geometry_info object = {0};
  error = getGeometryInfo(argv[1], &object);

  if (!error) {
    for (int i = 1; i < object.vertices_count + 1; i++) {
      double x = object.vertices[i].x;
      double y = object.vertices[i].y;
      double z = object.vertices[i].z;
      printf("vertex #%d:\n\tx = %lf\n\ty = %lf\n\tz = %lf\n", i, x, y, z);
    }

    for (int i = 1; i < object.facets_count + 1; i++) {
      printf("facet #%d:\n", i);
      for (int j = 0; j < object.facets[i].facet_vertices_count; j++) {
        printf("\t vertex #%d: %d\n", j + 1, object.facets[i].vertex_IDs[j]);
      }
    }
  }

  printf("\nx_max = %lf\nx_min = %lf\n\n", object.x_max, object.x_min);
  printf("y_max = %lf\ny_min = %lf\n\n", object.y_max, object.y_min);
  printf("z_max = %lf\nz_min = %lf\n", object.z_max, object.z_min);

  structClean(&object);
  return error;
}
