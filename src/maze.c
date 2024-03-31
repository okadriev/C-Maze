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
      for (int x = 0; x < MAZE_X - 1; x++) {
        if (maze.horizontal[y][x] == 0) {
          maze.group[y][x + 1] = maze.group[y][x];
        }
      }

    } else {
      for (int x = 0; x < MAZE_X - 1; x++) {
        if (maze.group[y][x] != maze.group[y][x + 1]) {
          maze.horizontal[y][x] = 0;

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

  return 0;
}