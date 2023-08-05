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
Read more [Linux userspace graphics](./kocialkowski-overview-linux-userspace-graphics-stack.pdf)