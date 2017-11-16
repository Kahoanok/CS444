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
mount /dev/sbulla tempmont
