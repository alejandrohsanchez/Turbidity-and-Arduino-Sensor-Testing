float sensorPin = A0;
float voltage = 0;
float turbidity = 0;
void setup() {
  pinMode(13, OUTPUT);
  pinMode(12, OUTPUT);
  pinMode(11, OUTPUT);
  Serial.begin(9600); // Baud rate: 9600
}

void loop() {
  float sensorValue = analogRead(sensorPin);
  for (int i = 0; i < 800; i++) {
    voltage += ((float)analogRead(sensorPin)/1023) * 5;
  }
  voltage = voltage/800;

  turbidity = map(voltage, 0, 5, 4000, 0);

  // Printing to serial monitor
  Serial.print("FTU Approximation = ");
  Serial.print(turbidity);
  Serial.print("\n");

  // Lighting LED based on turbidity measurement
  if (turbidity>=0 && turbidity<=2400) {
    digitalWrite(13, HIGH);
    digitalWrite(12, LOW);
    digitalWrite(11, LOW);
  }
  else if (turbidity>2400 && turbidity<=3200) {
    digitalWrite(13, LOW);
    digitalWrite(12, HIGH);
    digitalWrite(11, LOW);
  }
  else if (turbidity>3200 && turbidity<=4000) {
    digitalWrite(13, LOW);
    digitalWrite(12, LOW);
    digitalWrite(11, HIGH);
  }
  else {
    digitalWrite(12, LOW);
    digitalWrite(13, LOW);
  }
}
