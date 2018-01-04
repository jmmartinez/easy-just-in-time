add_llvm_loadable_module(EasyJitPass
  RegisterPasses.cpp
  Easy.cpp)

set(EASY_JIT_PASS ${CMAKE_LIBRARY_OUTPUT_DIRECTORY}/EasyJitPass${CMAKE_SHARED_LIBRARY_SUFFIX} PARENT_SCOPE)
