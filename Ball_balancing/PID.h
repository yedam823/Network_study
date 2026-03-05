#pragma once
class PID {
private:
	float Kp, Ki, Kd;

	float integral;
	float integral_min = -1000.0f;
	float integral_max = 1000.0f;

	float previous_error;
	float previous_measurement;

	float output_min = -1000.0f;
	float output_max = 1000.0f;

public:
	PID(float kp, float ki, float kd);

	void setOutputLimits(float min, float max);
	void setIntegralLimits(float min, float max);

	float update(float setPoint, float measurement, float dt);

	void reset();
};