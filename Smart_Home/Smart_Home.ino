
#define BLYNK_TEMPLATE_ID "TMPL2F5eBQRUD"
#define BLYNK_TEMPLATE_NAME "Smart Home"
#define BLYNK_AUTH_TOKEN "i8ysdCBDeQ2FAyvY-0ypyUFUAPdbhqAD"

#include <ESP32Servo.h>
#include <BlynkSimpleEsp32.h>

char ssid[] = "WE_4D9380";
char pass[] = "n8149333";

//Relay Pins
uint8_t Room_light = 32;
uint8_t Fan = 33;
uint8_t AC = 25;
uint8_t Heater = 26;

//Other Devices
uint8_t Rain_pin = 34;
uint8_t Smoke_pin = 35;
uint8_t Buzzer_pin = 13;


Servo myServo;

//Blynk Controls
BLYNK_WRITE(V26)
{
  digitalWrite(Heater , param.asInt());
}

BLYNK_WRITE(V25)
{
  digitalWrite(AC , param.asInt());
}

BLYNK_WRITE(V33)
{
  digitalWrite(Fan , param.asInt());
}

BLYNK_WRITE(V32)
{
  digitalWrite(Room_light , param.asInt());
}



void setup() {
  // put your setup code here, to run once:

  //Pin Modes
  pinMode(Room_light , OUTPUT);
  pinMode(Fan , OUTPUT);
  pinMode(AC , OUTPUT);
  pinMode(Heater , OUTPUT);

  pinMode(Rain_pin , INPUT);
  pinMode(Smoke_pin , INPUT);
  pinMode(Buzzer_pin , OUTPUT);

  myServo.attach(27);

  Blynk.begin(BLYNK_AUTH_TOKEN, ssid, pass);

}

void loop() {
  // put your main code here, to run repeatedly:

  //Application logic
  Blynk.run();

  //Rain check

  bool rainState = digitalRead(Rain_pin);

  if(rainState == LOW)
  {
    Blynk.virtualWrite(34 , "Rain Detected");

    myServo.write(5);
    delay(500);
    
  }

  if(rainState == HIGH)
  {
    Blynk.virtualWrite(34 , "No Rain");

    myServo.write(95);
    delay(500);
    
  }

  //Smoke check
  bool smokeState = digitalRead(Smoke_pin);
  

  if(smokeState == LOW)
  {
    Blynk.virtualWrite(35 , "Smoke Detected");
    digitalWrite(Buzzer_pin , HIGH);
    delay(500);
  }
  else
  {
    Blynk.virtualWrite(35 , "No Smoke");
    digitalWrite(Buzzer_pin , LOW);
    delay(500);
  }

  }

