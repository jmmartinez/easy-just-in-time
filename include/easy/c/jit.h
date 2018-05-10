#ifndef JIT_C
#define JIT_C

#include <easy/attributes.h>
#include <stdarg.h>
#include <stdint.h>
#include <stddef.h>

#ifdef __cplusplus
extern "C" {
#endif

// dummy types
struct easy_function {};
struct easy_context {};

// function to jit some code 
struct easy_function* EASY_JIT_COMPILER_INTERFACE easy_jit(void*, void(*)(struct easy_context*, va_list), int nargs, ...);

// access the function pointer
void* easy_get_function(struct easy_function*);

// handle the parameters
void easy_context_set_parameter_index(struct easy_context*, unsigned);
void easy_context_set_parameter_int(struct easy_context*, int64_t);
void easy_context_set_parameter_float(struct easy_context*, double);
void easy_context_set_parameter_pointer(struct easy_context*, void const*);
void easy_context_set_parameter_struct(struct easy_context*, char const*, size_t);

// free the allocated resources
void easy_free(struct easy_function*);

#ifdef __cplusplus
}
#endif

#endif
