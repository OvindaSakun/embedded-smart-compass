#include <AM2302-Sensor.h>    //humidity and temp
#include <LiquidCrystal.h>    //display
#include <QMC5883LCompass.h>  //compass

QMC5883LCompass compass;
constexpr unsigned int SENSOR_PIN{ A0 };
AM2302::AM2302_Sensor am2302{ SENSOR_PIN };

const int rs = 13, en = 11, d4 = 6, d5 = 5, d6 = 4, d7 = 3;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);


void setup() {

  pinMode(A1, INPUT);
  pinMode(A2, INPUT);
  pinMode(A3, INPUT);
  Serial.begin(9600);

  // Humidity and temp sensor...
  if (am2302.begin()) {
    delay(1000);
  } else {
    while (true) {
      Serial.println("No humidity & temperature sensor detected");
      delay(10000);
    }
  }
  //  ..
  // compass
  compass.init();
  // ..
  // display
  lcd.begin(16, 2);
  // ..
}

int button = 0;

void loop() {

  lcd.clear();

  if (digitalRead(A1) == HIGH) {
    button = 1;
  }
  if (digitalRead(A2) == HIGH) {
    button = 2;
  }
  if (digitalRead(A3) == HIGH) {
    button = 3;
  }

  if (button == 1) {
    lcd.setCursor(0, 0);
    lcd.print("Temperature");
    Temperature();
  } else if (button == 2) {
    lcd.setCursor(0, 0);
    lcd.print("Humidity");
    Humidity();
  } else if (button == 3) {
    lcd.setCursor(0, 0);
    lcd.print("Compass");
    Compass();
  } else {
    lcd.setCursor(0, 0);
    lcd.print("Press a button");
  }

  delay(100);
}


void Humidity() {

  am2302.read();
  Serial.print("Humidity:    ");
  Serial.println(am2302.get_Humidity());
  lcd.setCursor(0, 1);
  lcd.print(String(am2302.get_Humidity()) + " %");
  delay(100);
}
void Temperature() {

  am2302.read();
  Serial.print("Temperature: ");
  Serial.println(am2302.get_Temperature());
  lcd.setCursor(0, 1);
  lcd.print(String(am2302.get_Temperature()) + " C");
  delay(100);
}

void Compass() {

  compass.read();

  int a = compass.getAzimuth();
  int direction = a - 80;
  if(direction>-260 && direction<0){
  direction = map(direction, -259, -1, 100, 360);
  }
  direction = map(direction, 0, 360, 360, 0);
  

  Serial.print(direction);
  Serial.println();
  lcd.setCursor(0, 1);
  lcd.print(String(direction)+ " '");
  

  lcd.setCursor(13, 0);
  lcd.print("^");

  if(direction>337.5 || direction<22.5){
    lcd.setCursor(13, 1);
  lcd.print("N");
  }
   else if(direction>22.5 && direction<67.5){
    lcd.setCursor(13, 1);
  lcd.print("NE");
  }
  else if(direction>67.5 && direction<112.5){
    lcd.setCursor(13, 1);
  lcd.print("E");
  }
   else if(direction>112.5 && direction<157.5){
    lcd.setCursor(13, 1);
  lcd.print("SE");
  }
   else if(direction>157.5 && direction<202.5){
    lcd.setCursor(13, 1);
  lcd.print("S");
  }
  else if(direction>202.5 && direction<247.5){
    lcd.setCursor(13, 1);
  lcd.print("SW");
  }
  else if(direction>247.5 && direction<292.5){
    lcd.setCursor(13, 1);
  lcd.print("W");
  }
  else if(direction>292.5 && direction<337.5){
    lcd.setCursor(13, 1);
  lcd.print("NW");
  }


  delay(100);
}