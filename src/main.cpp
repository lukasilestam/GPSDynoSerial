#include <Arduino.h>
#include <TinyGPS++.h>

TinyGPSPlus gps;
#define printf Serial.printf

void setup() {
  Serial.begin(115200);
  Serial2.begin(38400, SERIAL_8N1, 16, 17);
  printf("DynoGPS v1.0\n\n");

  printf("date,time,lat,lng,mps,kmph,alt,sats\n");
}

long prevTime = 0;

void parseGps(){
  long time = gps.time.value();
  if(time != prevTime){
    prevTime = time;
    
    printf("%d,", gps.date.value());
    printf("%d,", gps.time.value());
    printf("%.6f,", gps.location.lat());
    printf("%.6f,", gps.location.lng());
    printf("%.6f,", gps.speed.mps());
    printf("%.6f,", gps.speed.kmph());
    printf("%.6f,", gps.altitude.meters());
    printf("%d", gps.satellites.value());

    printf("\n");
  }
}

void loop() {
  if (Serial2.available() > 0){
    gps.encode(Serial2.read());
    parseGps();
  }
}