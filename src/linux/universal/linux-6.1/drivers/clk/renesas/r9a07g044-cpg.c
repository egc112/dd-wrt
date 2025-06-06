// SPDX-License-Identifier: GPL-2.0
/*
 * RZ/G2L CPG driver
 *
 * Copyright (C) 2021 Renesas Electronics Corp.
 */

#include <linux/clk-provider.h>
#include <linux/device.h>
#include <linux/init.h>
#include <linux/kernel.h>

#include <dt-bindings/clock/r9a07g044-cpg.h>
#include <dt-bindings/clock/r9a07g054-cpg.h>

#include "rzg2l-cpg.h"

/* Specific registers. */
#define CPG_PL2SDHI_DSEL	(0x218)

/* Clock select configuration. */
#define SEL_SDHI0		SEL_PLL_PACK(CPG_PL2SDHI_DSEL, 0, 2)
#define SEL_SDHI1		SEL_PLL_PACK(CPG_PL2SDHI_DSEL, 4, 2)

/* Clock status configuration. */
#define SEL_SDHI0_STS		SEL_PLL_PACK(CPG_CLKSTATUS, 28, 1)
#define SEL_SDHI1_STS		SEL_PLL_PACK(CPG_CLKSTATUS, 29, 1)

enum clk_ids {
	/* Core Clock Outputs exported to DT */
	LAST_DT_CORE_CLK = R9A07G054_CLK_DRP_A,

	/* External Input Clocks */
	CLK_EXTAL,

	/* Internal Core Clocks */
	CLK_OSC_DIV1000,
	CLK_PLL1,
	CLK_PLL2,
	CLK_PLL2_DIV2,
	CLK_PLL2_DIV2_8,
	CLK_PLL2_DIV2_10,
	CLK_PLL3,
	CLK_PLL3_400,
	CLK_PLL3_533,
	CLK_M2_DIV2,
	CLK_PLL3_DIV2,
	CLK_PLL3_DIV2_2,
	CLK_PLL3_DIV2_4,
	CLK_PLL3_DIV2_4_2,
	CLK_SEL_PLL3_3,
	CLK_DIV_PLL3_C,
	CLK_PLL4,
	CLK_PLL5,
	CLK_PLL5_FOUTPOSTDIV,
	CLK_PLL5_FOUT1PH0,
	CLK_PLL5_FOUT3,
	CLK_PLL5_250,
	CLK_PLL6,
	CLK_PLL6_250,
	CLK_P1_DIV2,
	CLK_PLL2_800,
	CLK_PLL2_SDHI_533,
	CLK_PLL2_SDHI_400,
	CLK_PLL2_SDHI_266,
	CLK_SD0_DIV4,
	CLK_SD1_DIV4,
	CLK_SEL_GPU2,
	CLK_SEL_PLL5_4,
	CLK_DSI_DIV,
	CLK_PLL2_533,
	CLK_PLL2_533_DIV2,
	CLK_DIV_DSI_LPCLK,

	/* Module Clocks */
	MOD_CLK_BASE,
};

/* Divider tables */
static const struct clk_div_table dtable_1_8[] = {
	{0, 1},
	{1, 2},
	{2, 4},
	{3, 8},
	{0, 0},
};

static const struct clk_div_table dtable_1_32[] = {
	{0, 1},
	{1, 2},
	{2, 4},
	{3, 8},
	{4, 32},
	{0, 0},
};

static const struct clk_div_table dtable_16_128[] = {
	{0, 16},
	{1, 32},
	{2, 64},
	{3, 128},
	{0, 0},
};

/* Mux clock tables */
static const char * const sel_pll3_3[] = { ".pll3_533", ".pll3_400" };
static const char * const sel_pll5_4[] = { ".pll5_foutpostdiv", ".pll5_fout1ph0" };
static const char * const sel_pll6_2[]	= { ".pll6_250", ".pll5_250" };
static const char * const sel_sdhi[] = { ".clk_533", ".clk_400", ".clk_266" };
static const char * const sel_gpu2[] = { ".pll6", ".pll3_div2_2" };

static const u32 mtable_sdhi[] = { 1, 2, 3 };

static const struct {
	struct cpg_core_clk common[56];
#ifdef CONFIG_CLK_R9A07G054
	struct cpg_core_clk drp[0];
#endif
} core_clks __initconst = {
	.common = {
		/* External Clock Inputs */
		DEF_INPUT("extal", CLK_EXTAL),

		/* Internal Core Clocks */
		DEF_FIXED(".osc", R9A07G044_OSCCLK, CLK_EXTAL, 1, 1),
		DEF_FIXED(".osc_div1000", CLK_OSC_DIV1000, CLK_EXTAL, 1, 1000),
		DEF_SAMPLL(".pll1", CLK_PLL1, CLK_EXTAL, PLL146_CONF(0)),
		DEF_FIXED(".pll2", CLK_PLL2, CLK_EXTAL, 200, 3),
		DEF_FIXED(".pll2_533", CLK_PLL2_533, CLK_PLL2, 1, 3),
		DEF_FIXED(".pll3", CLK_PLL3, CLK_EXTAL, 200, 3),
		DEF_FIXED(".pll3_400", CLK_PLL3_400, CLK_PLL3, 1, 4),
		DEF_FIXED(".pll3_533", CLK_PLL3_533, CLK_PLL3, 1, 3),

		DEF_FIXED(".pll5", CLK_PLL5, CLK_EXTAL, 125, 1),
		DEF_FIXED(".pll5_fout3", CLK_PLL5_FOUT3, CLK_PLL5, 1, 6),

		DEF_FIXED(".pll6", CLK_PLL6, CLK_EXTAL, 125, 6),

		DEF_FIXED(".pll2_div2", CLK_PLL2_DIV2, CLK_PLL2, 1, 2),
		DEF_FIXED(".clk_800", CLK_PLL2_800, CLK_PLL2, 1, 2),
		DEF_FIXED(".clk_533", CLK_PLL2_SDHI_533, CLK_PLL2, 1, 3),
		DEF_FIXED(".clk_400", CLK_PLL2_SDHI_400, CLK_PLL2_800, 1, 2),
		DEF_FIXED(".clk_266", CLK_PLL2_SDHI_266, CLK_PLL2_SDHI_533, 1, 2),

		DEF_FIXED(".pll2_div2_8", CLK_PLL2_DIV2_8, CLK_PLL2_DIV2, 1, 8),
		DEF_FIXED(".pll2_div2_10", CLK_PLL2_DIV2_10, CLK_PLL2_DIV2, 1, 10),

		DEF_FIXED(".pll2_533_div2", CLK_PLL2_533_DIV2, CLK_PLL2_533, 1, 2),

		DEF_FIXED(".pll3_div2", CLK_PLL3_DIV2, CLK_PLL3, 1, 2),
		DEF_FIXED(".pll3_div2_2", CLK_PLL3_DIV2_2, CLK_PLL3_DIV2, 1, 2),
		DEF_FIXED(".pll3_div2_4", CLK_PLL3_DIV2_4, CLK_PLL3_DIV2, 1, 4),
		DEF_FIXED(".pll3_div2_4_2", CLK_PLL3_DIV2_4_2, CLK_PLL3_DIV2_4, 1, 2),
		DEF_MUX_RO(".sel_pll3_3", CLK_SEL_PLL3_3, SEL_PLL3_3, sel_pll3_3),
		DEF_DIV("divpl3c", CLK_DIV_PLL3_C, CLK_SEL_PLL3_3, DIVPL3C, dtable_1_32),

		DEF_FIXED(".pll5_250", CLK_PLL5_250, CLK_PLL5_FOUT3, 1, 2),
		DEF_FIXED(".pll6_250", CLK_PLL6_250, CLK_PLL6, 1, 2),
		DEF_MUX_RO(".sel_gpu2", CLK_SEL_GPU2, SEL_GPU2, sel_gpu2),
		DEF_PLL5_FOUTPOSTDIV(".pll5_foutpostdiv", CLK_PLL5_FOUTPOSTDIV, CLK_EXTAL),
		DEF_FIXED(".pll5_fout1ph0", CLK_PLL5_FOUT1PH0, CLK_PLL5_FOUTPOSTDIV, 1, 2),
		DEF_PLL5_4_MUX(".sel_pll5_4", CLK_SEL_PLL5_4, SEL_PLL5_4, sel_pll5_4),
		DEF_DIV(".div_dsi_lpclk", CLK_DIV_DSI_LPCLK, CLK_PLL2_533_DIV2,
			DIVDSILPCLK, dtable_16_128),

		/* Core output clk */
		DEF_DIV("I", R9A07G044_CLK_I, CLK_PLL1, DIVPL1A, dtable_1_8),
		DEF_DIV("P0", R9A07G044_CLK_P0, CLK_PLL2_DIV2_8, DIVPL2A, dtable_1_32),
		DEF_FIXED("P0_DIV2", R9A07G044_CLK_P0_DIV2, R9A07G044_CLK_P0, 1, 2),
		DEF_FIXED("TSU", R9A07G044_CLK_TSU, CLK_PLL2_DIV2_10, 1, 1),
		DEF_DIV("P1", R9A07G044_CLK_P1, CLK_PLL3_DIV2_4, DIVPL3B, dtable_1_32),
		DEF_FIXED("P1_DIV2", CLK_P1_DIV2, R9A07G044_CLK_P1, 1, 2),
		DEF_DIV("P2", R9A07G044_CLK_P2, CLK_PLL3_DIV2_4_2, DIVPL3A, dtable_1_32),
		DEF_FIXED("M0", R9A07G044_CLK_M0, CLK_PLL3_DIV2_4, 1, 1),
		DEF_FIXED("ZT", R9A07G044_CLK_ZT, CLK_PLL3_DIV2_4_2, 1, 1),
		DEF_MUX("HP", R9A07G044_CLK_HP, SEL_PLL6_2, sel_pll6_2),
		DEF_FIXED("SPI0", R9A07G044_CLK_SPI0, CLK_DIV_PLL3_C, 1, 2),
		DEF_FIXED("SPI1", R9A07G044_CLK_SPI1, CLK_DIV_PLL3_C, 1, 4),
		DEF_SD_MUX("SD0", R9A07G044_CLK_SD0, SEL_SDHI0, SEL_SDHI0_STS, sel_sdhi,
			   mtable_sdhi, 0, rzg2l_cpg_sd_clk_mux_notifier),
		DEF_SD_MUX("SD1", R9A07G044_CLK_SD1, SEL_SDHI1, SEL_SDHI1_STS, sel_sdhi,
			   mtable_sdhi, 0, rzg2l_cpg_sd_clk_mux_notifier),
		DEF_FIXED("SD0_DIV4", CLK_SD0_DIV4, R9A07G044_CLK_SD0, 1, 4),
		DEF_FIXED("SD1_DIV4", CLK_SD1_DIV4, R9A07G044_CLK_SD1, 1, 4),
		DEF_DIV("G", R9A07G044_CLK_G, CLK_SEL_GPU2, DIVGPU, dtable_1_8),
		DEF_FIXED("M1", R9A07G044_CLK_M1, CLK_PLL5_FOUTPOSTDIV, 1, 1),
		DEF_FIXED("M2", R9A07G044_CLK_M2, CLK_PLL3_533, 1, 2),
		DEF_FIXED("M2_DIV2", CLK_M2_DIV2, R9A07G044_CLK_M2, 1, 2),
		DEF_DSI_DIV("DSI_DIV", CLK_DSI_DIV, CLK_SEL_PLL5_4, CLK_SET_RATE_PARENT),
		DEF_FIXED("M3", R9A07G044_CLK_M3, CLK_DSI_DIV, 1, 1),
		DEF_FIXED("M4", R9A07G044_CLK_M4, CLK_DIV_DSI_LPCLK, 1, 1),
	},
#ifdef CONFIG_CLK_R9A07G054
	.drp = {
	},
#endif
};

static const struct {
	struct rzg2l_mod_clk common[76];
#ifdef CONFIG_CLK_R9A07G054
	struct rzg2l_mod_clk drp[0];
#endif
} mod_clks = {
	.common = {
		DEF_MOD("gic",		R9A07G044_GIC600_GICCLK, R9A07G044_CLK_P1,
					0x514, 0),
		DEF_MOD("ia55_pclk",	R9A07G044_IA55_PCLK, R9A07G044_CLK_P2,
					0x518, 0),
		DEF_MOD("ia55_clk",	R9A07G044_IA55_CLK, R9A07G044_CLK_P1,
					0x518, 1),
		DEF_MOD("dmac_aclk",	R9A07G044_DMAC_ACLK, R9A07G044_CLK_P1,
					0x52c, 0),
		DEF_MOD("dmac_pclk",	R9A07G044_DMAC_PCLK, CLK_P1_DIV2,
					0x52c, 1),
		DEF_MOD("ostm0_pclk",	R9A07G044_OSTM0_PCLK, R9A07G044_CLK_P0,
					0x534, 0),
		DEF_MOD("ostm1_pclk",	R9A07G044_OSTM1_PCLK, R9A07G044_CLK_P0,
					0x534, 1),
		DEF_MOD("ostm2_pclk",	R9A07G044_OSTM2_PCLK, R9A07G044_CLK_P0,
					0x534, 2),
		DEF_MOD("gpt_pclk",	R9A07G044_GPT_PCLK, R9A07G044_CLK_P0,
					0x540, 0),
		DEF_MOD("poeg_a_clkp",	R9A07G044_POEG_A_CLKP, R9A07G044_CLK_P0,
					0x544, 0),
		DEF_MOD("poeg_b_clkp",	R9A07G044_POEG_B_CLKP, R9A07G044_CLK_P0,
					0x544, 1),
		DEF_MOD("poeg_c_clkp",	R9A07G044_POEG_C_CLKP, R9A07G044_CLK_P0,
					0x544, 2),
		DEF_MOD("poeg_d_clkp",	R9A07G044_POEG_D_CLKP, R9A07G044_CLK_P0,
					0x544, 3),
		DEF_MOD("wdt0_pclk",	R9A07G044_WDT0_PCLK, R9A07G044_CLK_P0,
					0x548, 0),
		DEF_MOD("wdt0_clk",	R9A07G044_WDT0_CLK, R9A07G044_OSCCLK,
					0x548, 1),
		DEF_MOD("wdt1_pclk",	R9A07G044_WDT1_PCLK, R9A07G044_CLK_P0,
					0x548, 2),
		DEF_MOD("wdt1_clk",	R9A07G044_WDT1_CLK, R9A07G044_OSCCLK,
					0x548, 3),
		DEF_MOD("wdt2_pclk",	R9A07G044_WDT2_PCLK, R9A07G044_CLK_P0,
					0x548, 4),
		DEF_MOD("wdt2_clk",	R9A07G044_WDT2_CLK, R9A07G044_OSCCLK,
					0x548, 5),
		DEF_MOD("spi_clk2",	R9A07G044_SPI_CLK2, R9A07G044_CLK_SPI1,
					0x550, 0),
		DEF_MOD("spi_clk",	R9A07G044_SPI_CLK, R9A07G044_CLK_SPI0,
					0x550, 1),
		DEF_MOD("sdhi0_imclk",	R9A07G044_SDHI0_IMCLK, CLK_SD0_DIV4,
					0x554, 0),
		DEF_MOD("sdhi0_imclk2",	R9A07G044_SDHI0_IMCLK2, CLK_SD0_DIV4,
					0x554, 1),
		DEF_MOD("sdhi0_clk_hs",	R9A07G044_SDHI0_CLK_HS, R9A07G044_CLK_SD0,
					0x554, 2),
		DEF_MOD("sdhi0_aclk",	R9A07G044_SDHI0_ACLK, R9A07G044_CLK_P1,
					0x554, 3),
		DEF_MOD("sdhi1_imclk",	R9A07G044_SDHI1_IMCLK, CLK_SD1_DIV4,
					0x554, 4),
		DEF_MOD("sdhi1_imclk2",	R9A07G044_SDHI1_IMCLK2, CLK_SD1_DIV4,
					0x554, 5),
		DEF_MOD("sdhi1_clk_hs",	R9A07G044_SDHI1_CLK_HS, R9A07G044_CLK_SD1,
					0x554, 6),
		DEF_MOD("sdhi1_aclk",	R9A07G044_SDHI1_ACLK, R9A07G044_CLK_P1,
					0x554, 7),
		DEF_MOD("gpu_clk",	R9A07G044_GPU_CLK, R9A07G044_CLK_G,
					0x558, 0),
		DEF_MOD("gpu_axi_clk",	R9A07G044_GPU_AXI_CLK, R9A07G044_CLK_P1,
					0x558, 1),
		DEF_MOD("gpu_ace_clk",	R9A07G044_GPU_ACE_CLK, R9A07G044_CLK_P1,
					0x558, 2),
		DEF_MOD("dsi_pll_clk",	R9A07G044_MIPI_DSI_PLLCLK, R9A07G044_CLK_M1,
					0x568, 0),
		DEF_MOD("dsi_sys_clk",	R9A07G044_MIPI_DSI_SYSCLK, CLK_M2_DIV2,
					0x568, 1),
		DEF_MOD("dsi_aclk",	R9A07G044_MIPI_DSI_ACLK, R9A07G044_CLK_P1,
					0x568, 2),
		DEF_MOD("dsi_pclk",	R9A07G044_MIPI_DSI_PCLK, R9A07G044_CLK_P2,
					0x568, 3),
		DEF_MOD("dsi_vclk",	R9A07G044_MIPI_DSI_VCLK, R9A07G044_CLK_M3,
					0x568, 4),
		DEF_MOD("dsi_lpclk",	R9A07G044_MIPI_DSI_LPCLK, R9A07G044_CLK_M4,
					0x568, 5),
		DEF_COUPLED("lcdc_a",	R9A07G044_LCDC_CLK_A, R9A07G044_CLK_M0,
					0x56c, 0),
		DEF_COUPLED("lcdc_p",	R9A07G044_LCDC_CLK_P, R9A07G044_CLK_ZT,
					0x56c, 0),
		DEF_MOD("lcdc_clk_d",	R9A07G044_LCDC_CLK_D, R9A07G044_CLK_M3,
					0x56c, 1),
		DEF_MOD("ssi0_pclk",	R9A07G044_SSI0_PCLK2, R9A07G044_CLK_P0,
					0x570, 0),
		DEF_MOD("ssi0_sfr",	R9A07G044_SSI0_PCLK_SFR, R9A07G044_CLK_P0,
					0x570, 1),
		DEF_MOD("ssi1_pclk",	R9A07G044_SSI1_PCLK2, R9A07G044_CLK_P0,
					0x570, 2),
		DEF_MOD("ssi1_sfr",	R9A07G044_SSI1_PCLK_SFR, R9A07G044_CLK_P0,
					0x570, 3),
		DEF_MOD("ssi2_pclk",	R9A07G044_SSI2_PCLK2, R9A07G044_CLK_P0,
					0x570, 4),
		DEF_MOD("ssi2_sfr",	R9A07G044_SSI2_PCLK_SFR, R9A07G044_CLK_P0,
					0x570, 5),
		DEF_MOD("ssi3_pclk",	R9A07G044_SSI3_PCLK2, R9A07G044_CLK_P0,
					0x570, 6),
		DEF_MOD("ssi3_sfr",	R9A07G044_SSI3_PCLK_SFR, R9A07G044_CLK_P0,
					0x570, 7),
		DEF_MOD("usb0_host",	R9A07G044_USB_U2H0_HCLK, R9A07G044_CLK_P1,
					0x578, 0),
		DEF_MOD("usb1_host",	R9A07G044_USB_U2H1_HCLK, R9A07G044_CLK_P1,
					0x578, 1),
		DEF_MOD("usb0_func",	R9A07G044_USB_U2P_EXR_CPUCLK, R9A07G044_CLK_P1,
					0x578, 2),
		DEF_MOD("usb_pclk",	R9A07G044_USB_PCLK, R9A07G044_CLK_P1,
					0x578, 3),
		DEF_COUPLED("eth0_axi",	R9A07G044_ETH0_CLK_AXI, R9A07G044_CLK_M0,
					0x57c, 0),
		DEF_COUPLED("eth0_chi",	R9A07G044_ETH0_CLK_CHI, R9A07G044_CLK_ZT,
					0x57c, 0),
		DEF_COUPLED("eth1_axi",	R9A07G044_ETH1_CLK_AXI, R9A07G044_CLK_M0,
					0x57c, 1),
		DEF_COUPLED("eth1_chi",	R9A07G044_ETH1_CLK_CHI, R9A07G044_CLK_ZT,
					0x57c, 1),
		DEF_MOD("i2c0",		R9A07G044_I2C0_PCLK, R9A07G044_CLK_P0,
					0x580, 0),
		DEF_MOD("i2c1",		R9A07G044_I2C1_PCLK, R9A07G044_CLK_P0,
					0x580, 1),
		DEF_MOD("i2c2",		R9A07G044_I2C2_PCLK, R9A07G044_CLK_P0,
					0x580, 2),
		DEF_MOD("i2c3",		R9A07G044_I2C3_PCLK, R9A07G044_CLK_P0,
					0x580, 3),
		DEF_MOD("scif0",	R9A07G044_SCIF0_CLK_PCK, R9A07G044_CLK_P0,
					0x584, 0),
		DEF_MOD("scif1",	R9A07G044_SCIF1_CLK_PCK, R9A07G044_CLK_P0,
					0x584, 1),
		DEF_MOD("scif2",	R9A07G044_SCIF2_CLK_PCK, R9A07G044_CLK_P0,
					0x584, 2),
		DEF_MOD("scif3",	R9A07G044_SCIF3_CLK_PCK, R9A07G044_CLK_P0,
					0x584, 3),
		DEF_MOD("scif4",	R9A07G044_SCIF4_CLK_PCK, R9A07G044_CLK_P0,
					0x584, 4),
		DEF_MOD("sci0",		R9A07G044_SCI0_CLKP, R9A07G044_CLK_P0,
					0x588, 0),
		DEF_MOD("sci1",		R9A07G044_SCI1_CLKP, R9A07G044_CLK_P0,
					0x588, 1),
		DEF_MOD("rspi0",	R9A07G044_RSPI0_CLKB, R9A07G044_CLK_P0,
					0x590, 0),
		DEF_MOD("rspi1",	R9A07G044_RSPI1_CLKB, R9A07G044_CLK_P0,
					0x590, 1),
		DEF_MOD("rspi2",	R9A07G044_RSPI2_CLKB, R9A07G044_CLK_P0,
					0x590, 2),
		DEF_MOD("canfd",	R9A07G044_CANFD_PCLK, R9A07G044_CLK_P0,
					0x594, 0),
		DEF_MOD("gpio",		R9A07G044_GPIO_HCLK, R9A07G044_OSCCLK,
					0x598, 0),
		DEF_MOD("adc_adclk",	R9A07G044_ADC_ADCLK, R9A07G044_CLK_TSU,
					0x5a8, 0),
		DEF_MOD("adc_pclk",	R9A07G044_ADC_PCLK, R9A07G044_CLK_P0,
					0x5a8, 1),
		DEF_MOD("tsu_pclk",	R9A07G044_TSU_PCLK, R9A07G044_CLK_TSU,
					0x5ac, 0),
	},
#ifdef CONFIG_CLK_R9A07G054
	.drp = {
	},
#endif
};

static struct rzg2l_reset r9a07g044_resets[] = {
	DEF_RST(R9A07G044_GIC600_GICRESET_N, 0x814, 0),
	DEF_RST(R9A07G044_GIC600_DBG_GICRESET_N, 0x814, 1),
	DEF_RST(R9A07G044_IA55_RESETN, 0x818, 0),
	DEF_RST(R9A07G044_DMAC_ARESETN, 0x82c, 0),
	DEF_RST(R9A07G044_DMAC_RST_ASYNC, 0x82c, 1),
	DEF_RST(R9A07G044_OSTM0_PRESETZ, 0x834, 0),
	DEF_RST(R9A07G044_OSTM1_PRESETZ, 0x834, 1),
	DEF_RST(R9A07G044_OSTM2_PRESETZ, 0x834, 2),
	DEF_RST(R9A07G044_GPT_RST_C, 0x840, 0),
	DEF_RST(R9A07G044_POEG_A_RST, 0x844, 0),
	DEF_RST(R9A07G044_POEG_B_RST, 0x844, 1),
	DEF_RST(R9A07G044_POEG_C_RST, 0x844, 2),
	DEF_RST(R9A07G044_POEG_D_RST, 0x844, 3),
	DEF_RST(R9A07G044_WDT0_PRESETN, 0x848, 0),
	DEF_RST(R9A07G044_WDT1_PRESETN, 0x848, 1),
	DEF_RST(R9A07G044_WDT2_PRESETN, 0x848, 2),
	DEF_RST(R9A07G044_SPI_RST, 0x850, 0),
	DEF_RST(R9A07G044_SDHI0_IXRST, 0x854, 0),
	DEF_RST(R9A07G044_SDHI1_IXRST, 0x854, 1),
	DEF_RST(R9A07G044_GPU_RESETN, 0x858, 0),
	DEF_RST(R9A07G044_GPU_AXI_RESETN, 0x858, 1),
	DEF_RST(R9A07G044_GPU_ACE_RESETN, 0x858, 2),
	DEF_RST(R9A07G044_MIPI_DSI_CMN_RSTB, 0x868, 0),
	DEF_RST(R9A07G044_MIPI_DSI_ARESET_N, 0x868, 1),
	DEF_RST(R9A07G044_MIPI_DSI_PRESET_N, 0x868, 2),
	DEF_RST(R9A07G044_LCDC_RESET_N, 0x86c, 0),
	DEF_RST(R9A07G044_SSI0_RST_M2_REG, 0x870, 0),
	DEF_RST(R9A07G044_SSI1_RST_M2_REG, 0x870, 1),
	DEF_RST(R9A07G044_SSI2_RST_M2_REG, 0x870, 2),
	DEF_RST(R9A07G044_SSI3_RST_M2_REG, 0x870, 3),
	DEF_RST(R9A07G044_USB_U2H0_HRESETN, 0x878, 0),
	DEF_RST(R9A07G044_USB_U2H1_HRESETN, 0x878, 1),
	DEF_RST(R9A07G044_USB_U2P_EXL_SYSRST, 0x878, 2),
	DEF_RST(R9A07G044_USB_PRESETN, 0x878, 3),
	DEF_RST(R9A07G044_ETH0_RST_HW_N, 0x87c, 0),
	DEF_RST(R9A07G044_ETH1_RST_HW_N, 0x87c, 1),
	DEF_RST(R9A07G044_I2C0_MRST, 0x880, 0),
	DEF_RST(R9A07G044_I2C1_MRST, 0x880, 1),
	DEF_RST(R9A07G044_I2C2_MRST, 0x880, 2),
	DEF_RST(R9A07G044_I2C3_MRST, 0x880, 3),
	DEF_RST(R9A07G044_SCIF0_RST_SYSTEM_N, 0x884, 0),
	DEF_RST(R9A07G044_SCIF1_RST_SYSTEM_N, 0x884, 1),
	DEF_RST(R9A07G044_SCIF2_RST_SYSTEM_N, 0x884, 2),
	DEF_RST(R9A07G044_SCIF3_RST_SYSTEM_N, 0x884, 3),
	DEF_RST(R9A07G044_SCIF4_RST_SYSTEM_N, 0x884, 4),
	DEF_RST(R9A07G044_SCI0_RST, 0x888, 0),
	DEF_RST(R9A07G044_SCI1_RST, 0x888, 1),
	DEF_RST(R9A07G044_RSPI0_RST, 0x890, 0),
	DEF_RST(R9A07G044_RSPI1_RST, 0x890, 1),
	DEF_RST(R9A07G044_RSPI2_RST, 0x890, 2),
	DEF_RST(R9A07G044_CANFD_RSTP_N, 0x894, 0),
	DEF_RST(R9A07G044_CANFD_RSTC_N, 0x894, 1),
	DEF_RST(R9A07G044_GPIO_RSTN, 0x898, 0),
	DEF_RST(R9A07G044_GPIO_PORT_RESETN, 0x898, 1),
	DEF_RST(R9A07G044_GPIO_SPARE_RESETN, 0x898, 2),
	DEF_RST(R9A07G044_ADC_PRESETN, 0x8a8, 0),
	DEF_RST(R9A07G044_ADC_ADRST_N, 0x8a8, 1),
	DEF_RST(R9A07G044_TSU_PRESETN, 0x8ac, 0),
};

static const unsigned int r9a07g044_crit_mod_clks[] __initconst = {
	MOD_CLK_BASE + R9A07G044_GIC600_GICCLK,
	MOD_CLK_BASE + R9A07G044_IA55_CLK,
	MOD_CLK_BASE + R9A07G044_DMAC_ACLK,
};

#ifdef CONFIG_CLK_R9A07G044
const struct rzg2l_cpg_info r9a07g044_cpg_info = {
	/* Core Clocks */
	.core_clks = core_clks.common,
	.num_core_clks = ARRAY_SIZE(core_clks.common),
	.last_dt_core_clk = LAST_DT_CORE_CLK,
	.num_total_core_clks = MOD_CLK_BASE,

	/* Critical Module Clocks */
	.crit_mod_clks = r9a07g044_crit_mod_clks,
	.num_crit_mod_clks = ARRAY_SIZE(r9a07g044_crit_mod_clks),

	/* Module Clocks */
	.mod_clks = mod_clks.common,
	.num_mod_clks = ARRAY_SIZE(mod_clks.common),
	.num_hw_mod_clks = R9A07G044_TSU_PCLK + 1,

	/* Resets */
	.resets = r9a07g044_resets,
	.num_resets = R9A07G044_TSU_PRESETN + 1, /* Last reset ID + 1 */

	.has_clk_mon_regs = true,
};
#endif

#ifdef CONFIG_CLK_R9A07G054
const struct rzg2l_cpg_info r9a07g054_cpg_info = {
	/* Core Clocks */
	.core_clks = core_clks.common,
	.num_core_clks = ARRAY_SIZE(core_clks.common) + ARRAY_SIZE(core_clks.drp),
	.last_dt_core_clk = LAST_DT_CORE_CLK,
	.num_total_core_clks = MOD_CLK_BASE,

	/* Critical Module Clocks */
	.crit_mod_clks = r9a07g044_crit_mod_clks,
	.num_crit_mod_clks = ARRAY_SIZE(r9a07g044_crit_mod_clks),

	/* Module Clocks */
	.mod_clks = mod_clks.common,
	.num_mod_clks = ARRAY_SIZE(mod_clks.common) + ARRAY_SIZE(mod_clks.drp),
	.num_hw_mod_clks = R9A07G054_STPAI_ACLK_DRP + 1,

	/* Resets */
	.resets = r9a07g044_resets,
	.num_resets = R9A07G054_STPAI_ARESETN + 1, /* Last reset ID + 1 */

	.has_clk_mon_regs = true,
};
#endif
