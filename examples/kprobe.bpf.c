#include <linux/bpf.h> // 要在前边
#include <linux/limits.h>
#include <stddef.h>

#include "bpf_helpers.h"

typedef unsigned long long pid_t;

char LICENSE[] SEC("license") = "Dual BSD/GPL";

struct data_t {
    pid_t pid;
    char comm[NAME_MAX];
};

SEC("kprobe/__x64_sys_write")
int kprobe_write(struct pt_regs *ctx, int fd, const void *buf, size_t count) {
    struct data_t data = {};
    data.pid = bpf_get_current_pid_tgid() >> 32;
    bpf_get_current_comm(&data.comm, sizeof(data.comm));
    bpf_printk("pid=%d, name=%s. write data\n ", data.pid, data.comm);
    return 0;
}

// cat /proc/kallsyms
// 但需要注意的，并不是所有的内核函数都可以选作 hook 点，inline 函数无法被 hook，static 函数也有可能被优化掉；
// 如果想知道究竟有哪些函数可以选做 hook 点，在 Linux 机器上，可以通过less /proc/kallsyms查看。