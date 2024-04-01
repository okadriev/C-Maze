#ifndef A1_MAZE_1_MAZE_H
#define A1_MAZE_1_MAZE_H

#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <time.h>

#define MAZE_X 10
#define MAZE_Y 10

typedef struct Maze_struct {
  int vertical[MAZE_Y + 1][MAZE_X + 1];
  int horizontal[MAZE_Y + 1][MAZE_X + 1];
  int map[MAZE_Y * 2 + 1][MAZE_X * 2 + 1];
  int x;
  int y;
} Maze;

void read_from_file(Maze* test, char* filename);
void draw(Maze* test);
void get_map(Maze* test);
void print_map(Maze maze);


#endif