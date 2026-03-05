#pragma once
class Physics {
private:
	float position;
	float velocity;
	float g;

	float beam_len;
public:
	Physics(float initial_position);

	void update(float theta, float dt);

	float getPosition() const;
	float getVelocity() const;

	void reset(float initial_position);
};