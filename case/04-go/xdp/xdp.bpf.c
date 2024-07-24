//go:build ignore
#include <linux/bpf.h>
#include <bpf/bpf_helpers.h>
#include <linux/if_ether.h>
#include <linux/ip.h>

struct ip_data {
    __u32 sip;
    __u32 dip;
};

char LICENSE[] SEC("license") = "Dual BSD/GPL";

struct {
    __uint(type, BPF_MAP_TYPE_RINGBUF);
    __uint(max_entries, 1 << 20);
} ip_map SEC(".maps");

SEC("xdp")
int my_pass(struct xdp_md *ctx) {
    void *_data = (void *)(long)ctx->data;
    void *data_end = (void *)(long)ctx->data_end;
    // int pkt_sz = data_end - _data;
    //
    struct ethhdr *eth = _data;
    if ((void *)eth + sizeof(*eth) > data_end) {
        bpf_printk("invalid ethernet header\n");
        return XDP_DROP;
    }

    struct iphdr *ip = _data + sizeof(*ip);
    if ((void *)ip + sizeof(*ip) > data_end) {
        bpf_printk("invalid ip header\n");
        return XDP_DROP;
    }

    struct ip_data *data = NULL;

    data = bpf_ringbuf_reserve(&ip_map, sizeof(struct ip_data), 0); // 环形缓冲区获取一块内存

    if (data) {
        data->sip = ip->saddr;
        data->dip = ip->daddr;
        bpf_ringbuf_submit(data, 0);
    }
    // unsigned int src_ip = ip->saddr;
    // unsigned char bytes[4];
    // bytes[0] = (src_ip >> 0) & 0xFF;
    // bytes[1] = (src_ip >> 8) & 0xFF;
    // bytes[2] = (src_ip >> 16) & 0xFF;
    // bytes[3] = (src_ip >> 24) & 0xFF;
    //
    // bpf_printk("packet size is %d, protocol is %d, ip is %d.%d.%d.%d\n", pkt_sz, ip->protocol, bytes[0], bytes[1], bytes[2], bytes[3]);
    return XDP_PASS;
}

// XDP_DROP 丢弃网络包--常用DDos防范
// XDP_REDIRECT 数据包转发到不同的网络接口
// XDP_TX 将数据包转发到接收它的同一网络接口
// XDP_PASS 正常流转,流转之前可以做修改
// XDP_ABORTED 丢弃并抛出异常

// ip link set dev docker0 xdp obj xdp_bpfeb.o sec xdp verbose
// ip link set dev docker0 xdp off
