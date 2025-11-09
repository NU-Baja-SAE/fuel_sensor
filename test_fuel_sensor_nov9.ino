// #include <LiquidCrystal.h>

// LCD pin configuration (adjust if needed)
// LiquidCrystal lcd(7, 8, 9, 10, 11, 12);

// Flow sensor pin
#define FLOWSENSORPIN 2

// Pulse counter
volatile uint16_t pulses = 0;

// Timing variables
unsigned long oldTime = 0;
float flowRate = 0.0;
float liters = 0.0;

// Interrupt service routine
void IRAM_ATTR flowISR() {
  pulses++;
}

void setup() {
  Serial.begin(115200);
  Serial.println("ESP32 Flow Sensor Test");

  // lcd.begin(16, 2);
  // lcd.setCursor(0, 0);
  // lcd.print("Initializing...");

  pinMode(FLOWSENSORPIN, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(FLOWSENSORPIN), flowISR, RISING);

  delay(1000);
  // lcd.clear();
}

void loop() {
  unsigned long currentTime = millis();
  unsigned long elapsedTime = currentTime - oldTime;

  if (elapsedTime >= 1000) { // Update every second
    flowRate = (pulses / 7.5); // Hz to L/min for plastic sensor
    liters += (flowRate / 60.0); // L/min to Liters per second

    // lcd.setCursor(0, 0);
    // lcd.print("Rate: ");
    // lcd.print(flowRate, 2);
    // lcd.print(" L/min");

    // lcd.setCursor(0, 1);
    // lcd.print("Total: ");
    // lcd.print(liters, 2);
    // lcd.print(" L     ");

    Serial.print("Flow Rate: ");
    Serial.print(flowRate, 2);
    Serial.print(" L/min, Total: ");
    Serial.print(liters, 2);
    Serial.println(" Liters");

    pulses = 0;
    oldTime = currentTime;
  }
}