unsigned long tempo = 10*60*1000;
void setup() {
  // put your setup code here, to run once:
Serial.begin(9600);
Serial.print('A');
delay((unsigned long)60000);
Serial.print('B');
}

void loop() {
}
