#include "maze.h"

/**
 * Инициализация лабиринта
 * @param maze указатель на структуру лабиринта
 */
void clear_maze(Maze* maze) {
  for (int i = 0; i < MAX_MAP; i++) {
    for (int j = 0; j < MAX_MAP; j++) {
      if (i < MAX_MAZE && j < MAX_MAZE) {
        maze->vertical[i][j] = 0;
        maze->horizontal[i][j] = 0;
      }
      maze->map[i][j] = 0;
    }
  }
  maze->x = 0;
  maze->y = 0;
  maze->start.y = 0;
  maze->start.x = 0;
  maze->end.y = 0;
  maze->end.x = 0;
}

/**
 * Запись лабиринта в файл
 * @param maze указатель на структуру лабиринта
 * @param filename имя файла
 */
void write_to_file(const Maze* maze, char* filename) {
  FILE* file = fopen(filename, "wt");
  if (file != NULL) {
    fprintf(file, "%d %d\n", maze->y, maze->x);
    for (int i = 0; i < maze->y; i++) {
      for (int j = 0; j < maze->x; j++) {
        putc(maze->vertical[i][j] + 48, file);
        if (j != maze->x - 1) {
          putc(' ', file);
        }
      }
      putc('\n', file);
    }
    putc('\n', file);
    for (int i = 0; i < maze->y; i++) {
      for (int j = 0; j < maze->x; j++) {
        putc(maze->horizontal[i][j] + 48, file);
        if (j != maze->x - 1) {
          putc(' ', file);
        }
      }
      if (i != maze->y - 1) {
        putc('\n', file);
      }
    }
    fclose(file);
  }
}

/**
 * Чтение лабиринта из файла
 * @param maze указатель на структуру лабиринта
 * @param filename имя файла
 */
int read_from_file(Maze* maze, char* filename) {
  int error = 0;
  FILE* file = fopen(filename, "rt");
  if (file != NULL) {
    int cur = 0;
    int last = 0;
    int flag = 1;
    int i = 0;
    int j = 0;
    if (fscanf(file, "%d%d\n", &maze->y, &maze->x) != 0) {
      while ((cur = fgetc(file)) != EOF) {
        if (cur == '1' || cur == '0') {
          if (flag) {
            maze->vertical[i][j] = cur - 48;
          } else {
            maze->horizontal[i][j] = cur - 48;
          }
          j++;
        } else if (cur == '\n' && last == '\n') {
          flag = 0;
          i = 0;
          j = 0;
        } else if (cur == '\n') {
          i++;
          j = 0;
        }
        last = cur;
      }
      fclose(file);
    } else {
      printf("Incorrect file.\n");
      error = 1;
    }
  } else {
    printf("Bad file.\n");
    error = 1;
  }
  return error;
}

/**
 * Формирование матрицы лабиринта для печати
 * @param maze указатель на структуру лабиринта
 */
void get_map(Maze* maze) {
  for (int i = 0; i < maze->x * 2 + 1; i++) {
    maze->map[0][i] = 1;
  }
  for (int i = 0; i < maze->y * 2 + 1; i++) {
    maze->map[i][0] = 1;
  }
  for (int y = maze->y - 1; y >= 0; y--) {
    for (int x = maze->x - 1; x >= 0; x--) {
      maze->map[y * 2 + 2][x * 2 + 2] =
          maze->horizontal[y][x] || maze->vertical[y][x] ||
          maze->horizontal[y][x + 1] || maze->vertical[y + 1][x];
      maze->map[y * 2 + 2][x * 2 + 1] = maze->horizontal[y][x];
      maze->map[y * 2 + 1][x * 2 + 2] = maze->vertical[y][x];
    }
  }
}

/**
 * Печать лабиринта
 * @param maze указатель на структуру лабиринта
 */
void print_map(Maze maze) {
  CLS;
  printf("    ");
  for (int x = 0; x < maze.x; x++) {
    printf(" %2d ", x);
  }
  printf("\n");

  for (int y = 0; y < maze.y * 2 + 1; y++) {
    printf((y & 1) ? "%2d " : "   ", (y - 1) / 2);

    for (int x = 0; x < maze.x * 2 + 1; x++) {
      int pixel = maze.map[y][x];
      if (pixel == 2) {
        printf("\033[43m  \033[0m");
      } else {
        printf((pixel == 1) ? "\033[47m  \033[0m" : "  ");
      }
    }
    printf("\n");
  }
  printf("\n");
}

/**
 * Поиск пути в лабиринте от начальной и до конечной точки
 * @param maze указатель на структуру лабиринта
 * @param y_1 y-координата начальной точки
 * @param x_1 x-координата начальной точки
 * @param y_2 y-координата конечной точки
 * @param x_2 x-координата конечной точки
 * @return
 */
int find_path(Maze* maze, int y_1, int x_1, int y_2, int x_2) {
  int get_path = 0;
  int x = x_1 * 2 + 1;
  int y = y_1 * 2 + 1;
  maze->map[y][x] = -1;
  if (x_1 != x_2 || y_1 != y_2) {
    if (maze->map[y][x + 1] == 0 && maze->map[y][x + 2] == 0) {
      if (find_path(maze, y_1, x_1 + 1, y_2, x_2)) {
        maze->map[y][x] = 2;
        maze->map[y][x + 1] = 2;
        get_path = 1;
      }
    }
    if (maze->map[y + 1][x] == 0 && maze->map[y + 2][x] == 0) {
      if (find_path(maze, y_1 + 1, x_1, y_2, x_2)) {
        maze->map[y][x] = 2;
        maze->map[y + 1][x] = 2;
        get_path = 1;
      }
    }
    if (maze->map[y][x - 1] == 0 && maze->map[y][x - 2] == 0) {
      if (find_path(maze, y_1, x_1 - 1, y_2, x_2)) {
        maze->map[y][x] = 2;
        maze->map[y][x - 1] = 2;
        get_path = 1;
      }
    }
    if (maze->map[y - 1][x] == 0 && maze->map[y - 2][x] == 0) {
      if (find_path(maze, y_1 - 1, x_1, y_2, x_2)) {
        maze->map[y][x] = 2;
        maze->map[y - 1][x] = 2;
        get_path = 1;
      }
    }
  } else {
    maze->map[y][x] = 2;
    get_path = 1;
  }
  return get_path;
}

/**
 * Замена элементов в строке swap на target
 * @param group массив групп
 * @param target целевая группа
 * @param swap исходная группа
 * @param line порядковый номер строки
 */
void group_swap(int group[][MAX_MAZE], int target, int swap, int line) {
  for (int i = 0; i < MAX_MAZE; i++) {
    if (group[line][i] == swap) {
      group[line][i] = target;
    }
  }
}

/**
 * Генерация идеального лабиринта
 * @param maze указатель на структуру лабиринта
 */
void generate_maze(Maze* maze) {
  srand(time(NULL));  // ToDo запускать один раз в main ?
  maze->y = maze->y;
  maze->x = maze->x;
  int group[MAX_MAZE][MAX_MAZE] = {0};
  int group_count = 1;

  for (int y = 0; y < maze->y; y++) {
    for (int x = 0; x < maze->x; x++) {
      if (!group[y][x]) group[y][x] = group_count++;
    }

    for (int x = 0; x < maze->x - 1; x++) {
      if (group[y][x] == group[y][x + 1] || rand() & 1) {
        maze->vertical[y][x] = 1;

      } else {
        group_swap(group, group[y][x], group[y][x + 1], y);
      }
    }

    for (int x = 0; x < maze->x; x++) {
      int count = 0;
      for (int i = 0; i < maze->x; i++) {
        if (group[y][i] == group[y][x] && !maze->horizontal[y][i]) {
          count++;
        }
      }

      if (count > 1 && rand() & 1) {
        maze->horizontal[y][x] = 1;
      }
    }

    if (y < maze->y - 1) {
      for (int x = 0; x < maze->x; x++) {
        if (maze->horizontal[y][x] == 0) {
          group[y + 1][x] = group[y][x];
        }
      }

    } else {
      for (int x = 0; x < maze->x - 1; x++) {
        if (group[y][x] != group[y][x + 1]) {
          maze->vertical[y][x] = 0;
          group_swap(group, group[y][x], group[y][x + 1], y);
        }
      }
    }
  }

  for (int i = 0; i < maze->x; i++) {
    maze->horizontal[maze->y - 1][i] = 1;
  }

  for (int i = 0; i < maze->y; i++) {
    maze->vertical[i][maze->x - 1] = 1;
  }
}