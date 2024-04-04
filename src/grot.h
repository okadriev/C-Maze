#ifndef GROT_H
#define GROT_H

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>

#define G_MAZE_X 50
#define G_MAZE_Y 50
#define MIN_LIMIT 0
#define MAX_LIMIT 7
#define MIN_CHANCE 1
#define MAX_CHANCE 10

typedef struct Grot_struct {
  int grotto[G_MAZE_Y][G_MAZE_X];
  int birth;
  int death;
  int chance;
} Grot;

void grot();
void generate_grot(Grot* grot);
void life_grot(Grot* grot);
int count_life(Grot* grot, int i, int j);
void user_input(Grot* grot);
int choose_mode(int* n);
void print_step_by_step(Grot* grot);
void print_auto(Grot* grot, int n);
void print_grot(Grot* grot);
int compare(int grotto[G_MAZE_Y][G_MAZE_X]);

#endif