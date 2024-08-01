package tc

//go:generate go install github.com/cilium/ebpf/cmd/bpf2go@latest
//go:generate bpf2go -cc $BPF_CLANG -go-package tc -cflags $BPF_CFLAGS tc_write tc_write.bpf.c -- -I $BPF_HEADERS
