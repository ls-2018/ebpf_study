cmake_minimum_required(VERSION 3.27.7)
project(ebpf_study C)

set(CMAKE_C_STANDARD 11)

include_directories(
        include
)

# 无用
add_library(
        test
        examples/_cgroup_skb/cgroup_skb.c
        examples/_tracepoint_in_c/tracepoint.c
        examples/_tcprtt/tcprtt.c
        examples/_kprobe/kprobe.c
        examples/_tcx/tcx.c
        examples/_kprobepin/kprobe_pin.c
        examples/_cgroup_skb/cgroup_skb.c
        examples/01-sys_enter_write/test.bpf.c
        examples/_uretprobe/uretprobe.c
        examples/04-go/xdp/xdp.bpf.c
        examples/04-go/sys/sys.bpf.c
        examples/04-go/tc/tc_write.bpf.c
        examples/03-xdp/test.bpf.c
        examples/_tcprtt_sockops/tcprtt_sockops.c
        examples/_xdp/xdp.c
        examples/_kprobe_percpu/kprobe_percpu.c
        examples/02-kprobe/test.bpf.c
        examples/_ringbuffer/ringbuffer.c
        examples/_fentry/fentry.c
        examples/data/hello.c
)
