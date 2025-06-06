/*
 * Copyright (c) 2012, The Linux Foundation. All rights reserved.
 * Copyright (c) 2023 Qualcomm Innovation Center, Inc. All rights reserved.
 *
 * Permission to use, copy, modify, and/or distribute this software for any
 * purpose with or without fee is hereby granted, provided that the above
 * copyright notice and this permission notice appear in all copies.
 *
 * THE SOFTWARE IS PROVIDED "AS IS" AND THE AUTHOR DISCLAIMS ALL WARRANTIES
 * WITH REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED WARRANTIES OF
 * MERCHANTABILITY AND FITNESS. IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR
 * ANY SPECIAL, DIRECT, INDIRECT, OR CONSEQUENTIAL DAMAGES OR ANY DAMAGES
 * WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR PROFITS, WHETHER IN AN
 * ACTION OF CONTRACT, NEGLIGENCE OR OTHER TORTIOUS ACTION, ARISING OUT OF
 * OR IN CONNECTION WITH THE USE OR PERFORMANCE OF THIS SOFTWARE.
 */

#ifndef _ISISC_PORT_CTRL_H_
#define _ISISC_PORT_CTRL_H_

#ifdef __cplusplus
extern "C" {
#endif                          /* __cplusplus */

#include "fal/fal_port_ctrl.h"

    sw_error_t isisc_port_ctrl_init(a_uint32_t dev_id);

#ifdef IN_PORTCONTROL
#define ISISC_PORT_CTRL_INIT(rv, dev_id) \
    { \
        rv = isisc_port_ctrl_init(dev_id); \
        SW_RTN_ON_ERROR(rv); \
    }
#else
#define ISISC_PORT_CTRL_INIT(rv, dev_id)
#endif

#ifdef HSL_STANDALONG


    HSL_LOCAL sw_error_t
    isisc_port_duplex_set(a_uint32_t dev_id, fal_port_t port_id,
                         fal_port_duplex_t duplex);


    HSL_LOCAL sw_error_t
    isisc_port_duplex_get(a_uint32_t dev_id, fal_port_t port_id,
                         fal_port_duplex_t * pduplex);


    HSL_LOCAL sw_error_t
    isisc_port_speed_set(a_uint32_t dev_id, fal_port_t port_id,
                        fal_port_speed_t speed);


    HSL_LOCAL sw_error_t
    isisc_port_speed_get(a_uint32_t dev_id, fal_port_t port_id,
                        fal_port_speed_t * pspeed);


    HSL_LOCAL sw_error_t
    isisc_port_flowctrl_set(a_uint32_t dev_id, fal_port_t port_id,
                           a_bool_t enable);


    HSL_LOCAL sw_error_t
    isisc_port_flowctrl_get(a_uint32_t dev_id, fal_port_t port_id,
                           a_bool_t * enable);


    HSL_LOCAL sw_error_t
    isisc_port_flowctrl_forcemode_set(a_uint32_t dev_id,
                                     fal_port_t port_id, a_bool_t enable);


    HSL_LOCAL sw_error_t
    isisc_port_flowctrl_forcemode_get(a_uint32_t dev_id,
                                     fal_port_t port_id,
                                     a_bool_t * enable);


    HSL_LOCAL sw_error_t
    isisc_port_rxhdr_mode_set(a_uint32_t dev_id, fal_port_t port_id,
                             fal_port_header_mode_t mode);


    HSL_LOCAL sw_error_t
    isisc_port_rxhdr_mode_get(a_uint32_t dev_id, fal_port_t port_id,
                             fal_port_header_mode_t * mode);


    HSL_LOCAL sw_error_t
    isisc_port_txhdr_mode_set(a_uint32_t dev_id, fal_port_t port_id,
                             fal_port_header_mode_t mode);


    HSL_LOCAL sw_error_t
    isisc_port_txhdr_mode_get(a_uint32_t dev_id, fal_port_t port_id,
                             fal_port_header_mode_t * mode);


    HSL_LOCAL sw_error_t
    isisc_header_type_set(a_uint32_t dev_id, a_bool_t enable, a_uint32_t type);


    HSL_LOCAL sw_error_t
    isisc_header_type_get(a_uint32_t dev_id, a_bool_t * enable, a_uint32_t * type);


    HSL_LOCAL sw_error_t
    isisc_port_txmac_status_set(a_uint32_t dev_id, fal_port_t port_id, a_bool_t enable);


    HSL_LOCAL sw_error_t
    isisc_port_txmac_status_get(a_uint32_t dev_id, fal_port_t port_id, a_bool_t * enable);


    HSL_LOCAL sw_error_t
    isisc_port_rxmac_status_set(a_uint32_t dev_id, fal_port_t port_id, a_bool_t enable);


    HSL_LOCAL sw_error_t
    isisc_port_rxmac_status_get(a_uint32_t dev_id, fal_port_t port_id, a_bool_t * enable);


    HSL_LOCAL sw_error_t
    isisc_port_txfc_status_set(a_uint32_t dev_id, fal_port_t port_id, a_bool_t enable);


    HSL_LOCAL sw_error_t
    isisc_port_txfc_status_get(a_uint32_t dev_id, fal_port_t port_id, a_bool_t * enable);


    HSL_LOCAL sw_error_t
    isisc_port_rxfc_status_set(a_uint32_t dev_id, fal_port_t port_id, a_bool_t enable);


    HSL_LOCAL sw_error_t
    isisc_port_rxfc_status_get(a_uint32_t dev_id, fal_port_t port_id, a_bool_t * enable);


    HSL_LOCAL sw_error_t
    isisc_port_bp_status_set(a_uint32_t dev_id, fal_port_t port_id, a_bool_t enable);


    HSL_LOCAL sw_error_t
    isisc_port_bp_status_get(a_uint32_t dev_id, fal_port_t port_id, a_bool_t * enable);


    HSL_LOCAL sw_error_t
    isisc_port_link_forcemode_set(a_uint32_t dev_id, fal_port_t port_id, a_bool_t enable);


    HSL_LOCAL sw_error_t
    isisc_port_link_forcemode_get(a_uint32_t dev_id, fal_port_t port_id, a_bool_t * enable);


    HSL_LOCAL sw_error_t
    isisc_port_link_status_get(a_uint32_t dev_id, fal_port_t port_id, a_bool_t * status);

    HSL_LOCAL sw_error_t
    isisc_ports_link_status_get(a_uint32_t dev_id, a_uint32_t * status);

    HSL_LOCAL sw_error_t
    isisc_port_mac_loopback_set(a_uint32_t dev_id, fal_port_t port_id, a_bool_t enable);


    HSL_LOCAL sw_error_t
    isisc_port_mac_loopback_get(a_uint32_t dev_id, fal_port_t port_id, a_bool_t * enable);
#endif

#ifdef __cplusplus
}
#endif                          /* __cplusplus */
#endif                          /* _ISISC_PORT_CTRL_H_ */

