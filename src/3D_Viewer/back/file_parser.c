#include "3d_viewer.h"

int open_file(char *f_name, FILE **f) {
  *f = fopen(f_name, "r");
  if (!*f) {
    printf("3D_Viewer: No such file %s\n", f_name);
  }
  return (*f) ? SUCCESS : FAIL;
}

int count_options(FILE *f, object *result) {
  int status = FAIL;
  char buffer[BUFF_SIZE] = {0};
  init_object(result);
  while (fgets(buffer, BUFF_SIZE, f)) {
    if (buffer[0] == 'v' && buffer[1] == ' ')
      ++(result->vertex_count);
    else if (buffer[0] == 'f' && buffer[1] == ' ') {
      ++(result->facets_count);
      result->connections += amount_connections(buffer);
    }
  }
  if (result->vertex_count && result->facets_count) status = allocate(result);
  return status;
}

int allocate(object *result) {
  result->vertex_arr =
      (double *)calloc(result->vertex_count * 3, sizeof(double));
  if (result->vertex_arr) {
    result->facets_arr =
        (unsigned int *)calloc(result->connections * 2, sizeof(unsigned int));
  }
  int status = (result->facets_arr) ? SUCCESS : FAIL;
  if (status) free_object(result);
  return status;
}

int amount_connections(char *buffer) {
  char sep[2] = " ";
  char *istr = strtok(buffer, sep);
  int i = 0;
  while (istr) {
    // istr = strtok(NULL, sep);
    if (istr != NULL && (isdigit(*istr) || *istr == '-')) {
      i++;
    }
    istr = strtok(NULL, sep);
  }
  return i;
}

void free_object(object *result) {
  if (result->vertex_arr) free(result->vertex_arr);
  if (result->facets_arr) free(result->facets_arr);
  if (result) free(result);
}

void init_object(object *result) {
  result->vertex_count = 0;
  result->facets_count = 0;
  result->vertex_arr = 0;
  result->facets_arr = 0;
  result->connections = 0;
  /*Обнуляем структуру опорных координат*/
  result->scale.x_center = 0;
  result->scale.y_center = 0;
  result->scale.z_center = 0;
  result->scale.x_max = 0;
  result->scale.y_max = 0;
  result->scale.z_max = 0;
  result->scale.x_min = 0;
  result->scale.y_min = 0;
  result->scale.z_min = 0;
}

int filling_object(FILE *f, object *result) {
  int status = SUCCESS;
  char buffer[BUFF_SIZE] = {0};
  int is_first = 1;
  fseek(f, 0, SEEK_SET);
  int i = 0, j = 0;
  double *vertex = result->vertex_arr;
  while (fgets(buffer, BUFF_SIZE, f) && !status) {
    if (buffer[0] == 'v' && buffer[1] == ' ') {
      sscanf(buffer + 2, "%lf%lf%lf", &vertex[i], &vertex[i + 1],
             &vertex[i + 2]);
      maxmin(result, vertex[i], vertex[i + 1], vertex[i + 2], is_first);
      is_first = 0;
      i += 3;
    } else if (buffer[0] == 'f' && buffer[1] == ' ') {
      status = filling_facets(buffer, result, &j, i / 3);
    }
  }
  centerObj(result);
  return status;
}

int filling_facets(char *buffer, object *result, int *current_index,
                   int currentVertexIndex) {
  int status = SUCCESS;
  unsigned int *facets = result->facets_arr;
  unsigned int first_num = 1;
  int first_value = 0, actual_value = 0;
  char sep[2] = " ";
  char *istr = strtok(buffer, sep);
  int i = *current_index;
  while (istr) {
    if (istr != NULL && (isdigit(*istr) || *istr == '-')) {
      if (first_num) {
        first_value = atoi(istr) - 1;
        if (first_value < 0) first_value = currentVertexIndex + first_value + 1;
        if (first_value < 0 ||
            (unsigned int)first_value >= result->vertex_count)
          status = FAIL;
        facets[i] = first_value;
        i++;
        first_num = 0;
      } else {
        actual_value = atoi(istr) - 1;
        if (actual_value < 0)
          actual_value = currentVertexIndex + actual_value + 1;
        if (actual_value < 0 ||
            (unsigned int)actual_value >= result->vertex_count)
          status = FAIL;
        facets[i] = actual_value;
        i++;
        facets[i] = actual_value;
        i++;
      }
    }
    istr = strtok(NULL, sep);
  }
  facets[i] = first_value;
  i++;
  *current_index = i;
  return status;
}

void maxmin(object *result, double x, double y, double z, int first_line) {
  if (first_line) {
    result->scale.x_min = x;
    result->scale.y_min = y;
    result->scale.z_min = z;

    result->scale.x_max = x;
    result->scale.y_max = y;
    result->scale.z_max = z;
  } else {
    compare(&result->scale.x_max, &result->scale.x_min, x);
    compare(&result->scale.y_max, &result->scale.y_min, y);
    compare(&result->scale.z_max, &result->scale.z_min, z);
  }
}

void compare(double *max, double *min, double value) {
  if (*max < value) *max = value;
  if (*min > value) *min = value;
}
