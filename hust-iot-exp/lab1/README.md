# lab1 notes

```
# decompress linux 3.x
cd linux-3.0.15/ &&
make menuconfig && make zImage && cp arch/arm/boot/zImage /tmp/zImage

cd ..

# burn everything
cd images &&
sudo ./fastboot flash kernel /tmp/zImage &&
sudo ./fastboot flash ramdisk ramdisk-uboot.img &&
sudo ./fastboot flash system system.img
```

Run cutecom

```
sudo cutecom

# type the following cmds in cutecom after booting.
setenv bootcmd movi read kernel 0 40008000;movi read rootfs 0 41000000 100000;bootm 40008000 41000000
setenv bootargs
saveenv
```


