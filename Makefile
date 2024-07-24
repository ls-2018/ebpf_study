CLANG ?= clang
CFLAGS ?= -O2 -g -Wall -Werror

EBPF_ROOT = /root/ebpf_study
MY_HEADERS=/usr/include/aarch64-linux-gnu
clean:
	find ./case -name "*.json" |xargs -I F rm -rf F
	find ./case -name "*.o" |xargs -I F rm -rf F



generate: export BPF_CLANG=$(CLANG)
generate: export BPF_CFLAGS=$(CFLAGS)
generate: export BPF_HEADERS=$(MY_HEADERS)
generate:
	go generate ./case/04-go/tc
	go generate ./case/04-go/xdp
