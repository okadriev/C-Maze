#include "grot.h"

/**
 * Генерация пещеры
 * @param grot указатель на структуру пещеры
 */
void generate_grot(Grot* grot) {
  srand(time(NULL));

  for (int i = 0; i < grot->row; i++)
    for (int j = 0; j < grot->col; j++)
      grot->grotto[i][j] = ((rand() % 10) > grot->chance) ? 1 : 0;
}

/**
 * Изменение состояния пещеры
 * @param grot указатель на структуру пещеры
 */
void life_grot(Grot* grot) {
  int cnt_life[GROT_Y][GROT_X] = {0};

  for (int i = 0; i < grot->row; i++)
    for (int j = 0; j < grot->col; j++) cnt_life[i][j] = count_life(grot, i, j);

  for (int i = 0; i < grot->row; i++)
    for (int j = 0; j < grot->col; j++) {
      if (grot->grotto[i][j] && cnt_life[i][j] < grot->death)
        grot->grotto[i][j] = 0;
      else if (!grot->grotto[i][j] && cnt_life[i][j] > grot->birth)
        grot->grotto[i][j] = 1;
    }
}

/**
 * Подсчет живых клеток
 * @param grot указатель на структуру пещеры
 * @param i - строка
 * @param j - столбец
 * @return количество живых клеток
 */
int count_life(Grot* grot, int i, int j) {
  int cnt_life = 0;

  for (int y = i - 1; y <= i + 1; y++)
    for (int x = j - 1; x <= j + 1; x++) {
      if (y < 0 || x < 0 || y >= grot->row || x >= grot->col)
        cnt_life++;
      else if (y == i && x == j)
        continue;
      else if (grot->grotto[y][x])
        cnt_life++;
    }
  return cnt_life;
}

/**
 * Сравнение текущего и прошлого состояния пещеры
 * @param grotto - матрица пещеры
 * @return 1 если состояния равны, 0 если нет
 */
int compare(int grotto[GROT_Y][GROT_X]) {
  int res = 1;
  static int temp[GROT_Y][GROT_X] = {0};

  for (int i = 0; i < GROT_Y && res; i++)
    for (int j = 0; j < GROT_X && res; j++)
      if (grotto[i][j] != temp[i][j]) res = 0;

  for (int i = 0; i < GROT_Y; i++)
    for (int j = 0; j < GROT_X; j++) temp[i][j] = grotto[i][j];

  return res;
}
