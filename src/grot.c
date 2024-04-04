#include "grot.h"

// ToDo добавить fopen для чтения из файла

void user_input(Grot* grot) {
  while (grot->birth < MIN_LIMIT || grot->birth > MAX_LIMIT) {
    printf("Enter the limit of life (0-7): \n");
    scanf("%d", &grot->birth);

    if (grot->birth < MIN_LIMIT || grot->birth > MAX_LIMIT)
      printf("Incorrect input\n");
  }
  while (grot->death < MIN_LIMIT || grot->death > MAX_LIMIT) {
    printf("Enter the limit of death (0-7): \n");
    scanf("%d", &grot->death);

    if (grot->death < MIN_LIMIT || grot->death > MAX_LIMIT)
      printf("Incorrect input\n");
  }
  while (grot->chance < MIN_CHANCE || grot->chance > MAX_CHANCE) {
    printf("Enter the chance of life (1-10): \n");
    scanf("%d", &grot->chance);

    if (grot->chance < MIN_CHANCE || grot->chance > MAX_CHANCE)
      printf("Incorrect input\n");
  }
}

int choose_mode(int* n) {
  int mode = 0;
  while (mode < 1 || mode > 2) {
    printf("Choose mode: \n");
    printf("1. step by step work \n");
    printf("2. automatic work \n");
    scanf("%d", &mode);
    if (mode < 1 || mode > 2) {
      printf("Incorrect input\n");
    }
  }
  if (mode == 2) {
    while (*n <= 0) {
      printf("Enter the rendering time for each iteration in seconds:\n");
      scanf("%d", n);
      if (*n <= 0) {
        printf("Incorrect input\n");
      }
    }
  }

  return mode;
}

void print_step_by_step(Grot* grot) {
  int iteration = 1;
  while (iteration == 1) {
    print_grot(grot);
    life_grot(grot);
    printf("To continue enter 1 or another number to exit:\n");
    scanf("%d", &iteration);
  }
}

void print_auto(Grot* grot, int n) {
  while (!compare(grot->grotto)) {
    print_grot(grot);
    life_grot(grot);
    sleep(n);
  }
}

void print_grot(Grot* grot) {
  for (int i = 0; i < G_MAZE_Y; i++) {
    for (int j = 0; j < G_MAZE_X; j++) {
      printf(grot->grotto[i][j] ? "\033[47m  \033[0m" : "  ");
    }
    printf("\n");
  }
}
void grot() {
  Grot grot = {0};
  grot.birth = -1;
  grot.death = -1;
  grot.chance = -1;
  user_input(&grot);
  generate_grot(&grot);
  int n = 0;
  int mode = choose_mode(&n);
  if (mode == 1)
    print_step_by_step(&grot);
  else if (mode == 2)
    print_auto(&grot, n);
}

// int main() { grot(); } // ToDo Удалить