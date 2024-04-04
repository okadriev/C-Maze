#include "grot.h"

void generate_grot(Grot* grot) {
  srand(time(NULL));

  for (int i = 0; i < G_MAZE_Y; i++)
    for (int j = 0; j < G_MAZE_X; j++)
      grot->grotto[i][j] = ((rand() % 10) > grot->chance) ? 1 : 0;
}

void life_grot(Grot* grot) {
  int cnt_life = 0;

  for (int i = 0; i < G_MAZE_Y; i++) {
    for (int j = 0; j < G_MAZE_X; j++) {
      cnt_life = count_life(grot, i, j);

      if (grot->grotto[i][j] && cnt_life < grot->death) grot->grotto[i][j] = 0;
      if (!grot->grotto[i][j] && cnt_life > grot->birth) grot->grotto[i][j] = 1;
    }
  }
}

int count_life(Grot* grot, int i, int j) {
  int cnt_life = 0;

  for (int k = (j > 0 ? j - 1 : j); k <= j + 1; k++) {
    if (!i) cnt_life++;
    if (!j) cnt_life++;
    if (i == G_MAZE_Y - 1) cnt_life++;
    if (j == G_MAZE_X - 1) cnt_life++;
    if (i > 0 && grot->grotto[i - 1][k]) cnt_life++;
    if (k != j && grot->grotto[i][k]) cnt_life++;
    if (i < G_MAZE_Y - 2 && grot->grotto[i + 1][k]) cnt_life++;
  }

  return cnt_life;
}

int compare(int grotto[G_MAZE_Y][G_MAZE_X]) {
  int res = 1;
  static int temp[G_MAZE_Y][G_MAZE_X] = {0};

  for (int i = 0; i < G_MAZE_Y && res; i++)
    for (int j = 0; j < G_MAZE_X && res; j++)
      if (grotto[i][j] != temp[i][j]) res = 0;

  for (int i = 0; i < G_MAZE_Y; i++)
    for (int j = 0; j < G_MAZE_X; j++) temp[i][j] = grotto[i][j];

  return res;
}
