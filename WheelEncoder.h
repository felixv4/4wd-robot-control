
class WheelEncoder{
	//variables
	private:
	
	bool m_encoderReversed = false;
	
	const int m_SAMPLE_DELAY = 10; //normal 20
	const int m_COUNT_PER_INTERRUPT = 3;
	
	unsigned int m_lastTime = 0;
	unsigned int m_totalSteps = 0;
	
	int m_currentStepsPerDelay = 0;
	int m_lastStepsPerDelay = 0;
	
	int m_encoderInterrupt = 18;
	int m_encoderPin = 40;

	//functions
	public:
	
	void onInterrupt();
	void setup(int encoderInterrupt, int encoderPin, bool encoderReversed);
	bool calc();
	void resetVariables();
	int getInterrupt();
	unsigned int getTotalSteps();
	int getLastStepsPerDelay();
};
