#ifndef A1_MAZE_1_MAZE_H
#define A1_MAZE_1_MAZE_H

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MAZE_X 15
#define MAZE_Y 7

typedef struct Maze_struct {
  int vertical[51][51];
  int horizontal[51][51];
  int map[101][101];
  int x;
  int y;
} Maze;

void menu();
void print_menu();
int get_variant(int count);

void write_to_file(const Maze* test, char* filename);
void read_from_file(Maze* test, char* filename);

void draw(Maze* test);  // ToDo удалить
void generate_maze(Maze* maze);
void get_map(Maze* maze);
void print_map(Maze maze);
int find_path(Maze* maze, int y_1, int x_1, int y_2, int x_2);
void group_swap(int group[][MAZE_X + 1], int target, int swap, int line);

#endif