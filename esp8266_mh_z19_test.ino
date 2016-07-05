#define pwmPin 5

int prevVal = LOW;
long th, tl, h, l, ppm, ppm1;

void setup() {
  Serial.begin(115200);
  pinMode(pwmPin, INPUT);
  ppm1 = 0;
}

void loop() {
  long tt = millis();
  int myVal = digitalRead(pwmPin);
  
  // Если обнаружили изменение 
  if (myVal == HIGH) {
    if (myVal != prevVal) {
      h = tt;
      tl = h - l;
      prevVal = myVal;
    }
  } 
  else
  {
    if (myVal != prevVal) {
      l = tt;
      th = l - h;
      prevVal = myVal;
      ppm = 5000 * (th - 2) / (th + tl - 4);
      if ( ppm != ppm1 ) // чтобы не выводить повторяющиеся значения
      {
        ppm1 = ppm;
        Serial.println("PPM = " + String(ppm));
      }
    }
  }
}
