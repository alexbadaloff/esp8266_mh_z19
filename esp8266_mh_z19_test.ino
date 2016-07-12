#define pwmPin 12 // gpio12

int prevVal = LOW;
long th, tl, h, l, ppm, ppm1;
long tt;
int myVal;

void setup() {
  Serial.begin(115200);
  pinMode(pwmPin, INPUT);
}

int getPPM() {
  int j = 0, ppm;
  long t1 = millis();
  while (1) { // начинаем опрос mh-z19
    tt = millis();
    myVal = digitalRead(pwmPin);
    if (myVal == HIGH) {
      if (myVal != prevVal) {
        h = tt;
        tl = h - l;
        prevVal = myVal;
      }
    }  else {
      if (myVal != prevVal) {
        l = tt;
        th = l - h;
        prevVal = myVal;
        ppm = 5000 * (th - 2) / (th + tl - 4);
        if (j > 0) { // первое значение пропускаем, в нём мусор
          return ppm;
        }
        j++;
      }
    }
    if ((millis() - t1) > 3000) {
      return -1;
    }
  }
}

void loop() {
  Serial.println(String(getPPM()) + "   " + String(millis()));
  delay(20000);
}
