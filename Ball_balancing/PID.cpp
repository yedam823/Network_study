#include"PID.h"

PID::PID(float kp, float ki, float kd) {
	Kp = kp;
	Ki = ki;
	Kd = kd;
	 
	integral = 0.0f; //적분
	previous_error = 0.0f;
	previous_measurement = 0.0f;
}

float PID::update(float setpoint, float measurement, float dt) {
	if (dt <= 0.0f) { return 0.0f; }

	//P 제어 (현재 오차 줄이기)
	float error = setpoint - measurement;

	//D제어 (속도 유지)
	float derivative = (measurement - previous_measurement) / dt;

	//I 제어 (누적 오차 줄이기
	
	//출력 포화 시 적분 누적 중단
	float current_output = Kp * error + Ki * integral - Kd * derivative;
	if ((current_output < output_max) && (current_output > output_min))
		integral += error * dt;

	if (integral > integral_max) integral = integral_max;
	if (integral < integral_min) integral = integral_min;

	float output = Kp * error + Ki * integral - Kd * derivative;

	if (output > output_max) output = output_max;
	if (output < output_min) output = output_min;

	previous_error = error;
	previous_measurement = measurement;

	return output;
}

void PID::reset() {
	integral = 0.0f;
	previous_error = 0.0f;
	previous_measurement = 0.0f;
}