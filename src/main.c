#include "../obj_viewer.h"

int main(int argc, char** argv) {
  int error = OK;
  geometry_info object = {0};
  (void)argc;
  FILE* fp;
  if ((fp = fopen(argv[1], "r")) == NULL) return NO_SUCH_FILE_OR_DIRECTORY;

  char* line = NULL;
  size_t line_len = 0;
  while (getline(&line, &line_len, fp) != -1) {
    if (line[0] == 'v' && line[1] == ' ') object.v_count++;
    if (line[0] == 'f' && line[1] == ' ') object.f_count++;
  }

  printf("vertices number is %d\n", object.v_count);
  printf("faces number is %d\n", object.f_count);

  fseek(fp, 0, SEEK_SET);
  getline(&line, &line_len, fp);
  printf("first line is \"%s\"", line);
  free(line);

  fclose(fp);
  return error;
}
