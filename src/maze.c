#include "maze.h"

#include "grot.h"

int main() {
  menu();
  return 0;
}

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
}

/**
 * Основной цикл программы с выводом меню
 */
void menu() {
  print_main_menu();
  int state = 0;
  int user_choice;
  Maze maze = {0};
  // ToDo Добавить инициализацию новой/существующей структуры
  int start_x = 0;  // add struct point(x,y)?
  int start_y = MAZE_Y - 1;
  int end_x = MAZE_X - 1;
  int end_y = 0;
  while ((user_choice = get_variant(4)) != 4) {
    state = state * 10 + user_choice;
    switch (state) {
      case 1:
        clear_maze(&maze);
        // ToDo Возможность указания произвольного файла, либо выбора из
        // преддефайнов ?
        read_from_file(&maze, "../data-samples/example_of_maze_1.txt");
        printf("\nPrint labyrinth from file:\n\n");
        get_map(&maze);
        print_map(maze);
        break;
      case 2:
        clear_maze(&maze);
        generate_maze(&maze);
        printf("\nPrint generate labyrinth:\n\n");
        write_to_file(&maze, "../data-samples/test.txt");
        get_map(&maze);
        print_map(maze);
        break;
      case 3:
        grot();
        break;
      case 11:
        // ToDo Задать начальные и конечные точки
        if (find_path(&maze, start_y, start_x, end_y, end_x) == 0) {
          printf("There is no path\n");
          maze.map[start_y][start_x] = 2;
          maze.map[end_y][end_x] = 2;
        } else {
          print_map(maze);
        }
        break;
      case 21:
        // ToDo Удалить дублирование
        if (find_path(&maze, start_y, start_x, end_y, end_x) == 0) {
          printf("There is no path\n");
          maze.map[start_y][start_x] = 2;
          maze.map[end_y][end_x] = 2;
        }
        print_map(maze);
        break;
      default:
        state = 0;
        print_main_menu();
    }
  }
};

/**
 * Печать main menu
 */
void print_main_menu() {
  CLS;
  printf("What do you want to do?\n");
  printf("1. Load maze from file\n");
  printf("2. Generate a maze\n");
  printf("3. Generate cave\n");
  printf("4. Exit\n");
  printf("> ");
}

/**
 * Считываение из консоли ввода пользователя
 * @param count кол-во пунктов меню
 * @return введенное значение
 */
int get_variant(int count) {
  int user_choice;
  char s[256];
  scanf("%s", s);
  while (sscanf(s, "%d", &user_choice) != 1 || user_choice < 1 ||
         user_choice > count) {
    printf("Incorrect input. Try again: ");
    scanf("%s", s);
  }
  return user_choice;
}

/**
 * Запись лабиринта в файл
 * @param maze указатель на структуру лабиринта
 * @param filename имя файла
 */
void write_to_file(const Maze* maze, char* filename) {
  // ToDo Откуда узнать размерность лабиринта для записи в файл ? Текущая
  // реализация некорректна
  FILE* file = fopen(filename, "wt");
  if (file != NULL) {
    fprintf(file, "%d %d\n", maze->y, maze->x);
    for (int i = 0; i < maze->y; i++) {
      for (int j = 0; j < maze->x; j++) {
        putc(maze->vertical[i][j] + 48, file);
        if (j != maze->x - 1) {
          putc(' ', file);  // ToDo по условию}
        }
      }
      putc('\n', file);
    }
    putc('\n', file);
    // ToDo Устранить дублирование кода
    for (int i = 0; i < maze->y; i++) {
      for (int j = 0; j < maze->x; j++) {
        putc(maze->horizontal[i][j] + 48, file);
        if (j != maze->x - 1) {
          putc(' ', file);  // ToDo по условию}
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
void read_from_file(Maze* maze, char* filename) {
  // ToDo Возвращать ошибку в случае сбоя
  FILE* file = fopen(filename, "rt");
  if (file != NULL) {
    int cur = 0;
    int last = 0;
    int flag = 1;
    int i = 0;
    int j = 0;
    // ToDo Обработать ошибку scanf
    fscanf(file, "%d%d\n", &maze->y, &maze->x);
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
  }
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
    // ToDo можно немного оптимизировать добавив ( && !get_path) в условие if
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

void group_swap(int group[][MAZE_X + 1], int target, int swap, int line) {
  for (int i = 0; i < MAZE_X; i++) {
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
  maze->y = MAZE_Y;
  maze->x = MAZE_X;
  int group[MAZE_Y + 1][MAZE_X + 1] = {0};
  int group_count = 1;

  for (int y = 0; y < MAZE_Y; y++) {
    for (int x = 0; x < MAZE_X; x++) {
      if (!group[y][x]) group[y][x] = group_count++;
    }

    for (int x = 0; x < MAZE_X - 1; x++) {
      if (group[y][x] == group[y][x + 1] || rand() & 1) {
        maze->vertical[y][x] = 1;

      } else {
        group_swap(group, group[y][x], group[y][x + 1], y);
      }
    }

    for (int x = 0; x < MAZE_X; x++) {
      int count = 0;
      for (int i = 0; i < MAZE_X; i++) {
        if (group[y][i] == group[y][x] && !maze->horizontal[y][i]) {
          count++;
        }
      }

      if (count > 1 && rand() & 1) {
        maze->horizontal[y][x] = 1;
      }
    }

    if (y < MAZE_Y - 1) {
      for (int x = 0; x < MAZE_X; x++) {
        if (maze->horizontal[y][x] == 0) {
          group[y + 1][x] = group[y][x];
        }
      }

    } else {
      for (int x = 0; x < MAZE_X - 1; x++) {
        if (group[y][x] != group[y][x + 1]) {
          maze->vertical[y][x] = 0;
          group_swap(group, group[y][x], group[y][x + 1], y);
        }
      }
    }
  }

  for (int i = 0; i < MAZE_X; i++) {
    maze->horizontal[MAZE_Y - 1][i] = 1;
  }

  for (int i = 0; i < MAZE_Y; i++) {
    maze->vertical[i][MAZE_X - 1] = 1;
  }
}