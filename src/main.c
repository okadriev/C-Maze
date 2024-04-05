#include "grot.h"
#include "maze.h"

int main() {
  menu();
  return 0;
}

/**
 * Основной цикл программы с выводом меню
 */
void menu() {
  CLS;
  print_main_menu();
  int state = 0;
  int user_choice;
  Maze maze = {0};
  while ((user_choice = get_variant(4)) != 4) {
    state = state * 10 + user_choice;
    if (state == 1) {
      clear_maze(&maze);
      // ToDo Выбор файла для загрузки
      if (!read_from_file(&maze, "../data-samples/example_of_maze_1.txt")) {
        maze.end.y = maze.y - 1;
        maze.end.x = maze.x - 1;
        printf("\nPrint labyrinth from file:\n\n");
        get_map(&maze);
        print_map(maze);
        print_maze_menu();
      } else {
        state = 0;
        print_main_menu();
      }
    } else if (state == 2) {
      clear_maze(&maze);
      get_coord(&maze.y, &maze.x, 0);
      generate_maze(&maze);
      maze.end.y = maze.y - 1;
      maze.end.x = maze.x - 1;
      printf("\nPrint generate labyrinth:\n\n");
      write_to_file(&maze, "../data-samples/test.txt");
      get_map(&maze);
      print_map(maze);
      print_maze_menu();
    } else if (state == 3) {
      grot();
    } else if (state == 11 || state == 21) {
      if (find_path(&maze, maze.start.y, maze.start.x, maze.end.y,
                    maze.end.x) == 0) {
        printf("\nThere is no path\n\n");
        //        maze.map[start_y][start_x] = 2; ToDo Удалить ?
        //        maze.map[end_y][end_x] = 2; ToDo Удалить ?
      } else {
        print_map(maze);
      }
      state = 0;
      print_main_menu();
    } else if (state == 12 || state == 22) {
      get_coord(&maze.start.y, &maze.start.x, 1);
      get_coord(&maze.end.y, &maze.end.x, 2);
      if (find_path(&maze, maze.start.y, maze.start.x, maze.end.y,
                    maze.end.x) == 0) {
        printf("\nThere is no path\n\n");
        //        maze.map[start_y][start_x] = 2; ToDo Удалить ?
        //        maze.map[end_y][end_x] = 2; ToDo Удалить ?
      } else {
        print_map(maze);
      }
      state = 0;
      print_main_menu();
    } else {
      state = 0;
      print_main_menu();
    }
  }
};

/**
 * Печать main menu
 */
void print_main_menu() {
  printf("What do you want to do?\n");
  printf("1. Load maze from file\n");
  printf("2. Generate a random maze\n");
  printf("3. Generate cave\n");
  printf("4. Exit\n");
  printf("> ");
}

void print_maze_menu() {
  printf("What do you want to do?\n");
  printf("1. Find path to default points\n");
  printf("2. Find path your points\n");
  printf("3. Back\n");
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
 * Считывание размерности лабиринта, начальных и конечных точек пути
 * @param y y-координата
 * @param x x-координата
 * @param mode режим: 0 - размерность лабиринта, 1 - начальная точка пути, 2 -
 * конечная точка пути
 */
void get_coord(int* y, int* x, int mode) {
  char s[256];
  if (mode == 0) {
    printf("Enter count rows (y): ");
  } else if (mode == 1) {
    printf("Enter Y-coord of START point: ");
  } else if (mode == 2) {
    printf("Enter Y-coord of END point: ");
  }

  scanf("%s", s);
  while (sscanf(s, "%d", y) != 1 || *y < 0 || *y > MAX_MAZE - 1) {
    printf("Incorrect input. Try again: ");
    scanf("%s", s);
  }

  if (mode == 0) {
    printf("Enter count columns (x): ");
  } else if (mode == 1) {
    printf("Enter X-coord of START point: ");
  } else if (mode == 2) {
    printf("Enter X-coord of END point: ");
  }
  scanf("%s", s);
  while (sscanf(s, "%d", x) != 1 || *x < 0 || *x > MAX_MAZE - 1) {
    printf("Incorrect input. Try again: ");
    scanf("%s", s);
  }
}