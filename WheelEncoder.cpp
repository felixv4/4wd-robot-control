#include "WheelEncoder.h"
#include "DigitalReadFast.h"
#include "Arduino.h"

void WheelEncoder::setup(int encoderInterrupt, int encoderPin, bool encoderReversed) {
	m_encoderInterrupt = encoderInterrupt;
	m_encoderPin = encoderPin;
	m_encoderReversed = encoderReversed;
	pinMode(m_encoderPin, INPUT);
}

void WheelEncoder::onInterrupt(){
	if (digitalReadFast2(m_encoderPin) == digitalReadFast2(m_encoderInterrupt)) m_currentStepsPerDelay += m_COUNT_PER_INTERRUPT;
	else m_currentStepsPerDelay -= m_COUNT_PER_INTERRUPT;
}

bool WheelEncoder::calc(){
	int return1 = false;
	if ((unsigned int)millis() - m_lastTime >= m_SAMPLE_DELAY){
		
		if (m_encoderReversed == true) {
			m_currentStepsPerDelay = m_currentStepsPerDelay*(-1);
		}
		
		m_lastStepsPerDelay = m_currentStepsPerDelay;
		m_totalSteps += m_currentStepsPerDelay;
		m_currentStepsPerDelay = 0;
		m_lastTime = (unsigned int) millis();
		
		return1 = true;
	}
	return return1;
}

void WheelEncoder::resetVariables(){
	m_totalSteps = 0;
	m_currentStepsPerDelay = 0;
	m_lastStepsPerDelay = 0;
}

int WheelEncoder::getLastStepsPerDelay(){
	return m_lastStepsPerDelay;
}

unsigned int WheelEncoder::getTotalSteps(){
	return m_totalSteps;
}

int WheelEncoder::getInterrupt(){
	return m_encoderInterrupt;
}
