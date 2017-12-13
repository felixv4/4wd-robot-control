class WheelEncoder;

class WheelControl{
	//variables
	private:
	const int m_SAMPLE_DELAY = 10; //normal 20
	const int m_PULSES_PER_TURN = 1;
	
	int m_lastTime = 0;
	
	WheelEncoder *m_encoder;
	
	int m_motorPin1 = 0;
	int m_motorPin2 = 0;
	int m_motorEn = 0;
	
	int m_steps = 0;
	
	bool m_motorReversed = false;
	bool m_debugging = false;
	
	//PID variables
	float m_pScalar = 0;
	float m_iScalar = 0;
	float m_dScalar = 0;
	int m_integral = 0;
	int m_errorPrev = 0;

	int m_currentSpeed = 0; //for pwm function
	
	//functions
	public:
	void setupMotor(int motorPin1, int motorPin2, int motorEn, bool motorReversed);
	void setupEncoder(WheelEncoder *encoder);
	void setupPID(float pScalar, float iScalar, float dScalar);
	void goPWM(int speed);
	void goACCEL(int wantedRPM, int steps, int stepsToRPM);
	void goRPM(int wantedRPM, int minPWM, int maxPWM);
	void resetVariables();
	void setDebugging(bool debugging);
};
