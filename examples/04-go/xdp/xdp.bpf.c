//go:build ignore
#include <linux/bpf.h>
#include <bpf/bpf_endian.h>
#include <bpf/bpf_helpers.h>
#include <linux/if_ether.h>
#include <linux/ip.h>
#include <linux/tcp.h>

struct ip_data {
    __u32 sip;
    __u32 dip;
    __be16 sport;
    __be16 dport;
};

struct bpf_map_def SEC("maps") allow_ip_maps = {
    .type = BPF_MAP_TYPE_HASH,
    .key_size = sizeof(__u32),
    .value_size = sizeof(__u8),
    .max_entries = 1024,
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
    struct tcphdr *tcp = _data + sizeof(*tcp);
    if ((void *)tcp + sizeof(*tcp) > data_end) {
        bpf_printk("invalid tcp header\n");
        return XDP_DROP;
    }

    if (ip->protocol != 6) { // 不是 TCP 跳过
        return XDP_PASS;
    }

    struct ip_data *data = NULL;

    data = bpf_ringbuf_reserve(&ip_map, sizeof(struct ip_data), 0); // 环形缓冲区获取一块内存

    if (data) {
        data->sip = bpf_ntohl(ip->saddr); // 网络字节序 转 主机字节序  32位  大小端
        data->dip = bpf_ntohl(ip->daddr);
        data->sport = bpf_ntohs(tcp->source); // 16位
        data->dport = bpf_ntohs(tcp->dest);
        bpf_ringbuf_submit(data, 0);
    }
    __u32 sip = bpf_ntohl(ip->saddr);
    __u8 *allow = bpf_map_lookup_elem(&allow_ip_maps, &sip);

    if (allow && *allow == 1) {
        return XDP_PASS;
    }

    // unsigned int src_ip = ip->saddr;
    // unsigned char bytes[4];
    // bytes[0] = (src_ip >> 0) & 0xFF;
    // bytes[1] = (src_ip >> 8) & 0xFF;
    // bytes[2] = (src_ip >> 16) & 0xFF;
    // bytes[3] = (src_ip >> 24) & 0xFF;
    //
    // bpf_printk("packet size is %d, protocol is %d, ip is %d.%d.%d.%d\n", pkt_sz, ip->protocol, bytes[0], bytes[1], bytes[2], bytes[3]);
    return XDP_DROP;
}

// XDP_DROP 丢弃网络包--常用DDos防范
// XDP_REDIRECT 数据包转发到不同的网络接口
// XDP_TX 将数据包转发到接收它的同一网络接口
// XDP_PASS 正常流转,流转之前可以做修改
// XDP_ABORTED 丢弃并抛出异常

// ip link set dev docker0 xdp obj xdp_bpfeb.o sec xdp verbose
// ip link set dev docker0 xdp off

// 启动两个容器，分别从宿主机 和另一个容器访问