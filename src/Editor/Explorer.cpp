#include "Explorer.h"
#include <filesystem>
#include <iostream>
#include <Engine/Util.h>
#include <Engine/Events.h>
#include "EditorStatus.h"

static auto& registry = lucy::Registry::Instance();
static auto& spriteregistry = registry.store<lucy::SpriteRegistry>();
static auto& editorstatus = registry.store<lucy::EditorStatus>();
static auto& events = registry.store<lucy::Events>();

lucy::Explorer::Explorer() {
	treeinit_path = "D:/C++/Lucy Framework V5/assets/";
	explorer_path = "D:/C++/Lucy Framework V5/assets/";
}

void lucy::Explorer::SetTreePath(std::string path) {
	tree_path = path;
}

void lucy::Explorer::SetExplorerPath(std::string path) {
	explorer_path = path;
}

void lucy::Explorer::SetTreeInitPath(std::string path) {
	treeinit_path = path;
}

std::string lucy::Explorer::GetSelectedTreePath() {
	return selectedtree_path;
}

std::string lucy::Explorer::GetSelectedExplorerItemPath() {
	return selectedexploreritem_path;
}

void lucy::Explorer::MainNavigation() {
	if (ImGui::IsWindowFocused()) {
		// if (events.)
	}
}

void lucy::Explorer::RenderTree() {
	RenderTree(treeinit_path);
}

void lucy::Explorer::RenderTree(const std::string& dirpath) {
	if (!std::filesystem::exists(dirpath)) return;

	for (auto entry: std::filesystem::directory_iterator(dirpath)) {
		const auto& path = entry.path().generic_string();

		if (entry.is_directory()) {
			auto node_state_path = path + "/";

			if (node_state.find(node_state_path) != node_state.end()) {
				ImGui::SetNextItemOpen(node_state[node_state_path]);
			}

			bool open = ImGui::TreeNode(entry.path().filename().generic_string().c_str());

			node_state[node_state_path] = open;

			if (ImGui::IsItemClicked() && open) {
				selectedtree_path = entry.path().generic_string();
			}

			if (open) {
				RenderTree(path);
				ImGui::TreePop();
			}
		} else {
			if (ImGui::TreeNodeEx(entry.path().filename().generic_string().c_str(), ImGuiTreeNodeFlags_Leaf)) {
				// explorer_path = entry.path().generic_string();
				ImGui::TreePop();
			}
		}
	}
}

void lucy::Explorer::ShortcutMenu() {
	if (ImGui::IsWindowHovered() && ImGui::IsMouseClicked(ImGuiMouseButton_Right)) {
		ImGui::OpenPopup("Scene Shortcut");
	}
	
	if (ImGui::BeginPopup("Scene Shortcut")) {
		if (ImGui::Selectable("New File")) {
			
		}
		if (ImGui::Selectable("New Folder")) {

		}
		if (ImGui::Selectable("New Scene")) {

		}
		if (ImGui::Selectable("New Material")) {

		}
		if (ImGui::Selectable("Delete")) {

		}
		ImGui::EndPopup();
	}
}

void lucy::Explorer::RenderExplorer() {
	if (!std::filesystem::exists(explorer_path)) return;

	if (ImGui::BeginTable("##3", 3, ImGuiTableFlags_Borders | ImGuiTableFlags_Resizable)) {
		ImGui::TableNextRow();

		ImGui::TableSetColumnIndex(0);

		ImGui::Text("Name");

		ImGui::TableSetColumnIndex(1);

		ImGui::Text("Type");

		ImGui::TableSetColumnIndex(2);

		ImGui::Text("ID");

		for (auto entry: std::filesystem::directory_iterator(explorer_path)) {
			ImGui::TableNextRow();

			ImGui::TableSetColumnIndex(0);

			if (ImGui::Selectable(entry.path().generic_string().c_str())) {
				if (entry.is_directory()) {
					explorer_path = entry.path().generic_string().c_str();
					break;
				}
			}

			ImGui::TableSetColumnIndex(1);

			if (entry.is_directory()) {
				ImGui::Text("Folder");
			}
		}
		ImGui::EndTable();
	}

	static std::string exp_path = "";
	if (exp_path == explorer_path) return;
	exp_path = explorer_path;

	if (path_stack.size()) {
		if (exp_path != path_stack.back()) {
			path_stack.push_back(exp_path);
		}
		if (path_stack.size() > 256) {
			path_stack.pop_front();
		}
	} else {
		path_stack.push_back(exp_path);
	}

	std::stringstream test(explorer_path);
	std::vector<std::string> seglist;
	std::string segment, temp = "";

	while(std::getline(test, segment, '/')) {
		seglist.push_back(segment);
	}

	for (int i = 0; i < seglist.size(); i++) {
		temp += seglist[i] + '/';
		node_state[temp] = true;
	}
}

void lucy::Explorer::Render() {
	static float slider = 0.3;
	ImGui::SliderFloat("Column Size", &slider, 0.1f, 1.0f, "%.2f", ImGuiSliderFlags_Logarithmic);
	float offset = ImGui::GetContentRegionAvail().x * slider;

	ImGui::Columns(2, 0, false);
	ImGui::SetColumnOffset(1, offset);

	ImGui::BeginChild("##0", { offset - 10, 0 });
	RenderTree();
	ImGui::EndChild();

	ImGui::NextColumn();

	ImGui::BeginChild("##1");
	ImGui::SetNextItemWidth(ImGui::GetContentRegionAvail().x);

	ImGui::InputText("##", &explorer_path);

	while (explorer_path.find("\\") != std::string::npos)
		util::replace_first(explorer_path, "\\", "/");

	RenderExplorer();

	ImGui::EndChild();

	ShortcutMenu();
}

