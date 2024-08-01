package sys

//go:generate go install github.com/cilium/ebpf/cmd/bpf2go@latest
//go:generate bpf2go -cc $BPF_CLANG -go-package sys -cflags $BPF_CFLAGS sys sys.bpf.c -- -I $BPF_HEADERS -I /media/psf/ebpf_study/include
