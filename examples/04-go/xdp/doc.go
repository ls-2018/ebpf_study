package xdp

//go:generate go install github.com/cilium/ebpf/cmd/bpf2go@latest
//go:generate bpf2go xdp xdp.bpf.c -- -I $BPF_HEADERS -I $ASM_HEADERS
