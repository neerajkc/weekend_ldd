obj-m := first_module.o first_char_driver.o

KERNEL_DIR ?= $(HOME)/linux_rpi4b/linux

all:
	make -C $(KERNEL_DIR) ARCH=arm CROSS_COMPILE=arm-linux-gnueabihf- \
			M=$(PWD) modules

clean:
	make -C $(KERNEL_DIR) ARCH=arm CROSS_COMPILE=arm-linux-gnueabihf- \
			M=$(PWD) clean

deploy:
	scp *.ko pi@192.168.1.67:/home/pi