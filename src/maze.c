#include "maze.h"

void read_from_file(Maze* test, char* filename) {
  FILE* file = fopen(filename, "rt");
  if (file != NULL) {
    int cur = 0;
    int last = 0;
    int flag = 1;
    int i = 0;
    int j = 0;
    // ToDo Обработать ошибку scanf
    fscanf(file, "%d%d\n", &test->y, &test->x);
    while ((cur = fgetc(file)) != EOF) {
      if (cur == '1' || cur == '0') {
        if (flag) {
          test->vertical[i][j] = cur - 48;
        } else {
          test->horizontal[i][j] = cur - 48;
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
  }
}

void draw(Maze* test) {
  for (int i = 0; i < 4 * MAZE_X + 1; i++) {
    printf("#");
  }
  printf("\n");
  for (int i = 0; i < 2 * MAZE_Y; i++) {
    printf("#");
    for (int j = 0; j < 2 * MAZE_X; j++) {
      if (!(i & 1)) {
        if (test->vertical[i / 2][j / 2]) {
          if (!(j & 1)) {
            printf("  ");
          } else {
            printf(" #");
          }

        } else {
          printf("  ");
        }
      } else {
        if (test->horizontal[i / 2][j / 2]) {
          printf("##");
        } else {
          if ((j & 1) && test->vertical[i / 2][j / 2]) {
            printf(" #");
          } else if (test->horizontal[1 + i / 2][j / 2] && (j & 1)) {
            printf(" #");
          } else {
            printf("  ");
          }
        }
      }
    }
    printf("\n");
  }
}

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

void print_map(Maze maze) {
  for (int i = 0; i < maze.y * 2 + 1; i++) {
    for (int j = 0; j < maze.x * 2 + 1; j++) {
      printf((maze.map[i][j]) ? "##" : "  ");
    }
    printf("\n");
  }
}

int main() {
  srand(time(NULL));
  Maze maze = {0};
  maze.y = MAZE_Y;
  maze.x = MAZE_X;
  int group[MAZE_Y + 1][MAZE_X + 1] = {0};
  int group_count = 1;

  for (int y = 0; y < MAZE_Y; y++) {
    for (int x = 0; x < MAZE_X; x++) {
      if (!group[y][x]) group[y][x] = group_count++;
    }

    for (int x = 0; x < MAZE_X - 1; x++) {
      if (group[y][x] == group[y][x + 1] || rand() & 1) {
        maze.vertical[y][x] = 1;

      } else {
        int group_to_swap = group[y][x + 1];
        int target = group[y][x];

        for (int i = 0; i < MAZE_X; i++) {
          if (group[y][i] == group_to_swap) {
            group[y][i] = target;
          }
        }
      }
    }

    for (int x = 0; x < MAZE_X; x++) {
      int count = 0;
      for (int i = 0; i < MAZE_X; i++) {
        if ((group[y][i] == group[y][x]) && (i != x)) {
          if (!maze.horizontal[y][i]) count++;
        }
      }

      if (count > 1 && rand() & 1) {
        maze.horizontal[y][x] = 1;
      }
    }

    if (y < MAZE_Y - 1) {
      for (int x = 0; x < MAZE_X; x++) {
        if (maze.horizontal[y][x] == 0) {
          group[y + 1][x] = group[y][x];
        }
      }

    } else {
      for (int x = 0; x < MAZE_X - 1; x++) {
        if (group[y][x] != group[y][x + 1]) {
          maze.vertical[y][x] = 0;

          int group_to_swap = group[y][x + 1];
          int target = group[y][x];

          for (int i = x; i < MAZE_X; i++) {
            if (group[y][i] == group_to_swap) {
              group[y][i] = target;
            }
          }
        }
      }
    }
  }

  for (int y = 0; y < MAZE_Y; y++) {
    maze.horizontal[MAZE_Y - 1][y] = 1;
    maze.vertical[y][MAZE_X - 1] = 1;
  }

  get_map(&maze);
  print_map(maze);
  printf("\n\n");

  Maze maze2 = {0};
  read_from_file(&maze2, "../data-samples/example_of_maze_1.txt");
  draw(&maze2);

  return 0;
}