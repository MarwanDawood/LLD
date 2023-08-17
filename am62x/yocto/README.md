# Building using Yocto

## Cross-Compile Toolchain
install the ARM Toolchains for Armv7 and Armv8

`wget https://developer.arm.com/-/media/Files/downloads/gnu-a/9.2-2019.12/binrel/gcc-arm-9.2-2019.12-x86_64-arm-none-linux-gnueabihf.tar.xz`

`tar -Jxvf gcc-arm-9.2-2019.12-x86_64-arm-none-linux-gnueabihf.tar.xz -C $HOME`

`wget https://developer.arm.com/-/media/Files/downloads/gnu-a/9.2-2019.12/binrel/gcc-arm-9.2-2019.12-x86_64-aarch64-none-linux-gnu.tar.xz`

`tar -Jxvf gcc-arm-9.2-2019.12-x86_64-aarch64-none-linux-gnu.tar.xz -C $HOME`

## Build steps
Reference https://software-dl.ti.com/processor-sdk-linux/esd/AM62X/08_06_00_42/exports/docs/linux/Overview_Building_the_SDK.html#

`git clone https://git.ti.com/git/arago-project/oe-layersetup.git tisdk`

`cd tisdk`

Configure layer
`./oe-layertool-setup.sh -f configs/processor-sdk/processor-sdk-08.06.00-config.txt`

`cd build`

`. conf/setenv`

`export TOOLCHAIN_PATH_ARMV7=$HOME/gcc-arm-9.2-2019.12-x86_64-arm-none-linux-gnueabihf`

`export TOOLCHAIN_PATH_ARMV8=$HOME/gcc-arm-9.2-2019.12-x86_64-aarch64-none-linux-gnu`

Libraries needed for bitbake

`sudo apt-get install chrpath gawk`

`git clone https://git.ti.com/git/security-development-tools/core-secdev-k3.git -b master`

`export TI_SECURE_DEV_PKG_K3=`pwd`/core-secdev-k3`

`MACHINE=am62xx-evm bitbake -k tisdk-base-image`

The build output can be found in `images/am62xx-evm/tisdk-base-image-am62xx-evm.tar.xz`