KDIR = /usr/src/kernels/`uname -r`

obj-m += HelloWorld.o

all:
	make -C $(KDIR) M=$(PWD) modules
clean:
	make -C $(KDIR) M=$(PWD) clean
