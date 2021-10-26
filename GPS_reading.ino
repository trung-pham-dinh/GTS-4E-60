#include "GTS_4E.h"
// $GPGGA,130304.838,1046.2619,N,10641.2620,E,1,03,4.6,-2.4,M,2.4,M,,0000*4DTX

GPS gps(2,3,9600);
String lat = gps.getGGA_Data(GGA_Latitude);
String lon = gps.getGGA_Data(GGA_Longitude);
String ele = gps.getGGA_Data(GGA_MSL_Altitude);
long long premil = millis();

void setup() {
  Serial.begin(115200);
}

void loop() {
  gps.readGGA();
  lat = gps.getGGA_Data(GGA_Latitude);
  lon = gps.getGGA_Data(GGA_Longitude);
  ele = gps.getGGA_Data(GGA_MSL_Altitude);
  if(millis()-premil > 5000) {
    premil = millis();
    if(lat != "" && lon != "" && ele != "") {
      Serial.println("!1:iot-gps:" + lat + "," + lon + "," + ele + "#");
    }
  }
  //delay(5000);
}
