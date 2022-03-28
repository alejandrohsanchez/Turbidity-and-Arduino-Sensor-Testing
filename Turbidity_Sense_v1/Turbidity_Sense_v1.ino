/*
 * DFROBOT turbidity sensor documentation
 * https://wiki.dfrobot.com/Turbidity_sensor_SKU__SEN0189
 * 
 * Reference on data collection with turbidity modules
 * https://en.wikipedia.org/wiki/Turbidity
 * 
 * */

int sensorPin = A0;
float voltage = 0;
float turbidity = 0;
void setup() {
  Serial.begin(9600); //Baud rate: 9600
}
void loop() {
  // First read the input on the analog pin 0 (A0)
  int sensorValue = analogRead(sensorPin);// read the input on analog pin 0:
  
  // Using for loop to find average value of voltage.
  // Average value is necessary to accommodate for sensor noise.
  for(int i=0; i<800; i++) {
    /*
   * Convert the analog reading
   * (which goes from 0 - 1023) to a voltage (0 - 5V):
   */
    voltage += ((float)analogRead(sensorPin)/1023)*5;
  }
  voltage = voltage/800;

  /*
   * Re-maps a number from one range to another. That is, a
   * value of fromLow would get mapped to toLow, a value of
   * fromHigh to toHigh, values in-between to values in-between,
   * etc.
   */
  // Syntax: map(value, fromLow, fromHigh, toLow, toHigh)
  turbidity = map(voltage, 0, 5, 1000, 0);
  //turbidity = voltage;
  /* 
   * Print out the newly mapped values
   * (representing NTU calibrated scale) 
   */
  Serial.print("NTU Approximation = "); // print out the value you read:
  Serial.println(turbidity);
  delay(250);
}
