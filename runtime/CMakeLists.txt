llvm_map_components_to_libnames(RUNTIME_LLVM_LIBS core codegen interpreter support mcjit native executionengine passes objcarcopts)

add_library(EasyJitRuntime SHARED
  BitcodeTracker.cpp
  Context.cpp
  Function.cpp
  InitNativeTarget.cpp
  Utils.cpp
  CApi.cpp
  pass/ContextAnalysis.cpp
  pass/DevirtualizeConstant.cpp
  pass/InlineParameters.cpp
)

target_link_libraries(EasyJitRuntime ${RUNTIME_LLVM_LIBS})

set(EASY_JIT_RUNTIME ${CMAKE_LIBRARY_OUTPUT_DIRECTORY}/libEasyJitRuntime${CMAKE_SHARED_LIBRARY_SUFFIX} PARENT_SCOPE)

install(TARGETS EasyJitRuntime 
        LIBRARY DESTINATION lib)
