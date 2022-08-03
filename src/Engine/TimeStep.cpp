#include "TimeStep.h"
#include <chrono>

void lucy::TimeStep::Update() {
	static std::chrono::steady_clock::time_point start_time, end_time;
	end_time = std::chrono::high_resolution_clock::now();
	dt = std::chrono::duration<double, std::ratio<1, 60>>(end_time - start_time).count();
	start_time = std::chrono::high_resolution_clock::now();
}

const double& lucy::TimeStep::GetTimeStep() {
	return dt;
}

const double& lucy::TimeStep::GetFixedTimeStep() {
	return fixed_dt;
}

