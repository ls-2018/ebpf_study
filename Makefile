# 定义一个函数来检测系统架构
detect_architecture = $(shell arch | sed s/aarch64/arm64/ | sed s/x86_64/amd64/)

ifeq ($(detect_architecture), arm64)
    MY_HEADERS = /usr/include/aarch64-linux-gnu
else ifeq ($(detect_architecture), amd64)
	MY_HEADERS=/usr/include/x86_64-linux-gnu
else
	MY_HEADERS=""
endif


CLANG ?= clang
CFLAGS ?= -O2 -g -Wall -Werror

EBPF_ROOT = /root/ebpf_study
#MY_HEADERS=

all: generate


clean:
	find ./case -name "*.json" |xargs -I F rm -rf F
	find ./case -name "*.o" |xargs -I F rm -rf F



generate: export BPF_CLANG=$(CLANG)
generate: export BPF_CFLAGS=$(CFLAGS)
generate: export BPF_HEADERS=$(MY_HEADERS)
generate:
	go generate ./case/04-go/tc
	go generate ./case/04-go/xdp
