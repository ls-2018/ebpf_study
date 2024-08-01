```
[root@aps04 ~]# perf list tracepoint |grep sys_enter_write
syscalls:sys_enter_write                           [Tracepoint event]
syscalls:sys_enter_writev                          [Tracepoint event]



root@ubuntu-linux-22-04-desktop:~# cat /sys/kernel/debug/tracing/available_filter_functions | wc -l
60765



包含了系统运行 linux 内核源代码中使用的所有类型的定义， bpf 的可能没有
bpftool btf dump file /sys/kernel/btf/vmlinux format c > include/vmlinux.h 


```

xdp 入流量
tc  入出流量
选择网卡 -> chaugnjian duilie  qdisc -> 创建分类class(用于设定宽带级别) -> 创建filter,把流量进行分类,并将包分发到前面定义的class中


# 使用docker0创建一个队列
tc qdisc add dev docker clsact

tc filter add dev docker0 ingress bpf direct-action obj dockertcxdp_bpfel_x86.0 sec.txt

tc filter show dev docker0 ingress 

# 清理掉
tc qdisc del dev docker0 clsact
