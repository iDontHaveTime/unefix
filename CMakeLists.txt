cmake_minimum_required(VERSION 3.10.0)
project(unefix VERSION 0.1.0 LANGUAGES C CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

set(CMAKE_CXX_COMPILER clang++)
set(CMAKE_C_COMPILER clang)

file(GLOB_RECURSE LIB_SOURCES "lib/*.cpp")

add_library(unefix OBJECT ${LIB_SOURCES})

target_compile_options(unefix PRIVATE
    --target=x86_64-windows-gnu
    -Wall -Wextra
    -ffreestanding -nostdlib -nostdinc
    -fno-exceptions -fno-threadsafe-statics
    -ffunction-sections -fdata-sections
    -mno-red-zone -mcmodel=kernel
    -fno-stack-protector -fno-stack-check -fshort-wchar
)

target_include_directories(unefix PUBLIC "include")

add_library(unefix_test_obj OBJECT test/test.cpp)

target_compile_options(unefix_test_obj PRIVATE
    --target=x86_64-windows-gnu
    -fno-stack-protector -fno-stack-check -fshort-wchar -mno-red-zone
    -ffreestanding -nostdlib -nostdinc -Wall -Wextra -fno-exceptions
)

target_include_directories(unefix_test_obj PUBLIC "include")