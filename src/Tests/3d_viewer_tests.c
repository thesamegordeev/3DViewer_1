#include "3d_viewer_tests.h"

#include <stdio.h>

#include "arrays_for_tests.h"

START_TEST(file_open_fail) {
  char *file_name = "sadflasdf";
  FILE *f = NULL;
  int status = open_file(file_name, &f);
  ck_assert_int_eq(FAIL, status);
  ck_assert_ptr_eq(f, NULL);
}
END_TEST

START_TEST(file_open_ok) {
  char *file_name = "obj_files/cubecarcas.obj";
  FILE *f = NULL;
  int status = open_file(file_name, &f);
  ck_assert_int_eq(SUCCESS, status);
  ck_assert_ptr_ne(f, NULL);
  fclose(f);
}
END_TEST

START_TEST(counters) {
  char *file_name = "obj_files/cubecarcas.obj";
  FILE *f = NULL;
  object *res = calloc(1, sizeof(object));
  init_object(res);
  int status = open_file(file_name, &f);
  if (!status) status = count_options(f, res);
  ck_assert_int_eq(SUCCESS, status);
  ck_assert_int_eq(res->vertex_count, 72);
  ck_assert_int_eq(res->facets_count, 144);
  ck_assert_ptr_ne(f, NULL);
  fclose(f);
  free_object(res);
}
END_TEST

START_TEST(vertexes) {
  char *file_name = "obj_files/cubecarcas.obj";
  FILE *f = NULL;
  object *res = calloc(1, sizeof(object));
  init_object(res);
  int status = open_file(file_name, &f);
  if (!status) status = count_options(f, res);
  status = filling_object(f, res);
  ck_assert_int_eq(SUCCESS, status);
  for (unsigned int i = 0; i < res->vertex_count * 3; i++) {
    ck_assert_double_eq(res->vertex_arr[i], vert[i]);
  }
  fclose(f);
  free_object(res);
}
END_TEST

START_TEST(facets) {
  char *file_name = "obj_files/cubecarcas.obj";
  FILE *f = NULL;
  object *res = calloc(1, sizeof(object));
  init_object(res);
  int status = open_file(file_name, &f);
  if (!status) status = count_options(f, res);
  status = filling_object(f, res);
  ck_assert_int_eq(SUCCESS, status);
  for (unsigned int i = 0; i < res->connections * 2; i++) {
    ck_assert_double_eq(res->facets_arr[i], fct[i]);
  }
  fclose(f);
  free_object(res);
}
END_TEST

START_TEST(move) {
  char *file_name = "obj_files/cubecarcas.obj";
  FILE *f = NULL;
  object *res = calloc(1, sizeof(object));
  int status = open_file(file_name, &f);
  if (!status) status = count_options(f, res);
  status = filling_object(f, res);

  double x = 1.32;
  double y = 1.4563;
  double z = 1.134;
  moveX(x, res);
  moveY(y, res);
  moveZ(z, res);
  ck_assert_int_eq(SUCCESS, status);
  for (unsigned int i = 0; i < res->vertex_count * 3 - 3; i += 3) {
    ck_assert_double_eq(res->vertex_arr[i], vert[i] + x);
    ck_assert_double_eq(res->vertex_arr[i + 1], vert[i + 1] + y);
    ck_assert_double_eq(res->vertex_arr[i + 2], vert[i + 2] + z);
  }
  fclose(f);
  free_object(res);
}
END_TEST

START_TEST(rescale) {
  char *file_name = "obj_files/cubecarcas.obj";
  FILE *f = NULL;
  object *res = calloc(1, sizeof(object));
  int status = open_file(file_name, &f);
  if (!status) status = count_options(f, res);
  status = filling_object(f, res);
  initialRescaleObj(res);
  ck_assert_int_eq(SUCCESS, status);
  for (unsigned int i = 0; i < res->vertex_count * 3; i++) {
    ck_assert_double_eq(res->vertex_arr[i], vert_rescale[i]);
  }
  fclose(f);
  free_object(res);
}
END_TEST

START_TEST(rotateX_test) {
  char *file_name = "obj_files/cubecarcas.obj";
  FILE *f = NULL;
  object *res = calloc(1, sizeof(object));
  double angle = 12.5;
  int status = open_file(file_name, &f);
  if (!status) status = count_options(f, res);
  status = filling_object(f, res);
  rotateX(angle, res);
  ck_assert_int_eq(SUCCESS, status);
  for (unsigned int i = 0; i < res->vertex_count * 3; i++) {
    ck_assert_double_eq_tol(res->vertex_arr[i], vert_rotX[i], 1e-6);
  }
  fclose(f);
  free_object(res);
}
END_TEST

START_TEST(rotateY_test) {
  char *file_name = "obj_files/cubecarcas.obj";
  FILE *f = NULL;
  object *res = calloc(1, sizeof(object));
  double angle = 12.5;
  int status = open_file(file_name, &f);
  if (!status) status = count_options(f, res);
  status = filling_object(f, res);
  rotateY(angle, res);
  ck_assert_int_eq(SUCCESS, status);
  for (unsigned int i = 0; i < res->vertex_count * 3; i++) {
    ck_assert_double_eq_tol(res->vertex_arr[i], vert_rotY[i], 1e-6);
  }
  fclose(f);
  free_object(res);
}
END_TEST

START_TEST(rotateZ_test) {
  char *file_name = "obj_files/cubecarcas.obj";
  FILE *f = NULL;
  object *res = calloc(1, sizeof(object));
  double angle = 12.5;
  int status = open_file(file_name, &f);
  if (!status) status = count_options(f, res);
  status = filling_object(f, res);
  rotateZ(angle, res);
  ck_assert_int_eq(SUCCESS, status);
  for (unsigned int i = 0; i < res->vertex_count * 3; i++) {
    ck_assert_double_eq_tol(res->vertex_arr[i], vert_rotZ[i], 1e-6);
  }
  fclose(f);
  free_object(res);
}
END_TEST

Suite *s21_common_suite() {
  Suite *test;
  TCase *tc_file, *tc_counters, *tc_parse, *tc_affine;
  // TCase *tc_file_operations;

  test = suite_create("3D_Viewer_test");

  tc_file = tcase_create("file");
  tcase_add_test(tc_file, file_open_fail);
  tcase_add_test(tc_file, file_open_ok);

  tc_counters = tcase_create("counters");
  tcase_add_test(tc_counters, counters);

  tc_parse = tcase_create("vertexes and facets");
  tcase_add_test(tc_parse, vertexes);
  tcase_add_test(tc_parse, facets);

  tc_affine = tcase_create("affine");
  tcase_add_test(tc_affine, move);
  tcase_add_test(tc_affine, rescale);
  tcase_add_test(tc_affine, rotateX_test);
  tcase_add_test(tc_affine, rotateY_test);
  tcase_add_test(tc_affine, rotateZ_test);

  suite_add_tcase(test, tc_file);
  suite_add_tcase(test, tc_counters);
  suite_add_tcase(test, tc_parse);
  suite_add_tcase(test, tc_affine);

  return test;
}

int main() {
  SRunner *runner;
  Suite *list[] = {s21_common_suite()};

  int tests_count = sizeof(list) / sizeof(list[0]);
  int failed = 0;

  runner = srunner_create(list[0]);
  for (int i = 1; i < tests_count; i++) srunner_add_suite(runner, list[i]);

  srunner_run_all(runner, CK_NORMAL);
  failed = srunner_ntests_failed(runner);
  srunner_free(runner);
  printf("\nFAILED TESTS ARE: %d \n\n", failed);

  return (!failed) ? EXIT_SUCCESS : EXIT_FAILURE;
}
