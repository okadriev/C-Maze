#ifndef A1_MAZE_1_MAZE_H
#define A1_MAZE_1_MAZE_H

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MAX_MAZE 51
#define MAX_MAP 101
#define CLS printf("\033[2J")

typedef struct Point {
  int x;
  int y;
} Point;

typedef struct Maze_struct {
  int vertical[MAX_MAZE][MAX_MAZE];
  int horizontal[MAX_MAZE][MAX_MAZE];
  int map[MAX_MAP][MAX_MAP];
  Point start;
  Point end;
  int x;
  int y;
} Maze;

void menu();
void print_main_menu();
void print_maze_menu();
int get_variant(int count);
void get_coord(int* y, int* x, int mode);

void write_to_file(const Maze* maze, char* filename);
int read_from_file(Maze* maze, char* filename);

void clear_maze(Maze* maze);
void generate_maze(Maze* maze);
void get_map(Maze* maze);
void print_map(Maze maze);
int find_path(Maze* maze, int y_1, int x_1, int y_2, int x_2);
void group_swap(int group[][MAX_MAZE], int target, int swap, int line);

#endif