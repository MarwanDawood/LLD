## Kernel Compilation using SDK
https://casparting.github.io/embedded%20system/SK-AM62x_Build_Kernel/#%E7%B7%A8%E8%AD%AF-kernel-%E4%BD%BF%E7%94%A8-sdk-top-level-makefile

`cd ti-processor-sdk-linux-am62xx-evm-08.06.00.42/`

`make linux`

`sudo DESTDIR=/media/mfarrah/root/boot make linux_install`

## Kernel Compilation using Top Level Makefile
https://casparting.github.io/embedded%20system/SK-AM62x_Build_Kernel/#%E7%B7%A8%E8%AD%AF-kernel-%E4%BD%BF%E7%94%A8-kernel-top-level-makefile
1. Export PATH

`export PATH=/home/mfarrah/ti-processor-sdk-linux-am62xx-evm-08.06.00.42/linux-devkit/sysroots/x86_64-arago-linux/usr/bin:$PATH`

`cd board-support/linux-5.10.168+gitAUTOINC+2c23e6c538-g2c23e6c538/`

2. Clean existing images

`make ARCH=arm64 CROSS_COMPILE=aarch64-none-linux-gnu- distclean`

3. Confirm that compiler _aarch64-none-linux-gnu-_ exists

`ls /home/mfarrah/ti-processor-sdk-linux-am62xx-evm-08.06.00.42/linux-devkit/sysroots/x86_64-arago-linux/usr/bin`

4. Confirm the architecture by checking the result of below command, architecture can be found in the path, here it's _arm64_ `find ./ -name *_defconfig |grep am62`
* Choose the appropriate development platform from the existing defconfig file

`make ARCH=arm64 CROSS_COMPILE=aarch64-none-linux-gnu- tisdk_am62xx-evm_defconfig`
* If the board is customized then you need to go to make menuconfig to customize the settings

`make ARCH=arm64 CROSS_COMPILE=aarch64-none-linux-gnu- menuconfig`

5. Compile linux kernel image

`$ make ARCH=arm64 CROSS_COMPILE=aarch64-none-linux-gnu- Image -j $(nproc)`

#### Device Tree Source
https://casparting.github.io/embedded%20system/SK-AM62x_Build_Kernel/#%E7%B7%A8%E8%AD%AF-device-tree-source

The table below from TI shows correct dts to compile for different targets:
https://software-dl.ti.com/processor-sdk-linux/esd/AM62AX/08_06_00_45/exports/docs/linux/Foundational_Components_Kernel_Users_Guide.html#compiling-the-device-tree-binaries

Show available dts

`cd board-support/linux-5.10.168+gitAUTOINC+2c23e6c538-g2c23e6c538/`

`vi arch/arm64/boot/dts/ti/k3-am642-sk.dts`

`make ARCH=arm64 CROSS_COMPILE=aarch64-none-linux-gnu- ti/k3-am625-sk.dtb`

#### Compile Kernel Modules
https://casparting.github.io/embedded%20system/SK-AM62x_Build_Kernel/#%E7%B7%A8%E8%AD%AF-kernel-modules

`make ARCH=arm64 CROSS_COMPILE=aarch64-none-linux-gnu- modules`

#### Installing Linux
`cd /home/mfarrah/ti-processor-sdk-linux-am62xx-evm-08.06.00.42/board-support/linux-5.10.168+gitAUTOINC+2c23e6c538-g2c23e6c538`

`sudo cp arch/arm64/boot/Image /media/mfarrah/root/boot`

`sudo cp arch/arm64/boot/dts/ti/k3-am625-sk.dtb /media/mfarrah/root/boot`

`sudo make ARCH=arm64 INSTALL_MOD_PATH=/mnt/sdcard/ modules_install`

#### Confirm the Kernel version after booting
`uname -a`