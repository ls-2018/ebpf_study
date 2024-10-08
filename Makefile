CURRENT_DIR := $(shell pwd)

CLANG ?= clang
CFLAGS ?= -O2 -g -Wall -Werror


# 定义一个函数来检测系统架构
detect_architecture = $(shell arch | sed s/aarch64/arm64/ | sed s/x86_64/amd64/)

ifeq ($(detect_architecture), arm64)
    OTHERS_HEADERS=/usr/include/aarch64-linux-gnu
else ifeq ($(detect_architecture), amd64)
	OTHERS_HEADERS=/usr/include/x86_64-linux-gnu
else
	OTHERS_HEADERS=""
endif


all: generate

clean:
	find . -name "*.json" |xargs -I F rm -rf F
	find . -name "*.o" |xargs -I F rm -rf F
	find . -name "*bpfeb.go" |xargs -I F rm -rf F
	find . -name "*bpfel.go" |xargs -I F rm -rf F


generate: export BPF_CFLAGS=$(CFLAGS)
generate: export ASM_HEADERS=$(OTHERS_HEADERS)
generate: export BPF_HEADERS=$(CURRENT_DIR)/include
generate:
	#ln -sf /usr/include/asm-generic/ /usr/include/asm
	echo $(BPF_HEADERS)
	bash ./resources/compile.sh

build:
	docker run --rm -it -v `pwd`:/data -w /data registry.cn-hangzhou.aliyuncs.com/acejilam/mygo:v1.22.2 make generate
