## U-Boot Load Default dtb
```
ver
mmc rescan
```

bootargs can be read from linux using

```
cat /proc/cmdline
env set bootargs console=ttyS2,115200n8 earlycon=ns16550a,mmio32,0x02800000 root=PARTUUID=c879998c-02 rw rootfstype=ext4 rootwait
```

Show SD card content using `ls mmc 1:2 boot/`
* MMC 0 is flash
* MMC 1:1 is SD card, boot partition
* MMC 1:2 is SD card, root partition

Load Kernel and dtb files:\
```
load mmc 1:2 0x82000000 boot/fitImage
iminfo
load mmc 1:2 0x88000000 boot/k3-am625-sk.dtb
```

Boot Kernel\
`bootm $loadaddr - 0x88000000`

## U-Boot Customized Default dtb
Optional: set env variable with default kernel image address\
`env set $loaddtb 0x88000000`

Load flattened device tree\
```
fdt addr 0x88000000
fdt list
```

Change Kernel model and boot\
```
fdt set / model "Hello World!"
bootm 0x82000000 - 0x88000000
```

Check that Kernel model changed\
`dmesg |grep Hello`

## Load Files from Serial Connection
1. `loady`
2. Show help, then send file from host to target by pressing _ctrl-a z s_
3. Choose _ymodem_
4. Navigate using 'space', once you are in the desired folder, write the file name
5. Press any key to continue
6. Read the transferred file `md.l $loadaddr $filesize` _#b/h/l/q_
7. Import environment variables `env import $loadaddr $filesize`
8. Print environment variables `env print foo`

## Build U-Boot Sandbox to run from Host
Show available configurations `ls configs |grep am6`

* Build uboot for sandbox `make sandbox_defconfig`
* Build uboot for am62x `make am62x_evm_a53_defconfig`

Make sure that python3.7 or above is installed
https://cloudbytes.dev/snippets/upgrade-python-to-latest-version-on-ubuntu-linux

Install following packages:\
```
sudo apt-get install python3-dev python3-setuptools uuid-dev libgnutls28-dev swig
make -j $(nproc)
```