#!/bin/csh

insmod sbull.ko
(
echo g
echo n
echo
echo
echo
echo w
) | fdisk /dev/sbulla
echo
sleep 2
mkfs.ext2 /dev/sbulla
mkdir tempmount
mount /dev/sbulla tempmount
