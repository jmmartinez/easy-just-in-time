// RUN: %clang %cflags %include_flags %ld_flags %s -Xclang -load -Xclang %lib_pass -o %t
// RUN: %t > %t.out
// RUN: %FileCheck %s < %t.out

#include <easy/c/jit.h>
#include <stdio.h>

int add (int a, int b) {
  return a+b;
}

static void register_add_args(struct easy_context* C, va_list args) {
  // bind (_1, 1)
  easy_context_set_parameter_index(C, 0);
  easy_context_set_parameter_int(C, va_arg(args, int));
}

int main() {
  struct easy_function* inc_wrapper = easy_jit(add, register_add_args, 1, 1);
  int (*inc)(int) = easy_get_function(inc_wrapper);

  // CHECK: inc(4) is 5
  // CHECK: inc(5) is 6
  // CHECK: inc(6) is 7
  // CHECK: inc(7) is 8
  for(int v = 4; v != 8; ++v)
    printf("inc(%d) is %d\n", v, (**inc)(v));

  easy_free(inc_wrapper);

  return 0;
}
