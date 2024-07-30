//#include <linux/bpf.h>
//#include <linux/if_ether.h>
//#include <linux/ip.h>
//#include <bpf/bpf_endian.h>
#include "vmlinux.h"
#include <bpf/bpf_helpers.h>
//#include <linux/tcp.h>
#include <linux/limits.h>

struct proc_t {
    __u32 ppid;
    __u32 pid;
    char pname[NAME_MAX];
};

struct {
    __uint(type, BPF_MAP_TYPE_RINGBUF);
    __uint(max_entries, 1 << 20);
} proc_map SEC(".maps");

//SEC("tracepoint/syscalls/sys_enter_execve")

SEC("tracepoint/syscalls/sys_exit_execve")
int handle_tp(void *ctx) {
    struct proc_t *p = NULL;
    p = bpf_ringbuf_reserve(&proc_map, sizeof(*p), 0);
    if (!p) {
        return 0;
    }
    p->pid = bpf_get_current_pid_tgid() >> 32;
    bpf_get_current_comm(&p->pname, sizeof(p->pname));

    struct task_struct *task = (struct task_struct *) bpf_get_current_task();

    if (task) {
        struct task_struct *parent = NULL;
        bpf_probe_read_kernel(&parent, sizeof(*parent), &task->real_parent);
        if (parent) {
            bpf_probe_read_kernel(&p->ppid, sizeof(p->ppid), &parent->pid);
        }
    }

    bpf_ringbuf_submit(p, 0);
    return 0;
}