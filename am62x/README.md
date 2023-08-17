# Instruction Set Architectures
ISA is divided into two categories:
* load-store architecture -> both operands and destination for opcode must be in registers; for example RISC ISA such as ARM, PowerPC, ...
* register-memory architecture -> one of the operands may be in memory, while the other in register; for example CISC ISA such as x86

# ARM Microcontrollers
Exceptions explanation
https://interrupt.memfault.com/blog/arm-cortex-m-exceptions-and-nvic
## ARM Cortex-M, ARMv7E-M architecture
* Cortex-M4, TI TM4C, Tiva C (Stellaris)
* Cortex-M4, TI AM62x, Sitara safety core
*  Supports CMSIS (Common Microcontroller Software Interface Standard), it provides interfaces to processor and peripherals.

## ARM Cortex-A, ARMv8-A architecture, 
* Cortex-A53, TI AM62x, Sitara MPU
* Cortex-A53, Broadcom BCM2835, Raspberry Pi 3

# AM62x Sitara Kernel Preparation
## Install AM62x SDK
`sudo apt update`

`sudo apt install build-essential bison flex libssl-dev libncurses-dev u-boot-tools`

`chmod +x ti-processor-sdk-linux-am62xx-evm-08.06.00.42-Linux-x86-Install.bin`

`./ti-processor-sdk-linux-am62xx-evm-08.06.00.42-Linux-x86-Install.bin`

## References
* Read more [AM62x datasheet](./AM62x%20Sitara%20Processors%20datasheet%20-%20am623.pdf)
* Read more [SK-AM62 starter kit](./SK-AM62%20Starter%20Kit%20User's%20Guide%20-%20spruj40c.pdf)
* Read more [Buildroot vs Yocto Differences](./Buildroot-vs-Yocto-Differences-for-Your-Daily-Job-Luca-Ceresoli-AIM-Sportline.pdf)
* Read more [ARM systems booting](./How_ARM_systems_are_booted_an_introduction_to_the_ARM_boot_flow.pdf)
* Read more [Linux userspace graphics](./kocialkowski-overview-linux-userspace-graphics-stack.pdf)

# Compiling Linux Kernel
To read total folder content size

`du -sch`

Generate full patch

`git format-patch -1 --pretty=fuller <path-id>`

## Cloning
Clone Kernel Git to linux_mainline folder

`git clone https://github.com/torvalds/linux.git linux_mainline`

Install dependencies

`sudo apt-get install cscope libncurses5-dev libssl-dev bison flex git-email`

Clone stable Kernel Git to linux_stable folder

`git clone git://git.kernel.org/pub/scm/linux/kernel/git/stable/linux-stable.git linux_stable`

Checkout latest branch version

`git br -a |grep linux-5`

`git co linux-5.19.y`

## Configuration
Copy configuration file of current Kernel from `/boot`

`cp /boot/config-5.4.0-150-generic .config`

* to generate config based on old one `make oldconfig`
* to see list of new config symbols `make listnewconfig`

Most functionality in the Linux kernel can either be compiled in (y) or left out (n), and most of it can also be compiled as a loadable module(m).

Edit the config file by removing the assigned value to `CONFIG_SYSTEM_TRUSTED_KEYS` and any other keys has values related to certificates and signatures

## Compile the Kernel
* To compile all `make -j $(nproc) all`
* To compile only changed files `make -j $(nproc)`

Once Kernel compilation is complete, install the new Kerne, the below command will run `update-grub` to add the new Kernel to the grub menu

Login as super user

`sudo -i`

Build modules and install them afterwards
`sudo make modules_install install`

Notes:
* If signing modules fails due to unsupported feature from hardware, disable security for modules signing by running `make menuconfig`, then enter the option `Enable loadable kernel module` then under `Module Signature verification`, uncheck `Automatically sign all modules`
* Another way is to setup certificates manually by running below command, then adjusting **.config** file with the next below parameters:

`openssl req -x509 -newkey rsa:4096 -keyout certs/mycert.pem -out certs/mycert.pem -nodes -days 3650`

`CONFIG_MODULE_SIG_KEY="certs/mycert.pem"`
`CONFIG_SYSTEM_TRUSTED_KEYRING=y`
`CONFIG_SYSTEM_TRUSTED_KEYS="certs/mycert.pem"`

if not installed, install it using `sudo apt-get install mokutil`

Using the option `-t` allows to generate dmesg logs without timestamp

`dmesg -t > dmesg_current`
`dmesg -t -k > dmesg_kernel`
`dmesg -t -l <emerg|alert|crit|err|warn|info> > dmesg_current_xx`

## Booting the Kernel
Comment out `GRUB_TIMEOUT_STYLE=hidden` and change `GRUB_TIMEOUT` value to 5

`sudo vim /etc/default/grub`

`sudo cp arch/x86/boot/bzImage /boot/`

Update the grub configuration, it will locate any new kernel images in \boot\

`sudo update-grub`

## Patch preparation
To know who you should send the patch to, run this script

`scripts/get_maintainer.pl <changed-file>`

To check if code changes are complying with Linux Kernel coding style, run

`checkpatch.pl <changed-file>`

To add all files and create commit message

`git commit -a`

To create a formatted patch

`git format-patch -1 HEAD --to=<email> --cc=<email>`

To send the email, first you need to setup smtp fields in `.gitconfig`, for smtppass, if 2-steps verifications is enabled, you can create **App Password** from Google Account, and add it in that file

`git send-email 0001-add-print-log.patch`

Git doesn't know about changed files and will see them as untracked
`patch -p1 < file.patch`

To remove untracked files, run both below

`git clean -dfx`

`git reset --hard`

Git will be aware of changed files
`git apply --index file.patch`

`git diff`

## Driver Dependency
The file `Kconfig` has the dependency information, as well as the driver possible types, tristate means:
* **y** to enable as a built-in, i.e., loaded during Kernel loading.
* **m** to enable as module, i.e., loaded on request after Kernel is loaded.
* **n** to disable it.

## Debugging Kernel
Ordered from the least severity
* Kernel Oops
* Kernel Aiee
* Kernel Panic

https://sanjeev1sharma.wordpress.com/tag/debug-kernel-panics/
https://www.opensourceforu.com/2011/01/understanding-a-kernel-oops/
