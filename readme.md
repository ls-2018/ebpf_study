```
[root@aps04 ~]# perf list tracepoint |grep sys_enter_write
syscalls:sys_enter_write                           [Tracepoint event]
syscalls:sys_enter_writev                          [Tracepoint event]



root@ubuntu-linux-22-04-desktop:~# cat /sys/kernel/debug/tracing/available_filter_functions | wc -l
60765



包含了系统运行 linux 内核源代码中使用的所有类型的定义， bpf 的可能没有
bpftool btf dump file /sys/kernel/btf/vmlinux format c > include/vmlinux.h


```
- uprobe            挂载在函数进入之前,可以获取到函数的参数值
- uretprobe         挂载在函数返回值之后,可以获取到函数的返回值
- nm /bin/bash   查看一个程序的符号表

xdp 入流量
tc  入出流量
选择网卡 -> chaugnjian duilie  qdisc -> 创建分类class(用于设定宽带级别) -> 创建filter,把流量进行分类,并将包分发到前面定义的class中


# 使用docker0创建一个队列
tc qdisc add dev docker clsact

tc filter add dev docker0 ingress bpf direct-action obj dockertcxdp_bpfel_x86.0 sec.txt

tc filter show dev docker0 ingress 

# 清理掉
tc qdisc del dev docker0 clsact

# 静态hook 点
find /sys/kernel/debug/tracing/events-type d




arp :   广播
ip -> mac地址    封装在了以太网报文里

arping -I etho0 192.168.0.3

arp 欺骗，metallb



- bpf_map_lookup_elem
- bpf_map_update_elem
- bpf_map_delete_elem

- bpf_probe_read
- bpf_get_current_pid_tgid



```
struct bpf_map_def SEC("maps") kprobe_map = {
	.type        = BPF_MAP_TYPE_PERCPU_ARRAY, // BPF_MAP_TYPE_ARRAY,BPF_MAP_TYPE_PERF_EVENT_ARRAY
	.key_size    = sizeof(u32),
	.value_size  = sizeof(u64),
	.max_entries = 1,
};




```


- BPF_SOCK_OPS_ACTIVE_ESTABLISHED_CB    如果客户端发起连接请求并完成三次握手后的操作符
- BPF_SOCK_OPS_TCP_LISTEN_CB            套接字进入监听状态时的操作符
- BPF_SOCK_OPS_DATA_ACK_CB              数据被确认
- BPF_SOCK_OPS_STATE_CB                 TCP 状态改变


- BPF_SOCK_OPS_RTT_CB_FLAG
- BPF_SOCK_OPS_STATE_CB_FLAG


