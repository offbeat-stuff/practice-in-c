#include <assert.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

#define i32 int32_t

#define new_list(type) type *
#define list_cap(vec) (vec ? list_cap_unsafe(vec) : 0)
#define list_cap_unsafe(vec) ((i32 *)vec)[-1]
#define list_len(vec) (vec ? list_len_unsafe(vec) : 0)
#define list_len_unsafe(vec) ((i32 *)vec)[-2]

#define list_cap_set(vec, cap)                                                 \
  do {                                                                         \
    i32 req = cap * sizeof(*(vec)) + sizeof(i32) * 2;                          \
    if (vec) {                                                                 \
      i32 *l_pa = &((i32 *)vec)[-2];                                           \
      i32 *l_pb = (i32 *)realloc(l_pa, req);                                   \
      (vec) = (void *)(&l_pb[2]);                                              \
    } else {                                                                   \
      i32 *l_pb = malloc(req);                                                 \
      (vec) = (void *)(&(l_pb)[2]);                                            \
      list_len_unsafe(vec) = 0;                                                \
    }                                                                          \
    assert(vec);                                                               \
    list_cap_unsafe(vec) = cap;                                                \
  } while (0)

#define list_grow(vec)                                                         \
  if (list_cap(vec)) {                                                         \
    i32 cap = list_cap(vec);                                                   \
    list_cap_set(vec, cap * 2);                                                \
  } else {                                                                     \
    list_cap_set(vec, 1);                                                      \
  }

#define list_len_set(vec, len)                                                 \
  while (len > list_cap(vec)) {                                                \
    list_grow(vec);                                                            \
  };                                                                           \
  do {                                                                         \
    list_len_unsafe(vec) = len;                                                \
  } while (0)

#define list_add(vec, data)                                                    \
  do {                                                                         \
    i32 len = list_len(vec);                                                   \
    list_len_set(vec, len + 1);                                                \
    vec[len] = data;                                                           \
  } while (0)

#define debug_list(vec)                                                        \
  do {                                                                         \
    printf("len : %i = %i\n", &list_len_unsafe(vec), list_len(vec));           \
    printf("cap : %i = %i\n", &list_cap_unsafe(vec), list_cap(vec));           \
    for (int i = 0; i < list_len(vec); i++) {                                  \
      printf("%i = %i\n", &vec[i], vec[i]);                                    \
    }                                                                          \
  } while (0)