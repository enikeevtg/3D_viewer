#include "model_loading.h"

int main(int argc, char** argv) {
  (void)argc;
  int error = OK;
  geometry_info object = {0};

  FILE* fp;
  if ((fp = fopen(argv[1], "r")) == NULL) {
    error = NO_SUCH_FILE_OR_DIRECTORY;
  } else {
    error = getGeometryInfo(fp, &object);

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
    structClean(&object);
    fclose(fp);
  }
  return error;
}
