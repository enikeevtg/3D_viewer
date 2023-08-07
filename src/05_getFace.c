#include "../obj_viewer.h"

int getPointsCount(char* line);
int getFacePoint(char* line, geometry_info* pobject, int f_index,
                 int point_index);

/// @brief
/// @param line
/// @param pobject
/// @param f_index
/// @return
int getFace(char* line, geometry_info* pobject, int f_index) {
  int points_number = getPointsCount(line);
  if (points_number < 3) return INCORRECT_FILE;

  pobject->array_faces[f_index] = (int*)calloc(points_number, sizeof(int));
  if (pobject->array_faces == NULL) return RAM_ERROR;

  int error = OK;
  line++;
  line += strspn(line, " ");
  int point_index = 0;
  while (*line != '\r' && !error) {
    error = getFacePoint(&line, pobject, f_index, point_index);
  }
  return error;
}

int getPointsCount(char* line) {
  int points_number = 0;
  char* ptr = line + 1;
  ptr += strspn(ptr, " ");
  do {
    ptr = strpbrk(ptr, " \r");
    if (ptr) {
      points_number++;
      ptr += strspn(ptr, " ");
    }
  } while (*ptr != '\r');

  return points_number;
}

int getFacePoint(char* line, geometry_info* pobject, int f_index,
                 int point_index) {
  return OK;
}
