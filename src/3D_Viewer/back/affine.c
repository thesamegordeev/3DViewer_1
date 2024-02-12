#include "3d_viewer.h"

void rescaleObj(double scaleValue, object* obj) {
  obj->scale.x_max *= scaleValue;
  obj->scale.x_min *= scaleValue;
  obj->scale.y_max *= scaleValue;
  obj->scale.y_min *= scaleValue;
  obj->scale.z_max *= scaleValue;
  obj->scale.z_min *= scaleValue;
  for (unsigned int i = 0; i < obj->vertex_count * 3; i += 3) {
    obj->vertex_arr[i] *= scaleValue;
    obj->vertex_arr[i + 1] *= scaleValue;
    obj->vertex_arr[i + 2] *= scaleValue;
  }
}

void initialRescaleObj(object* obj) {
  double dynamicScale = (defaultScale - (defaultScale * (-1))) / maxWidth(obj);
  rescaleObj(dynamicScale, obj);
}

double maxWidth(object* obj) {
  double result = 0.0;
  double xDistance = obj->scale.x_max - obj->scale.x_min;
  double yDistance = obj->scale.y_max - obj->scale.y_min;
  double zDistance = obj->scale.z_max - obj->scale.z_min;
  result = xDistance;
  if (yDistance > result) result = yDistance;
  if (zDistance > result) result = zDistance;
  return result;
}

void moveX(double xVal, object* obj) {
  obj->scale.x_max += xVal;
  obj->scale.x_min += xVal;
  for (unsigned int i = 0; i < obj->vertex_count * 3; i += 3) {
    obj->vertex_arr[i] += xVal;
  }
}

void moveY(double yVal, object* obj) {
  obj->scale.y_max += yVal;
  obj->scale.y_min += yVal;
  for (unsigned int i = 0; i < obj->vertex_count * 3; i += 3) {
    obj->vertex_arr[i + 1] += yVal;
  }
}

void moveZ(double zVal, object* obj) {
  obj->scale.z_max += zVal;
  obj->scale.z_min += zVal;
  for (unsigned int i = 0; i < obj->vertex_count * 3; i += 3) {
    obj->vertex_arr[i + 2] += zVal;
  }
}

void rotateX(double angle, object* obj) {
  double radian = angle * PI / 180.0;
  double sin_x = sin(radian);
  double cos_x = cos(radian);
  double y_max = obj->scale.y_max;
  double y_min = obj->scale.y_min;
  double z_max = obj->scale.z_max;
  double z_min = obj->scale.z_min;
  obj->scale.y_max = cos_x * y_max - sin_x * z_max;
  obj->scale.y_min = cos_x * y_min - sin_x * z_min;
  obj->scale.z_max = sin_x * y_max + cos_x * z_max;
  obj->scale.z_min = sin_x * y_min + cos_x * z_min;
  for (unsigned int i = 0; i < obj->vertex_count * 3; i += 3) {
    double y = obj->vertex_arr[i + 1];
    double z = obj->vertex_arr[i + 2];
    obj->vertex_arr[i + 1] = cos_x * y - sin_x * z;
    obj->vertex_arr[i + 2] = sin_x * y + cos_x * z;
  }
}

void rotateY(double angle, object* obj) {
  double radian = angle * PI / 180.0;
  double sin_y = sin(radian);
  double cos_y = cos(radian);
  double x_max = obj->scale.x_max;
  double x_min = obj->scale.x_min;
  double z_max = obj->scale.z_max;
  double z_min = obj->scale.z_min;
  obj->scale.x_max = cos_y * x_max + sin_y * z_max;
  obj->scale.x_min = cos_y * x_min + sin_y * z_min;
  obj->scale.z_max = sin_y * (-x_max) + cos_y * z_max;
  obj->scale.z_min = sin_y * (-x_min) + cos_y * z_min;
  for (unsigned int i = 0; i < obj->vertex_count * 3; i += 3) {
    double x = obj->vertex_arr[i + 0];
    double z = obj->vertex_arr[i + 2];
    obj->vertex_arr[i + 0] = cos_y * x + sin_y * z;
    obj->vertex_arr[i + 2] = sin_y * (-x) + cos_y * z;
  }
}

void rotateZ(double angle, object* obj) {
  double radian = angle * PI / 180.0;
  double sin_z = sin(radian);
  double cos_z = cos(radian);
  double x_max = obj->scale.x_max;
  double x_min = obj->scale.x_min;
  double y_max = obj->scale.y_max;
  double y_min = obj->scale.y_min;
  obj->scale.x_max = cos_z * x_max - sin_z * y_max;
  obj->scale.x_min = cos_z * x_min - sin_z * y_min;
  obj->scale.y_max = sin_z * x_max + cos_z * y_max;
  obj->scale.y_min = sin_z * x_min + cos_z * y_min;
  for (unsigned int i = 0; i < obj->vertex_count * 3; i += 3) {
    double x = obj->vertex_arr[i + 0];
    double y = obj->vertex_arr[i + 1];
    obj->vertex_arr[i + 0] = cos_z * x - sin_z * y;
    obj->vertex_arr[i + 1] = sin_z * x + cos_z * y;
  }
}

void centerObj(object* obj) {
  obj->scale.x_center = centerAxis(&obj->scale.x_min, &obj->scale.x_max);
  obj->scale.y_center = centerAxis(&obj->scale.y_min, &obj->scale.y_max);
  obj->scale.z_center = centerAxis(&obj->scale.z_min, &obj->scale.z_max);
  for (unsigned int i = 0; i < obj->vertex_count * 3; i += 3) {
    obj->vertex_arr[i] -= obj->scale.x_center;
    obj->vertex_arr[i + 1] -= obj->scale.y_center;
    obj->vertex_arr[i + 2] -= obj->scale.z_center;
  }
}

double centerAxis(double* minVal, double* maxVal) {
  double center = *minVal + (*maxVal - *minVal) / 2;
  *minVal -= center;
  *maxVal -= center;
  return center;
}
