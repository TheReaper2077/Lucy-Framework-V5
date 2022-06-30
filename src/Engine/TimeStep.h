#pragma once

namespace lucy {
	class TimeStep {
		double dt;
		double fixed_dt;

	public:
		void Update();

		const double& GetTimeStep();
		const double& GetFixedTimeStep();
	};
}