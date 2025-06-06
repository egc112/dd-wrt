#!/bin/sh
OLDPATH=$PATH
DATE=$(date +%m-%d-%Y)
DATE+="-r"
DATE+=$(svnversion -n octeon/src/router/httpd)
export PATH=/xfs/toolchains/toolchain-mips64_octeon_64_gcc-7.3.0_musl/bin:$OLDPATH
cd octeon/src/router
cp .config_e200 .config
echo "CONFIG_SPEEDCHECKER=y" >>.config
echo "CONFIG_STRACE=y" >>.config
echo "CONFIG_LSOF=y" >> .config
echo "CONFIG_MIKROTIK_BTEST=y" >> .config
echo "CONFIG_WIREGUARD=y" >> .config
echo "CONFIG_ZFS=y" >> .config
echo "CONFIG_SCREEN=y" >> .config
echo  "CONFIG_DDRESCUE=y" >>.config
sed -i 's/CONFIG_QUAGGA=y/CONFIG_FRR=y/g' .config

make -f Makefile.octeon kernel clean all install
mkdir -p ~/GruppenLW/releases/$DATE/ubnt-edgerouter-pro
mkdir -p ~/GruppenLW/releases/$DATE/ubnt-edgerouter-pro-usbboot
mkdir -p ~/GruppenLW/releases/$DATE/ubnt-unifi-ugw4
mkdir -p ~/GruppenLW/releases/$DATE/ubnt-unifi-ugw4-usbboot
cd ../../../
cp octeon/src/router/mips64-uclibc/erouter.image ~/GruppenLW/releases/$DATE/ubnt-edgerouter-pro/edgerouter-e200.image
cp octeon/src/router/mips64-uclibc/erouter.bin ~/GruppenLW/releases/$DATE/ubnt-edgerouter-pro/edgerouter-e200-webupgrade.bin

cp octeon/src/router/mips64-uclibc/erouter.image ~/GruppenLW/releases/$DATE/ubnt-unifi-ugw4/ugw4-e220.image
cp octeon/src/router/mips64-uclibc/erouter.bin ~/GruppenLW/releases/$DATE/ubnt-unifi-ugw4/ugw4-e220-webupgrade.bin

cd octeon/src/router
echo "CONFIG_USBBOOT=y" >> .config
make -f Makefile.octeon kernel clean all install

cd ../../../
cp octeon/src/router/mips64-uclibc/erouter.image ~/GruppenLW/releases/$DATE/ubnt-edgerouter-pro-usbboot/edgerouter-e200.image
cp octeon/src/router/mips64-uclibc/erouter.bin ~/GruppenLW/releases/$DATE/ubnt-edgerouter-pro-usbboot/edgerouter-e200-webupgrade.bin

cp octeon/src/router/mips64-uclibc/erouter.image ~/GruppenLW/releases/$DATE/ubnt-unifi-ugw4-usbboot/ugw4-e220.image
cp octeon/src/router/mips64-uclibc/erouter.bin ~/GruppenLW/releases/$DATE/ubnt-unifi-ugw4-usbboot/ugw4-e220-webupgrade.bin
