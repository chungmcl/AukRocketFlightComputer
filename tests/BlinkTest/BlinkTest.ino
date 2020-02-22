void setup() {
  pinMode(2, OUTPUT);    // sets the digital pin 13 as output
}

void loop() {
  digitalWrite(2, HIGH); 
  delay(1000);            
  digitalWrite(2, LOW);  
  delay(1000);            
}
