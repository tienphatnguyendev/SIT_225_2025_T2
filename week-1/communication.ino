

int ledPin = 13; 

void setup() {
  Serial.begin(9600);
  pinMode(ledPin, OUTPUT);   
  Serial.println("Arduino Ready!");
}

void loop() {
  if (Serial.available() > 0) {
    
    int blinkTimes = Serial.parseInt();
    
    if (blinkTimes > 0) {
      

      for (int i = 0; i < blinkTimes; i++) {
        digitalWrite(ledPin, HIGH);  
        delay(500);                  
        digitalWrite(ledPin, LOW);   
        delay(500);                  
      }
      
      int sleepTime = random(1, 9);
      Serial.println(sleepTime);
    }
  }
}
