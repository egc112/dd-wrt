/*
 * sflow.c
 *
 * Copyright (C) 2011-25 - ntop.org
 *
 * nDPI is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Lesser General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * nDPI is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public License
 * along with nDPI.  If not, see <http://www.gnu.org/licenses/>.
 *
 */

#include "ndpi_protocol_ids.h"

#define NDPI_CURRENT_PROTO NDPI_PROTOCOL_SFLOW

#include "ndpi_api.h"
#include "ndpi_private.h"

static void ndpi_search_sflow(struct ndpi_detection_module_struct *ndpi_struct, struct ndpi_flow_struct *flow)
{
  struct ndpi_packet_struct *packet = ndpi_get_packet_struct(ndpi_struct);
  // const u_int8_t *packet_payload = packet->payload;
  u_int32_t payload_len = packet->payload_packet_len;

  NDPI_LOG_DBG(ndpi_struct, "search sflow\n");

  if((packet->udp != NULL)
     && (payload_len >= 24)
     /* Version */
     && ntohl(get_u_int32_t(packet->payload, 0)) == 0x00000005
     /* Agent Address type: IPv4 / IPv6 */
     && (ntohl(get_u_int32_t(packet->payload, 4)) == 0x00000001 ||
         ntohl(get_u_int32_t(packet->payload, 4)) == 0x00000002)) {
    NDPI_LOG_INFO(ndpi_struct, "found (probably) sflow\n");
    if (flow->packet_counter >= 2)
    {
      NDPI_LOG_INFO(ndpi_struct, "found sflow\n");
      ndpi_set_detected_protocol(ndpi_struct, flow,
                                 NDPI_PROTOCOL_SFLOW,
                                 NDPI_PROTOCOL_UNKNOWN,
                                 NDPI_CONFIDENCE_DPI);
    }
    return;
  }

  NDPI_EXCLUDE_PROTO(ndpi_struct, flow);
}

void init_sflow_dissector(struct ndpi_detection_module_struct *ndpi_struct)
{
  ndpi_set_bitmask_protocol_detection("sFlow", ndpi_struct,
				      NDPI_PROTOCOL_SFLOW,
				      ndpi_search_sflow,
				      NDPI_SELECTION_BITMASK_PROTOCOL_V4_V6_UDP_WITH_PAYLOAD,
				      SAVE_DETECTION_BITMASK_AS_UNKNOWN,
				      ADD_TO_DETECTION_BITMASK);
}

