/** @file
 *    @brief MAVLink comm protocol testsuite generated from simba_radio.xml
 *    @see https://mavlink.io/en/
 */
#pragma once
#ifndef SIMBA_RADIO_TESTSUITE_H
#define SIMBA_RADIO_TESTSUITE_H

#ifdef __cplusplus
extern "C" {
#endif

#ifndef MAVLINK_TEST_ALL
#define MAVLINK_TEST_ALL

static void mavlink_test_simba_radio(uint8_t, uint8_t, mavlink_message_t *last_msg);

static void mavlink_test_all(uint8_t system_id, uint8_t component_id, mavlink_message_t *last_msg)
{

    mavlink_test_simba_radio(system_id, component_id, last_msg);
}
#endif




static void mavlink_test_radio_status(uint8_t system_id, uint8_t component_id, mavlink_message_t *last_msg)
{
#ifdef MAVLINK_STATUS_FLAG_OUT_MAVLINK1
    mavlink_status_t *status = mavlink_get_channel_status(MAVLINK_COMM_0);
        if ((status->flags & MAVLINK_STATUS_FLAG_OUT_MAVLINK1) && MAVLINK_MSG_ID_RADIO_STATUS >= 256) {
            return;
        }
#endif
    mavlink_message_t msg;
        uint8_t buffer[MAVLINK_MAX_PACKET_LEN];
        uint16_t i;
    mavlink_radio_status_t packet_in = {
        17235,17339,17,84,151,218,29
    };
    mavlink_radio_status_t packet1, packet2;
        memset(&packet1, 0, sizeof(packet1));
        packet1.rxerrors = packet_in.rxerrors;
        packet1.fixed = packet_in.fixed;
        packet1.rssi = packet_in.rssi;
        packet1.remrssi = packet_in.remrssi;
        packet1.txbuf = packet_in.txbuf;
        packet1.noise = packet_in.noise;
        packet1.remnoise = packet_in.remnoise;
        
        
#ifdef MAVLINK_STATUS_FLAG_OUT_MAVLINK1
        if (status->flags & MAVLINK_STATUS_FLAG_OUT_MAVLINK1) {
           // cope with extensions
           memset(MAVLINK_MSG_ID_RADIO_STATUS_MIN_LEN + (char *)&packet1, 0, sizeof(packet1)-MAVLINK_MSG_ID_RADIO_STATUS_MIN_LEN);
        }
#endif
        memset(&packet2, 0, sizeof(packet2));
    mavlink_msg_radio_status_encode(system_id, component_id, &msg, &packet1);
    mavlink_msg_radio_status_decode(&msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);

        memset(&packet2, 0, sizeof(packet2));
    mavlink_msg_radio_status_pack(system_id, component_id, &msg , packet1.rssi , packet1.remrssi , packet1.txbuf , packet1.noise , packet1.remnoise , packet1.rxerrors , packet1.fixed );
    mavlink_msg_radio_status_decode(&msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);

        memset(&packet2, 0, sizeof(packet2));
    mavlink_msg_radio_status_pack_chan(system_id, component_id, MAVLINK_COMM_0, &msg , packet1.rssi , packet1.remrssi , packet1.txbuf , packet1.noise , packet1.remnoise , packet1.rxerrors , packet1.fixed );
    mavlink_msg_radio_status_decode(&msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);

        memset(&packet2, 0, sizeof(packet2));
        mavlink_msg_to_send_buffer(buffer, &msg);
        for (i=0; i<mavlink_msg_get_send_buffer_length(&msg); i++) {
            comm_send_ch(MAVLINK_COMM_0, buffer[i]);
        }
    mavlink_msg_radio_status_decode(last_msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);
        
        memset(&packet2, 0, sizeof(packet2));
    mavlink_msg_radio_status_send(MAVLINK_COMM_1 , packet1.rssi , packet1.remrssi , packet1.txbuf , packet1.noise , packet1.remnoise , packet1.rxerrors , packet1.fixed );
    mavlink_msg_radio_status_decode(last_msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);

#ifdef MAVLINK_HAVE_GET_MESSAGE_INFO
    MAVLINK_ASSERT(mavlink_get_message_info_by_name("RADIO_STATUS") != NULL);
    MAVLINK_ASSERT(mavlink_get_message_info_by_id(MAVLINK_MSG_ID_RADIO_STATUS) != NULL);
#endif
}

static void mavlink_test_l76k_gps(uint8_t system_id, uint8_t component_id, mavlink_message_t *last_msg)
{
#ifdef MAVLINK_STATUS_FLAG_OUT_MAVLINK1
    mavlink_status_t *status = mavlink_get_channel_status(MAVLINK_COMM_0);
        if ((status->flags & MAVLINK_STATUS_FLAG_OUT_MAVLINK1) && MAVLINK_MSG_ID_L76K_GPS >= 256) {
            return;
        }
#endif
    mavlink_message_t msg;
        uint8_t buffer[MAVLINK_MAX_PACKET_LEN];
        uint16_t i;
    mavlink_l76k_gps_t packet_in = {
        963497464,963497672,963497880,963498088,129.0,157.0,963498712,213.0,963499128,113
    };
    mavlink_l76k_gps_t packet1, packet2;
        memset(&packet1, 0, sizeof(packet1));
        packet1.date = packet_in.date;
        packet1.time = packet_in.time;
        packet1.lat = packet_in.lat;
        packet1.lon = packet_in.lon;
        packet1.speed = packet_in.speed;
        packet1.course = packet_in.course;
        packet1.alt = packet_in.alt;
        packet1.hdop = packet_in.hdop;
        packet1.sentences_with_fix = packet_in.sentences_with_fix;
        packet1.satellites_visible = packet_in.satellites_visible;
        
        
#ifdef MAVLINK_STATUS_FLAG_OUT_MAVLINK1
        if (status->flags & MAVLINK_STATUS_FLAG_OUT_MAVLINK1) {
           // cope with extensions
           memset(MAVLINK_MSG_ID_L76K_GPS_MIN_LEN + (char *)&packet1, 0, sizeof(packet1)-MAVLINK_MSG_ID_L76K_GPS_MIN_LEN);
        }
#endif
        memset(&packet2, 0, sizeof(packet2));
    mavlink_msg_l76k_gps_encode(system_id, component_id, &msg, &packet1);
    mavlink_msg_l76k_gps_decode(&msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);

        memset(&packet2, 0, sizeof(packet2));
    mavlink_msg_l76k_gps_pack(system_id, component_id, &msg , packet1.date , packet1.time , packet1.lat , packet1.lon , packet1.speed , packet1.course , packet1.alt , packet1.satellites_visible , packet1.hdop , packet1.sentences_with_fix );
    mavlink_msg_l76k_gps_decode(&msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);

        memset(&packet2, 0, sizeof(packet2));
    mavlink_msg_l76k_gps_pack_chan(system_id, component_id, MAVLINK_COMM_0, &msg , packet1.date , packet1.time , packet1.lat , packet1.lon , packet1.speed , packet1.course , packet1.alt , packet1.satellites_visible , packet1.hdop , packet1.sentences_with_fix );
    mavlink_msg_l76k_gps_decode(&msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);

        memset(&packet2, 0, sizeof(packet2));
        mavlink_msg_to_send_buffer(buffer, &msg);
        for (i=0; i<mavlink_msg_get_send_buffer_length(&msg); i++) {
            comm_send_ch(MAVLINK_COMM_0, buffer[i]);
        }
    mavlink_msg_l76k_gps_decode(last_msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);
        
        memset(&packet2, 0, sizeof(packet2));
    mavlink_msg_l76k_gps_send(MAVLINK_COMM_1 , packet1.date , packet1.time , packet1.lat , packet1.lon , packet1.speed , packet1.course , packet1.alt , packet1.satellites_visible , packet1.hdop , packet1.sentences_with_fix );
    mavlink_msg_l76k_gps_decode(last_msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);

#ifdef MAVLINK_HAVE_GET_MESSAGE_INFO
    MAVLINK_ASSERT(mavlink_get_message_info_by_name("L76K_GPS") != NULL);
    MAVLINK_ASSERT(mavlink_get_message_info_by_id(MAVLINK_MSG_ID_L76K_GPS) != NULL);
#endif
}

static void mavlink_test_simba_radio(uint8_t system_id, uint8_t component_id, mavlink_message_t *last_msg)
{
    mavlink_test_radio_status(system_id, component_id, last_msg);
    mavlink_test_l76k_gps(system_id, component_id, last_msg);
}

#ifdef __cplusplus
}
#endif // __cplusplus
#endif // SIMBA_RADIO_TESTSUITE_H
