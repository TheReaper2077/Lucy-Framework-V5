#pragma once

#include "Panel.h"

namespace lucy {
	struct InspectorPanel: public Panel {
		void Render() override;
	};
}