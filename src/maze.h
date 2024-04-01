#ifndef A1_MAZE_1_MAZE_H
#define A1_MAZE_1_MAZE_H

#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <time.h>

#define MAZE_X 10  // delete me
#define MAZE_Y 10  // delete me

typedef struct Maze_struct {
  int vertical[51][51];
  int horizontal[51][51];
  int map[101][101];
  int x;
  int y;
} Maze;

void read_from_file(Maze* test, char* filename);
void draw(Maze* test);
void get_map(Maze* test);
void print_map(Maze maze);

#endif