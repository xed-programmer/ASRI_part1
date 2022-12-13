#include <Wire.h>

#include <Adafruit_MLX90614.h>
Adafruit_MLX90614 mlx = Adafruit_MLX90614();

// IR Sensors for temp and alcohol
const byte IR_IR_TEMP = 12;

// RELAYS
const byte RELAY_IR_TEMP = 7;
const byte RELAY_ALCOHOL = 6;

const long interval = 3000;
unsigned long previousMillis = 0;
byte irIRTemp;

bool previousState = false;
void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  Serial.setTimeout(1);

  pinMode(IR_IR_TEMP, INPUT);
  pinMode(RELAY_IR_TEMP, OUTPUT);
  pinMode(RELAY_ALCOHOL, OUTPUT);

  digitalWrite(RELAY_IR_TEMP, LOW);

  digitalWrite(RELAY_ALCOHOL, LOW);
  //  mlx.begin();
  delay(2000);
  digitalWrite(RELAY_IR_TEMP, HIGH);
  digitalWrite(RELAY_ALCOHOL, HIGH);
}

void loop() {
  while (!Serial.available()) {
    if (millis() - previousMillis > interval)
    {
      digitalWrite(RELAY_IR_TEMP, HIGH);
      digitalWrite(RELAY_ALCOHOL, HIGH);
      previousMillis = millis();
    }
  }
  String name = Serial.readString();

  if (millis() - previousMillis < interval)
  {
    if (name == "Dex" || name == "Bori") {
      digitalWrite(RELAY_IR_TEMP, LOW);
    }
    if (name == "Lou" || name == "Ain") {
      digitalWrite(RELAY_ALCOHOL, LOW);
    }
  } else {
    digitalWrite(RELAY_IR_TEMP, HIGH);
    digitalWrite(RELAY_ALCOHOL, HIGH);
    previousMillis = millis();
  }


  //  if (millis() - previousMillis < interval) {
  //    Serial.println("Reading");
  //    digitalWrite(RELAY_IR_TEMP, LOW);
  //    Serial.print("Temperature : ");
  //    Serial.print(readTemperature());
  //    Serial.println("Celsius");
  //    delay(3000);
  //    digitalWrite(RELAY_ALCOHOL, LOW);
  //    delay(2000);
  //  } else {
  //    Serial.println("Stop");
  //    digitalWrite(RELAY_IR_TEMP, HIGH);
  //    digitalWrite(RELAY_ALCOHOL, HIGH);
  //    previousMillis = millis();
  //  }
}

float readTemperature() {
  float aveTemperature = 0;
  byte len = 100;
  for (byte i = 0; i < len; i++) {
    byte count = 0;
    while (isnan(mlx.readObjectTempC()) && count < 500) count++;
    float temp = mlx.readObjectTempC();
    aveTemperature += temp;
    Serial.println(temp);
  }
  return aveTemperature / len;
}
