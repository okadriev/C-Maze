#include <stdio.h>

int dist[4][4] = {{0, 10, 15, 20}, 
                  {10, 0, 35, 25}, 
                  {15, 35, 0, 30}, 
                  {20, 25, 30, 0}};

void path(int path_len, int visited[6], int curr_location);

int main() {
  int path_len = 0;
  int visited[6] = {0};

  path(path_len, visited, 1);

  return 0;
}

void path(int path_len, int visited[6], int curr_location) {
  if (curr_location == 4) {
    printf("Длина пути: %3d; Путь:", path_len + dist[visited[3]][0]);
    for (int k = 0; k < 5; k++) {
      printf(" %d", visited[k]);
    }
    printf("\n");

  } else {
    for (int i = 1; i <= 3; i++) {
      int next = 0;

      for (int j = 1; j < curr_location && next == 0; j++) {
        if (visited[j] == i) next = 1;
      }

      if (next == 0) {
        if (visited[curr_location]) {
          path_len -= dist[visited[curr_location - 1]][visited[curr_location]];
        }

        path_len += dist[visited[curr_location - 1]][i];
        visited[curr_location] = i;
        path(path_len, visited, curr_location + 1);
      }
    }
  }

  visited[curr_location] = 0;
}