#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char** argv) {
  FILE* fp = NULL;
  if ((fp = fopen(argv[1], "r")) != NULL) {
    ssize_t bytes_read = 0;
    char* str = NULL;
    size_t str_len = 0;

    int line_count = 0;
    while ((bytes_read = getline(&str, &str_len, fp)) != -1) {
      line_count++;
      if (str[bytes_read - 2] == '\r') {
        printf("line #%d: -2 \\r\n", line_count);
      }
      if (str[bytes_read - 1] == '\n') {
        printf("line #%d: -1 \\n\n", line_count);
      }
      if (str[bytes_read - 1] == '\r') {
        printf("line #%d: -1 \\r\n", line_count);
      }
      if (str[bytes_read] == '\0') {
        printf("line #%d: -0 \\0\n", line_count);
      }
    }
    fclose(fp);
    if (str) free(str);
  }
  printf("%d", atoi(" -1 1"));
  return 0;
}
