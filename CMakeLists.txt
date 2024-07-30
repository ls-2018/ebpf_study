cmake_minimum_required(VERSION 3.27.7)
project(ebpf_study C)

set(CMAKE_C_STANDARD 11)

include_directories(
        /media/psf/ebpf_study/include
        /usr/include
        /usr/local/src/workspace/include
        /usr/include/aarch64-linux-gnu
        # /usr/local/src/workspace/include/bpf
        # /usr/local/src/workspace/include/vmlinux
)

# 无用
add_library(
        test
        case/01-sys_enter_write/test.bpf.c
        case/02-kprobe/test.bpf.c
        case/03-xdp/test.bpf.c
        case/04-go/tc/tc_write.bpf.c
        case/04-go/xdp/xdp.bpf.c
        case/04-go/sys/sys.bpf.c
)

add_executable(ebpf_study
        main.c
)
