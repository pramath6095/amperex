#include <OneWire.h>
#include <DallasTemperature.h>
#include <LCD_I2C.h>

#define ONE_WIRE_BUS 4
#define IN1 12
#define IN2 14
#define IN3 27
#define IN4 26
#define TEMP_THRESHOLD 12.0

OneWire oneWire(ONE_WIRE_BUS);
DallasTemperature sensors(&oneWire);
LCD_I2C lcd(0x27, 16, 2);

enum MotorPhase {IDLE, MOTOR2_ON, WAIT_BETWEEN, MOTOR1_ON, COOLDOWN};
MotorPhase phase = IDLE;

unsigned long lastTempRead = 0;
unsigned long motorTimer = 0;
unsigned long cooldownStart = 0;

const unsigned long TEMP_READ_INTERVAL = 1000;
const unsigned long MOTOR_RUN_TIME = 5000;
const unsigned long WAIT_BETWEEN_MOTORS = 2000;
const unsigned long COOLDOWN_DURATION = 20UL * 60UL * 1000UL;

float actualTemp = 0.0;
bool initialized = false;

void setup() {
  Serial.begin(115200);
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, LOW);
  sensors.begin();
  lcd.begin();
  lcd.backlight();
  lcd.print("System Init...");
  delay(1000);
  lcd.clear();
}

void loop() {
  unsigned long now = millis();

  if (now - lastTempRead >= TEMP_READ_INTERVAL) {
    lastTempRead = now;
    sensors.requestTemperatures();
    float newTemp = sensors.getTempCByIndex(0);
    if (newTemp != DEVICE_DISCONNECTED_C && newTemp > -100 && newTemp < 100) {
      actualTemp = newTemp;
      if (!initialized) {
        initialized = true;
        lcd.clear();
      }

      lcd.setCursor(0, 0);
      lcd.print("                ");
      lcd.setCursor(0, 0);
      lcd.print(actualTemp, 1);
      lcd.print((char)223);
      lcd.print("C M1:");
      lcd.print(digitalRead(IN1) ? "1" : "0");
      lcd.print(" M2:");
      lcd.print(digitalRead(IN3) ? "1" : "0");

      lcd.setCursor(0, 1);
      if (phase == COOLDOWN) {
        unsigned long timeLeft = COOLDOWN_DURATION - (now - cooldownStart);
        int mins = timeLeft / 60000;
        int secs = (timeLeft % 60000) / 1000;
        lcd.print("Next in: ");
        if (mins < 10) lcd.print("0");
        lcd.print(mins); lcd.print(":");
        if (secs < 10) lcd.print("0");
        lcd.print(secs);
        lcd.print("   ");
      } else if (phase == IDLE) {
        lcd.print("Waiting...     ");
      } else {
        lcd.print("Running...     ");
      }

      Serial.print("Temp: ");
      Serial.print(actualTemp);
      Serial.print(" | Phase: ");
      Serial.println(phase);
    }
  }

  switch (phase) {
    case IDLE:
      if (initialized && actualTemp > TEMP_THRESHOLD) {
        motorTimer = now;
        digitalWrite(IN3, HIGH);
        digitalWrite(IN4, LOW);
        phase = MOTOR2_ON;
      }
      break;

    case MOTOR2_ON:
      if (now - motorTimer >= MOTOR_RUN_TIME) {
        digitalWrite(IN3, LOW);
        digitalWrite(IN4, LOW);
        motorTimer = now;
        phase = WAIT_BETWEEN;
      }
      break;

    case WAIT_BETWEEN:
      if (now - motorTimer >= WAIT_BETWEEN_MOTORS) {
        digitalWrite(IN1, HIGH);
        digitalWrite(IN2, LOW);
        motorTimer = now;
        phase = MOTOR1_ON;
      }
      break;

    case MOTOR1_ON:
      if (now - motorTimer >= MOTOR_RUN_TIME) {
        digitalWrite(IN1, LOW);
        digitalWrite(IN2, LOW);
        cooldownStart = now;
        phase = COOLDOWN;
      }
      break;

    case COOLDOWN:
      if (now - cooldownStart >= COOLDOWN_DURATION) {
        phase = IDLE;
      }
      break;
  }
}
