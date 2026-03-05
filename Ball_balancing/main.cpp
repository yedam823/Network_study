#include <iostream>
#include <fstream>
#include <algorithm>
#include <cmath>
#include "PID.h"
#include "physics.h"

int main() {
	float initial_position = 1.5f;
	float dt = 0.01f;
	float target = 0.0f;
	float theta_max = 0.2618f; //15도

	PID pid(15.0f, 3.0f, 2.0f);

	Physics physics(initial_position);

	std::ofstream file("log.csv");
	if (!file.is_open()) {
		std::cerr << "파일 열기 실패\n";
		return -1;
	}

	file << "time,position,theta\n";

	float time = 0.0f;
	for (int i = 0; i < 2000; i++) {
		float position = physics.getPosition();
		float theta = pid.update(target, position, dt);

		physics.update(theta, dt);

		file << time << "," << position << "," << theta << "\n";

		time += dt;
	}
	file.close();
	system("python plot.py");
}