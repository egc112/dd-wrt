#
# linux/drivers/nand/Makefile
#
EXTRA_CFLAGS+= -g

obj-$(CONFIG_MTD_NAND)			+= nand.o
obj-$(CONFIG_MTD_NAND_ECC)		+= nand_ecc.o  nand_ecc_mlc.o
obj-$(CONFIG_MTD_NAND_BCH)		+= nand_bch.o
obj-$(CONFIG_MTD_NAND_IDS)		+= nand_ids.o
obj-$(CONFIG_MTD_SM_COMMON) 		+= sm_common.o

obj-$(CONFIG_MTD_NAND_CAFE)		+= cafe_nand.o
obj-$(CONFIG_MTD_NAND_AMS_DELTA)	+= ams-delta.o
obj-$(CONFIG_MTD_NAND_DENALI)		+= denali.o
obj-$(CONFIG_MTD_NAND_DENALI_PCI)	+= denali_pci.o
obj-$(CONFIG_MTD_NAND_DENALI_DT)	+= denali_dt.o
obj-$(CONFIG_MTD_NAND_AU1550)		+= au1550nd.o
obj-$(CONFIG_MTD_NAND_BF5XX)		+= bf5xx_nand.o
obj-$(CONFIG_MTD_NAND_S3C2410)		+= s3c2410.o
obj-$(CONFIG_MTD_NAND_DAVINCI)		+= davinci_nand.o
obj-$(CONFIG_MTD_NAND_DISKONCHIP)	+= diskonchip.o
obj-$(CONFIG_MTD_NAND_DOCG4)		+= docg4.o
obj-$(CONFIG_MTD_NAND_FSMC)		+= fsmc_nand.o
obj-$(CONFIG_MTD_NAND_SHARPSL)		+= sharpsl.o
obj-$(CONFIG_MTD_NAND_NANDSIM)		+= nandsim.o
obj-$(CONFIG_MTD_NAND_CS553X)		+= cs553x_nand.o
obj-$(CONFIG_MTD_NAND_NDFC)		+= ndfc.o
obj-$(CONFIG_MTD_NAND_ATMEL)		+= atmel_nand.o
obj-$(CONFIG_MTD_NAND_GPIO)		+= gpio.o
obj-$(CONFIG_MTD_NAND_OMAP2) 		+= omap2.o
obj-$(CONFIG_MTD_NAND_OMAP_BCH_BUILD)	+= omap_elm.o
obj-$(CONFIG_MTD_NAND_CM_X270)		+= cmx270_nand.o
obj-$(CONFIG_MTD_NAND_PXA3xx)		+= pxa3xx_nand.o
obj-$(CONFIG_MTD_NAND_TMIO)		+= tmio_nand.o
obj-$(CONFIG_MTD_NAND_PLATFORM)		+= plat_nand.o
obj-$(CONFIG_MTD_NAND_RB)		+= rb.o
obj-$(CONFIG_MTD_NAND_RB500)		+= rb500nand.o
#obj-$(CONFIG_MTD_NAND_RB400)		+= rb400_nand.o
#obj-$(CONFIG_MTD_NAND_RB400)		+= rb700_nand.o
#obj-$(CONFIG_MTD_NAND_RB400)		+= rb750g_nand.o
#obj-$(CONFIG_MTD_NAND_RB400)		+= ar9330_nand.o
obj-$(CONFIG_MTD_NAND_RB400)		+= ar9344_nand.o
#obj-$(CONFIG_MTD_NAND_RB1200)		+= rb1200_nand.o
obj-$(CONFIG_MTD_NAND_RB_PPC)		+= rb_ppc.o
obj-$(CONFIG_MTD_NAND_PASEMI)		+= pasemi_nand.o
obj-$(CONFIG_MTD_NAND_ORION)		+= orion_nand.o
obj-$(CONFIG_MTD_NAND_FSL_ELBC)		+= fsl_elbc_nand.o
obj-$(CONFIG_MTD_NAND_FSL_IFC)		+= fsl_ifc_nand.o
obj-$(CONFIG_MTD_NAND_FSL_UPM)		+= fsl_upm.o
obj-$(CONFIG_MTD_NAND_SLC_LPC32XX)      += lpc32xx_slc.o
obj-$(CONFIG_MTD_NAND_MLC_LPC32XX)      += lpc32xx_mlc.o
obj-$(CONFIG_MTD_NAND_SH_FLCTL)		+= sh_flctl.o
obj-$(CONFIG_MTD_NAND_MXC)		+= mxc_nand.o
obj-$(CONFIG_MTD_NAND_SOCRATES)		+= socrates_nand.o
obj-$(CONFIG_MTD_NAND_TXX9NDFMC)	+= txx9ndfmc.o
obj-$(CONFIG_MTD_NAND_NUC900)		+= nuc900_nand.o
obj-$(CONFIG_MTD_NAND_MPC5121_NFC)	+= mpc5121_nfc.o
obj-$(CONFIG_MTD_NAND_RICOH)		+= r852.o
obj-$(CONFIG_MTD_NAND_JZ4740)		+= jz4740_nand.o
obj-$(CONFIG_MTD_NAND_GPMI_NAND)	+= gpmi-nand/
obj-$(CONFIG_MTD_NAND_XWAY)		+= xway_nand.o
obj-$(CONFIG_MTD_NAND_BCM47XXNFLASH)	+= bcm47xxnflash/
obj-$(CONFIG_MTD_NAND_ATH)		+= ath_nand.o
obj-$(CONFIG_MTD_NAND_QCOM)		+= qcom_nandc.o

nand-objs := nand_base.o nand_bbt.o nand_timings.o
