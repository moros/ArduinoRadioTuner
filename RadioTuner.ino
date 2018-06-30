#include <EEPROM.h>
#include <Wire.h>
#include <LiquidCrystal.h>
#include <TEA5767Radio.h>

const int fmRange = 20;

// initializing the LCD display
const int rs = 11, en = 12, d4 = 4, d5 = 5, d6 = 6, d7 = 7;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

// initializing the tuner module library
TEA5767Radio radio = TEA5767Radio();
float station = (99.3);

int pot = A0;

void setup()
{
	Wire.begin();
	lcd.begin(16, 2);
	
	pinMode(pot, INPUT);
}

void loop()
{
	int input = analogRead(pot);
	float percent = input / 1024.0;

	float delta = fmRange * percent;
	station = 88.0 + delta;

	lcd.clear();
	lcd.setCursor(0, 0);
	lcd.print("station: ");
	lcd.print(station);

	// this is all we need to set the station.
	radio.setFrequency(station);

	delay(10);
}