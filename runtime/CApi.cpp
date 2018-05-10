#include <easy/c/jit.h>
#include <easy/jit.h>
#include <easy/runtime/Context.h>
#include <easy/runtime/Function.h>

using namespace easy;

struct easy_function* easy_jit(void* fun_ptr, void(*register_params)(struct easy_context*, va_list), int nargs, ...) {
  std::unique_ptr<easy::Context> Ctx(new easy::Context());

  va_list args;
  va_start(args, nargs);

  register_params(reinterpret_cast<struct easy_context*>(Ctx.get()), args);

  va_end(args);

  std::unique_ptr<easy::FunctionWrapperBase> Wrapper(
        new FunctionWrapperBase(Function::Compile(fun_ptr, *Ctx)));

  return reinterpret_cast<struct easy_function*>(Wrapper.release());
}

void* easy_get_function(struct easy_function* Wrapper) {
  auto *FWB = reinterpret_cast<FunctionWrapperBase*>(Wrapper);
  return FWB->getRawPointer();
}

void easy_context_set_parameter_index(struct easy_context* C, unsigned idx) {
  auto* Ctx = reinterpret_cast<easy::Context*>(C);
  Ctx->setParameterIndex(idx);
}

void easy_context_set_parameter_int(struct easy_context* C, int64_t val) {
  auto* Ctx = reinterpret_cast<easy::Context*>(C);
  Ctx->setParameterInt(val);
}

void easy_context_set_parameter_float(struct easy_context* C, double val) {
  auto* Ctx = reinterpret_cast<easy::Context*>(C);
  Ctx->setParameterFloat(val);
}

void easy_context_set_parameter_pointer(struct easy_context* C, void const* ptr) {
  auto* Ctx = reinterpret_cast<easy::Context*>(C);
  Ctx->setParameterPointer(ptr);
}

void easy_context_set_parameter_struct(struct easy_context* C, char const* ptr, size_t size) {
  auto* Ctx = reinterpret_cast<easy::Context*>(C);
  Ctx->setParameterStruct(ptr, size);
}

void easy_free(struct easy_function* Wrapper) {
  auto *FWB = reinterpret_cast<FunctionWrapperBase*>(Wrapper);
  delete FWB;
}

