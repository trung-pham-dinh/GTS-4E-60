#ifndef GTS_4E
#define GTS_4E

#include "Arduino.h"
#include <SoftwareSerial.h>

enum GGA_Data {
  GGA_Message_ID,
  GGA_UTC_Time,
  GGA_Latitude,
  GGA_NS_Indicator,
  GGA_Longitude,
  GGA_EW_Indicator,
  GGA_Position_Fix_Indicator,
  GGA_Satellites_Used,
  GGA_HDOP,
  GGA_MSL_Altitude,
  GGA_Units_1,
  GGA_Geoid_Separation,
  GGA_Units_2,
  GGA_Age_of_Diff_Corr,
  GGA_Diff_Ref_Station_ID,
  GGA_Checksum
};

class GPS {
  String GPGGA[16];
  SoftwareSerial GPSSerial;
private:
  char readSerialChar();
public:
  GPS(int Rx, int Tx, int baudrate);
  bool readGGA();
  String getGGA_Data(int data);
  String getLatitude();
  String getLongitude();
};

#endif
