package sys

import (
	"errors"
	"github.com/cilium/ebpf/link"
	"github.com/cilium/ebpf/perf"
	"github.com/cilium/ebpf/ringbuf"
	"log"
	"time"
	"unsafe"
)

type Proc struct {
	Pid  uint64
	Name [255]byte
}

func Load() {
	sysObj := sysObjects{}
	err := loadSysObjects(&sysObj, nil)
	if err != nil {
		log.Fatalln(err)
	}
	//tracepoint, err := link.Tracepoint("syscalls", "sys_enter_execve", sysObj.HandleTp, nil)
	tracepoint, err := link.Tracepoint("syscalls", "sys_exit_execve", sysObj.HandleTp, nil)
	if err != nil {
		log.Fatalln(err)
	}
	defer tracepoint.Close()

	// 创建 reader 读取 内核map

	reader, err := ringbuf.NewReader(sysObj.ProcMap)
	if err != nil {
		log.Fatalln(err)
	}

	defer reader.Close()

	for {
		record, err := reader.Read()
		if err != nil {
			if errors.Is(err, perf.ErrClosed) {
				log.Println("received signal, exiting...")
				return
			}
			log.Println("received signal, exiting...")

			continue
		}
		if len(record.RawSample) > 0 {
			data := (*Proc)(unsafe.Pointer(&record.RawSample[0]))
			log.Println(data)
		}
	}

	time.Sleep(time.Minute)
}
