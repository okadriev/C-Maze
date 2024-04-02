#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>

#define MAZE_X 50
#define MAZE_Y 50
#define MIN_LIMIT 0
#define MAX_LIMIT 7

typedef struct Grot_struct {
  int grotto[MAZE_Y][MAZE_X];
  int berth;
  int death;
  int chance[2];
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
int compare(int grotto[MAZE_Y][MAZE_X]);

void generate_grot(Grot* grot) {
  srand(time(NULL));

  for (int i = 0; i < MAZE_Y; i++) {
    for (int j = 0; j < MAZE_X; j++) {
      grot->grotto[i][j] = rand() & 1;
      if (i == grot->chance[0] && j == grot->chance[1]) {
        grot->grotto[i][j] = 1;
      }
    }
  }
}

void life_grot(Grot* grot) {
  int cnt_life = 0;

  for (int i = 0; i < MAZE_Y; i++) {
    for (int j = 0; j < MAZE_X; j++) {
      cnt_life = count_life(grot, i, j);

      if (grot->grotto[i][j] && cnt_life < grot->death) grot->grotto[i][j] = 0;
      if (!grot->grotto[i][j] && cnt_life > grot->berth) grot->grotto[i][j] = 1;
    }
  }
}

int count_life(Grot* grot, int i, int j) {
  int cnt_life = 0;

  for (int k = j - 1; k <= j + 1; k++) {
    if (i > 0 && grot->grotto[i - 1][k]) cnt_life;
    if (k != j && grot->grotto[i][k]) cnt_life++;
    if (i < MAZE_Y - 1 && grot->grotto[i + 1][k]) cnt_life;
  }

  return cnt_life;
}

void user_input(Grot* grot) {
  while (grot->berth < MIN_LIMIT || grot->berth > MAX_LIMIT) {
    printf("Enter the limit of life (0-7): \n");
    scanf("%d", &grot->berth);

    if (grot->berth < MIN_LIMIT || grot->berth > MAX_LIMIT)
      printf("Incorrect input\n");
  }

  while (grot->death < MIN_LIMIT || grot->death > MAX_LIMIT) {
    printf("Enter the limit of death (0-7): \n");
    scanf("%d", &grot->death);

    if (grot->death < MIN_LIMIT || grot->death > MAX_LIMIT)
      printf("Incorrect input\n");
  }

  printf("Enter the chance of grotto (0-49): \n");
  printf("Enter the x coordinate: \n");
  scanf("%d", &grot->chance[1]);
  printf("Enter the y coordinate: \n");
  scanf("%d", &grot->chance[0]);
}

int choose_mode(int* n) {
  int mode = 0;
  while (mode < 1 || mode > 2) {
    printf("Choose mode: \n");
    printf("1. step by step work \n");
    printf("2. automatic work \n");
    scanf("%d", &mode);

    if (mode < 1 || mode > 2) printf("Incorrect input\n");
  }

  if (mode == 2) {
    while (n <= 0) {
      printf("Enter the rendering time for each iteration in milliseconds:\n");
      scanf("%d", n);

      if (n <= 0) printf("Incorrect input\n");
    }
  }
}

void print_step_by_step(Grot* grot) {
  int iteration = 1;
  while (iteration == 1) {
    while (!compare(grot->grotto)) {
      life_grot(grot);
      print_grot(grot);
    }

    printf("To continue enter 1 or another number to exit:\n");
    scanf("%d", &iteration);
  }
}

void print_auto(Grot* grot, int n) {
  while (!compare(grot->grotto)) {
    life_grot(grot);
    print_grot(grot);
    sleep(n / 1000);
  }
}

void print_grot(Grot* grot) {
  for (int i = 0; i < MAZE_Y; i++) {
    for (int j = 0; j < MAZE_X; j++) {
      printf(grot->grotto[i][j] ? "\033[47m  \033[0m" : "  ");
    }
  }
}

int compare(int grotto[MAZE_Y][MAZE_X]) {
  int res = 1;
  static int temp[MAZE_Y][MAZE_X] = {0};

  for (int i = 0; i < MAZE_Y && res; i++)
    for (int j = 0; j < MAZE_X && res; j++)
      if (grotto[i][j] != temp[i][j]) res = 0;

  for (int i = 0; i < MAZE_Y; i++)
    for (int j = 0; j < MAZE_X; j++) temp[i][j] = grotto[i][j];

  return res;
}

void grot() {
  Grot grot = {0};
  grot.berth = -1;
  grot.death = -1;

  user_input(&grot);
  generate_grot(&grot);

  int n = 0;
  int mode = choose_mode(&n);

  if (mode == 1)
    print_step_by_step(&grot);
  else if (mode == 2)
    print_auto(&grot, n);
}

int main() { grot(); }