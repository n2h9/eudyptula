KDIR 		   := /lib/modules/$(shell uname -r)/build
PWD            := $(shell pwd)
obj-m          := eudyptula_task01_lkm.o
EXTRA_CFLAGS   += -DDEBUG

all:
	make -C $(KDIR) M=$(PWD) EXTRA_CFLAGS=${EXTRA_CFLAGS} modules
clean:
	make -C $(KDIR) M=$(PWD) clean
	rm -f *~

