```
[root@aps04 ~]# perf list tracepoint |grep sys_enter_write
syscalls:sys_enter_write                           [Tracepoint event]
syscalls:sys_enter_writev                          [Tracepoint event]



root@ubuntu-linux-22-04-desktop:~# cat /sys/kernel/debug/tracing/available_filter_functions | wc -l
60765



包含了系统运行 linux 内核源代码中使用的所有类型的定义， bpf 的可能没有
bpftool btf dump file /sys/kernel/btf/vmlinux format c > include/vmlinux.h 


```

