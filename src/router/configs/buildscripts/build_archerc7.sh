#!/bin/sh
OLDPATH=$PATH
DATE=$(date +%m-%d-%Y)
DATE+="-r"
DATE+=$(svnversion -n pb42/src/router/httpd)
export PATH=/xfs/toolchains/toolchain-mips_24kc_gcc-13.1.0_musl/bin:$OLDPATH
#export PATH=/xfs/toolchains/toolchain-mips_gcc-4.3.3+cs_uClibc-0.9.30.1/usr/bin:$OLDPATH
cd pb42/src/router
[ -n "$DO_UPDATE" ] && svn update
cd opt/etc/config
[ -n "$DO_UPDATE" ] && svn update
cd ../../../
cp .config_wr1043v2 .config
echo CONFIG_ARCHERC7=y >> .config
echo CONFIG_ATH10K=y >> .config
echo CONFIG_CPUTEMP=y >> .config
#echo "CONFIG_TDMA=y" >> .config
echo "CONFIG_CAKE=y" >> .config
echo "CONFIG_WIREGUARD=y" >> .config
echo "CONFIG_WPA3=y" >> .config
echo "CONFIG_SMBD=y" >> .config
echo "CONFIG_SAMBA=y" >> .config
#echo "CONFIG_SMARTDNS=y" >> .config
echo "CONFIG_SPEEDTEST_CLI=y" >> .config
#echo "CONFIG_MDNS=y" >> .config
#echo "CONFIG_MAC80211_ATH9K_HTC=y" >> .config
#echo "CONFIG_KERNELLTO=y" >> .config
#echo "CONFIG_KERNELLTO_CP_CLONE=y" >> .config
make -f Makefile.pb42 kernel clean all install
mkdir -p ~/GruppenLW/releases/$DATE/tplink-archer-c7-v1
cd ../../../
cp pb42/src/router/mips-uclibc/ARCHER-C7v1-firmware.bin ~/GruppenLW/releases/$DATE/tplink-archer-c7-v1/tplink-archer-c7.bin
cp pb42/src/router/mips-uclibc/tplink-ARCHER-C7v1-firmware.bin ~/GruppenLW/releases/$DATE/tplink-archer-c7-v1/factory-to-ddwrt.bin

cp pb42/src/router/mips-uclibc/ARCHER-C7v1-firmwareUS.bin ~/GruppenLW/releases/$DATE/tplink-archer-c7-v1/tplink-archer-c7-US.bin
cp pb42/src/router/mips-uclibc/tplink-ARCHER-C7v1-firmwareUS.bin ~/GruppenLW/releases/$DATE/tplink-archer-c7-v1/factory-to-ddwrt-US.bin


