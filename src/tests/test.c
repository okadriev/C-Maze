#include "../maze.h"

Suite *XXXXXX(void);

int main(void) {
  int failed = 0;
  int success = 0;
  Suite *maze[] = {XXXXXX,        NULL};

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

START_TEST(YYYYYY_1) {
}
END_TEST

Suite *XXXXXX(void) {
  Suite *s = suite_create("\033[45m-=XXXXXX=-\033[0m");
  TCase *tc = tcase_create("XXXXXX");
  tcase_add_test(tc, YYYYYY_1);
  suite_add_tcase(s, tc);
  return s;
}