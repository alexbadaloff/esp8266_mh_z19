#define pwmPin 12 // gpio12

void setup() {
  Serial.begin(115200);
  pinMode(pwmPin, INPUT);
}

int myPPM() {
  int  ppm, val;
  int step = 0;
  long th, tl;

  while (1) { // начинаем опрос mh-z19
    delay(2);
    val = digitalRead(pwmPin);
    if (val == HIGH) {
      if (step > 0) {
        th = millis();
        step = 2;
      } else {
        continue;
      }
    } else {
      if (step < 2) {
        tl = millis();
        if (step < 1)
          step = 1;
      }
      else
      {
        th = th - tl;
        tl = 1004 - th;
        ppm = 5000 * (th - 2) / (th + tl - 4);
        return ppm;
      }
    }
  }
}

void loop() {
  Serial.println("CO2: " + String(myPPM()));
  delay(10000);
}
