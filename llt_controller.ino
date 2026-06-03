// Pin assignments
#define LASER_PIN 11

uint32_t flashingRate = 1; // Flashing rate in Hz
uint32_t dutyCycle = 50; // Duty cycle in percent

void setup() {
  // put your setup code here, to run once:
  pinMode(LASER_PIN, OUTPUT);

  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  digitalWrite(LASER_PIN, 1);
  delay(500.0f/flashingRate * dutyCycle/50.0f);
  digitalWrite(LASER_PIN, 0);
  delay(500.0f/flashingRate * (100.0f - dutyCycle)/50.0f);

  if(Serial.available()) { // Read values from serial if entered
    String input = Serial.readStringUntil('\n');
    input.trim();

    int hzEndIndex = input.indexOf(',', 0);
    String flashingRateStr = input.substring(0, hzEndIndex); // Read flashing rate from first value
    String dutyCycleStr = input.substring(hzEndIndex + 1, input.length()); // Read duty cycle from rest

    flashingRate = flashingRateStr.toInt();
    dutyCycle = dutyCycleStr.toInt();

    Serial.print("Laser set to ");
    Serial.print(flashingRate);
    Serial.print(" Hz and ");
    Serial.print(dutyCycle);
    Serial.println("% duty cycle.");
  }
}
