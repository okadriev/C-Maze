#ifndef GROT_H
#define GROT_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>

#define GROT_X 50
#define GROT_Y 50
#define MIN_LIMIT 0
#define MAX_LIMIT 7
#define MIN_CHANCE 1
#define MAX_CHANCE 10
#define FILE1 "cave/cave1.txt"
#define FILE2 "cave/cave2.txt"
#define FILE3 "cave/cave3.txt"

typedef struct Grot_struct {
  int grotto[GROT_Y][GROT_X];
  int row;
  int col;
  int birth;
  int death;
  int chance;
} Grot;

void grot();
void generate_grot(Grot* grot);
void life_grot(Grot* grot);
int count_life(Grot* grot, int i, int j);
int compare(int grotto[GROT_Y][GROT_X]);

void user_input(Grot* grot);
int choose_mode(int* n);
void chance_for_life(int* chance);
void print_step_by_step(Grot* grot);
void print_auto(Grot* grot, int n);
void print_grot(Grot* grot);
void read_grot(Grot* grot, char* file_name);
void choose_cave(int* cave, char* filename);

#endif