#pragma once
// MESSAGE SIMBA_TANK_SENSORS PACKING

#define MAVLINK_MSG_ID_SIMBA_TANK_SENSORS 69


typedef struct __mavlink_simba_tank_sensors_t {
 int16_t upper_tank; /*<  Upper tank temperature*/
 int16_t middle_tank; /*<  Middle tank temperature*/
 int16_t lower_tank; /*<  Lower tank temperature*/
 uint16_t pressure; /*<  Tank pressure*/
} mavlink_simba_tank_sensors_t;

#define MAVLINK_MSG_ID_SIMBA_TANK_SENSORS_LEN 8
#define MAVLINK_MSG_ID_SIMBA_TANK_SENSORS_MIN_LEN 8
#define MAVLINK_MSG_ID_69_LEN 8
#define MAVLINK_MSG_ID_69_MIN_LEN 8

#define MAVLINK_MSG_ID_SIMBA_TANK_SENSORS_CRC 142
#define MAVLINK_MSG_ID_69_CRC 142



#if MAVLINK_COMMAND_24BIT
#define MAVLINK_MESSAGE_INFO_SIMBA_TANK_SENSORS { \
    69, \
    "SIMBA_TANK_SENSORS", \
    4, \
    {  { "upper_tank", NULL, MAVLINK_TYPE_INT16_T, 0, 0, offsetof(mavlink_simba_tank_sensors_t, upper_tank) }, \
         { "middle_tank", NULL, MAVLINK_TYPE_INT16_T, 0, 2, offsetof(mavlink_simba_tank_sensors_t, middle_tank) }, \
         { "lower_tank", NULL, MAVLINK_TYPE_INT16_T, 0, 4, offsetof(mavlink_simba_tank_sensors_t, lower_tank) }, \
         { "pressure", NULL, MAVLINK_TYPE_UINT16_T, 0, 6, offsetof(mavlink_simba_tank_sensors_t, pressure) }, \
         } \
}
#else
#define MAVLINK_MESSAGE_INFO_SIMBA_TANK_SENSORS { \
    "SIMBA_TANK_SENSORS", \
    4, \
    {  { "upper_tank", NULL, MAVLINK_TYPE_INT16_T, 0, 0, offsetof(mavlink_simba_tank_sensors_t, upper_tank) }, \
         { "middle_tank", NULL, MAVLINK_TYPE_INT16_T, 0, 2, offsetof(mavlink_simba_tank_sensors_t, middle_tank) }, \
         { "lower_tank", NULL, MAVLINK_TYPE_INT16_T, 0, 4, offsetof(mavlink_simba_tank_sensors_t, lower_tank) }, \
         { "pressure", NULL, MAVLINK_TYPE_UINT16_T, 0, 6, offsetof(mavlink_simba_tank_sensors_t, pressure) }, \
         } \
}
#endif

/**
 * @brief Pack a simba_tank_sensors message
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param msg The MAVLink message to compress the data into
 *
 * @param upper_tank  Upper tank temperature
 * @param middle_tank  Middle tank temperature
 * @param lower_tank  Lower tank temperature
 * @param pressure  Tank pressure
 * @return length of the message in bytes (excluding serial stream start sign)
 */
static inline uint16_t mavlink_msg_simba_tank_sensors_pack(uint8_t system_id, uint8_t component_id, mavlink_message_t* msg,
                               int16_t upper_tank, int16_t middle_tank, int16_t lower_tank, uint16_t pressure)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char buf[MAVLINK_MSG_ID_SIMBA_TANK_SENSORS_LEN];
    _mav_put_int16_t(buf, 0, upper_tank);
    _mav_put_int16_t(buf, 2, middle_tank);
    _mav_put_int16_t(buf, 4, lower_tank);
    _mav_put_uint16_t(buf, 6, pressure);

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), buf, MAVLINK_MSG_ID_SIMBA_TANK_SENSORS_LEN);
#else
    mavlink_simba_tank_sensors_t packet;
    packet.upper_tank = upper_tank;
    packet.middle_tank = middle_tank;
    packet.lower_tank = lower_tank;
    packet.pressure = pressure;

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), &packet, MAVLINK_MSG_ID_SIMBA_TANK_SENSORS_LEN);
#endif

    msg->msgid = MAVLINK_MSG_ID_SIMBA_TANK_SENSORS;
    return mavlink_finalize_message(msg, system_id, component_id, MAVLINK_MSG_ID_SIMBA_TANK_SENSORS_MIN_LEN, MAVLINK_MSG_ID_SIMBA_TANK_SENSORS_LEN, MAVLINK_MSG_ID_SIMBA_TANK_SENSORS_CRC);
}

/**
 * @brief Pack a simba_tank_sensors message
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param status MAVLink status structure
 * @param msg The MAVLink message to compress the data into
 *
 * @param upper_tank  Upper tank temperature
 * @param middle_tank  Middle tank temperature
 * @param lower_tank  Lower tank temperature
 * @param pressure  Tank pressure
 * @return length of the message in bytes (excluding serial stream start sign)
 */
static inline uint16_t mavlink_msg_simba_tank_sensors_pack_status(uint8_t system_id, uint8_t component_id, mavlink_status_t *_status, mavlink_message_t* msg,
                               int16_t upper_tank, int16_t middle_tank, int16_t lower_tank, uint16_t pressure)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char buf[MAVLINK_MSG_ID_SIMBA_TANK_SENSORS_LEN];
    _mav_put_int16_t(buf, 0, upper_tank);
    _mav_put_int16_t(buf, 2, middle_tank);
    _mav_put_int16_t(buf, 4, lower_tank);
    _mav_put_uint16_t(buf, 6, pressure);

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), buf, MAVLINK_MSG_ID_SIMBA_TANK_SENSORS_LEN);
#else
    mavlink_simba_tank_sensors_t packet;
    packet.upper_tank = upper_tank;
    packet.middle_tank = middle_tank;
    packet.lower_tank = lower_tank;
    packet.pressure = pressure;

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), &packet, MAVLINK_MSG_ID_SIMBA_TANK_SENSORS_LEN);
#endif

    msg->msgid = MAVLINK_MSG_ID_SIMBA_TANK_SENSORS;
#if MAVLINK_CRC_EXTRA
    return mavlink_finalize_message_buffer(msg, system_id, component_id, _status, MAVLINK_MSG_ID_SIMBA_TANK_SENSORS_MIN_LEN, MAVLINK_MSG_ID_SIMBA_TANK_SENSORS_LEN, MAVLINK_MSG_ID_SIMBA_TANK_SENSORS_CRC);
#else
    return mavlink_finalize_message_buffer(msg, system_id, component_id, _status, MAVLINK_MSG_ID_SIMBA_TANK_SENSORS_MIN_LEN, MAVLINK_MSG_ID_SIMBA_TANK_SENSORS_LEN);
#endif
}

/**
 * @brief Pack a simba_tank_sensors message on a channel
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param chan The MAVLink channel this message will be sent over
 * @param msg The MAVLink message to compress the data into
 * @param upper_tank  Upper tank temperature
 * @param middle_tank  Middle tank temperature
 * @param lower_tank  Lower tank temperature
 * @param pressure  Tank pressure
 * @return length of the message in bytes (excluding serial stream start sign)
 */
static inline uint16_t mavlink_msg_simba_tank_sensors_pack_chan(uint8_t system_id, uint8_t component_id, uint8_t chan,
                               mavlink_message_t* msg,
                                   int16_t upper_tank,int16_t middle_tank,int16_t lower_tank,uint16_t pressure)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char buf[MAVLINK_MSG_ID_SIMBA_TANK_SENSORS_LEN];
    _mav_put_int16_t(buf, 0, upper_tank);
    _mav_put_int16_t(buf, 2, middle_tank);
    _mav_put_int16_t(buf, 4, lower_tank);
    _mav_put_uint16_t(buf, 6, pressure);

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), buf, MAVLINK_MSG_ID_SIMBA_TANK_SENSORS_LEN);
#else
    mavlink_simba_tank_sensors_t packet;
    packet.upper_tank = upper_tank;
    packet.middle_tank = middle_tank;
    packet.lower_tank = lower_tank;
    packet.pressure = pressure;

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), &packet, MAVLINK_MSG_ID_SIMBA_TANK_SENSORS_LEN);
#endif

    msg->msgid = MAVLINK_MSG_ID_SIMBA_TANK_SENSORS;
    return mavlink_finalize_message_chan(msg, system_id, component_id, chan, MAVLINK_MSG_ID_SIMBA_TANK_SENSORS_MIN_LEN, MAVLINK_MSG_ID_SIMBA_TANK_SENSORS_LEN, MAVLINK_MSG_ID_SIMBA_TANK_SENSORS_CRC);
}

/**
 * @brief Encode a simba_tank_sensors struct
 *
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param msg The MAVLink message to compress the data into
 * @param simba_tank_sensors C-struct to read the message contents from
 */
static inline uint16_t mavlink_msg_simba_tank_sensors_encode(uint8_t system_id, uint8_t component_id, mavlink_message_t* msg, const mavlink_simba_tank_sensors_t* simba_tank_sensors)
{
    return mavlink_msg_simba_tank_sensors_pack(system_id, component_id, msg, simba_tank_sensors->upper_tank, simba_tank_sensors->middle_tank, simba_tank_sensors->lower_tank, simba_tank_sensors->pressure);
}

/**
 * @brief Encode a simba_tank_sensors struct on a channel
 *
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param chan The MAVLink channel this message will be sent over
 * @param msg The MAVLink message to compress the data into
 * @param simba_tank_sensors C-struct to read the message contents from
 */
static inline uint16_t mavlink_msg_simba_tank_sensors_encode_chan(uint8_t system_id, uint8_t component_id, uint8_t chan, mavlink_message_t* msg, const mavlink_simba_tank_sensors_t* simba_tank_sensors)
{
    return mavlink_msg_simba_tank_sensors_pack_chan(system_id, component_id, chan, msg, simba_tank_sensors->upper_tank, simba_tank_sensors->middle_tank, simba_tank_sensors->lower_tank, simba_tank_sensors->pressure);
}

/**
 * @brief Encode a simba_tank_sensors struct with provided status structure
 *
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param status MAVLink status structure
 * @param msg The MAVLink message to compress the data into
 * @param simba_tank_sensors C-struct to read the message contents from
 */
static inline uint16_t mavlink_msg_simba_tank_sensors_encode_status(uint8_t system_id, uint8_t component_id, mavlink_status_t* _status, mavlink_message_t* msg, const mavlink_simba_tank_sensors_t* simba_tank_sensors)
{
    return mavlink_msg_simba_tank_sensors_pack_status(system_id, component_id, _status, msg,  simba_tank_sensors->upper_tank, simba_tank_sensors->middle_tank, simba_tank_sensors->lower_tank, simba_tank_sensors->pressure);
}

/**
 * @brief Send a simba_tank_sensors message
 * @param chan MAVLink channel to send the message
 *
 * @param upper_tank  Upper tank temperature
 * @param middle_tank  Middle tank temperature
 * @param lower_tank  Lower tank temperature
 * @param pressure  Tank pressure
 */
#ifdef MAVLINK_USE_CONVENIENCE_FUNCTIONS

static inline void mavlink_msg_simba_tank_sensors_send(mavlink_channel_t chan, int16_t upper_tank, int16_t middle_tank, int16_t lower_tank, uint16_t pressure)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char buf[MAVLINK_MSG_ID_SIMBA_TANK_SENSORS_LEN];
    _mav_put_int16_t(buf, 0, upper_tank);
    _mav_put_int16_t(buf, 2, middle_tank);
    _mav_put_int16_t(buf, 4, lower_tank);
    _mav_put_uint16_t(buf, 6, pressure);

    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_SIMBA_TANK_SENSORS, buf, MAVLINK_MSG_ID_SIMBA_TANK_SENSORS_MIN_LEN, MAVLINK_MSG_ID_SIMBA_TANK_SENSORS_LEN, MAVLINK_MSG_ID_SIMBA_TANK_SENSORS_CRC);
#else
    mavlink_simba_tank_sensors_t packet;
    packet.upper_tank = upper_tank;
    packet.middle_tank = middle_tank;
    packet.lower_tank = lower_tank;
    packet.pressure = pressure;

    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_SIMBA_TANK_SENSORS, (const char *)&packet, MAVLINK_MSG_ID_SIMBA_TANK_SENSORS_MIN_LEN, MAVLINK_MSG_ID_SIMBA_TANK_SENSORS_LEN, MAVLINK_MSG_ID_SIMBA_TANK_SENSORS_CRC);
#endif
}

/**
 * @brief Send a simba_tank_sensors message
 * @param chan MAVLink channel to send the message
 * @param struct The MAVLink struct to serialize
 */
static inline void mavlink_msg_simba_tank_sensors_send_struct(mavlink_channel_t chan, const mavlink_simba_tank_sensors_t* simba_tank_sensors)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    mavlink_msg_simba_tank_sensors_send(chan, simba_tank_sensors->upper_tank, simba_tank_sensors->middle_tank, simba_tank_sensors->lower_tank, simba_tank_sensors->pressure);
#else
    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_SIMBA_TANK_SENSORS, (const char *)simba_tank_sensors, MAVLINK_MSG_ID_SIMBA_TANK_SENSORS_MIN_LEN, MAVLINK_MSG_ID_SIMBA_TANK_SENSORS_LEN, MAVLINK_MSG_ID_SIMBA_TANK_SENSORS_CRC);
#endif
}

#if MAVLINK_MSG_ID_SIMBA_TANK_SENSORS_LEN <= MAVLINK_MAX_PAYLOAD_LEN
/*
  This variant of _send() can be used to save stack space by reusing
  memory from the receive buffer.  The caller provides a
  mavlink_message_t which is the size of a full mavlink message. This
  is usually the receive buffer for the channel, and allows a reply to an
  incoming message with minimum stack space usage.
 */
static inline void mavlink_msg_simba_tank_sensors_send_buf(mavlink_message_t *msgbuf, mavlink_channel_t chan,  int16_t upper_tank, int16_t middle_tank, int16_t lower_tank, uint16_t pressure)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char *buf = (char *)msgbuf;
    _mav_put_int16_t(buf, 0, upper_tank);
    _mav_put_int16_t(buf, 2, middle_tank);
    _mav_put_int16_t(buf, 4, lower_tank);
    _mav_put_uint16_t(buf, 6, pressure);

    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_SIMBA_TANK_SENSORS, buf, MAVLINK_MSG_ID_SIMBA_TANK_SENSORS_MIN_LEN, MAVLINK_MSG_ID_SIMBA_TANK_SENSORS_LEN, MAVLINK_MSG_ID_SIMBA_TANK_SENSORS_CRC);
#else
    mavlink_simba_tank_sensors_t *packet = (mavlink_simba_tank_sensors_t *)msgbuf;
    packet->upper_tank = upper_tank;
    packet->middle_tank = middle_tank;
    packet->lower_tank = lower_tank;
    packet->pressure = pressure;

    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_SIMBA_TANK_SENSORS, (const char *)packet, MAVLINK_MSG_ID_SIMBA_TANK_SENSORS_MIN_LEN, MAVLINK_MSG_ID_SIMBA_TANK_SENSORS_LEN, MAVLINK_MSG_ID_SIMBA_TANK_SENSORS_CRC);
#endif
}
#endif

#endif

// MESSAGE SIMBA_TANK_SENSORS UNPACKING


/**
 * @brief Get field upper_tank from simba_tank_sensors message
 *
 * @return  Upper tank temperature
 */
static inline int16_t mavlink_msg_simba_tank_sensors_get_upper_tank(const mavlink_message_t* msg)
{
    return _MAV_RETURN_int16_t(msg,  0);
}

/**
 * @brief Get field middle_tank from simba_tank_sensors message
 *
 * @return  Middle tank temperature
 */
static inline int16_t mavlink_msg_simba_tank_sensors_get_middle_tank(const mavlink_message_t* msg)
{
    return _MAV_RETURN_int16_t(msg,  2);
}

/**
 * @brief Get field lower_tank from simba_tank_sensors message
 *
 * @return  Lower tank temperature
 */
static inline int16_t mavlink_msg_simba_tank_sensors_get_lower_tank(const mavlink_message_t* msg)
{
    return _MAV_RETURN_int16_t(msg,  4);
}

/**
 * @brief Get field pressure from simba_tank_sensors message
 *
 * @return  Tank pressure
 */
static inline uint16_t mavlink_msg_simba_tank_sensors_get_pressure(const mavlink_message_t* msg)
{
    return _MAV_RETURN_uint16_t(msg,  6);
}

/**
 * @brief Decode a simba_tank_sensors message into a struct
 *
 * @param msg The message to decode
 * @param simba_tank_sensors C-struct to decode the message contents into
 */
static inline void mavlink_msg_simba_tank_sensors_decode(const mavlink_message_t* msg, mavlink_simba_tank_sensors_t* simba_tank_sensors)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    simba_tank_sensors->upper_tank = mavlink_msg_simba_tank_sensors_get_upper_tank(msg);
    simba_tank_sensors->middle_tank = mavlink_msg_simba_tank_sensors_get_middle_tank(msg);
    simba_tank_sensors->lower_tank = mavlink_msg_simba_tank_sensors_get_lower_tank(msg);
    simba_tank_sensors->pressure = mavlink_msg_simba_tank_sensors_get_pressure(msg);
#else
        uint8_t len = msg->len < MAVLINK_MSG_ID_SIMBA_TANK_SENSORS_LEN? msg->len : MAVLINK_MSG_ID_SIMBA_TANK_SENSORS_LEN;
        memset(simba_tank_sensors, 0, MAVLINK_MSG_ID_SIMBA_TANK_SENSORS_LEN);
    memcpy(simba_tank_sensors, _MAV_PAYLOAD(msg), len);
#endif
}
