#include <Wire.h>
#include <LiquidCrystal_I2C.h>

#define MQ2_PIN 34
#define BUZZER_PIN 2

LiquidCrystal_I2C lcd(0x27, 16, 2);

void setup() {
  Serial.begin(115200);
  lcd.init();
  lcd.backlight();
  pinMode(MQ2_PIN, INPUT);
  pinMode(BUZZER_PIN, OUTPUT);
  digitalWrite(BUZZER_PIN, LOW);

  lcd.setCursor(0, 0);
  lcd.print("Gas Detector");
  delay(2000);
  lcd.clear();
}

void loop() {
  int gasValue = analogRead(MQ2_PIN);
  Serial.println(gasValue);

  lcd.setCursor(0, 0);
  lcd.print("Gas Value:");
  lcd.setCursor(10, 0);
  lcd.print(gasValue);

  if (gasValue > 1200) { // Adjust threshold based on your test
    digitalWrite(BUZZER_PIN, HIGH);
    lcd.setCursor(0, 1);
    lcd.print("!!! GAS LEAK !!!");
  } else {
    digitalWrite(BUZZER_PIN, LOW);
    lcd.setCursor(0, 1);
    lcd.print("Safe Environment ");
  }

  delay(500);
}
