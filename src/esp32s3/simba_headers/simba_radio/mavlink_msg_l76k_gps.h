#pragma once
// MESSAGE L76K_GPS PACKING

#define MAVLINK_MSG_ID_L76K_GPS 24


typedef struct __mavlink_l76k_gps_t {
 uint32_t date; /*< [compact] Date in NMEA 0183 format (ddmmyy)*/
 uint32_t time; /*< [compact] Time in NMEA 0183 format centiseconds (hhmmsscc)*/
 int32_t lat; /*< [degE7] Latitude (WGS84, EGM96 ellipsoid)*/
 int32_t lon; /*< [degE7] Longitude (WGS84, EGM96 ellipsoid)*/
 float speed; /*< [m/s] GPS speed*/
 float course; /*< [deg] Course*/
 int32_t alt; /*< [mm] Altitude (MSL). Positive for up.*/
 float hdop; /*< [unitless] Horizontal dilution of position*/
 uint32_t sentences_with_fix; /*<  Number of sentences with a valid fix*/
 uint8_t satellites_visible; /*<  Number of satellites visible*/
} mavlink_l76k_gps_t;

#define MAVLINK_MSG_ID_L76K_GPS_LEN 37
#define MAVLINK_MSG_ID_L76K_GPS_MIN_LEN 37
#define MAVLINK_MSG_ID_24_LEN 37
#define MAVLINK_MSG_ID_24_MIN_LEN 37

#define MAVLINK_MSG_ID_L76K_GPS_CRC 82
#define MAVLINK_MSG_ID_24_CRC 82



#if MAVLINK_COMMAND_24BIT
#define MAVLINK_MESSAGE_INFO_L76K_GPS { \
    24, \
    "L76K_GPS", \
    10, \
    {  { "date", NULL, MAVLINK_TYPE_UINT32_T, 0, 0, offsetof(mavlink_l76k_gps_t, date) }, \
         { "time", NULL, MAVLINK_TYPE_UINT32_T, 0, 4, offsetof(mavlink_l76k_gps_t, time) }, \
         { "lat", NULL, MAVLINK_TYPE_INT32_T, 0, 8, offsetof(mavlink_l76k_gps_t, lat) }, \
         { "lon", NULL, MAVLINK_TYPE_INT32_T, 0, 12, offsetof(mavlink_l76k_gps_t, lon) }, \
         { "speed", NULL, MAVLINK_TYPE_FLOAT, 0, 16, offsetof(mavlink_l76k_gps_t, speed) }, \
         { "course", NULL, MAVLINK_TYPE_FLOAT, 0, 20, offsetof(mavlink_l76k_gps_t, course) }, \
         { "alt", NULL, MAVLINK_TYPE_INT32_T, 0, 24, offsetof(mavlink_l76k_gps_t, alt) }, \
         { "satellites_visible", NULL, MAVLINK_TYPE_UINT8_T, 0, 36, offsetof(mavlink_l76k_gps_t, satellites_visible) }, \
         { "hdop", NULL, MAVLINK_TYPE_FLOAT, 0, 28, offsetof(mavlink_l76k_gps_t, hdop) }, \
         { "sentences_with_fix", NULL, MAVLINK_TYPE_UINT32_T, 0, 32, offsetof(mavlink_l76k_gps_t, sentences_with_fix) }, \
         } \
}
#else
#define MAVLINK_MESSAGE_INFO_L76K_GPS { \
    "L76K_GPS", \
    10, \
    {  { "date", NULL, MAVLINK_TYPE_UINT32_T, 0, 0, offsetof(mavlink_l76k_gps_t, date) }, \
         { "time", NULL, MAVLINK_TYPE_UINT32_T, 0, 4, offsetof(mavlink_l76k_gps_t, time) }, \
         { "lat", NULL, MAVLINK_TYPE_INT32_T, 0, 8, offsetof(mavlink_l76k_gps_t, lat) }, \
         { "lon", NULL, MAVLINK_TYPE_INT32_T, 0, 12, offsetof(mavlink_l76k_gps_t, lon) }, \
         { "speed", NULL, MAVLINK_TYPE_FLOAT, 0, 16, offsetof(mavlink_l76k_gps_t, speed) }, \
         { "course", NULL, MAVLINK_TYPE_FLOAT, 0, 20, offsetof(mavlink_l76k_gps_t, course) }, \
         { "alt", NULL, MAVLINK_TYPE_INT32_T, 0, 24, offsetof(mavlink_l76k_gps_t, alt) }, \
         { "satellites_visible", NULL, MAVLINK_TYPE_UINT8_T, 0, 36, offsetof(mavlink_l76k_gps_t, satellites_visible) }, \
         { "hdop", NULL, MAVLINK_TYPE_FLOAT, 0, 28, offsetof(mavlink_l76k_gps_t, hdop) }, \
         { "sentences_with_fix", NULL, MAVLINK_TYPE_UINT32_T, 0, 32, offsetof(mavlink_l76k_gps_t, sentences_with_fix) }, \
         } \
}
#endif

/**
 * @brief Pack a l76k_gps message
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param msg The MAVLink message to compress the data into
 *
 * @param date [compact] Date in NMEA 0183 format (ddmmyy)
 * @param time [compact] Time in NMEA 0183 format centiseconds (hhmmsscc)
 * @param lat [degE7] Latitude (WGS84, EGM96 ellipsoid)
 * @param lon [degE7] Longitude (WGS84, EGM96 ellipsoid)
 * @param speed [m/s] GPS speed
 * @param course [deg] Course
 * @param alt [mm] Altitude (MSL). Positive for up.
 * @param satellites_visible  Number of satellites visible
 * @param hdop [unitless] Horizontal dilution of position
 * @param sentences_with_fix  Number of sentences with a valid fix
 * @return length of the message in bytes (excluding serial stream start sign)
 */
static inline uint16_t mavlink_msg_l76k_gps_pack(uint8_t system_id, uint8_t component_id, mavlink_message_t* msg,
                               uint32_t date, uint32_t time, int32_t lat, int32_t lon, float speed, float course, int32_t alt, uint8_t satellites_visible, float hdop, uint32_t sentences_with_fix)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char buf[MAVLINK_MSG_ID_L76K_GPS_LEN];
    _mav_put_uint32_t(buf, 0, date);
    _mav_put_uint32_t(buf, 4, time);
    _mav_put_int32_t(buf, 8, lat);
    _mav_put_int32_t(buf, 12, lon);
    _mav_put_float(buf, 16, speed);
    _mav_put_float(buf, 20, course);
    _mav_put_int32_t(buf, 24, alt);
    _mav_put_float(buf, 28, hdop);
    _mav_put_uint32_t(buf, 32, sentences_with_fix);
    _mav_put_uint8_t(buf, 36, satellites_visible);

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), buf, MAVLINK_MSG_ID_L76K_GPS_LEN);
#else
    mavlink_l76k_gps_t packet;
    packet.date = date;
    packet.time = time;
    packet.lat = lat;
    packet.lon = lon;
    packet.speed = speed;
    packet.course = course;
    packet.alt = alt;
    packet.hdop = hdop;
    packet.sentences_with_fix = sentences_with_fix;
    packet.satellites_visible = satellites_visible;

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), &packet, MAVLINK_MSG_ID_L76K_GPS_LEN);
#endif

    msg->msgid = MAVLINK_MSG_ID_L76K_GPS;
    return mavlink_finalize_message(msg, system_id, component_id, MAVLINK_MSG_ID_L76K_GPS_MIN_LEN, MAVLINK_MSG_ID_L76K_GPS_LEN, MAVLINK_MSG_ID_L76K_GPS_CRC);
}

/**
 * @brief Pack a l76k_gps message
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param status MAVLink status structure
 * @param msg The MAVLink message to compress the data into
 *
 * @param date [compact] Date in NMEA 0183 format (ddmmyy)
 * @param time [compact] Time in NMEA 0183 format centiseconds (hhmmsscc)
 * @param lat [degE7] Latitude (WGS84, EGM96 ellipsoid)
 * @param lon [degE7] Longitude (WGS84, EGM96 ellipsoid)
 * @param speed [m/s] GPS speed
 * @param course [deg] Course
 * @param alt [mm] Altitude (MSL). Positive for up.
 * @param satellites_visible  Number of satellites visible
 * @param hdop [unitless] Horizontal dilution of position
 * @param sentences_with_fix  Number of sentences with a valid fix
 * @return length of the message in bytes (excluding serial stream start sign)
 */
static inline uint16_t mavlink_msg_l76k_gps_pack_status(uint8_t system_id, uint8_t component_id, mavlink_status_t *_status, mavlink_message_t* msg,
                               uint32_t date, uint32_t time, int32_t lat, int32_t lon, float speed, float course, int32_t alt, uint8_t satellites_visible, float hdop, uint32_t sentences_with_fix)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char buf[MAVLINK_MSG_ID_L76K_GPS_LEN];
    _mav_put_uint32_t(buf, 0, date);
    _mav_put_uint32_t(buf, 4, time);
    _mav_put_int32_t(buf, 8, lat);
    _mav_put_int32_t(buf, 12, lon);
    _mav_put_float(buf, 16, speed);
    _mav_put_float(buf, 20, course);
    _mav_put_int32_t(buf, 24, alt);
    _mav_put_float(buf, 28, hdop);
    _mav_put_uint32_t(buf, 32, sentences_with_fix);
    _mav_put_uint8_t(buf, 36, satellites_visible);

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), buf, MAVLINK_MSG_ID_L76K_GPS_LEN);
#else
    mavlink_l76k_gps_t packet;
    packet.date = date;
    packet.time = time;
    packet.lat = lat;
    packet.lon = lon;
    packet.speed = speed;
    packet.course = course;
    packet.alt = alt;
    packet.hdop = hdop;
    packet.sentences_with_fix = sentences_with_fix;
    packet.satellites_visible = satellites_visible;

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), &packet, MAVLINK_MSG_ID_L76K_GPS_LEN);
#endif

    msg->msgid = MAVLINK_MSG_ID_L76K_GPS;
#if MAVLINK_CRC_EXTRA
    return mavlink_finalize_message_buffer(msg, system_id, component_id, _status, MAVLINK_MSG_ID_L76K_GPS_MIN_LEN, MAVLINK_MSG_ID_L76K_GPS_LEN, MAVLINK_MSG_ID_L76K_GPS_CRC);
#else
    return mavlink_finalize_message_buffer(msg, system_id, component_id, _status, MAVLINK_MSG_ID_L76K_GPS_MIN_LEN, MAVLINK_MSG_ID_L76K_GPS_LEN);
#endif
}

/**
 * @brief Pack a l76k_gps message on a channel
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param chan The MAVLink channel this message will be sent over
 * @param msg The MAVLink message to compress the data into
 * @param date [compact] Date in NMEA 0183 format (ddmmyy)
 * @param time [compact] Time in NMEA 0183 format centiseconds (hhmmsscc)
 * @param lat [degE7] Latitude (WGS84, EGM96 ellipsoid)
 * @param lon [degE7] Longitude (WGS84, EGM96 ellipsoid)
 * @param speed [m/s] GPS speed
 * @param course [deg] Course
 * @param alt [mm] Altitude (MSL). Positive for up.
 * @param satellites_visible  Number of satellites visible
 * @param hdop [unitless] Horizontal dilution of position
 * @param sentences_with_fix  Number of sentences with a valid fix
 * @return length of the message in bytes (excluding serial stream start sign)
 */
static inline uint16_t mavlink_msg_l76k_gps_pack_chan(uint8_t system_id, uint8_t component_id, uint8_t chan,
                               mavlink_message_t* msg,
                                   uint32_t date,uint32_t time,int32_t lat,int32_t lon,float speed,float course,int32_t alt,uint8_t satellites_visible,float hdop,uint32_t sentences_with_fix)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char buf[MAVLINK_MSG_ID_L76K_GPS_LEN];
    _mav_put_uint32_t(buf, 0, date);
    _mav_put_uint32_t(buf, 4, time);
    _mav_put_int32_t(buf, 8, lat);
    _mav_put_int32_t(buf, 12, lon);
    _mav_put_float(buf, 16, speed);
    _mav_put_float(buf, 20, course);
    _mav_put_int32_t(buf, 24, alt);
    _mav_put_float(buf, 28, hdop);
    _mav_put_uint32_t(buf, 32, sentences_with_fix);
    _mav_put_uint8_t(buf, 36, satellites_visible);

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), buf, MAVLINK_MSG_ID_L76K_GPS_LEN);
#else
    mavlink_l76k_gps_t packet;
    packet.date = date;
    packet.time = time;
    packet.lat = lat;
    packet.lon = lon;
    packet.speed = speed;
    packet.course = course;
    packet.alt = alt;
    packet.hdop = hdop;
    packet.sentences_with_fix = sentences_with_fix;
    packet.satellites_visible = satellites_visible;

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), &packet, MAVLINK_MSG_ID_L76K_GPS_LEN);
#endif

    msg->msgid = MAVLINK_MSG_ID_L76K_GPS;
    return mavlink_finalize_message_chan(msg, system_id, component_id, chan, MAVLINK_MSG_ID_L76K_GPS_MIN_LEN, MAVLINK_MSG_ID_L76K_GPS_LEN, MAVLINK_MSG_ID_L76K_GPS_CRC);
}

/**
 * @brief Encode a l76k_gps struct
 *
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param msg The MAVLink message to compress the data into
 * @param l76k_gps C-struct to read the message contents from
 */
static inline uint16_t mavlink_msg_l76k_gps_encode(uint8_t system_id, uint8_t component_id, mavlink_message_t* msg, const mavlink_l76k_gps_t* l76k_gps)
{
    return mavlink_msg_l76k_gps_pack(system_id, component_id, msg, l76k_gps->date, l76k_gps->time, l76k_gps->lat, l76k_gps->lon, l76k_gps->speed, l76k_gps->course, l76k_gps->alt, l76k_gps->satellites_visible, l76k_gps->hdop, l76k_gps->sentences_with_fix);
}

/**
 * @brief Encode a l76k_gps struct on a channel
 *
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param chan The MAVLink channel this message will be sent over
 * @param msg The MAVLink message to compress the data into
 * @param l76k_gps C-struct to read the message contents from
 */
static inline uint16_t mavlink_msg_l76k_gps_encode_chan(uint8_t system_id, uint8_t component_id, uint8_t chan, mavlink_message_t* msg, const mavlink_l76k_gps_t* l76k_gps)
{
    return mavlink_msg_l76k_gps_pack_chan(system_id, component_id, chan, msg, l76k_gps->date, l76k_gps->time, l76k_gps->lat, l76k_gps->lon, l76k_gps->speed, l76k_gps->course, l76k_gps->alt, l76k_gps->satellites_visible, l76k_gps->hdop, l76k_gps->sentences_with_fix);
}

/**
 * @brief Encode a l76k_gps struct with provided status structure
 *
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param status MAVLink status structure
 * @param msg The MAVLink message to compress the data into
 * @param l76k_gps C-struct to read the message contents from
 */
static inline uint16_t mavlink_msg_l76k_gps_encode_status(uint8_t system_id, uint8_t component_id, mavlink_status_t* _status, mavlink_message_t* msg, const mavlink_l76k_gps_t* l76k_gps)
{
    return mavlink_msg_l76k_gps_pack_status(system_id, component_id, _status, msg,  l76k_gps->date, l76k_gps->time, l76k_gps->lat, l76k_gps->lon, l76k_gps->speed, l76k_gps->course, l76k_gps->alt, l76k_gps->satellites_visible, l76k_gps->hdop, l76k_gps->sentences_with_fix);
}

/**
 * @brief Send a l76k_gps message
 * @param chan MAVLink channel to send the message
 *
 * @param date [compact] Date in NMEA 0183 format (ddmmyy)
 * @param time [compact] Time in NMEA 0183 format centiseconds (hhmmsscc)
 * @param lat [degE7] Latitude (WGS84, EGM96 ellipsoid)
 * @param lon [degE7] Longitude (WGS84, EGM96 ellipsoid)
 * @param speed [m/s] GPS speed
 * @param course [deg] Course
 * @param alt [mm] Altitude (MSL). Positive for up.
 * @param satellites_visible  Number of satellites visible
 * @param hdop [unitless] Horizontal dilution of position
 * @param sentences_with_fix  Number of sentences with a valid fix
 */
#ifdef MAVLINK_USE_CONVENIENCE_FUNCTIONS

static inline void mavlink_msg_l76k_gps_send(mavlink_channel_t chan, uint32_t date, uint32_t time, int32_t lat, int32_t lon, float speed, float course, int32_t alt, uint8_t satellites_visible, float hdop, uint32_t sentences_with_fix)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char buf[MAVLINK_MSG_ID_L76K_GPS_LEN];
    _mav_put_uint32_t(buf, 0, date);
    _mav_put_uint32_t(buf, 4, time);
    _mav_put_int32_t(buf, 8, lat);
    _mav_put_int32_t(buf, 12, lon);
    _mav_put_float(buf, 16, speed);
    _mav_put_float(buf, 20, course);
    _mav_put_int32_t(buf, 24, alt);
    _mav_put_float(buf, 28, hdop);
    _mav_put_uint32_t(buf, 32, sentences_with_fix);
    _mav_put_uint8_t(buf, 36, satellites_visible);

    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_L76K_GPS, buf, MAVLINK_MSG_ID_L76K_GPS_MIN_LEN, MAVLINK_MSG_ID_L76K_GPS_LEN, MAVLINK_MSG_ID_L76K_GPS_CRC);
#else
    mavlink_l76k_gps_t packet;
    packet.date = date;
    packet.time = time;
    packet.lat = lat;
    packet.lon = lon;
    packet.speed = speed;
    packet.course = course;
    packet.alt = alt;
    packet.hdop = hdop;
    packet.sentences_with_fix = sentences_with_fix;
    packet.satellites_visible = satellites_visible;

    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_L76K_GPS, (const char *)&packet, MAVLINK_MSG_ID_L76K_GPS_MIN_LEN, MAVLINK_MSG_ID_L76K_GPS_LEN, MAVLINK_MSG_ID_L76K_GPS_CRC);
#endif
}

/**
 * @brief Send a l76k_gps message
 * @param chan MAVLink channel to send the message
 * @param struct The MAVLink struct to serialize
 */
static inline void mavlink_msg_l76k_gps_send_struct(mavlink_channel_t chan, const mavlink_l76k_gps_t* l76k_gps)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    mavlink_msg_l76k_gps_send(chan, l76k_gps->date, l76k_gps->time, l76k_gps->lat, l76k_gps->lon, l76k_gps->speed, l76k_gps->course, l76k_gps->alt, l76k_gps->satellites_visible, l76k_gps->hdop, l76k_gps->sentences_with_fix);
#else
    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_L76K_GPS, (const char *)l76k_gps, MAVLINK_MSG_ID_L76K_GPS_MIN_LEN, MAVLINK_MSG_ID_L76K_GPS_LEN, MAVLINK_MSG_ID_L76K_GPS_CRC);
#endif
}

#if MAVLINK_MSG_ID_L76K_GPS_LEN <= MAVLINK_MAX_PAYLOAD_LEN
/*
  This variant of _send() can be used to save stack space by reusing
  memory from the receive buffer.  The caller provides a
  mavlink_message_t which is the size of a full mavlink message. This
  is usually the receive buffer for the channel, and allows a reply to an
  incoming message with minimum stack space usage.
 */
static inline void mavlink_msg_l76k_gps_send_buf(mavlink_message_t *msgbuf, mavlink_channel_t chan,  uint32_t date, uint32_t time, int32_t lat, int32_t lon, float speed, float course, int32_t alt, uint8_t satellites_visible, float hdop, uint32_t sentences_with_fix)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char *buf = (char *)msgbuf;
    _mav_put_uint32_t(buf, 0, date);
    _mav_put_uint32_t(buf, 4, time);
    _mav_put_int32_t(buf, 8, lat);
    _mav_put_int32_t(buf, 12, lon);
    _mav_put_float(buf, 16, speed);
    _mav_put_float(buf, 20, course);
    _mav_put_int32_t(buf, 24, alt);
    _mav_put_float(buf, 28, hdop);
    _mav_put_uint32_t(buf, 32, sentences_with_fix);
    _mav_put_uint8_t(buf, 36, satellites_visible);

    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_L76K_GPS, buf, MAVLINK_MSG_ID_L76K_GPS_MIN_LEN, MAVLINK_MSG_ID_L76K_GPS_LEN, MAVLINK_MSG_ID_L76K_GPS_CRC);
#else
    mavlink_l76k_gps_t *packet = (mavlink_l76k_gps_t *)msgbuf;
    packet->date = date;
    packet->time = time;
    packet->lat = lat;
    packet->lon = lon;
    packet->speed = speed;
    packet->course = course;
    packet->alt = alt;
    packet->hdop = hdop;
    packet->sentences_with_fix = sentences_with_fix;
    packet->satellites_visible = satellites_visible;

    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_L76K_GPS, (const char *)packet, MAVLINK_MSG_ID_L76K_GPS_MIN_LEN, MAVLINK_MSG_ID_L76K_GPS_LEN, MAVLINK_MSG_ID_L76K_GPS_CRC);
#endif
}
#endif

#endif

// MESSAGE L76K_GPS UNPACKING


/**
 * @brief Get field date from l76k_gps message
 *
 * @return [compact] Date in NMEA 0183 format (ddmmyy)
 */
static inline uint32_t mavlink_msg_l76k_gps_get_date(const mavlink_message_t* msg)
{
    return _MAV_RETURN_uint32_t(msg,  0);
}

/**
 * @brief Get field time from l76k_gps message
 *
 * @return [compact] Time in NMEA 0183 format centiseconds (hhmmsscc)
 */
static inline uint32_t mavlink_msg_l76k_gps_get_time(const mavlink_message_t* msg)
{
    return _MAV_RETURN_uint32_t(msg,  4);
}

/**
 * @brief Get field lat from l76k_gps message
 *
 * @return [degE7] Latitude (WGS84, EGM96 ellipsoid)
 */
static inline int32_t mavlink_msg_l76k_gps_get_lat(const mavlink_message_t* msg)
{
    return _MAV_RETURN_int32_t(msg,  8);
}

/**
 * @brief Get field lon from l76k_gps message
 *
 * @return [degE7] Longitude (WGS84, EGM96 ellipsoid)
 */
static inline int32_t mavlink_msg_l76k_gps_get_lon(const mavlink_message_t* msg)
{
    return _MAV_RETURN_int32_t(msg,  12);
}

/**
 * @brief Get field speed from l76k_gps message
 *
 * @return [m/s] GPS speed
 */
static inline float mavlink_msg_l76k_gps_get_speed(const mavlink_message_t* msg)
{
    return _MAV_RETURN_float(msg,  16);
}

/**
 * @brief Get field course from l76k_gps message
 *
 * @return [deg] Course
 */
static inline float mavlink_msg_l76k_gps_get_course(const mavlink_message_t* msg)
{
    return _MAV_RETURN_float(msg,  20);
}

/**
 * @brief Get field alt from l76k_gps message
 *
 * @return [mm] Altitude (MSL). Positive for up.
 */
static inline int32_t mavlink_msg_l76k_gps_get_alt(const mavlink_message_t* msg)
{
    return _MAV_RETURN_int32_t(msg,  24);
}

/**
 * @brief Get field satellites_visible from l76k_gps message
 *
 * @return  Number of satellites visible
 */
static inline uint8_t mavlink_msg_l76k_gps_get_satellites_visible(const mavlink_message_t* msg)
{
    return _MAV_RETURN_uint8_t(msg,  36);
}

/**
 * @brief Get field hdop from l76k_gps message
 *
 * @return [unitless] Horizontal dilution of position
 */
static inline float mavlink_msg_l76k_gps_get_hdop(const mavlink_message_t* msg)
{
    return _MAV_RETURN_float(msg,  28);
}

/**
 * @brief Get field sentences_with_fix from l76k_gps message
 *
 * @return  Number of sentences with a valid fix
 */
static inline uint32_t mavlink_msg_l76k_gps_get_sentences_with_fix(const mavlink_message_t* msg)
{
    return _MAV_RETURN_uint32_t(msg,  32);
}

/**
 * @brief Decode a l76k_gps message into a struct
 *
 * @param msg The message to decode
 * @param l76k_gps C-struct to decode the message contents into
 */
static inline void mavlink_msg_l76k_gps_decode(const mavlink_message_t* msg, mavlink_l76k_gps_t* l76k_gps)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    l76k_gps->date = mavlink_msg_l76k_gps_get_date(msg);
    l76k_gps->time = mavlink_msg_l76k_gps_get_time(msg);
    l76k_gps->lat = mavlink_msg_l76k_gps_get_lat(msg);
    l76k_gps->lon = mavlink_msg_l76k_gps_get_lon(msg);
    l76k_gps->speed = mavlink_msg_l76k_gps_get_speed(msg);
    l76k_gps->course = mavlink_msg_l76k_gps_get_course(msg);
    l76k_gps->alt = mavlink_msg_l76k_gps_get_alt(msg);
    l76k_gps->hdop = mavlink_msg_l76k_gps_get_hdop(msg);
    l76k_gps->sentences_with_fix = mavlink_msg_l76k_gps_get_sentences_with_fix(msg);
    l76k_gps->satellites_visible = mavlink_msg_l76k_gps_get_satellites_visible(msg);
#else
        uint8_t len = msg->len < MAVLINK_MSG_ID_L76K_GPS_LEN? msg->len : MAVLINK_MSG_ID_L76K_GPS_LEN;
        memset(l76k_gps, 0, MAVLINK_MSG_ID_L76K_GPS_LEN);
    memcpy(l76k_gps, _MAV_PAYLOAD(msg), len);
#endif
}
