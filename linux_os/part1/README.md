* install virtualbox from Oracle
* create 2 virtual hard disks in virtualbox
* run for example `cfdisk /dev/sdb` to create a partition `dos, bootable, primary`
* format it using `mkfs.ext4 /dev/sdb1`
* `cd /mnt` then `mkdir myos`
* mount sdb1 as myos `mount /dev/sdb1 myos`
* `cd myos` and delete the folder lost+found
* add the basic linux directories `mkdir -pv ./{bin,sbin,etc,lib,lib64,var,dev,proc,sys,run,tmp,boot}`, p -> parents no error if existing, v -> verbose
* `mknod -m 600 ./dev/console c 5 1`, create a character device version 5.1
* `mknod -m 666 ./dev/null c 3 1`, create a null device
* `cp /boot/initrd.img-5.10.0-kali7-amd64 .`
* `cp /boot/vmlinuz-5.10.0-kali7-amd64 .`
* `grub-install /dev/sdb --skip-fs-prob --boot-directory=/mnt/myos/boot` to install grub in the boot directory
* `vim grub/grub.cfg` and add the following
    set default=0
    set timeout=30
    menuentry "myOs 0.0.1" {
        linux /boot/vmlinuz-5.10.0-kali7-amd64 root=/dev/sdb1 ro
        initrd /boot/initrd.img-5.10.0-kali7-amd6
    }
* add the source files into /mnt/myos/src
* compile the src files using `gcc -nostdlib -ffreestanding -no-pie init.c start.S`
* replace the binary file in sbin/init with the generated one `cp a.out ../sbin/init`
