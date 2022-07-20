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
std::tuple<float, float> ImGui::ThumbnailListLogic(const float& padding, const float& thumbnail_size) {
	float cell_size = padding + thumbnail_size;
	float panel_width = ImGui::GetContentRegionAvail().x;

	int column_count = (int)(panel_width / cell_size);
	int width_delta = int(panel_width) - int(cell_size)*(int(panel_width)/int(cell_size));

	if (panel_width > cell_size) {
		ImGui::Columns(column_count, 0, false);

		for (int i = 1; i < column_count; i++)
			ImGui::SetColumnOffset(i, i * cell_size);
	}

	auto* draw_list = ImGui::GetWindowDrawList();
	auto win_pos = ImGui::GetWindowPos();

	int column_idx = 0;
	int row_idx = 1;

	float y_scroll = ImGui::GetScrollY();

	return { panel_width, cell_size };
}
