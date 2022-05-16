#include "list.h"
#include <stdarg.h>

i32 *list_add_list(i32 *vec, int argc, ...) {
  i32 *res = vec;
  va_list ap;
  va_start(ap, argc);
  for (int i = 0; i < argc; i++) {
    list_add(res, va_arg(ap, i32));
    debug_list(res);
    printf("-+-----------\n");
  }
  va_end(ap);
  return res;
}

int main(int argc, char **argv) {
  new_list(i32) arr = NULL;
  arr = list_add_list(arr, 5, 2, 5, 2, 5, 5);
  debug_list(arr);
  return 0;
}