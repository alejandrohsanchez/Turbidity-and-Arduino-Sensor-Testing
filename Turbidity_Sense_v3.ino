#include <SPI.h>
#include <RF24.h>
#include <BTLE.h>

RF24 radio(9,10);

BTLE btle(&radio);

float sensorPin = A0;
float voltage = 0;

void setup() {
  pinMode(5, OUTPUT);
  pinMode(6, OUTPUT);
  pinMode(7, OUTPUT);
  Serial.begin(9600);
  while(!Serial) {}
  Serial.println("BTLE advertisement sender");
  
  btle.begin("Bobcat");
}

void loop() {
  float sensorValue = analogRead(sensorPin);
  for (int i = 0; i < 800; i++) {
    voltage += ((float)analogRead(sensorPin)/1023) * 5;
  }
  voltage = voltage/800;

  // Performing line-of-best-fit to represent turbidity.
  // More accurate than map() fitting.
  //float turbidity = map(voltage, 0, 5, 4000, 0);
  int turbidity = (-800 * voltage) + 4000;
  
  
  // Printing to Serial Monitor
  Serial.print("FTU Approximation = ");
  Serial.print(turbidity);
  Serial.print(", Voltage = ");
  Serial.println(voltage);

  // Lighting LED based on turbidity measurement
  if (turbidity>=0 && turbidity<=2400) {
    digitalWrite(5, HIGH);
    digitalWrite(6, LOW);
    digitalWrite(7, LOW);
  }
  else if (turbidity>2400 && turbidity<=3200) {
    digitalWrite(5, LOW);
    digitalWrite(6, HIGH);
    digitalWrite(7, LOW);
  }
  else if (turbidity>3200 && turbidity<=4000) {
    digitalWrite(5, LOW);
    digitalWrite(6, LOW);
    digitalWrite(7, HIGH);
  }
  
  nrf_service_data buf;
  
  // Send turbidity data
  buf.service_uuid = turbidity;
  // Send voltage data
  //buf.service_uuid = voltage;
  buf.value = BTLE::to_nRF_Float(turbidity);
  btle.advertise(&buf,sizeof(buf));
  btle.hopChannel();
}
