
#include "WheelControl.h"
#include "arduino.h"
#include "WheelEncoder.h"
#include "DigitalReadFast.h"
#include "functions.h"

void WheelControl::setupMotor(int motorPin1, int motorPin2, int motorEn, bool motorReversed){
	m_motorPin1 = motorPin1;
	m_motorPin2 = motorPin2;
	m_motorEn = motorEn;
	m_motorReversed = motorReversed;

	pinMode(m_motorPin1, OUTPUT);
	pinMode(m_motorPin2, OUTPUT);
	pinMode(m_motorEn, OUTPUT);
}

void WheelControl::setupEncoder(WheelEncoder *encoder) {
	m_encoder = encoder;
}

void WheelControl::setupPID(float pScalar, float iScalar, float dScalar) {
	m_pScalar = pScalar;
	m_iScalar = iScalar;
	m_dScalar = dScalar;
}

void WheelControl::goPWM(int speed) { //input: from -255 to +255  output: 2 motor_pins and 1 enable_pin  
	
	if (speed >= 255)speed = 255;
	if (speed <= -255)speed = -255;
	
	if (speed != m_currentSpeed) {
		if ((m_currentSpeed <= 0 && speed >= 0) || (m_currentSpeed >= 0 && speed <= 0)) {
			analogWrite(m_motorEn, LOW);
			if (speed<0) {
				digitalWriteFast2(m_motorPin1, HIGH);
				digitalWriteFast2(m_motorPin2, LOW);
			}else {
				digitalWriteFast2(m_motorPin1, LOW);
				digitalWriteFast2(m_motorPin2, HIGH);
			}
		}
		analogWrite(m_motorEn, abs(speed));
		m_currentSpeed = speed;
	}
}

void WheelControl::goACCEL(int wantedRPM, int steps, int stepsToRPM) { //still testing
	/*int x=steps;
	static int times = 0;
	if (goRPM((int)((wantedRPM/(stepsToRPM*1.0))*times),-255, 255) == true){
		times++;
		Serial.println(times);
	*/
}

void WheelControl::goRPM(int wantedRPM, int minPWM, int maxPWM) {
	if (m_encoder->calc() == true){
		
		int currentRPM = m_encoder->getLastStepsPerDelay();
		m_encoder->resetVariables();
		
		if (m_motorReversed == true) {
			wantedRPM = wantedRPM*(-1);
		}
		
		//PID routine
		int error = wantedRPM - currentRPM;
		
		int proportional = error * m_pScalar;
		
		m_integral += error*m_iScalar;
		if(m_integral >= 250){
			m_integral = 250;
		}
		
		int derivative = (error - m_errorPrev)*m_dScalar;
		m_errorPrev = error;
		
		int PID = proportional+m_integral+derivative;
		if (PID >= maxPWM)PID = maxPWM;
		if (PID <= minPWM)PID = minPWM;
		goPWM(PID);
		
		
		static int count = 0;
		count++;
		//only while debugging
		if (m_debugging == true && count >=50) {
			printSerial("c: %d   w: %d   g: %d   ||   p: %d   i: %d   d: %d",
			 currentRPM, wantedRPM, PID, proportional, m_integral, derivative);
			count = 0;
		}
	}
}

void WheelControl::resetVariables() {
	m_errorPrev = 0;
	m_integral = 0;
}

void WheelControl::setDebugging(bool debugging) {
	m_debugging = debugging;
}
