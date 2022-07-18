#include "Gui.h"
#include <Engine/ECS.h>
#include <Engine/Events.h>

static auto& registry = lucy::Registry::Instance();

void ImGui::PopupOpenLogic(bool& open, bool& toggle) {
	auto& events = registry.store<lucy::Events>();

	if ((!ImGui::IsWindowHovered() && events.IsButtonPressedAny()) || (ImGui::IsWindowHovered() && !events.IsButtonPressed(SDL_BUTTON_RIGHT) && events.IsButtonPressedAny()))
		open = false;

	if (toggle && ImGui::IsWindowHovered() && events.IsButtonPressed(SDL_BUTTON_RIGHT))
		open = true;
	
	toggle = (ImGui::IsWindowHovered() && !events.IsButtonPressed(SDL_BUTTON_RIGHT));
}

bool ImGui::in_expections(std::string value, const std::vector<std::string>& exceptions) {
	if (!exceptions.size()) return false;

	for (const auto& str: exceptions) {
		if (str == value)
			return true;
	}

	return false;
}