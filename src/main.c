#include "../obj_viewer.h"

int main(int argc, char** argv) {
  (void)argc;
  int error = OK;
  geometry_info object = {0};

  FILE* fp;
  if ((fp = fopen(argv[1], "r")) == NULL) {
    error = NO_SUCH_FILE_OR_DIRECTORY;
  } else {
    error = get_object_info(fp, &object);
    struct_clean(&object);
    fclose(fp);
  }
  return error;
}
