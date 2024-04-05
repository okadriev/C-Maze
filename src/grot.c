#include "grot.h"
#include "maze.h"

/**
 * Считываение из консоли начальных данных для генерации пещеры
 * @param grot указатель на структуру пещеры
 */
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
}

/**
 * Считываение из консоли ввода пользователя режима отображения пещеры
 * @param n задержка в секундах
 * @return Режим печати: 1 - StepByStep, 2 - Auto
 */
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
    while (*n <= 0) {
      printf("Enter the rendering time for each iteration in seconds:\n");
      scanf("%d", n);

      if (*n <= 0) printf("Incorrect input\n");
    }
  }

  return mode;
}

/**
 * Считываение из консоли ввода пользователя шанс на жизнь для клетки
 * @param chance шанс на жизнь
 */
void chance_for_life(int* chance) {
  while (*chance < MIN_CHANCE || *chance > MAX_CHANCE) {
    printf("Enter the chance of life (1-10): \n");
    scanf("%d", chance);

    if (*chance < MIN_CHANCE || *chance > MAX_CHANCE)
      printf("Incorrect input\n");
  }
}

/**
 * Пошаговая печать пещеры
 * @param grot указатель на структуру пещеры
 */
void print_step_by_step(Grot* grot) {
  int iteration = 1;
  while (iteration == 1) {
    CLS;
    print_grot(grot);
    life_grot(grot);

    printf("To continue enter 1 or another number to exit:\n");
    scanf("%d", &iteration);
  }
}

/**
 * Автоматическая печать пещеры с интервалом
 * @param grot указатель на структуру пещеры
 * @param n интервал обновления
 */
void print_auto(Grot* grot, int n) {
  while (!compare(grot->grotto)) {
    CLS;
    print_grot(grot);
    life_grot(grot);
    sleep(n);
  }
}

/**
 * Печать пещеры
 * @param grot указатель на структуру пещеры
 */
void print_grot(Grot* grot) {
  for (int i = 0; i < GROT_Y; i++) {
    for (int j = 0; j < GROT_X; j++) {
      printf(grot->grotto[i][j] ? "\033[47m  \033[0m" : "  ");
    }
    printf("\n");
  }
  printf("\n");
}

/**
 * Чтение пещеры из файла
 * @param grot указатель на структуру пещеры
 * @param file_name имя файла
 */
void read_grot(Grot* grot, char* file_name) {
  FILE* file = fopen(file_name, "r");
  if (!file)
    printf("File not found\n");

  else {
    fscanf(file, "%d%d\n", &grot->row, &grot->col);

    for (int i = 0; i < GROT_Y; i++)
      for (int j = 0; j < GROT_X; j++)
        if (i < grot->row && j < grot->col)
          fscanf(file, "%d", &grot->grotto[i][j]);
        else
          grot->grotto[i][j] = 1;

    fclose(file);
  }
}
/**
 * Диалог выбора пещеры из файла
 * @param cave режим выбора пещеры
 * @param filename имя файла
 */
void choose_cave(int* cave, char* filename) {
  while (*cave < 1 || *cave > 2) {
    printf("Choose cave: \n");
    printf("1. read from file \n");
    printf("2. random \n");
    scanf("%d", cave);
    if (*cave < 1 || *cave > 2) printf("Incorrect input\n");
  }

  if (*cave == 1) {
    int variant = 0;

    while (variant < 1 || variant > 4) {
      printf("Choose file: \n");
      printf("1. %s\n", FILE1);
      printf("2. %s\n", FILE2);
      printf("3. %s\n", FILE3);
      printf("4. Your file\n");
      scanf("%d", &variant);

      if (variant < 1 || variant > 4) printf("Incorrect input\n");
    }

    if (variant == 4) {
      printf("Enter the name of the file:\n");
      scanf("%s", filename);
    } else if (variant == 1) {
      strcpy(filename, FILE1);
    } else if (variant == 2) {
      strcpy(filename, FILE2);
    } else if (variant == 3) {
      strcpy(filename, FILE3);
    }
  }
}

/**
 * Точка входа в библиотеку grot
 */
void grot() {
  Grot grot = {0};
  grot.birth = -1;
  grot.death = -1;
  grot.chance = -1;
  int cave = -1;
  char filename[100] = {0};

  choose_cave(&cave, filename);
  user_input(&grot);

  if (cave == 1)
    read_grot(&grot, filename);

  else {
    chance_for_life(&grot.chance);
    generate_grot(&grot);
  }

  int n = 0;
  int mode = choose_mode(&n);

  if (mode == 1)
    print_step_by_step(&grot);
  else if (mode == 2)
    print_auto(&grot, n);
}