int LASER_PIN = 11;          // confirmed pin

float freqHz    = 0.5;       // 0.5Hz default
float dutyCycle = 50.0;      // 50% default

void setup() {
  Serial.begin(9600);
  pinMode(LASER_PIN, OUTPUT);
  printStatus();
}

void loop() {
  unsigned long periodMs = (1.0 / freqHz) * 1000;
  unsigned long onTime   = (dutyCycle / 100.0) * periodMs;
  unsigned long offTime  = periodMs - onTime;

  digitalWrite(LASER_PIN, HIGH);
  delay(onTime);
  digitalWrite(LASER_PIN, LOW);
  delay(offTime);

  if (Serial.available()) {
    handleCommand();
  }
}

void handleCommand() {
  String cmd = Serial.readStringUntil('\n');
  cmd.trim();

  if (cmd == "load default") {
    freqHz    = 0.5;
    dutyCycle = 50.0;
    LASER_PIN = 10;
    Serial.println(">> Defaults loaded.");

  } else if (cmd.startsWith("hz ")) {
    freqHz = cmd.substring(3).toFloat();
    Serial.print(">> Frequency set to: "); Serial.print(freqHz); Serial.println("Hz");

  } else if (cmd.startsWith("duty ")) {
    dutyCycle = cmd.substring(5).toFloat();
    Serial.print(">> Duty cycle set to: "); Serial.print(dutyCycle); Serial.println("%");

  } else {
    Serial.println(">> Unknown command");
  }

  printStatus();
}

void printStatus() {
  Serial.println("---------------------------");
  Serial.print("Pin: ");        Serial.println(LASER_PIN);
  Serial.print("Frequency: ");  Serial.print(freqHz); Serial.println("Hz");
  Serial.print("Period: ");     Serial.print(1.0/freqHz); Serial.println("s");
  Serial.print("Duty Cycle: "); Serial.print(dutyCycle); Serial.println("%");
  Serial.println("---------------------------");
}
