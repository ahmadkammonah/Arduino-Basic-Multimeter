#define analogPin      A0
#define chargePin      12
#define resistorPin    1
#define capacitorPin   2
#define knownResistor 6800.0F //in Ohms       

void setup() {
  pinMode(chargePin, OUTPUT);
  pinMode(resistorPin, OUTPUT);
  pinMode(capacitorPin, OUTPUT);
  Serial.begin(9600);
}

void loop() {
  unsigned long elapsedTime = 0;
  digitalWrite(chargePin, HIGH);
  int x1 = analogRead(analogPin);
  int x2 = analogRead(analogPin);

if (x2 == 1023) {
    Serial.println((String) "Where is the Component Broooo???");
    digitalWrite(resistorPin, LOW);
    digitalWrite(capacitorPin, LOW);

} else if (x1 == x2) {
    digitalWrite(chargePin, HIGH);
    float unknownResistor = (float) ( x2 * knownResistor) / (1024 - x2) ;
    Serial.println((String) "Unknown Resistor: " + unknownResistor + "Ohms");                //Outputs Value of Resistor
    digitalWrite(resistorPin, HIGH);

} else {
    digitalWrite(chargePin, LOW);                                                            //Discharge Cycle
    while ( analogRead(analogPin) > 0) {
      Serial.println((String)"Discharging... " + analogRead(analogPin));
      }

digitalWrite(chargePin, HIGH);                                                            //Charge Cycle
unsigned long start_time = micros();
while (analogRead(analogPin) <= 647) {
Serial.println((String)"Charging... " + analogRead(analogPin));
}

elapsedTime += (micros() - start_time);
float unknownCapacitor = (float) elapsedTime / knownResistor ;
Serial.println((String) "Unknown Capacitor: " + unknownCapacitor + " uF");                //Outputs Value of Capacitor
digitalWrite(capacitorPin, HIGH);

digitalWrite(chargePin, LOW);
delay(3000);
}
