int getFacetVerticesCount(char* line) {
  int vertices_count = 0;
  do {
    line = strpbrk(line, " \r");
    if (line) {
      vertices_count++;
      line += strspn(line, " ");  // if after last number not space?
    }
  } while (*line != '\r');

  return vertices_count;
}
