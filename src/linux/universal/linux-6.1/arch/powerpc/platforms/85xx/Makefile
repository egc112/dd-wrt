# SPDX-License-Identifier: GPL-2.0
#
# Makefile for the PowerPC 85xx linux kernel.
#
obj-$(CONFIG_SMP) += smp.o
ifneq ($(CONFIG_FSL_CORENET_RCPM),y)
obj-$(CONFIG_SMP) += mpc85xx_pm_ops.o
endif

obj-y += common.o

obj-$(CONFIG_BSC9131_RDB) += bsc913x_rdb.o
obj-$(CONFIG_BSC9132_QDS) += bsc913x_qds.o
obj-$(CONFIG_C293_PCIE)   += c293pcie.o
obj-$(CONFIG_BR200_WP) += br200-wp.o
obj-$(CONFIG_HIVEAP_330) += hiveap-330.o
obj-$(CONFIG_MPC8540_ADS) += mpc85xx_ads.o
obj-$(CONFIG_MPC8560_ADS) += mpc85xx_ads.o
obj-$(CONFIG_MPC85xx_CDS) += mpc85xx_cds.o
obj-$(CONFIG_MPC8536_DS)  += mpc8536_ds.o
obj-$(CONFIG_MPC85xx_DS)  += mpc85xx_ds.o
obj-$(CONFIG_MPC85xx_MDS) += mpc85xx_mds.o
obj-$(CONFIG_MPC85xx_RDB) += mpc85xx_rdb.o
obj-$(CONFIG_P1010_RDB)   += p1010rdb.o
obj-$(CONFIG_P1022_DS)    += p1022_ds.o
obj-$(CONFIG_P1022_RDK)   += p1022_rdk.o
obj-$(CONFIG_P1023_RDB)   += p1023_rdb.o
obj-$(CONFIG_PANDA)       += panda.o
obj-$(CONFIG_TWR_P102x)   += twr_p102x.o
obj-$(CONFIG_WS_AP3710I)  += ws-ap3710i.o
obj-$(CONFIG_WS_AP3715I)  += ws-ap3715i.o
obj-$(CONFIG_WS_AP3825I)  += ws-ap3825i.o
obj-$(CONFIG_FIREBOX_T10) += firebox_t10.o
obj-$(CONFIG_CORENET_GENERIC)   += corenet_generic.o
obj-$(CONFIG_FB_FSL_DIU)	+= t1042rdb_diu.o
obj-$(CONFIG_RED_15W_REV1)	+= red15w_rev1.o
obj-$(CONFIG_STX_GP3)	  += stx_gp3.o
obj-$(CONFIG_TL_WDR4900_V1) += tl_wdr4900_v1.o
obj-$(CONFIG_TQM85xx)	  += tqm85xx.o
obj-$(CONFIG_PPA8548)     += ppa8548.o
obj-$(CONFIG_SOCRATES)    += socrates.o socrates_fpga_pic.o
obj-$(CONFIG_KSI8560)	  += ksi8560.o
obj-$(CONFIG_XES_MPC85xx) += xes_mpc85xx.o
obj-$(CONFIG_GE_IMP3A)	  += ge_imp3a.o
obj-$(CONFIG_PPC_QEMU_E500) += qemu_e500.o
obj-$(CONFIG_SGY_CTS1000) += sgy_cts1000.o
obj-$(CONFIG_MVME2500)	  += mvme2500.o
