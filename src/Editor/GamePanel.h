#pragma once

#include "Panel.h"

namespace lucy {
	struct GamePanel: public Panel {
		void Render() override;
	};
}