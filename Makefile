
obj-m += test_sha512.o
test_sha512-objs := main.o wl_crypto.o wl_send_log.o

EXTRA_CFLAGS+=-I. -Wno-error
ccflags=y+=-I. -Wno-error
all:
	make -C /lib/modules/$(shell uname -r)/build M=$(PWD) modules

clean:
	make -C /lib/modules/$(shell uname -r)/build M=$(PWD) clean
