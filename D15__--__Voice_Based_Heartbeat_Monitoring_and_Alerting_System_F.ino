#include<LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x27,16,2);

#define USE_ARDUINO_INTERRUPTS true 
#include <PulseSensorPlayground.h> 
PulseSensorPlayground pulseSensor;
const int PulseWire = A0;
const int LED13 = 13;        
int Threshold = 650;
int myBPM;

bool j=false;

#define voice1 3

void setup()
{
  pinMode(voice1,OUTPUT);
  digitalWrite(voice1,HIGH);
  
  Serial.begin(9600);

  lcd.init();
  lcd.backlight();

  pulseSensor.analogInput(PulseWire);   
  pulseSensor.blinkOnPulse(LED13);       
  pulseSensor.setThreshold(Threshold);   

  if (pulseSensor.begin())
  {
    Serial.println("We created a pulseSensor Object !");  
  }

  lcd.clear();
  lcd.print("***  READY  ***");
  delay(2000);
}
void loop()
{

  myBPM = pulseSensor.getBeatsPerMinute();

  lcd.clear();
  lcd.print("BPM : ");lcd.print(myBPM);
  delay(1000);

  if(myBPM >= 200  &&  j==false)
  {
    j=true;
    lcd.clear();
    lcd.print("   **ALERT**   ");
    delay(1000);
    lcd.print("T: ");lcd.print(temp);lcd.print("  H: ");lcd.print(myBPM);
    digitalWrite(voice1,LOW);delay(100)digitalWrite(voice1,HIGH);
  }
  if(myBPM<200 && j==true)
  {
    j=false;
  }
}
