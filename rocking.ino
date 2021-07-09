// rocking
Servo servoR;

unsigned long rockingStartMillis = 0ul;

void rockingSetup() {
  servoR.attach(WEMOS_D3);
  delay(20);
  servoR.write(90);
  delay(1000);
  rockingStartMillis = mainMillis();
}

void rockingLoop() {
  unsigned long endMillis = mainMillis();
  unsigned long executionTime;
  if (endMillis < rockingStartMillis) {
    executionTime = MAX_UL - rockingStartMillis;
    executionTime += endMillis + 1;
  } else {
    executionTime = endMillis - rockingStartMillis;
  }
  dbg(2, "Rocking. Execution time: ");
  dbg(2, executionTime);
  if (executionTime >= s6s.pause) {
    rockingStartMillis = mainMillis();
    dbg(2, ". DO!");
    ledOn();
    servoR.write(s6s.a0);
    delay(s6s.speed);
    servoR.write(s6s.a1);
    delay(s6s.speed);
    ledOff();

    /*for (int pos = 45; pos <= 135; pos += 10) {
      servoR.write(pos);
      delay(15);
    }
    for (int pos = 135; pos >= 45; pos -= 10) {
      servoR.write(pos);
      delay(15);
    }*/
  }
  dbgLn(2);
}
