#include <linux/bpf.h>
#include <linux/if_ether.h>
#include <linux/ip.h>

#include "bpf_helpers.h"

SEC("xdp")
int my_pass(struct xdp_md *ctx) {
    void *data = (void *)(long)ctx->data;
    void *data_end = (void *)(long)ctx->data_end;
    int pkt_sz = data_end - data;

    struct ethhdr *eth = data;
    if ((void *)eth + sizeof(*eth) > data_end) {
        bpf_printk("invalid ethernet header\n");
        return XDP_DROP;
    }

    struct iphdr *ip = data + sizeof(*ip);
    if ((void *)ip + sizeof(*ip) > data_end) {
        bpf_printk("invalid ip header\n");
        return XDP_DROP;
    }

    unsigned int src_ip = ip->saddr;
    unsigned char bytes[4];
    bytes[0] = (src_ip >> 0) & 0xFF;
    bytes[1] = (src_ip >> 8) & 0xFF;
    bytes[2] = (src_ip >> 16) & 0xFF;
    bytes[3] = (src_ip >> 24) & 0xFF;

    bpf_printk("packet size is %d, protocol is %d, ip is %d.%d.%d.%d\n", pkt_sz, ip->protocol, bytes[0], bytes[1], bytes[2], bytes[3]);
    return XDP_PASS;
}

// XDP_DROP 丢弃网络包--常用DDos防范
// XDP_REDIRECT 数据包转发到不同的网络接口
// XDP_TX 将数据包转发到接收它的同一网络接口
// XDP_PASS 正常流转,流转之前可以做修改
// XDP_ABORTED 丢弃并抛出异常

// ip link set dev docker0 xdp obj test.bpf.o sec xdp verbose
// ip link set dev docker0 xdp off
