package tc

//go:generate go install github.com/cilium/ebpf/cmd/bpf2go@latest
//go:generate bpf2go tc_write tc_write.bpf.c -- -I $BPF_HEADERS -I $ASM_HEADERS
