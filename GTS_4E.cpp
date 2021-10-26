#include "GTS_4E.h"


GPS::GPS(int Rx, int Tx, int baudrate): GPSSerial(SoftwareSerial(Rx, Tx)) {
  GPSSerial.begin(baudrate);
  for(int i = 0; i < 15; i++) {
    GPGGA[i] = "";
  }
  GPGGA[GGA_Message_ID] = "GPGGA";
}
bool GPS::readGGA() {
  static char charRead = 0;
  static int dataIndex = 0;
  static String dataRead = "";
  
  if(readSerialChar() != '$') return false;

  charRead = 0;
  dataIndex = 0;
  dataRead = "";
  
  while(charRead != '*') { // end of dataframe
    charRead = readSerialChar();
    if(charRead) {
      if(charRead != ',') { // data
        dataRead += String(charRead);
      }
      else { // end of 1 data
        if(dataIndex == 0 && dataRead != "GPGGA") return false; // not a GPGGA frame
        if(dataRead != "") { // if the data exist, start update
          GPGGA[dataIndex] = dataRead;
        }
        dataRead = "";
        dataIndex++;
      }
    }
  }

  
  
  return true;
}
String GPS::getGGA_Data(int data) {
  return GPGGA[data];  
}

String GPS::getLatitude() {
  String lat = getGGA_Data(GGA_Latitude);
  if(lat == "") return "";

  double int_part = (lat.substring(0,2)).toDouble();
  double float_part = (lat.substring(2)).toDouble() / 60.0;
  return String(int_part+float_part);
}

String GPS::getLongitude() {
  String lon = getGGA_Data(GGA_Longitude);
  if(lon == "") return "";

  double int_part = (lon.substring(0,3)).toDouble();
  double float_part = (lon.substring(3)).toDouble() / 60.0;
  return String(int_part+float_part);
}

char GPS::readSerialChar() {
  if(GPSSerial.available() > 0) {
      return GPSSerial.read();
  }
  return 0;
}
