#include "physics.h"
#include <cmath>

Physics::Physics(float initial_position) {
	position = initial_position;
	velocity = 0.0f;
	g = 9.81f;
	beam_len = 0.5f; // 이정도면 총길이 1m 쯤 된다.
}

void Physics::update(float theta, float dt) {
	float acceleration = (5.0f/7.0f) * g* sinf(theta); // 작은 각도를 가정함

	velocity += acceleration * dt; // 속도 늘리기
	position += velocity * dt + 0.5f * acceleration * dt * dt; //위치 업데이트
	
	//빔 범위 제한
	const float restitution = 0.3f;
	if (position > beam_len) {
		position = beam_len;
		velocity = -velocity * restitution;
	}
	if (position < -beam_len) {
		position = -beam_len;
		velocity = -velocity * restitution;
	}
}

float Physics::getPosition() const { return position; } //위치
float Physics::getVelocity() const { return velocity; } //속도

void Physics::reset(float initial_position) {
	position = initial_position;
	velocity = 0.0f;
}