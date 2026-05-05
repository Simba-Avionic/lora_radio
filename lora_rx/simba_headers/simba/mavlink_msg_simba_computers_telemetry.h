#pragma once
// MESSAGE SIMBA_COMPUTERS_TELEMETRY PACKING

#define MAVLINK_MSG_ID_SIMBA_COMPUTERS_TELEMETRY 77


typedef struct __mavlink_simba_computers_telemetry_t {
 uint8_t mb_cpu_usage; /*<  Main Computer CPU usage (0-100%)*/
 uint8_t mb_memory_usage; /*<  Main Computer Memory usage (0-100%)*/
 uint8_t eb_cpu_usage; /*<  Engine Computer CPU usage (0-100%)*/
 uint8_t eb_memory_usage; /*<  Engine Computer Memory usage (0-100%)*/
} mavlink_simba_computers_telemetry_t;

#define MAVLINK_MSG_ID_SIMBA_COMPUTERS_TELEMETRY_LEN 4
#define MAVLINK_MSG_ID_SIMBA_COMPUTERS_TELEMETRY_MIN_LEN 4
#define MAVLINK_MSG_ID_77_LEN 4
#define MAVLINK_MSG_ID_77_MIN_LEN 4

#define MAVLINK_MSG_ID_SIMBA_COMPUTERS_TELEMETRY_CRC 207
#define MAVLINK_MSG_ID_77_CRC 207



#if MAVLINK_COMMAND_24BIT
#define MAVLINK_MESSAGE_INFO_SIMBA_COMPUTERS_TELEMETRY { \
    77, \
    "SIMBA_COMPUTERS_TELEMETRY", \
    4, \
    {  { "mb_cpu_usage", NULL, MAVLINK_TYPE_UINT8_T, 0, 0, offsetof(mavlink_simba_computers_telemetry_t, mb_cpu_usage) }, \
         { "mb_memory_usage", NULL, MAVLINK_TYPE_UINT8_T, 0, 1, offsetof(mavlink_simba_computers_telemetry_t, mb_memory_usage) }, \
         { "eb_cpu_usage", NULL, MAVLINK_TYPE_UINT8_T, 0, 2, offsetof(mavlink_simba_computers_telemetry_t, eb_cpu_usage) }, \
         { "eb_memory_usage", NULL, MAVLINK_TYPE_UINT8_T, 0, 3, offsetof(mavlink_simba_computers_telemetry_t, eb_memory_usage) }, \
         } \
}
#else
#define MAVLINK_MESSAGE_INFO_SIMBA_COMPUTERS_TELEMETRY { \
    "SIMBA_COMPUTERS_TELEMETRY", \
    4, \
    {  { "mb_cpu_usage", NULL, MAVLINK_TYPE_UINT8_T, 0, 0, offsetof(mavlink_simba_computers_telemetry_t, mb_cpu_usage) }, \
         { "mb_memory_usage", NULL, MAVLINK_TYPE_UINT8_T, 0, 1, offsetof(mavlink_simba_computers_telemetry_t, mb_memory_usage) }, \
         { "eb_cpu_usage", NULL, MAVLINK_TYPE_UINT8_T, 0, 2, offsetof(mavlink_simba_computers_telemetry_t, eb_cpu_usage) }, \
         { "eb_memory_usage", NULL, MAVLINK_TYPE_UINT8_T, 0, 3, offsetof(mavlink_simba_computers_telemetry_t, eb_memory_usage) }, \
         } \
}
#endif

/**
 * @brief Pack a simba_computers_telemetry message
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param msg The MAVLink message to compress the data into
 *
 * @param mb_cpu_usage  Main Computer CPU usage (0-100%)
 * @param mb_memory_usage  Main Computer Memory usage (0-100%)
 * @param eb_cpu_usage  Engine Computer CPU usage (0-100%)
 * @param eb_memory_usage  Engine Computer Memory usage (0-100%)
 * @return length of the message in bytes (excluding serial stream start sign)
 */
static inline uint16_t mavlink_msg_simba_computers_telemetry_pack(uint8_t system_id, uint8_t component_id, mavlink_message_t* msg,
                               uint8_t mb_cpu_usage, uint8_t mb_memory_usage, uint8_t eb_cpu_usage, uint8_t eb_memory_usage)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char buf[MAVLINK_MSG_ID_SIMBA_COMPUTERS_TELEMETRY_LEN];
    _mav_put_uint8_t(buf, 0, mb_cpu_usage);
    _mav_put_uint8_t(buf, 1, mb_memory_usage);
    _mav_put_uint8_t(buf, 2, eb_cpu_usage);
    _mav_put_uint8_t(buf, 3, eb_memory_usage);

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), buf, MAVLINK_MSG_ID_SIMBA_COMPUTERS_TELEMETRY_LEN);
#else
    mavlink_simba_computers_telemetry_t packet;
    packet.mb_cpu_usage = mb_cpu_usage;
    packet.mb_memory_usage = mb_memory_usage;
    packet.eb_cpu_usage = eb_cpu_usage;
    packet.eb_memory_usage = eb_memory_usage;

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), &packet, MAVLINK_MSG_ID_SIMBA_COMPUTERS_TELEMETRY_LEN);
#endif

    msg->msgid = MAVLINK_MSG_ID_SIMBA_COMPUTERS_TELEMETRY;
    return mavlink_finalize_message(msg, system_id, component_id, MAVLINK_MSG_ID_SIMBA_COMPUTERS_TELEMETRY_MIN_LEN, MAVLINK_MSG_ID_SIMBA_COMPUTERS_TELEMETRY_LEN, MAVLINK_MSG_ID_SIMBA_COMPUTERS_TELEMETRY_CRC);
}

/**
 * @brief Pack a simba_computers_telemetry message
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param status MAVLink status structure
 * @param msg The MAVLink message to compress the data into
 *
 * @param mb_cpu_usage  Main Computer CPU usage (0-100%)
 * @param mb_memory_usage  Main Computer Memory usage (0-100%)
 * @param eb_cpu_usage  Engine Computer CPU usage (0-100%)
 * @param eb_memory_usage  Engine Computer Memory usage (0-100%)
 * @return length of the message in bytes (excluding serial stream start sign)
 */
static inline uint16_t mavlink_msg_simba_computers_telemetry_pack_status(uint8_t system_id, uint8_t component_id, mavlink_status_t *_status, mavlink_message_t* msg,
                               uint8_t mb_cpu_usage, uint8_t mb_memory_usage, uint8_t eb_cpu_usage, uint8_t eb_memory_usage)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char buf[MAVLINK_MSG_ID_SIMBA_COMPUTERS_TELEMETRY_LEN];
    _mav_put_uint8_t(buf, 0, mb_cpu_usage);
    _mav_put_uint8_t(buf, 1, mb_memory_usage);
    _mav_put_uint8_t(buf, 2, eb_cpu_usage);
    _mav_put_uint8_t(buf, 3, eb_memory_usage);

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), buf, MAVLINK_MSG_ID_SIMBA_COMPUTERS_TELEMETRY_LEN);
#else
    mavlink_simba_computers_telemetry_t packet;
    packet.mb_cpu_usage = mb_cpu_usage;
    packet.mb_memory_usage = mb_memory_usage;
    packet.eb_cpu_usage = eb_cpu_usage;
    packet.eb_memory_usage = eb_memory_usage;

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), &packet, MAVLINK_MSG_ID_SIMBA_COMPUTERS_TELEMETRY_LEN);
#endif

    msg->msgid = MAVLINK_MSG_ID_SIMBA_COMPUTERS_TELEMETRY;
#if MAVLINK_CRC_EXTRA
    return mavlink_finalize_message_buffer(msg, system_id, component_id, _status, MAVLINK_MSG_ID_SIMBA_COMPUTERS_TELEMETRY_MIN_LEN, MAVLINK_MSG_ID_SIMBA_COMPUTERS_TELEMETRY_LEN, MAVLINK_MSG_ID_SIMBA_COMPUTERS_TELEMETRY_CRC);
#else
    return mavlink_finalize_message_buffer(msg, system_id, component_id, _status, MAVLINK_MSG_ID_SIMBA_COMPUTERS_TELEMETRY_MIN_LEN, MAVLINK_MSG_ID_SIMBA_COMPUTERS_TELEMETRY_LEN);
#endif
}

/**
 * @brief Pack a simba_computers_telemetry message on a channel
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param chan The MAVLink channel this message will be sent over
 * @param msg The MAVLink message to compress the data into
 * @param mb_cpu_usage  Main Computer CPU usage (0-100%)
 * @param mb_memory_usage  Main Computer Memory usage (0-100%)
 * @param eb_cpu_usage  Engine Computer CPU usage (0-100%)
 * @param eb_memory_usage  Engine Computer Memory usage (0-100%)
 * @return length of the message in bytes (excluding serial stream start sign)
 */
static inline uint16_t mavlink_msg_simba_computers_telemetry_pack_chan(uint8_t system_id, uint8_t component_id, uint8_t chan,
                               mavlink_message_t* msg,
                                   uint8_t mb_cpu_usage,uint8_t mb_memory_usage,uint8_t eb_cpu_usage,uint8_t eb_memory_usage)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char buf[MAVLINK_MSG_ID_SIMBA_COMPUTERS_TELEMETRY_LEN];
    _mav_put_uint8_t(buf, 0, mb_cpu_usage);
    _mav_put_uint8_t(buf, 1, mb_memory_usage);
    _mav_put_uint8_t(buf, 2, eb_cpu_usage);
    _mav_put_uint8_t(buf, 3, eb_memory_usage);

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), buf, MAVLINK_MSG_ID_SIMBA_COMPUTERS_TELEMETRY_LEN);
#else
    mavlink_simba_computers_telemetry_t packet;
    packet.mb_cpu_usage = mb_cpu_usage;
    packet.mb_memory_usage = mb_memory_usage;
    packet.eb_cpu_usage = eb_cpu_usage;
    packet.eb_memory_usage = eb_memory_usage;

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), &packet, MAVLINK_MSG_ID_SIMBA_COMPUTERS_TELEMETRY_LEN);
#endif

    msg->msgid = MAVLINK_MSG_ID_SIMBA_COMPUTERS_TELEMETRY;
    return mavlink_finalize_message_chan(msg, system_id, component_id, chan, MAVLINK_MSG_ID_SIMBA_COMPUTERS_TELEMETRY_MIN_LEN, MAVLINK_MSG_ID_SIMBA_COMPUTERS_TELEMETRY_LEN, MAVLINK_MSG_ID_SIMBA_COMPUTERS_TELEMETRY_CRC);
}

/**
 * @brief Encode a simba_computers_telemetry struct
 *
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param msg The MAVLink message to compress the data into
 * @param simba_computers_telemetry C-struct to read the message contents from
 */
static inline uint16_t mavlink_msg_simba_computers_telemetry_encode(uint8_t system_id, uint8_t component_id, mavlink_message_t* msg, const mavlink_simba_computers_telemetry_t* simba_computers_telemetry)
{
    return mavlink_msg_simba_computers_telemetry_pack(system_id, component_id, msg, simba_computers_telemetry->mb_cpu_usage, simba_computers_telemetry->mb_memory_usage, simba_computers_telemetry->eb_cpu_usage, simba_computers_telemetry->eb_memory_usage);
}

/**
 * @brief Encode a simba_computers_telemetry struct on a channel
 *
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param chan The MAVLink channel this message will be sent over
 * @param msg The MAVLink message to compress the data into
 * @param simba_computers_telemetry C-struct to read the message contents from
 */
static inline uint16_t mavlink_msg_simba_computers_telemetry_encode_chan(uint8_t system_id, uint8_t component_id, uint8_t chan, mavlink_message_t* msg, const mavlink_simba_computers_telemetry_t* simba_computers_telemetry)
{
    return mavlink_msg_simba_computers_telemetry_pack_chan(system_id, component_id, chan, msg, simba_computers_telemetry->mb_cpu_usage, simba_computers_telemetry->mb_memory_usage, simba_computers_telemetry->eb_cpu_usage, simba_computers_telemetry->eb_memory_usage);
}

/**
 * @brief Encode a simba_computers_telemetry struct with provided status structure
 *
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param status MAVLink status structure
 * @param msg The MAVLink message to compress the data into
 * @param simba_computers_telemetry C-struct to read the message contents from
 */
static inline uint16_t mavlink_msg_simba_computers_telemetry_encode_status(uint8_t system_id, uint8_t component_id, mavlink_status_t* _status, mavlink_message_t* msg, const mavlink_simba_computers_telemetry_t* simba_computers_telemetry)
{
    return mavlink_msg_simba_computers_telemetry_pack_status(system_id, component_id, _status, msg,  simba_computers_telemetry->mb_cpu_usage, simba_computers_telemetry->mb_memory_usage, simba_computers_telemetry->eb_cpu_usage, simba_computers_telemetry->eb_memory_usage);
}

/**
 * @brief Send a simba_computers_telemetry message
 * @param chan MAVLink channel to send the message
 *
 * @param mb_cpu_usage  Main Computer CPU usage (0-100%)
 * @param mb_memory_usage  Main Computer Memory usage (0-100%)
 * @param eb_cpu_usage  Engine Computer CPU usage (0-100%)
 * @param eb_memory_usage  Engine Computer Memory usage (0-100%)
 */
#ifdef MAVLINK_USE_CONVENIENCE_FUNCTIONS

static inline void mavlink_msg_simba_computers_telemetry_send(mavlink_channel_t chan, uint8_t mb_cpu_usage, uint8_t mb_memory_usage, uint8_t eb_cpu_usage, uint8_t eb_memory_usage)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char buf[MAVLINK_MSG_ID_SIMBA_COMPUTERS_TELEMETRY_LEN];
    _mav_put_uint8_t(buf, 0, mb_cpu_usage);
    _mav_put_uint8_t(buf, 1, mb_memory_usage);
    _mav_put_uint8_t(buf, 2, eb_cpu_usage);
    _mav_put_uint8_t(buf, 3, eb_memory_usage);

    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_SIMBA_COMPUTERS_TELEMETRY, buf, MAVLINK_MSG_ID_SIMBA_COMPUTERS_TELEMETRY_MIN_LEN, MAVLINK_MSG_ID_SIMBA_COMPUTERS_TELEMETRY_LEN, MAVLINK_MSG_ID_SIMBA_COMPUTERS_TELEMETRY_CRC);
#else
    mavlink_simba_computers_telemetry_t packet;
    packet.mb_cpu_usage = mb_cpu_usage;
    packet.mb_memory_usage = mb_memory_usage;
    packet.eb_cpu_usage = eb_cpu_usage;
    packet.eb_memory_usage = eb_memory_usage;

    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_SIMBA_COMPUTERS_TELEMETRY, (const char *)&packet, MAVLINK_MSG_ID_SIMBA_COMPUTERS_TELEMETRY_MIN_LEN, MAVLINK_MSG_ID_SIMBA_COMPUTERS_TELEMETRY_LEN, MAVLINK_MSG_ID_SIMBA_COMPUTERS_TELEMETRY_CRC);
#endif
}

/**
 * @brief Send a simba_computers_telemetry message
 * @param chan MAVLink channel to send the message
 * @param struct The MAVLink struct to serialize
 */
static inline void mavlink_msg_simba_computers_telemetry_send_struct(mavlink_channel_t chan, const mavlink_simba_computers_telemetry_t* simba_computers_telemetry)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    mavlink_msg_simba_computers_telemetry_send(chan, simba_computers_telemetry->mb_cpu_usage, simba_computers_telemetry->mb_memory_usage, simba_computers_telemetry->eb_cpu_usage, simba_computers_telemetry->eb_memory_usage);
#else
    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_SIMBA_COMPUTERS_TELEMETRY, (const char *)simba_computers_telemetry, MAVLINK_MSG_ID_SIMBA_COMPUTERS_TELEMETRY_MIN_LEN, MAVLINK_MSG_ID_SIMBA_COMPUTERS_TELEMETRY_LEN, MAVLINK_MSG_ID_SIMBA_COMPUTERS_TELEMETRY_CRC);
#endif
}

#if MAVLINK_MSG_ID_SIMBA_COMPUTERS_TELEMETRY_LEN <= MAVLINK_MAX_PAYLOAD_LEN
/*
  This variant of _send() can be used to save stack space by reusing
  memory from the receive buffer.  The caller provides a
  mavlink_message_t which is the size of a full mavlink message. This
  is usually the receive buffer for the channel, and allows a reply to an
  incoming message with minimum stack space usage.
 */
static inline void mavlink_msg_simba_computers_telemetry_send_buf(mavlink_message_t *msgbuf, mavlink_channel_t chan,  uint8_t mb_cpu_usage, uint8_t mb_memory_usage, uint8_t eb_cpu_usage, uint8_t eb_memory_usage)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char *buf = (char *)msgbuf;
    _mav_put_uint8_t(buf, 0, mb_cpu_usage);
    _mav_put_uint8_t(buf, 1, mb_memory_usage);
    _mav_put_uint8_t(buf, 2, eb_cpu_usage);
    _mav_put_uint8_t(buf, 3, eb_memory_usage);

    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_SIMBA_COMPUTERS_TELEMETRY, buf, MAVLINK_MSG_ID_SIMBA_COMPUTERS_TELEMETRY_MIN_LEN, MAVLINK_MSG_ID_SIMBA_COMPUTERS_TELEMETRY_LEN, MAVLINK_MSG_ID_SIMBA_COMPUTERS_TELEMETRY_CRC);
#else
    mavlink_simba_computers_telemetry_t *packet = (mavlink_simba_computers_telemetry_t *)msgbuf;
    packet->mb_cpu_usage = mb_cpu_usage;
    packet->mb_memory_usage = mb_memory_usage;
    packet->eb_cpu_usage = eb_cpu_usage;
    packet->eb_memory_usage = eb_memory_usage;

    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_SIMBA_COMPUTERS_TELEMETRY, (const char *)packet, MAVLINK_MSG_ID_SIMBA_COMPUTERS_TELEMETRY_MIN_LEN, MAVLINK_MSG_ID_SIMBA_COMPUTERS_TELEMETRY_LEN, MAVLINK_MSG_ID_SIMBA_COMPUTERS_TELEMETRY_CRC);
#endif
}
#endif

#endif

// MESSAGE SIMBA_COMPUTERS_TELEMETRY UNPACKING


/**
 * @brief Get field mb_cpu_usage from simba_computers_telemetry message
 *
 * @return  Main Computer CPU usage (0-100%)
 */
static inline uint8_t mavlink_msg_simba_computers_telemetry_get_mb_cpu_usage(const mavlink_message_t* msg)
{
    return _MAV_RETURN_uint8_t(msg,  0);
}

/**
 * @brief Get field mb_memory_usage from simba_computers_telemetry message
 *
 * @return  Main Computer Memory usage (0-100%)
 */
static inline uint8_t mavlink_msg_simba_computers_telemetry_get_mb_memory_usage(const mavlink_message_t* msg)
{
    return _MAV_RETURN_uint8_t(msg,  1);
}

/**
 * @brief Get field eb_cpu_usage from simba_computers_telemetry message
 *
 * @return  Engine Computer CPU usage (0-100%)
 */
static inline uint8_t mavlink_msg_simba_computers_telemetry_get_eb_cpu_usage(const mavlink_message_t* msg)
{
    return _MAV_RETURN_uint8_t(msg,  2);
}

/**
 * @brief Get field eb_memory_usage from simba_computers_telemetry message
 *
 * @return  Engine Computer Memory usage (0-100%)
 */
static inline uint8_t mavlink_msg_simba_computers_telemetry_get_eb_memory_usage(const mavlink_message_t* msg)
{
    return _MAV_RETURN_uint8_t(msg,  3);
}

/**
 * @brief Decode a simba_computers_telemetry message into a struct
 *
 * @param msg The message to decode
 * @param simba_computers_telemetry C-struct to decode the message contents into
 */
static inline void mavlink_msg_simba_computers_telemetry_decode(const mavlink_message_t* msg, mavlink_simba_computers_telemetry_t* simba_computers_telemetry)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    simba_computers_telemetry->mb_cpu_usage = mavlink_msg_simba_computers_telemetry_get_mb_cpu_usage(msg);
    simba_computers_telemetry->mb_memory_usage = mavlink_msg_simba_computers_telemetry_get_mb_memory_usage(msg);
    simba_computers_telemetry->eb_cpu_usage = mavlink_msg_simba_computers_telemetry_get_eb_cpu_usage(msg);
    simba_computers_telemetry->eb_memory_usage = mavlink_msg_simba_computers_telemetry_get_eb_memory_usage(msg);
#else
        uint8_t len = msg->len < MAVLINK_MSG_ID_SIMBA_COMPUTERS_TELEMETRY_LEN? msg->len : MAVLINK_MSG_ID_SIMBA_COMPUTERS_TELEMETRY_LEN;
        memset(simba_computers_telemetry, 0, MAVLINK_MSG_ID_SIMBA_COMPUTERS_TELEMETRY_LEN);
    memcpy(simba_computers_telemetry, _MAV_PAYLOAD(msg), len);
#endif
}
