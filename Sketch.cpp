
#include <Arduino.h>
#include "WheelControl.h"
#include "WheelEncoder.h"

#define testing

const float PTERM = 6;
const float ITERM = 0.4;
const float DTERM = 1;

WheelEncoder encoder1;
WheelEncoder encoder2;
WheelEncoder encoder3;
WheelEncoder encoder4;

WheelControl motor1;
WheelControl motor2;
WheelControl motor3;
WheelControl motor4;

void encoder1InterruptLoop(){encoder1.onInterrupt();}
void encoder2InterruptLoop(){encoder2.onInterrupt();}
void encoder3InterruptLoop(){encoder3.onInterrupt();}
void encoder4InterruptLoop(){encoder4.onInterrupt();}

void setup() {
	encoder1.setup(18, 40, false);
	motor1.setupEncoder(&encoder1);
	motor1.setupMotor(22, 23, 4, false);
	motor1.setupPID(PTERM, ITERM, DTERM);
	attachInterrupt(digitalPinToInterrupt(encoder1.getInterrupt()), encoder1InterruptLoop, CHANGE);
	//motor1.setDebugging(true); 
	
	encoder2.setup(19, 41, true);
	motor2.setupEncoder(&encoder2);
	motor2.setupMotor(24, 25, 5, false);
	motor2.setupPID(PTERM, ITERM, DTERM);
	attachInterrupt(digitalPinToInterrupt(encoder2.getInterrupt()), encoder2InterruptLoop, CHANGE);
	//motor2.setDebugging(true);
	
	encoder3.setup(20, 42, false);
	motor3.setupEncoder(&encoder3);
	motor3.setupMotor(26, 27, 6, false);
	motor3.setupPID(PTERM, ITERM, DTERM);
	attachInterrupt(digitalPinToInterrupt(encoder3.getInterrupt()), encoder3InterruptLoop, CHANGE);
	//motor3.setDebugging(true);
	
	encoder4.setup(21, 43, true);
	motor4.setupEncoder(&encoder4);
	motor4.setupMotor(28, 29, 7, false);
	motor4.setupPID(PTERM, ITERM, DTERM);
	attachInterrupt(digitalPinToInterrupt(encoder4.getInterrupt()), encoder4InterruptLoop, CHANGE);
	//motor4.setDebugging(true);
	
	#ifdef testing
		Serial.begin(9600);
		delay(1000);
		Serial.println("Start!");
	#endif
}

void loop() {
	unsigned int startTime = millis();
	
	motor1.goRPM(20, -255, 255);
	motor2.goRPM(20, -255, 255);
	motor3.goRPM(20, -255, 255);
	motor4.goRPM(20, -255, 255);
	
	
	
	/*while(millis()-startTime<2000){
		motor1.goRPM(20,-255,255);
		motor3.goRPM(20,-255,255);
		
		motor2.goRPM(20,-255,255);
		motor4.goRPM(20,-255,255);
	}*/

}


