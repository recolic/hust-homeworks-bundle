#!/usr/bin/fish
## source this script, and enjoy your job.

function rfs_create_test_image
    dd bs=4096 count=6000 if=/dev/zero of=$argv[1]
    ../mkfs.rfs $argv[1]
end

function rfs_mount_fs_image
    mkdir $argv[2]
    sudo insmod ../rfs.ko
    sudo mount -o loop,owner,group,users -t rfs $argv[1] $argv[2]
end

function rfs_unmount_fs
    sudo umount $argv[1]
    sudo rmmod ../rfs.ko
end

