#include <linux/bpf.h> // 要在前边
#include <bpf/bpf_helpers.h>

typedef unsigned long long pid_t;

char LICENSE[] SEC("license") = "Dual BSD/GPL";

SEC("tracepoint/syscalls/sys_enter_write")
int handle_tp(void *ctx) {
    pid_t pid = bpf_get_current_pid_tgid() >> 32;
    bpf_printk("bpf triggered from pid %d.\n", pid);
    return 0;
}

// [root@aps04 ~]# perf list tracepoint |grep sys_enter_write
//  syscalls:sys_enter_write                           [Tracepoint event]
//  syscalls:sys_enter_writev                          [Tracepoint event]