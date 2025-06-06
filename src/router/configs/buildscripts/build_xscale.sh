#!/bin/sh
#./build_cambria_kmt.sh
OLDPATH=$PATH
DATE=$(date +%m-%d-%Y)
DATE+="-r"
DATE+=$(svnversion -n xscale/src/router/libutils)
export PATH=/xfs/toolchains/toolchain-armeb_xscale_gcc-13.1.0_musl/bin:$OLDPATH
cd xscale/src/router
[ -n "$DO_UPDATE" ] && svn update
cd opt/etc/config
[ -n "$DO_UPDATE" ] && svn update
cd ../../../
cp .config_xscale .config
#echo "CONFIG_TDMA=y" >> .config
#echo "CONFIG_ATH5K=y" >> .config
#sed -i 's/CONFIG_QUAGGA=y/CONFIG_FRR=y/g' .config
make -f Makefile.armbe kernel clean all install
mkdir -p ~/GruppenLW/releases/$DATE/gateworks-avila-8M
mkdir -p ~/GruppenLW/releases/$DATE/gateworks-avila-16M
mkdir -p ~/GruppenLW/releases/$DATE/pronghorn-SBC
mkdir -p ~/GruppenLW/releases/$DATE/compex-wp188
cd ../../../
cp xscale/src/router/armeb-uclibc/gateworks-firmware-squashfs.bin ~/GruppenLW/releases/$DATE/gateworks-avila-8M
#cp xscale/src/router/armeb-uclibc/gateworks-firmware-jffs.bin ~/GruppenLW/releases/$DATE/gateworks_8M
cp xscale/src/router/armeb-uclibc/gateworx-firmware.raw2 ~/GruppenLW/releases/$DATE/gateworks-avila-8M/linux.bin

#cp xscale/src/router/armeb-uclibc/gateworks-firmware-squashfs.bin ~/GruppenLW/releases/$DATE/pronghorn-SBC/pronghorn-firmware.bin
#cp xscale/src/router/armeb-uclibc/gateworx-firmware.raw2 ~/GruppenLW/releases/$DATE/pronghorn-SBC/linux.bin

cp xscale/src/router/armeb-uclibc/gateworks-firmware-squashfs.bin ~/GruppenLW/releases/$DATE/compex-wp188/compex-firmware-webflash.bin
cp xscale/src/router/armeb-uclibc/firmware.compex ~/GruppenLW/releases/$DATE/compex-wp188/firmware.tftp


cd xscale/src/router

cp .config_xscale_16M .config
echo "CONFIG_WIREGUARD=y" >> .config
echo "CONFIG_SPEEDCHECKER=y" >> .config
echo "CONFIG_TDMA=y" >> .config
echo "CONFIG_WPA3=y" >> .config
echo "CONFIG_ATH5K=y" >> .config
echo "CONFIG_CAKE=y" >> .config
echo "CONFIG_MAC80211_MESH=y" >> .config
sed -i 's/CONFIG_QUAGGA=y/CONFIG_FRR=y/g' .config
make -f Makefile.armbe kernel clean all install
cd ../../../
cp xscale/src/router/armeb-uclibc/gateworks-firmware-squashfs.bin ~/GruppenLW/releases/$DATE/gateworks-avila-16M
#cp xscale/src/router/armeb-uclibc/gateworks-firmware-jffs.bin ~/GruppenLW/releases/$DATE/gateworks_16M
cp xscale/src/router/armeb-uclibc/gateworx-firmware.raw2 ~/GruppenLW/releases/$DATE/gateworks-avila-16M/linux.bin


cd xscale/src/router
echo "CONFIG_PRONGHORN=y" >> .config
echo "CONFIG_ATH5K=y" >> .config
make -f Makefile.armbe libutils-clean libutils install
cd ../../../
cp xscale/src/router/armeb-uclibc/gateworks-firmware-squashfs.bin ~/GruppenLW/releases/$DATE/pronghorn-SBC/pronghorn-firmware.bin
cp xscale/src/router/armeb-uclibc/gateworx-firmware.raw2 ~/GruppenLW/releases/$DATE/pronghorn-SBC/linux.bin

#./build_wrt300nv2.sh
./build_nop8670.sh
./build_wg302.sh
./build_wg302v1.sh
#./build_xscale_maksat.sh
#cd xscale/src/router
#svn update
#cp .config_ixpmaksat .config
#make -f Makefile.armbe kernel clean all install
#mkdir -p ~/GruppenLW/releases/$DATE/gateworks
#cd ../../../
#cp xscale/src/router/armeb-uclibc/gateworx-firmware-squashfs.bin ~/GruppenLW/releases/$DATE/gateworks/maksat-gateworks-firmware.bin
#cp xscale/src/router/armeb-uclibc/root.fs ~/GruppenLW/releases/$DATE/gateworks/maksat-root.fs
#cp xscale/src/linux/xscale/linux-2.6.23/arch/arm/boot/zImage ~/GruppenLW/releases/$DATE/gateworks/maksat-zImage


#cd xscale/src/router
#svn update
#cp .config_xscale_boese .config
#make -f Makefile.armbe kernel clean all install
#mkdir -p ~/GruppenLW/releases/$DATE/gateworks
#cd ../../../
#cp xscale/src/router/armeb-uclibc/gateworx-firmware-squashfs.bin ~/GruppenLW/releases/$DATE/gateworks/superchannel-gateworks-firmware.bin
#cp xscale/src/router/armeb-uclibc/root.fs ~/GruppenLW/releases/$DATE/gateworks/superchannel-root.fs
#cp xscale/src/linux/xscale/linux-2.6.22/arch/arm/boot/zImage ~/GruppenLW/releases/$DATE/gateworks/superchannel-zImage

#cd xscale/src/router
#svn update
#cp .config_xscale_william .config
#make -f Makefile.armbe kernel clean all install
#mkdir -p ~/GruppenLW/releases/$DATE/gateworks
#cd ../../../
#cp xscale/src/router/armeb-uclibc/gateworx-firmware-squashfs.bin ~/GruppenLW/releases/$DATE/gateworks/william-gateworks-firmware.bin
#cp xscale/src/router/armeb-uclibc/root.fs ~/GruppenLW/releases/$DATE/gateworks/william-root.fs
#cp xscale/src/linux/xscale/linux-2.6.22/arch/arm/boot/zImage ~/GruppenLW/releases/$DATE/gateworks/william-zImage

#cd xscale/src/router
#svn update
#cp .config_xscale_mimo .config
#make -f Makefile.armbe kernel clean all install
#mkdir -p ~/GruppenLW/releases/$DATE/gateworks
#cd ../../../
#cp xscale/src/router/armeb-uclibc/gateworx-firmware-squashfs.bin ~/GruppenLW/releases/$DATE/gateworks/gateworks-firmware-mimo.bin
#cp xscale/src/router/armeb-uclibc/root.fs ~/GruppenLW/releases/$DATE/gateworks/root.fs-mimo
#cp xscale/src/linux/xscale/linux-2.6.22/arch/arm/boot/zImage ~/GruppenLW/releases/$DATE/gateworks/zImage-mimo
