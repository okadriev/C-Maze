#ifndef A1_MAZE_1_MAZE_H
#define A1_MAZE_1_MAZE_H

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MAZE_X 15
#define MAZE_Y 7
#define MAX_MAZE 51
#define MAX_MAP 101
#define CLS printf("\033[2J")

// ToDo Удалить ?
// typedef struct Point {
//  int x;
//  int y;
//} Point;

typedef struct Maze_struct {
  int vertical[MAX_MAZE][MAX_MAZE];
  int horizontal[MAX_MAZE][MAX_MAZE];
  int map[MAX_MAP][MAX_MAP];
  //  Point start;  // ToDo Удалить ?
  //  Point end;    // ToDo Удалить ?
  int x;
  int y;
} Maze;

void menu();
void print_main_menu();
int get_variant(int count);

void write_to_file(const Maze* maze, char* filename);
void read_from_file(Maze* maze, char* filename);

void clear_maze(Maze* maze);
void generate_maze(Maze* maze);
void get_map(Maze* maze);
void print_map(Maze maze);
int find_path(Maze* maze, int y_1, int x_1, int y_2, int x_2);
void group_swap(int group[][MAZE_X + 1], int target, int swap, int line);

#endif