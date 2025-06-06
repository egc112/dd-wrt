/*-
 * Copyright (c) 2002-2008 Sam Leffler, Errno Consulting, Atheros
 * Communications, Inc.  All rights reserved.
 *
 * Redistribution and use in source and binary forms are permitted
 * provided that the following conditions are met:
 * 1. The materials contained herein are unmodified and are used
 *    unmodified.
 * 2. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following NO
 *    ''WARRANTY'' disclaimer below (''Disclaimer''), without
 *    modification.
 * 3. Redistributions in binary form must reproduce at minimum a
 *    disclaimer similar to the Disclaimer below and any redistribution
 *    must be conditioned upon including a substantially similar
 *    Disclaimer requirement for further binary redistribution.
 * 4. Neither the names of the above-listed copyright holders nor the
 *    names of any contributors may be used to endorse or promote
 *    product derived from this software without specific prior written
 *    permission.
 *
 * NO WARRANTY
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 * ''AS IS'' AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 * LIMITED TO, THE IMPLIED WARRANTIES OF NONINFRINGEMENT,
 * MERCHANTIBILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED.
 * IN NO EVENT SHALL THE COPYRIGHT HOLDERS OR CONTRIBUTORS BE LIABLE
 * FOR SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
 * LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF
 * USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
 * ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
 * OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT
 * OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
 * SUCH DAMAGES.
 *
 * $Id: //depot/sw/branches/sam_hal/ah_desc.h#8 $
 */

#ifndef _DEV_ATH_DESC_H
#define _DEV_ATH_DESC_H

#include "opt_ah.h"		/* NB: required for AH_SUPPORT_AR5416 */

/*
 * Transmit descriptor status.  This structure is filled
 * in only after the tx descriptor process method finds a
 * ``done'' descriptor; at which point it returns something
 * other than HAL_EINPROGRESS.
 *
 * Note that ts_antenna may not be valid for all h/w.  It
 * should be used only if non-zero.
 */
struct ath_tx_status {
	u_int16_t	ts_seqnum;	/* h/w assigned sequence number */
	u_int16_t	ts_tstamp;	/* h/w assigned timestamp */
	u_int8_t	ts_status;	/* frame status, 0 => xmit ok */
	u_int8_t	ts_rate;	/* h/w transmit rate index */
#define	HAL_TXSTAT_ALTRATE	0x80	/* alternate xmit rate used */
	int8_t		ts_rssi;	/* tx ack RSSI */
	u_int8_t	ts_shortretry;	/* # short retries */
	u_int8_t	ts_longretry;	/* # long retries */
	u_int8_t	ts_virtcol;	/* virtual collision count */
	u_int8_t	ts_antenna;	/* antenna information */
	u_int8_t	ts_finaltsi;	/* final transmit series index */
#ifdef AH_SUPPORT_AR5416
					/* 802.11n status */
	u_int8_t    	ts_flags;   	/* misc flags */
	int8_t      	ts_rssi_ctl[3];	/* tx ack RSSI [ctl, chain 0-2] */
	int8_t      	ts_rssi_ext[3];	/* tx ack RSSI [ext, chain 0-2] */
/* #define ts_rssi ts_rssi_combined */
	u_int32_t   	ts_ba_low;	/* blockack bitmap low */
	u_int32_t   	ts_ba_high;	/* blockack bitmap high */
	u_int32_t  	ts_evm0;	/* evm bytes */
	u_int32_t   	ts_evm1;
	u_int32_t   	ts_evm2;
#endif /* AH_SUPPORT_AR5416 */
};

/* bits found in ts_status */
#define	HAL_TXERR_XRETRY	0x01	/* excessive retries */
#define	HAL_TXERR_FILT		0x02	/* blocked by tx filtering */
#define	HAL_TXERR_FIFO		0x04	/* fifo underrun */
#define	HAL_TXERR_XTXOP		0x08	/* txop exceeded */
#define	HAL_TXERR_DESC_CFG_ERR	0x10	/* Error in 20/40 desc config */
#define	HAL_TXERR_DATA_UNDERRUN	0x20	/* Tx buffer underrun */
#define	HAL_TXERR_DELIM_UNDERRUN 0x40	/* Tx delimiter underrun */

/* bits found in ts_flags */
#define	HAL_TX_BA		0x01	/* Block Ack seen */
#define	HAL_TX_AGGR		0x02	/* Aggregate */

/*
 * Receive descriptor status.  This structure is filled
 * in only after the rx descriptor process method finds a
 * ``done'' descriptor; at which point it returns something
 * other than HAL_EINPROGRESS.
 *
 * If rx_status is zero, then the frame was received ok;
 * otherwise the error information is indicated and rs_phyerr
 * contains a phy error code if HAL_RXERR_PHY is set.  In general
 * the frame contents is undefined when an error occurred thought
 * for some errors (e.g. a decryption error), it may be meaningful.
 *
 * Note that the receive timestamp is expanded using the TSF to
 * at least 15 bits (regardless of what the h/w provides directly).
 * Newer hardware supports a full 32-bits; use HAL_CAP_32TSTAMP to
 * find out if the hardware is capable.
 *
 * rx_rssi is in units of dbm above the noise floor.  This value
 * is measured during the preamble and PLCP; i.e. with the initial
 * 4us of detection.  The noise floor is typically a consistent
 * -96dBm absolute power in a 20MHz channel.
 */
struct ath_rx_status {
	u_int16_t	rs_datalen;	/* rx frame length */
	u_int8_t	rs_status;	/* rx status, 0 => recv ok */
	u_int8_t	rs_phyerr;	/* phy error code */
	int8_t		rs_rssi;	/* rx frame RSSI (combined for 11n) */
	u_int8_t	rs_keyix;	/* key cache index */
	u_int8_t	rs_rate;	/* h/w receive rate index */
	u_int8_t	rs_more;	/* more descriptors follow */
	u_int32_t	rs_tstamp;	/* h/w assigned timestamp */
	u_int32_t	rs_antenna;	/* antenna information */
#ifdef AH_SUPPORT_AR5416
					/* 802.11n status */
	int8_t		rs_rssi_ctl[3];	/* rx frame RSSI [ctl, chain 0-2] */
	int8_t		rs_rssi_ext[3];	/* rx frame RSSI [ext, chain 0-2] */
	u_int8_t	rs_isaggr;	/* is part of the aggregate */
	u_int8_t	rs_moreaggr;	/* more frames in aggr to follow */
	u_int8_t	rs_num_delims;	/* number of delims in aggr */
	u_int8_t	rs_flags;	/* misc flags */
	u_int32_t	rs_evm0;	/* evm bytes */
	u_int32_t	rs_evm1;
	u_int32_t	rs_evm2;	
#endif /* AH_SUPPORT_AR5416 */
};

/* bits found in rs_status */
#define	HAL_RXERR_CRC		0x01	/* CRC error on frame */
#define	HAL_RXERR_PHY		0x02	/* PHY error, rs_phyerr is valid */
#define	HAL_RXERR_FIFO		0x04	/* fifo overrun */
#define	HAL_RXERR_DECRYPT	0x08	/* non-Michael decrypt error */
#define	HAL_RXERR_MIC		0x10	/* Michael MIC decrypt error */

/* bits found in rs_flags */
#define	HAL_RX_MORE		0x01	/* more descriptors follow */
#define	HAL_RX_MORE_AGGR	0x02	/* more frames in aggr */
#define	HAL_RX_GI		0x04	/* full gi */
#define	HAL_RX_2040		0x08	/* 40 MHz */
#define	HAL_RX_DELIM_CRC_PRE	0x10	/* crc error in delimiter pre */
#define	HAL_RX_DELIM_CRC_POST	0x20	/* crc error in delim after */
#define	HAL_RX_DECRYPT_BUSY	0x40	/* decrypt was too slow */
#define	HAL_RX_DUP_FRAME	0x80	/* Dup frame rx'd on control channel */

enum {
	HAL_PHYERR_UNDERRUN		= 0,	/* Transmit underrun */
	HAL_PHYERR_TIMING		= 1,	/* Timing error */
	HAL_PHYERR_PARITY		= 2,	/* Illegal parity */
	HAL_PHYERR_RATE			= 3,	/* Illegal rate */
	HAL_PHYERR_LENGTH		= 4,	/* Illegal length */
	HAL_PHYERR_RADAR		= 5,	/* Radar detect */
	HAL_PHYERR_SERVICE		= 6,	/* Illegal service */
	HAL_PHYERR_TOR			= 7,	/* Transmit override receive */
	/* NB: these are specific to the 5212 */
	HAL_PHYERR_OFDM_TIMING		= 17,	/* */
	HAL_PHYERR_OFDM_SIGNAL_PARITY	= 18,	/* */
	HAL_PHYERR_OFDM_RATE_ILLEGAL	= 19,	/* */
	HAL_PHYERR_OFDM_LENGTH_ILLEGAL	= 20,	/* */
	HAL_PHYERR_OFDM_POWER_DROP	= 21,	/* */
	HAL_PHYERR_OFDM_SERVICE		= 22,	/* */
	HAL_PHYERR_OFDM_RESTART		= 23,	/* */
	HAL_PHYERR_CCK_TIMING		= 25,	/* */
	HAL_PHYERR_CCK_HEADER_CRC	= 26,	/* */
	HAL_PHYERR_CCK_RATE_ILLEGAL	= 27,	/* */
	HAL_PHYERR_CCK_SERVICE		= 30,	/* */
	HAL_PHYERR_CCK_RESTART		= 31,	/* */
};

/* value found in rs_keyix to mark invalid entries */
#define	HAL_RXKEYIX_INVALID	((u_int8_t) -1)
/* value used to specify no encryption key for xmit */
#define	HAL_TXKEYIX_INVALID	((u_int) -1)

/* XXX rs_antenna definitions */

/*
 * Definitions for the software frame/packet descriptors used by
 * the Atheros HAL.  This definition obscures hardware-specific
 * details from the driver.  Drivers are expected to fillin the
 * portions of a descriptor that are not opaque then use HAL calls
 * to complete the work.  Status for completed frames is returned
 * in a device-independent format.
 */
#ifdef AH_SUPPORT_AR5416
#define	HAL_DESC_HW_SIZE	20
#else
#define	HAL_DESC_HW_SIZE	4
#endif /* AH_SUPPORT_AR5416 */

struct ath_desc {
	/*
	 * The following definitions are passed directly
	 * the hardware and managed by the HAL.  Drivers
	 * should not touch those elements marked opaque.
	 */
	u_int32_t	ds_link;	/* phys address of next descriptor */
	u_int32_t	ds_data;	/* phys address of data buffer */
	u_int32_t	ds_ctl0;	/* opaque DMA control 0 */
	u_int32_t	ds_ctl1;	/* opaque DMA control 1 */
	u_int32_t	ds_hw[HAL_DESC_HW_SIZE];	/* opaque h/w region */
};

struct ath_desc_status {
	union {
		struct ath_tx_status tx;/* xmit status */
		struct ath_rx_status rx;/* recv status */
	} ds_us;
};

#define	ds_txstat	ds_us.tx
#define	ds_rxstat	ds_us.rx

/* flags passed to tx descriptor setup methods */
#define	HAL_TXDESC_CLRDMASK	0x0001	/* clear destination filter mask */
#define	HAL_TXDESC_NOACK	0x0002	/* don't wait for ACK */
#define	HAL_TXDESC_RTSENA	0x0004	/* enable RTS */
#define	HAL_TXDESC_CTSENA	0x0008	/* enable CTS */
#define	HAL_TXDESC_INTREQ	0x0010	/* enable per-descriptor interrupt */
#define	HAL_TXDESC_VEOL		0x0020	/* mark virtual EOL */
/* NB: this only affects frame, not any RTS/CTS */
#define	HAL_TXDESC_DURENA	0x0040	/* enable h/w write of duration field */
#define	HAL_TXDESC_EXT_ONLY	0x0080	/* send on ext channel only (11n) */
#define	HAL_TXDESC_EXT_AND_CTL	0x0100	/* send on ext + ctl channels (11n) */
#define	HAL_TXDESC_VMF		0x0200	/* virtual more frag */

/* flags passed to rx descriptor setup methods */
#define	HAL_RXDESC_INTREQ	0x0020	/* enable per-descriptor interrupt */
#endif /* _DEV_ATH_DESC_H */
