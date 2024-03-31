#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <time.h>

#define MAZE_X 10
#define MAZE_Y 10

typedef struct Maze_struct {
  int group[MAZE_Y + 1][MAZE_X + 1];
  int vertical[MAZE_Y + 1][MAZE_X + 1];
  int horizontal[MAZE_Y + 1][MAZE_X + 1];
  int x;
  int y;
} Maze;

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

int main() {
  srand(time(NULL));
  Maze maze = {0};
  int group = 1;

  for (int y = 0; y < MAZE_Y; y++) {
    for (int x = 0; x < MAZE_X; x++) {
      if (!maze.group[y][x]) maze.group[y][x] = group++;
    }

    for (int x = 0; x < MAZE_X - 1; x++) {
      if (maze.group[y][x] == maze.group[y][x + 1] || rand() & 1) {
        maze.vertical[y][x] = 1;

      } else {
        int group_to_swap = maze.group[y][x + 1];
        int target = maze.group[y][x];

        for (int i = 0; i < MAZE_X; i++) {
          if (maze.group[y][i] == group_to_swap) {
            maze.group[y][i] = target;
          }
        }
      }
    }

    for (int x = 0; x < MAZE_X; x++) {
      int count = 0;
      for (int i = 0; i < MAZE_X; i++) {
        if ((maze.group[y][i] == maze.group[y][x]) && (i != x)) {
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
          maze.group[y + 1][x] = maze.group[y][x];
        }
      }

    } else {
      for (int x = 0; x < MAZE_X - 1; x++) {
        if (maze.group[y][x] != maze.group[y][x + 1]) {
          maze.vertical[y][x] = 0;

          int group_to_swap = maze.group[y][x + 1];
          int target = maze.group[y][x];

          for (int i = x; i < MAZE_X; i++) {
            if (maze.group[y][i] == group_to_swap) {
              maze.group[y][i] = target;
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
  draw(&maze);
  printf("\n\n");
  Maze maze2 = {0};
  read_from_file(&maze2, "test_lab.txt");
  draw(&maze2);

  return 0;
}