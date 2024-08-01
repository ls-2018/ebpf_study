package xdp

//go:generate go install github.com/cilium/ebpf/cmd/bpf2go@latest
//go:generate bpf2go -cc $BPF_CLANG -go-package xdp -cflags $BPF_CFLAGS xdp xdp.bpf.c -- -I $BPF_HEADERS
