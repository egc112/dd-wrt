/*
 * genshin_impact.c
 *
 * Copyright (C) 2012-22 - ntop.org
 *
 * This module is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Lesser General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This module is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public License.
 * If not, see <http://www.gnu.org/licenses/>.
 *
 */

#include "ndpi_protocol_ids.h"

#define NDPI_CURRENT_PROTO NDPI_PROTOCOL_GENSHIN_IMPACT

#include "ndpi_api.h"
#include "ndpi_private.h"


static void ndpi_int_genshin_impact_add_connection(
                struct ndpi_detection_module_struct *ndpi_struct,
                struct ndpi_flow_struct *flow)
{
  ndpi_set_detected_protocol(ndpi_struct, flow, NDPI_PROTOCOL_GENSHIN_IMPACT, NDPI_PROTOCOL_UNKNOWN, NDPI_CONFIDENCE_DPI);
}

static void ndpi_search_genshin_impact(struct ndpi_detection_module_struct *ndpi_struct,
                                       struct ndpi_flow_struct *flow)
{
  struct ndpi_packet_struct * packet = ndpi_get_packet_struct(ndpi_struct);

  NDPI_LOG_DBG(ndpi_struct, "search genshin-impact\n");

  if (packet->tcp != NULL && packet->payload_packet_len >= 18)
  {
    u_int32_t pdu_len = ntohl(get_u_int32_t(packet->payload, 1));

    if (packet->payload[0] == 0x01 && pdu_len == packet->payload_packet_len &&
        (packet->payload[5] == 0x01 || packet->payload[5] == 0x07) &&
        ntohs(get_u_int16_t(packet->payload, 16)) == 0x4da6)
    {
      NDPI_LOG_INFO(ndpi_struct, "found genshin-impact (TCP)\n");
      ndpi_int_genshin_impact_add_connection(ndpi_struct, flow);
      return;
    }
  }
  else if (packet->udp != NULL)
  {
    if (flow->packet_counter == 1 && packet->payload_packet_len >= 20 &&
        ntohl(get_u_int32_t(packet->payload, 0)) == 0x000000FF &&
        ntohl(get_u_int32_t(packet->payload, 4)) == 0x00000000 &&
        ntohl(get_u_int32_t(packet->payload, 12)) == 0x499602D2 &&
        ntohl(get_u_int32_t(packet->payload, 16)) == 0xFFFFFFFF)
    {
      NDPI_LOG_INFO(ndpi_struct, "found genshin-impact (UDP)\n");
      ndpi_int_genshin_impact_add_connection(ndpi_struct, flow);
      return;
    }
  }

  NDPI_EXCLUDE_PROTO(ndpi_struct, flow);
}


/* ***************************************************************** */

void init_genshin_impact_dissector(struct ndpi_detection_module_struct *ndpi_struct)
{
  ndpi_set_bitmask_protocol_detection("GenshinImpact",
                                      ndpi_struct,
                                      NDPI_PROTOCOL_GENSHIN_IMPACT,
                                      ndpi_search_genshin_impact,
                                      NDPI_SELECTION_BITMASK_PROTOCOL_V4_V6_TCP_OR_UDP_WITH_PAYLOAD_WITHOUT_RETRANSMISSION,
                                      SAVE_DETECTION_BITMASK_AS_UNKNOWN,
                                      ADD_TO_DETECTION_BITMASK);
}
