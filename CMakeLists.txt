cmake_minimum_required(VERSION 3.28)
project(ebpf_study C)

set(CMAKE_C_STANDARD 11)

include_directories(
        /usr/local/src/workspace/include
        /usr/local/src/workspace/include/bpf
)

# 无用
add_library(
        test
        case/01-sys_enter_write/test.bpf.c
)


add_executable(ebpf_study
        main.c
)