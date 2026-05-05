#pragma once
// MESSAGE SIMBA_ROCKET_HEARTBEAT PACKING

#define MAVLINK_MSG_ID_SIMBA_ROCKET_HEARTBEAT 73


typedef struct __mavlink_simba_rocket_heartbeat_t {
 uint64_t timestamp; /*<  Timestamp (system uptime in ms)*/
 uint32_t apps_alive; /*<  Bitmap for all ec and fc apps*/
 uint8_t flight_computer_state; /*<  Flight computer state*/
 uint8_t engine_computer_state; /*<  Engine computer state*/
 uint8_t values; /*<  Actuator bitmask*/
 uint8_t primer_state; /*<  Primer State*/
} mavlink_simba_rocket_heartbeat_t;

#define MAVLINK_MSG_ID_SIMBA_ROCKET_HEARTBEAT_LEN 16
#define MAVLINK_MSG_ID_SIMBA_ROCKET_HEARTBEAT_MIN_LEN 16
#define MAVLINK_MSG_ID_73_LEN 16
#define MAVLINK_MSG_ID_73_MIN_LEN 16

#define MAVLINK_MSG_ID_SIMBA_ROCKET_HEARTBEAT_CRC 48
#define MAVLINK_MSG_ID_73_CRC 48



#if MAVLINK_COMMAND_24BIT
#define MAVLINK_MESSAGE_INFO_SIMBA_ROCKET_HEARTBEAT { \
    73, \
    "SIMBA_ROCKET_HEARTBEAT", \
    6, \
    {  { "timestamp", NULL, MAVLINK_TYPE_UINT64_T, 0, 0, offsetof(mavlink_simba_rocket_heartbeat_t, timestamp) }, \
         { "apps_alive", NULL, MAVLINK_TYPE_UINT32_T, 0, 8, offsetof(mavlink_simba_rocket_heartbeat_t, apps_alive) }, \
         { "flight_computer_state", NULL, MAVLINK_TYPE_UINT8_T, 0, 12, offsetof(mavlink_simba_rocket_heartbeat_t, flight_computer_state) }, \
         { "engine_computer_state", NULL, MAVLINK_TYPE_UINT8_T, 0, 13, offsetof(mavlink_simba_rocket_heartbeat_t, engine_computer_state) }, \
         { "values", NULL, MAVLINK_TYPE_UINT8_T, 0, 14, offsetof(mavlink_simba_rocket_heartbeat_t, values) }, \
         { "primer_state", NULL, MAVLINK_TYPE_UINT8_T, 0, 15, offsetof(mavlink_simba_rocket_heartbeat_t, primer_state) }, \
         } \
}
#else
#define MAVLINK_MESSAGE_INFO_SIMBA_ROCKET_HEARTBEAT { \
    "SIMBA_ROCKET_HEARTBEAT", \
    6, \
    {  { "timestamp", NULL, MAVLINK_TYPE_UINT64_T, 0, 0, offsetof(mavlink_simba_rocket_heartbeat_t, timestamp) }, \
         { "apps_alive", NULL, MAVLINK_TYPE_UINT32_T, 0, 8, offsetof(mavlink_simba_rocket_heartbeat_t, apps_alive) }, \
         { "flight_computer_state", NULL, MAVLINK_TYPE_UINT8_T, 0, 12, offsetof(mavlink_simba_rocket_heartbeat_t, flight_computer_state) }, \
         { "engine_computer_state", NULL, MAVLINK_TYPE_UINT8_T, 0, 13, offsetof(mavlink_simba_rocket_heartbeat_t, engine_computer_state) }, \
         { "values", NULL, MAVLINK_TYPE_UINT8_T, 0, 14, offsetof(mavlink_simba_rocket_heartbeat_t, values) }, \
         { "primer_state", NULL, MAVLINK_TYPE_UINT8_T, 0, 15, offsetof(mavlink_simba_rocket_heartbeat_t, primer_state) }, \
         } \
}
#endif

/**
 * @brief Pack a simba_rocket_heartbeat message
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param msg The MAVLink message to compress the data into
 *
 * @param timestamp  Timestamp (system uptime in ms)
 * @param apps_alive  Bitmap for all ec and fc apps
 * @param flight_computer_state  Flight computer state
 * @param engine_computer_state  Engine computer state
 * @param values  Actuator bitmask
 * @param primer_state  Primer State
 * @return length of the message in bytes (excluding serial stream start sign)
 */
static inline uint16_t mavlink_msg_simba_rocket_heartbeat_pack(uint8_t system_id, uint8_t component_id, mavlink_message_t* msg,
                               uint64_t timestamp, uint32_t apps_alive, uint8_t flight_computer_state, uint8_t engine_computer_state, uint8_t values, uint8_t primer_state)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char buf[MAVLINK_MSG_ID_SIMBA_ROCKET_HEARTBEAT_LEN];
    _mav_put_uint64_t(buf, 0, timestamp);
    _mav_put_uint32_t(buf, 8, apps_alive);
    _mav_put_uint8_t(buf, 12, flight_computer_state);
    _mav_put_uint8_t(buf, 13, engine_computer_state);
    _mav_put_uint8_t(buf, 14, values);
    _mav_put_uint8_t(buf, 15, primer_state);

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), buf, MAVLINK_MSG_ID_SIMBA_ROCKET_HEARTBEAT_LEN);
#else
    mavlink_simba_rocket_heartbeat_t packet;
    packet.timestamp = timestamp;
    packet.apps_alive = apps_alive;
    packet.flight_computer_state = flight_computer_state;
    packet.engine_computer_state = engine_computer_state;
    packet.values = values;
    packet.primer_state = primer_state;

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), &packet, MAVLINK_MSG_ID_SIMBA_ROCKET_HEARTBEAT_LEN);
#endif

    msg->msgid = MAVLINK_MSG_ID_SIMBA_ROCKET_HEARTBEAT;
    return mavlink_finalize_message(msg, system_id, component_id, MAVLINK_MSG_ID_SIMBA_ROCKET_HEARTBEAT_MIN_LEN, MAVLINK_MSG_ID_SIMBA_ROCKET_HEARTBEAT_LEN, MAVLINK_MSG_ID_SIMBA_ROCKET_HEARTBEAT_CRC);
}

/**
 * @brief Pack a simba_rocket_heartbeat message
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param status MAVLink status structure
 * @param msg The MAVLink message to compress the data into
 *
 * @param timestamp  Timestamp (system uptime in ms)
 * @param apps_alive  Bitmap for all ec and fc apps
 * @param flight_computer_state  Flight computer state
 * @param engine_computer_state  Engine computer state
 * @param values  Actuator bitmask
 * @param primer_state  Primer State
 * @return length of the message in bytes (excluding serial stream start sign)
 */
static inline uint16_t mavlink_msg_simba_rocket_heartbeat_pack_status(uint8_t system_id, uint8_t component_id, mavlink_status_t *_status, mavlink_message_t* msg,
                               uint64_t timestamp, uint32_t apps_alive, uint8_t flight_computer_state, uint8_t engine_computer_state, uint8_t values, uint8_t primer_state)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char buf[MAVLINK_MSG_ID_SIMBA_ROCKET_HEARTBEAT_LEN];
    _mav_put_uint64_t(buf, 0, timestamp);
    _mav_put_uint32_t(buf, 8, apps_alive);
    _mav_put_uint8_t(buf, 12, flight_computer_state);
    _mav_put_uint8_t(buf, 13, engine_computer_state);
    _mav_put_uint8_t(buf, 14, values);
    _mav_put_uint8_t(buf, 15, primer_state);

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), buf, MAVLINK_MSG_ID_SIMBA_ROCKET_HEARTBEAT_LEN);
#else
    mavlink_simba_rocket_heartbeat_t packet;
    packet.timestamp = timestamp;
    packet.apps_alive = apps_alive;
    packet.flight_computer_state = flight_computer_state;
    packet.engine_computer_state = engine_computer_state;
    packet.values = values;
    packet.primer_state = primer_state;

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), &packet, MAVLINK_MSG_ID_SIMBA_ROCKET_HEARTBEAT_LEN);
#endif

    msg->msgid = MAVLINK_MSG_ID_SIMBA_ROCKET_HEARTBEAT;
#if MAVLINK_CRC_EXTRA
    return mavlink_finalize_message_buffer(msg, system_id, component_id, _status, MAVLINK_MSG_ID_SIMBA_ROCKET_HEARTBEAT_MIN_LEN, MAVLINK_MSG_ID_SIMBA_ROCKET_HEARTBEAT_LEN, MAVLINK_MSG_ID_SIMBA_ROCKET_HEARTBEAT_CRC);
#else
    return mavlink_finalize_message_buffer(msg, system_id, component_id, _status, MAVLINK_MSG_ID_SIMBA_ROCKET_HEARTBEAT_MIN_LEN, MAVLINK_MSG_ID_SIMBA_ROCKET_HEARTBEAT_LEN);
#endif
}

/**
 * @brief Pack a simba_rocket_heartbeat message on a channel
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param chan The MAVLink channel this message will be sent over
 * @param msg The MAVLink message to compress the data into
 * @param timestamp  Timestamp (system uptime in ms)
 * @param apps_alive  Bitmap for all ec and fc apps
 * @param flight_computer_state  Flight computer state
 * @param engine_computer_state  Engine computer state
 * @param values  Actuator bitmask
 * @param primer_state  Primer State
 * @return length of the message in bytes (excluding serial stream start sign)
 */
static inline uint16_t mavlink_msg_simba_rocket_heartbeat_pack_chan(uint8_t system_id, uint8_t component_id, uint8_t chan,
                               mavlink_message_t* msg,
                                   uint64_t timestamp,uint32_t apps_alive,uint8_t flight_computer_state,uint8_t engine_computer_state,uint8_t values,uint8_t primer_state)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char buf[MAVLINK_MSG_ID_SIMBA_ROCKET_HEARTBEAT_LEN];
    _mav_put_uint64_t(buf, 0, timestamp);
    _mav_put_uint32_t(buf, 8, apps_alive);
    _mav_put_uint8_t(buf, 12, flight_computer_state);
    _mav_put_uint8_t(buf, 13, engine_computer_state);
    _mav_put_uint8_t(buf, 14, values);
    _mav_put_uint8_t(buf, 15, primer_state);

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), buf, MAVLINK_MSG_ID_SIMBA_ROCKET_HEARTBEAT_LEN);
#else
    mavlink_simba_rocket_heartbeat_t packet;
    packet.timestamp = timestamp;
    packet.apps_alive = apps_alive;
    packet.flight_computer_state = flight_computer_state;
    packet.engine_computer_state = engine_computer_state;
    packet.values = values;
    packet.primer_state = primer_state;

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), &packet, MAVLINK_MSG_ID_SIMBA_ROCKET_HEARTBEAT_LEN);
#endif

    msg->msgid = MAVLINK_MSG_ID_SIMBA_ROCKET_HEARTBEAT;
    return mavlink_finalize_message_chan(msg, system_id, component_id, chan, MAVLINK_MSG_ID_SIMBA_ROCKET_HEARTBEAT_MIN_LEN, MAVLINK_MSG_ID_SIMBA_ROCKET_HEARTBEAT_LEN, MAVLINK_MSG_ID_SIMBA_ROCKET_HEARTBEAT_CRC);
}

/**
 * @brief Encode a simba_rocket_heartbeat struct
 *
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param msg The MAVLink message to compress the data into
 * @param simba_rocket_heartbeat C-struct to read the message contents from
 */
static inline uint16_t mavlink_msg_simba_rocket_heartbeat_encode(uint8_t system_id, uint8_t component_id, mavlink_message_t* msg, const mavlink_simba_rocket_heartbeat_t* simba_rocket_heartbeat)
{
    return mavlink_msg_simba_rocket_heartbeat_pack(system_id, component_id, msg, simba_rocket_heartbeat->timestamp, simba_rocket_heartbeat->apps_alive, simba_rocket_heartbeat->flight_computer_state, simba_rocket_heartbeat->engine_computer_state, simba_rocket_heartbeat->values, simba_rocket_heartbeat->primer_state);
}

/**
 * @brief Encode a simba_rocket_heartbeat struct on a channel
 *
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param chan The MAVLink channel this message will be sent over
 * @param msg The MAVLink message to compress the data into
 * @param simba_rocket_heartbeat C-struct to read the message contents from
 */
static inline uint16_t mavlink_msg_simba_rocket_heartbeat_encode_chan(uint8_t system_id, uint8_t component_id, uint8_t chan, mavlink_message_t* msg, const mavlink_simba_rocket_heartbeat_t* simba_rocket_heartbeat)
{
    return mavlink_msg_simba_rocket_heartbeat_pack_chan(system_id, component_id, chan, msg, simba_rocket_heartbeat->timestamp, simba_rocket_heartbeat->apps_alive, simba_rocket_heartbeat->flight_computer_state, simba_rocket_heartbeat->engine_computer_state, simba_rocket_heartbeat->values, simba_rocket_heartbeat->primer_state);
}

/**
 * @brief Encode a simba_rocket_heartbeat struct with provided status structure
 *
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param status MAVLink status structure
 * @param msg The MAVLink message to compress the data into
 * @param simba_rocket_heartbeat C-struct to read the message contents from
 */
static inline uint16_t mavlink_msg_simba_rocket_heartbeat_encode_status(uint8_t system_id, uint8_t component_id, mavlink_status_t* _status, mavlink_message_t* msg, const mavlink_simba_rocket_heartbeat_t* simba_rocket_heartbeat)
{
    return mavlink_msg_simba_rocket_heartbeat_pack_status(system_id, component_id, _status, msg,  simba_rocket_heartbeat->timestamp, simba_rocket_heartbeat->apps_alive, simba_rocket_heartbeat->flight_computer_state, simba_rocket_heartbeat->engine_computer_state, simba_rocket_heartbeat->values, simba_rocket_heartbeat->primer_state);
}

/**
 * @brief Send a simba_rocket_heartbeat message
 * @param chan MAVLink channel to send the message
 *
 * @param timestamp  Timestamp (system uptime in ms)
 * @param apps_alive  Bitmap for all ec and fc apps
 * @param flight_computer_state  Flight computer state
 * @param engine_computer_state  Engine computer state
 * @param values  Actuator bitmask
 * @param primer_state  Primer State
 */
#ifdef MAVLINK_USE_CONVENIENCE_FUNCTIONS

static inline void mavlink_msg_simba_rocket_heartbeat_send(mavlink_channel_t chan, uint64_t timestamp, uint32_t apps_alive, uint8_t flight_computer_state, uint8_t engine_computer_state, uint8_t values, uint8_t primer_state)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char buf[MAVLINK_MSG_ID_SIMBA_ROCKET_HEARTBEAT_LEN];
    _mav_put_uint64_t(buf, 0, timestamp);
    _mav_put_uint32_t(buf, 8, apps_alive);
    _mav_put_uint8_t(buf, 12, flight_computer_state);
    _mav_put_uint8_t(buf, 13, engine_computer_state);
    _mav_put_uint8_t(buf, 14, values);
    _mav_put_uint8_t(buf, 15, primer_state);

    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_SIMBA_ROCKET_HEARTBEAT, buf, MAVLINK_MSG_ID_SIMBA_ROCKET_HEARTBEAT_MIN_LEN, MAVLINK_MSG_ID_SIMBA_ROCKET_HEARTBEAT_LEN, MAVLINK_MSG_ID_SIMBA_ROCKET_HEARTBEAT_CRC);
#else
    mavlink_simba_rocket_heartbeat_t packet;
    packet.timestamp = timestamp;
    packet.apps_alive = apps_alive;
    packet.flight_computer_state = flight_computer_state;
    packet.engine_computer_state = engine_computer_state;
    packet.values = values;
    packet.primer_state = primer_state;

    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_SIMBA_ROCKET_HEARTBEAT, (const char *)&packet, MAVLINK_MSG_ID_SIMBA_ROCKET_HEARTBEAT_MIN_LEN, MAVLINK_MSG_ID_SIMBA_ROCKET_HEARTBEAT_LEN, MAVLINK_MSG_ID_SIMBA_ROCKET_HEARTBEAT_CRC);
#endif
}

/**
 * @brief Send a simba_rocket_heartbeat message
 * @param chan MAVLink channel to send the message
 * @param struct The MAVLink struct to serialize
 */
static inline void mavlink_msg_simba_rocket_heartbeat_send_struct(mavlink_channel_t chan, const mavlink_simba_rocket_heartbeat_t* simba_rocket_heartbeat)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    mavlink_msg_simba_rocket_heartbeat_send(chan, simba_rocket_heartbeat->timestamp, simba_rocket_heartbeat->apps_alive, simba_rocket_heartbeat->flight_computer_state, simba_rocket_heartbeat->engine_computer_state, simba_rocket_heartbeat->values, simba_rocket_heartbeat->primer_state);
#else
    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_SIMBA_ROCKET_HEARTBEAT, (const char *)simba_rocket_heartbeat, MAVLINK_MSG_ID_SIMBA_ROCKET_HEARTBEAT_MIN_LEN, MAVLINK_MSG_ID_SIMBA_ROCKET_HEARTBEAT_LEN, MAVLINK_MSG_ID_SIMBA_ROCKET_HEARTBEAT_CRC);
#endif
}

#if MAVLINK_MSG_ID_SIMBA_ROCKET_HEARTBEAT_LEN <= MAVLINK_MAX_PAYLOAD_LEN
/*
  This variant of _send() can be used to save stack space by reusing
  memory from the receive buffer.  The caller provides a
  mavlink_message_t which is the size of a full mavlink message. This
  is usually the receive buffer for the channel, and allows a reply to an
  incoming message with minimum stack space usage.
 */
static inline void mavlink_msg_simba_rocket_heartbeat_send_buf(mavlink_message_t *msgbuf, mavlink_channel_t chan,  uint64_t timestamp, uint32_t apps_alive, uint8_t flight_computer_state, uint8_t engine_computer_state, uint8_t values, uint8_t primer_state)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char *buf = (char *)msgbuf;
    _mav_put_uint64_t(buf, 0, timestamp);
    _mav_put_uint32_t(buf, 8, apps_alive);
    _mav_put_uint8_t(buf, 12, flight_computer_state);
    _mav_put_uint8_t(buf, 13, engine_computer_state);
    _mav_put_uint8_t(buf, 14, values);
    _mav_put_uint8_t(buf, 15, primer_state);

    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_SIMBA_ROCKET_HEARTBEAT, buf, MAVLINK_MSG_ID_SIMBA_ROCKET_HEARTBEAT_MIN_LEN, MAVLINK_MSG_ID_SIMBA_ROCKET_HEARTBEAT_LEN, MAVLINK_MSG_ID_SIMBA_ROCKET_HEARTBEAT_CRC);
#else
    mavlink_simba_rocket_heartbeat_t *packet = (mavlink_simba_rocket_heartbeat_t *)msgbuf;
    packet->timestamp = timestamp;
    packet->apps_alive = apps_alive;
    packet->flight_computer_state = flight_computer_state;
    packet->engine_computer_state = engine_computer_state;
    packet->values = values;
    packet->primer_state = primer_state;

    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_SIMBA_ROCKET_HEARTBEAT, (const char *)packet, MAVLINK_MSG_ID_SIMBA_ROCKET_HEARTBEAT_MIN_LEN, MAVLINK_MSG_ID_SIMBA_ROCKET_HEARTBEAT_LEN, MAVLINK_MSG_ID_SIMBA_ROCKET_HEARTBEAT_CRC);
#endif
}
#endif

#endif

// MESSAGE SIMBA_ROCKET_HEARTBEAT UNPACKING


/**
 * @brief Get field timestamp from simba_rocket_heartbeat message
 *
 * @return  Timestamp (system uptime in ms)
 */
static inline uint64_t mavlink_msg_simba_rocket_heartbeat_get_timestamp(const mavlink_message_t* msg)
{
    return _MAV_RETURN_uint64_t(msg,  0);
}

/**
 * @brief Get field apps_alive from simba_rocket_heartbeat message
 *
 * @return  Bitmap for all ec and fc apps
 */
static inline uint32_t mavlink_msg_simba_rocket_heartbeat_get_apps_alive(const mavlink_message_t* msg)
{
    return _MAV_RETURN_uint32_t(msg,  8);
}

/**
 * @brief Get field flight_computer_state from simba_rocket_heartbeat message
 *
 * @return  Flight computer state
 */
static inline uint8_t mavlink_msg_simba_rocket_heartbeat_get_flight_computer_state(const mavlink_message_t* msg)
{
    return _MAV_RETURN_uint8_t(msg,  12);
}

/**
 * @brief Get field engine_computer_state from simba_rocket_heartbeat message
 *
 * @return  Engine computer state
 */
static inline uint8_t mavlink_msg_simba_rocket_heartbeat_get_engine_computer_state(const mavlink_message_t* msg)
{
    return _MAV_RETURN_uint8_t(msg,  13);
}

/**
 * @brief Get field values from simba_rocket_heartbeat message
 *
 * @return  Actuator bitmask
 */
static inline uint8_t mavlink_msg_simba_rocket_heartbeat_get_values(const mavlink_message_t* msg)
{
    return _MAV_RETURN_uint8_t(msg,  14);
}

/**
 * @brief Get field primer_state from simba_rocket_heartbeat message
 *
 * @return  Primer State
 */
static inline uint8_t mavlink_msg_simba_rocket_heartbeat_get_primer_state(const mavlink_message_t* msg)
{
    return _MAV_RETURN_uint8_t(msg,  15);
}

/**
 * @brief Decode a simba_rocket_heartbeat message into a struct
 *
 * @param msg The message to decode
 * @param simba_rocket_heartbeat C-struct to decode the message contents into
 */
static inline void mavlink_msg_simba_rocket_heartbeat_decode(const mavlink_message_t* msg, mavlink_simba_rocket_heartbeat_t* simba_rocket_heartbeat)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    simba_rocket_heartbeat->timestamp = mavlink_msg_simba_rocket_heartbeat_get_timestamp(msg);
    simba_rocket_heartbeat->apps_alive = mavlink_msg_simba_rocket_heartbeat_get_apps_alive(msg);
    simba_rocket_heartbeat->flight_computer_state = mavlink_msg_simba_rocket_heartbeat_get_flight_computer_state(msg);
    simba_rocket_heartbeat->engine_computer_state = mavlink_msg_simba_rocket_heartbeat_get_engine_computer_state(msg);
    simba_rocket_heartbeat->values = mavlink_msg_simba_rocket_heartbeat_get_values(msg);
    simba_rocket_heartbeat->primer_state = mavlink_msg_simba_rocket_heartbeat_get_primer_state(msg);
#else
        uint8_t len = msg->len < MAVLINK_MSG_ID_SIMBA_ROCKET_HEARTBEAT_LEN? msg->len : MAVLINK_MSG_ID_SIMBA_ROCKET_HEARTBEAT_LEN;
        memset(simba_rocket_heartbeat, 0, MAVLINK_MSG_ID_SIMBA_ROCKET_HEARTBEAT_LEN);
    memcpy(simba_rocket_heartbeat, _MAV_PAYLOAD(msg), len);
#endif
}
