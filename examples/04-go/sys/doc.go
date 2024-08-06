package sys

//go:generate go install github.com/cilium/ebpf/cmd/bpf2go@latest
//go:generate bpf2go -target amd64 sys sys.bpf.c -- -I $BPF_HEADERS -I $ASM_HEADERS
