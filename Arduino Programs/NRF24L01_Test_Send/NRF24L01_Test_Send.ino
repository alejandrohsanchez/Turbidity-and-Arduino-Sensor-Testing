#include <SPI.h>
#include <RF24.h>
#include <BTLE.h>

RF24 radio(9,10);

BTLE btle(&radio);

void setup() {

  Serial.begin(9600);
  while (!Serial) { }
  Serial.println("BTLE advertisement sender");

  btle.begin("Bobcat");
}

void loop() {
  // This is a test value
  float temp=66;
  
  nrf_service_data buf;
  
  //buf.service_uuid = NRF_DEVICE_INFORMATION_SERVICE_UUID; //0x180A
  //buf.service_uuid = NRF_TEMPERATURE_SERVICE_UUID; //0x1809
  //buf.service_uuid =NRF_BATTERY_SERVICE_UUID; //0x180F

  // In the scanner app the service uuid will be what is read
  // The temp value will be read as a hexadecimal value and will
  // need to be converted to decimal
  buf.service_uuid = temp;
  
  buf.value = BTLE::to_nRF_Float(temp);
  //btle.advertise(0x16, &buf, sizeof(buf));
  btle.advertise(int(&buf),sizeof(0));
  
  btle.hopChannel();
  Serial.print(".");
}
