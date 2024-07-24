// go:build ignore
#define BPF_NO_GLOBAL_DATA
#include <linux/bpf.h>
#include <bpf/bpf_helpers.h>
#include <bpf/bpf_tracing.h>
#include <linux/limits.h>
typedef unsigned long long pid_t;

int is_eq(char *str1, char *str2) {
    int eq = 1;
    int i;
    for (i = 0; i < sizeof(str1) - 1 && i < sizeof(str2) - 1; i++) {
        if (str1[i] != str2[i]) {
            eq = 0;
            break;
            ;
        }
    }
    return eq;
}

struct data_t {
    pid_t pid;
    char comm[NAME_MAX];
};

int handle_tp(void *ctx) {
    char app_name[] = "testwrite";
    struct data_t data = {};
    data.pid = bpf_get_current_pid_tgid() >> 32;

    bpf_get_current_comm(&data.comm, sizeof(data.comm));
    int eq = is_eq(data.comm, app_name);
    if (eq == 1) {
        bpf_printk("bpf triggered from pid %d.\n", data.pid);
    }
    return 0;
}
