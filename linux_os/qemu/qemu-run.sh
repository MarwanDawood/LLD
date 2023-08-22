#!/bin/bash
#will make an image in qemu/myos.img and run it with qemu

rm -f qemu/myos.img
qemu-img create qemu/myos.img 512M
mkfs.ext4 qemu/myos.img
mkdir -p qemu/mnt
sudo mount qemu/myos.img qemu/mnt

#system files need to exist in /mnt/myos
sudo cp -r /mnt/myos/* qemu/mnt
sudo umount qemu/mnt

qemu-system-x86_64 -kernel /boot/vmlinuz-linux -initrd /boot/initramfs-linux.img -m 512m -append "root=/dev/sda" -hda qemu/myos.img
