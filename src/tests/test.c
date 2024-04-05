#include <check.h>

#include "../grot.h"
#include "../maze.h"

Suite *generate_grot_cases(void);
Suite *life_grot_cases(void);
Suite *count_life_cases(void);
Suite *compare_cases(void);
Suite *maze_generate(void);
Suite *maze_find_path(void);

int main(void) {
  int failed = 0;
  int success = 0;
  Suite *maze[] = {generate_grot_cases(),
                   life_grot_cases(),
                   count_life_cases(),
                   compare_cases(),
                   maze_generate(),
                   maze_find_path(),
                   NULL};

  for (int i = 0; maze[i] != NULL; i++) {
    SRunner *sr = srunner_create(maze[i]);
    srunner_set_fork_status(sr, CK_NOFORK);
    srunner_run_all(sr, CK_NORMAL);
    failed += srunner_ntests_failed(sr);
    success += srunner_ntests_run(sr);
    srunner_free(sr);
  }
  printf("\033[41m========= FAILED : %-3d =========\033[0m\n", failed);
  printf("\033[42m\033[30m========= SUCCESS: %-3d =========\033[0m\n", success);
  return failed == 0 ? 0 : 1;
}

START_TEST(generate_grot_1) {
  Grot grot = {0};
  grot.col = 10;
  grot.row = 10;
  grot.chance = 5;
  grot.death = 3;
  grot.birth = 2;
  generate_grot(&grot);
  life_grot(&grot);

  ck_assert(grot.grotto != NULL);
}
END_TEST

START_TEST(life_grot_1) {
  Grot grot = {0};
  grot.grotto[0][0] = 0;
  grot.grotto[0][1] = 1;
  grot.grotto[0][2] = 0;
  grot.grotto[1][0] = 1;
  grot.grotto[1][1] = 1;
  grot.grotto[1][2] = 0;
  grot.grotto[2][0] = 0;
  grot.grotto[2][1] = 1;
  grot.grotto[2][2] = 0;
  grot.birth = 4;
  grot.death = 2;
  Grot check = {0};
  for (int i = 0; i < GROT_Y; i++)
    for (int j = 0; j < GROT_X; j++) check.grotto[i][j] = grot.grotto[i][j];

  life_grot(&grot);

  for (int i = 0; i < GROT_Y; i++)
    for (int j = 0; j < GROT_X; j++)
      ck_assert(check.grotto[i][j] == grot.grotto[i][j]);
}
END_TEST

START_TEST(count_life_1) {
  Grot grot = {0};
  grot.col = 3;
  grot.row = 3;
  grot.grotto[0][0] = 0;
  grot.grotto[0][1] = 1;
  grot.grotto[0][2] = 0;
  grot.grotto[1][0] = 1;
  grot.grotto[1][1] = 1;
  grot.grotto[1][2] = 0;
  grot.grotto[2][0] = 0;
  grot.grotto[2][1] = 1;
  grot.grotto[2][2] = 0;

  ck_assert(count_life(&grot, 0, 0) == 8);
  ck_assert(count_life(&grot, 0, 1) == 5);
  ck_assert(count_life(&grot, 0, 2) == 7);
  ck_assert(count_life(&grot, 1, 0) == 6);
  ck_assert(count_life(&grot, 1, 1) == 3);
  ck_assert(count_life(&grot, 1, 2) == 6);
  ck_assert(count_life(&grot, 2, 0) == 8);
  ck_assert(count_life(&grot, 2, 1) == 5);
  ck_assert(count_life(&grot, 2, 2) == 7);
}
END_TEST

START_TEST(compare_1) {
  Grot grot = {0};
  grot.grotto[0][0] = 0;
  grot.grotto[0][1] = 1;
  grot.grotto[0][2] = 0;
  grot.grotto[1][0] = 1;
  grot.grotto[1][1] = 1;
  grot.grotto[1][2] = 0;
  grot.grotto[2][0] = 0;
  grot.grotto[2][1] = 1;
  grot.grotto[2][2] = 0;

  ck_assert(compare(grot.grotto) == 0);
  ck_assert(compare(grot.grotto) == 1);
}
END_TEST

Suite *generate_grot_cases(void) {
  Suite *c = suite_create("generate_grot_cases");
  TCase *tc = tcase_create("generate_grot_tc");

  tcase_add_test(tc, generate_grot_1);

  suite_add_tcase(c, tc);

  return c;
}

Suite *life_grot_cases(void) {
  Suite *c = suite_create("life_grot_cases");
  TCase *tc = tcase_create("life_grot_tc");

  tcase_add_test(tc, life_grot_1);

  suite_add_tcase(c, tc);

  return c;
}

Suite *count_life_cases(void) {
  Suite *c = suite_create("count_life_cases");
  TCase *tc = tcase_create("count_life_tc");

  tcase_add_test(tc, count_life_1);

  suite_add_tcase(c, tc);

  return c;
}

Suite *compare_cases(void) {
  Suite *c = suite_create("compare_cases");
  TCase *tc = tcase_create("compare_tc");

  tcase_add_test(tc, compare_1);

  suite_add_tcase(c, tc);

  return c;
}

START_TEST(maze_generate_1) {
  Maze maze = {0};
  maze.x = 10;
  maze.y = 10;

  generate_maze(&maze);

  for (int i = 0; i < maze.y; i++) {
    ck_assert(maze.horizontal[maze.y - 1][i] == 1);
    ck_assert(maze.vertical[i][maze.x - 1] == 1);
  }
}
END_TEST

Suite *maze_generate(void) {
  Suite *c = suite_create("maze_generate_cases");
  TCase *tc = tcase_create("maze_generate_1");

  tcase_add_test(tc, maze_generate_1);

  suite_add_tcase(c, tc);

  return c;
}

START_TEST(maze_find_path_1) {
  Maze maze = {0};
  maze.x = 0;
  maze.y = 0;
  print_map(maze);
  clear_maze(&maze);
  int test_array[101] = {
      2,  2,  2,  2,  2,  -1, -1, -1, 2,  2,  2,  2,  2,  2,  2,  2, 2,
      2,  2,  2,  -1, 2,  2,  2,  2,  2,  -1, 2,  2,  2,  -1, 2,  2, 2,
      2,  2,  -1, 2,  2,  2,  -1, -1, -1, 2,  2,  -1, -1, -1, -1, 2, -1,
      -1, -1, -1, -1, -1, -1, 2,  2,  2,  -1, -1, -1, -1, -1, 2,  2, 2,
      2,  2,  -1, -1, -1, -1, -1, 2,  -1, -1, -1, -1, -1, 2,  2,  2, 2,
      2,  -1, -1, -1, -1, 2,  2,  -1, -1, 2,  2,  -1, -1, -1, -1};
  int c = 0;
  read_from_file(&maze, MAZE_FILE1);
  get_map(&maze);

  find_path(&maze, 1, 1, 9, 0);

  for (int i = 0; i < maze.y; i++) {
    for (int j = 0; j < maze.x; j++) {
      ck_assert(maze.map[i * 2 + 1][j * 2 + 1] == test_array[c++]);
    }
  }

  write_to_file(&maze, "../data-samples/test.txt");
}
END_TEST

Suite *maze_find_path(void) {
  Suite *c = suite_create("maze_find_path_cases");
  TCase *tc = tcase_create("maze_find_path_1");

  tcase_add_test(tc, maze_find_path_1);

  suite_add_tcase(c, tc);

  return c;
}
