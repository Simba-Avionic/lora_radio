# GPS message - long form from L76K GNSS module using NMEA sentences
# ---

# <field type="uint32_t" name="date" units="compact">Date in NMEA 0183 format (ddmmyy)</field>
# <field type="uint32_t" name="time" units="compact">Time in NMEA 0183 format centiseconds (hhmmsscc)</field>
# <field type="int32_t" name="lat" units="degE7">Latitude (WGS84, EGM96 ellipsoid)</field>
# <field type="int32_t" name="lon" units="degE7">Longitude (WGS84, EGM96 ellipsoid)</field>
# <field type="float" name="speed" units="m/s">GPS speed</field>
# <field type="float" name="course" units="deg">Course</field>
# <field type="int32_t" name="alt" units="mm">Altitude (MSL). Positive for up.</field>
# <field type="uint8_t" name="satellites_visible">Number of satellites visible</field>
# <field type="float" name="hdop" units="unitless">Horizontal dilution of position</field>
# <field type="uint32_t" name="sentences_with_fix">Number of sentences with a valid fix</field>

std_msgs/Header header
uint32 date
uint32 time
float64 latitude_deg
float64 longitude_deg
float32 speed_mps
float32 course_deg
float64 altitude_m
uint8 satellites_visible
float32 hdop
uint32 sentences_with_fix