#include "grot.h"

void generate_grot(Grot* grot) {
  srand(time(NULL));

  for (int i = 0; i < GROT_Y; i++)
    for (int j = 0; j < GROT_X; j++)
      grot->grotto[i][j] = ((rand() % 10) > grot->chance) ? 1 : 0;
}

void life_grot(Grot* grot) {
  int cnt_life = 0;

  for (int i = 0; i < GROT_Y; i++) {
    for (int j = 0; j < GROT_X; j++) {
      cnt_life = count_life(grot, i, j);

      if (grot->grotto[i][j] && cnt_life < grot->death)
        grot->grotto[i][j] = 0;
      else if (!grot->grotto[i][j] && cnt_life > grot->birth)
        grot->grotto[i][j] = 1;
    }
  }
}

int count_life(Grot* grot, int i, int j) {
  int cnt_life = 0;

  for (int k = j - 1; k <= j + 1; k++) {
    int rule = (k >= 0 && k <= GROT_X - 1);

    if (!i) cnt_life++;
    if (!j) cnt_life++;
    if (i == GROT_Y - 1) cnt_life++;
    if (j == GROT_X - 1) cnt_life++;

    if (i > 0 && rule && grot->grotto[i - 1][k]) cnt_life++;
    if (k != j && rule && grot->grotto[i][k]) cnt_life++;
    if (i < GROT_Y - 2 && rule && grot->grotto[i + 1][k]) cnt_life++;
  }

  return cnt_life;
}

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
