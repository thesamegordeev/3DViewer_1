#ifndef SRC_3DVIEWER_BACK_3D_VIEWER_H_
#define SRC_3DVIEWER_BACK_3D_VIEWER_H_
#include <ctype.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/**
 * @brief Код возврата успешно - 0
 */
#define SUCCESS 0

/**
 * @brief Код возврата сбой - 1
 */
#define FAIL 1

/**
 * @brief Размер буфера, выделяемого под строку
 */
#define BUFF_SIZE (16 * 4096)

/**
 * @brief Константа для изменения масштаба
 */
#define defaultScale 0.5

/**
 * @brief Число Пи
 */
#define PI 3.14159265359

/**
 * @brief Структура с координатами для центрирования объекта
 */
typedef struct {
  double x_min;
  double x_max;
  double y_min;
  double y_max;
  double z_min;
  double z_max;
  double x_center;
  double y_center;
  double z_center;
} scale;

/**
 * @brief Структура со всей информацией об объекте.
 * @param vertex_count Количество точек (v-строки)
 * @param facets_count Количество полигонов (f-строки)
 * @param vertex_arr Указатель на массив с координатами всех точек объекта
 * @param facets_arr Указатель на массив с порядком соединения точек
 * @param connections Количество соединений / 2
 * @param scale Структура, содержащая данные о минимальных, максимальных и
 * центральных координатах объекта
 */
typedef struct {
  unsigned int vertex_count;  // Количество вершин
  unsigned int facets_count;  // Количество ребер
  double *vertex_arr;  // Массив координат вершин x1,y1,z1,x2..
  unsigned int *facets_arr;  // Нумерация соединений (f 1 2 3 -> 0 1 1 2 2 0)
  unsigned int connections;  // Суммарное количество соединений в ребрах
  scale scale;
} object;

/**
 * @brief Функция глобально открывает файл .obj
 * @param f_name Указатель на массив с названием файла
 * @param f Созданный указатель на файл, на который будет открыт файл .obj
 * @return 0 - Успешно, 1 - Неудачно
 */
int open_file(char *f_name, FILE **f);

/**
 * @brief Функция выделяет память на указатели facets_arr и vertex_arr структуры
 * object
 * @param result Указатель на структуру объекта с подсчитанными vertex_count и
 * connections
 * @return 0 - Успешно, 1 - Неудачно (Ошибка выделения памяти)
 */
int allocate(object *result);

/**
 * @brief Функция подсчитывает vertex_count, vertex_count и connections, а также
 * вызывает функцию allocate
 * @param f Указатель на открытый файл .obj
 * @param result Указатель на структуру объекта
 * @return 0 - Успешно, 1 - Неудачно
 */
int count_options(FILE *f, object *result);

/**
 * @brief Функция очищает память, выделенную на элементы структуры facets_arr и
 * vertex_arr
 * @param result Указатель на структуру объекта
 */
void free_object(object *result);

/**
 * @brief Функция подсчитывает количество соединений, записывает в connections в
 * структуре объекта
 * @param buffer Указатель на массив, содержащий номера точек для соединения
 * @return 0 - Успешно, 1 - Неудачно
 */
int amount_connections(char *buffer);

/**
 * @brief Функция инциализирует структуру объекта
 * @param result Инициализируемая структура объекта
 */
void init_object(object *result);

/**
 * @brief Функция заполняет vertex_arr, facets_arr и scale
 * @param f Файл .obj
 * @param result Заполняемая структура объекта
 * @return 0 - Успешно, 1 - Неудачно
 */
int filling_object(FILE *f, object *result);

/**
 * @brief Функция заполняет scale структуры объекта
 * @param result Указатель на структуру объекта
 * @param x Координата x рассматриваемой точки
 * @param y Координата y рассматриваемой точки
 * @param z Координата z рассматриваемой точки
 * @param first_line Флаг, сигнализирующий о передаче первой строки. В этом
 * случае координаты точки будут записаны во все поля структуры scale
 */
void maxmin(object *result, double x, double y, double z, int first_line);

/**
 * @brief Функция сравнивает актуальное значение с минимальным и максимальным
 * значением в структуре scale, обновляя значение этих переменных, если
 * актуальное значение подходит под условие сравнения
 * @param max Указатель на переменную максимального значения
 * @param min Указатель на переменную минимального значения
 * @param value Актуальное (рассматриваемое) значение
 */
void compare(double *max, double *min, double value);

/**
 * @brief Функция парсит f-строку в массив facets_arr структуры объекта
 * @param buffer Массив с f-строкой
 * @param result Структура объекта
 * @param current_index Текущий индекс для массива вершин facets_arr
 * @param currentVertexIndex Текущий индекс вершины в файле
 * @return 0 - Успешно, 1 - Неудачно
 */
int filling_facets(char *buffer, object *result, int *current_index,
                   int currentVertexIndex);

/**
 * @brief Функция умножает координаты фигуры для визуального увеличения
 * @param scaleValue Значение измненеия размера фигуры (множитель)
 * @param obj Структура объекта
 */
void rescaleObj(double scaleValue, object *obj);

/**
 * @brief Функция приводит все координаты фигуры к 0 <= X,Y,Z <= 0.5
 * @param obj Структура объекта
 */
void initialRescaleObj(object *obj);

/**
 * @brief Функция определяет, в каком направлении фигура наиболее вытянута
 * @param obj Структура объекта
 * @return Наибольшее расстояние между крайними точками
 */
double maxWidth(object *obj);

/**
 * @brief Функция смещает объект по оси X
 * @param xVal Значение смещения по оси X
 * @param obj Структура объекта
 */
void moveX(double xVal, object *obj);

/**
 * @brief Функция смещает объект по оси Y
 * @param yVal Значение смещения по оси Y
 * @param obj Структура объекта
 */
void moveY(double yVal, object *obj);

/**
 * @brief Функция смещает объект по оси Z
 * @param zVal Значение смещения по оси Z
 * @param obj Структура объекта
 */
void moveZ(double zVal, object *obj);

/**
 * @brief Функция вращает объект вокруг оси X
 * @param angle Угол вращения вокруг оси X
 * @param obj Структура объекта
 */
void rotateX(double angle, object *obj);

/**
 * @brief Функция вращает объект вокруг оси Y
 * @param angle Угол вращения вокруг оси Y
 * @param obj Структура объекта
 */
void rotateY(double angle, object *obj);

/**
 * @brief Функция вращает объект вокруг оси Z
 * @param angle Угол вращения вокруг оси Z
 * @param obj Структура объекта
 */
void rotateZ(double angle, object *obj);

/**
 * @brief Функция устанавливает объект по центру виджета
 * @param obj Структура объекта
 */
void centerObj(object *obj);

/**
 * @brief Вспомогательная функция для функции centerObj
 * @param minVal Указатель на минимальное значение координаты структуры объекта
 * @param maxVal Указатель на максимальное значение координаты структуры объекта
 * @return Центр относительно крайних координат
 */
double centerAxis(double *minVal, double *maxVal);

#endif  // SRC_3DVIEWER_BACK_3D_VIEWER_H_
