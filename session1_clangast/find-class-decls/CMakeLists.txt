set(LLVM_LINK_COMPONENTS
  Support
  )

add_clang_executable(find-class-decls FindClassDecls.cpp)

target_link_libraries(find-class-decls
  PRIVATE
  clangAST
  clangBasic
  clangFrontend
  clangSerialization
  clangTooling
  )
