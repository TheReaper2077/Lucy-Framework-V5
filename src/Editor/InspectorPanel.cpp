// #include "Panel.h"
// #include "EditorStatus.h"
// #include <Engine/ECS.h>
// #include <Registry/Registry.h>
// #include <Components/Components.h>
// #include <Engine/Events.h>
// #include "Gui.h"

// static auto& registry = lucy::Registry::Instance();
// static auto& editorstatus = registry.store<lucy::EditorStatus>();
// static auto& events = registry.store<lucy::Events>();
// static auto& materialregistry = registry.store<lucy::MaterialRegistry>();
// static auto& meshregistry = registry.store<lucy::MeshRegistry>();
// static auto& spriteregistry = registry.store<lucy::SpriteRegistry>();

// namespace lucy {
// 	template <typename T>
// 	class ComponentHeader {
// 	public:
// 		bool open = true;
// 		ImGuiTreeNodeFlags flags = ImGuiTreeNodeFlags_DefaultOpen;
// 		Entity last_entity;
// 		std::string name;
// 		bool has_component = false;
// 		bool permanent = false;

// 		ComponentHeader() {}
// 		ComponentHeader(std::string name, bool permanent = false) {
// 			this->name = name;
// 			this->permanent = permanent;
// 		}

// 		void Render(Entity entity);
// 		void Header(Entity entity) {
// 			if (entity != last_entity) open = true;
// 			last_entity = entity;
// 			has_component = (registry.try_get<T>(entity) != nullptr);

// 			if (has_component) {
// 				if (permanent) {
// 					if (ImGui::CollapsingHeader(name.c_str()))
// 						Render(entity);
// 				} else if (ImGui::CollapsingHeader(name.c_str(), &open, flags)) {
// 					Render(entity);
// 				} else if (!open) {
// 					registry.remove<T>(entity);
// 				}
// 			}
// 		}
// 	};
// }


// template <>
// void lucy::ComponentHeader<lucy::Tag>::Render(Entity entity) {
// 	auto& tag = registry.get<Tag>(entity);

// 	ImGui::InputText("Name", &tag.name);
// 	ImGui::TextWrapped(tag.id.c_str());
// }

// template <>
// void lucy::ComponentHeader<lucy::Transform>::Render(Entity entity) {
// 	auto& transform = registry.get<Transform>(entity);

// 	ImGui::DragFloat3("Translation", &transform.translation[0], 0.1);
// 	ImGui::DragFloat3("Rotation", &transform.rotation[0], 0.1);
// 	ImGui::DragFloat3("Scale", &transform.scale[0], 0.1);
// }

// template <>
// void lucy::ComponentHeader<lucy::Camera>::Render(Entity entity) {
// 	auto& camera = registry.get<Camera>(entity);
// 	auto* gamewindow = registry.store<WindowRegistry>()[camera.window_id];

// 	// camera.enable = (gamewindow->camera == entity || camera.enable);

// 	ImGui::Checkbox("Enable", &camera.enable);
	
// 	// if (camera.enable && gamewindow->camera != entity) {
// 	// 	gamewindow->camera = entity;
// 	// }
// 	// if (!camera.enable && gamewindow->camera == entity) {
// 	// 	gamewindow->camera = (Entity)0;
// 	// }

// 	// if (camera.mode == ORTHOGRAPHIC) {
		
// 	// }

// 	ImGui::DragFloat("Near", &camera.c_near, 0.1);
// 	ImGui::DragFloat("Far", &camera.c_far, 0.1);
// 	ImGui::DragFloat("Fov", &camera.fov, 0.1, 0.0, 180.0);

// 	ImGui::ColorEdit4("ClearColor", &camera.clear_color[0], ImGuiColorEditFlags_NoInputs);

// 	// ImGui::EnumComboLogic("Projection", { "ORTHOGRAPHIC", "PERSPECTIVE" }, camera.mode);
// 	ImGui::EnumComboLogic("Mode", { "FPS", "Editor", "None" }, camera.mode, { "Editor", "None"});
// }

// template <>
// void lucy::ComponentHeader<lucy::Light>::Render(Entity entity) {
// 	auto& light = registry.get<Light>(entity);

// 	ImGui::EnumComboLogic("Mode", { "Directional", "Areal", "Point", "Spot" }, light.mode);

// 	ImGui::Spacing();

// 	ImGui::Checkbox("Active", &light.enable);

// 	ImGui::Spacing();

// 	ImGui::ColorEdit3("Color", &light.color[0], ImGuiColorEditFlags_NoInputs);
// }

// template <>
// void lucy::ComponentHeader<lucy::SpriteRenderer>::Render(Entity entity) {
// 	auto& spriterenderer = registry.get<SpriteRenderer>(entity);

// 	ImGui::Checkbox("Visible", &spriterenderer.visible);

// 	ImGui::Spacing();

// 	ImGui::ColorEdit4("Color", &spriterenderer.color[0], ImGuiColorEditFlags_NoInputs);
// }

// template <>
// void lucy::ComponentHeader<lucy::MeshRenderer>::Render(Entity entity) {
// 	auto& meshrenderer = registry.get<MeshRenderer>(entity);

// 	ImGui::Checkbox("Enable Lighting", &meshrenderer.enable_lighting);

// 	if (ImGui::Selectable("Material")) {
// 		ImGui::OpenPopup("mat_select");
// 	}

// 	if (ImGui::Selectable("Mesh")) {
// 		ImGui::OpenPopup("mesh_select");
// 	}

// 	if (ImGui::BeginPopup("mat_select")) {
// 		for (auto& pair: materialregistry.material_registry) {
// 			if (ImGui::Selectable(pair.second.name.c_str())) {
// 				meshrenderer.material = &pair.second;
// 			}
// 		}

// 		ImGui::EndPopup();
// 	}

// 	if (ImGui::BeginPopup("mesh_select")) {
// 		for (auto& pair: meshregistry.mesh_registry) {
// 			if (ImGui::Selectable(pair.second.name.c_str())) {
// 				meshrenderer.mesh = &pair.second.mesh;
// 			}
// 		}

// 		ImGui::EndPopup();
// 	}
// }

// void lucy::Panel<lucy::PanelInstance_Inspector>::Render() {
// 	if (!panel_open) return;

// 	auto& editorstatus = registry.store<EditorStatus>();

// 	static Entity last_entity;
// 	static std::string last_texture;
// 	static std::string last_sprite;

// 	if (ImGui::Begin("Inspector", &panel_open)) {
// 		Entity selected_entity = editorstatus.GetEntityID();
// 		auto selected_texture = editorstatus.GetTextureID();
// 		auto selected_sprite = editorstatus.GetSpriteID();

// 		if (selected_entity != (Entity)0) {
// 			last_entity = selected_entity;

// 			static ComponentHeader<Tag> tag("Tag", true);
// 			static ComponentHeader<Transform> transform("Transform");
// 			static ComponentHeader<Camera> camera("Camera");
// 			static ComponentHeader<Light> light("Light");
// 			static ComponentHeader<SpriteRenderer> spriterenderer("SpriteRenderer");
// 			static ComponentHeader<MeshRenderer> meshrenderer("MeshRenderer");
			
// 			tag.Header(selected_entity);
// 			transform.Header(selected_entity);
// 			camera.Header(selected_entity);
// 			light.Header(selected_entity);
// 			spriterenderer.Header(selected_entity);
// 			meshrenderer.Header(selected_entity);

// 			ImGui::Spacing();
// 			if (ImGui::Button("Add Component", ImVec2(ImGui::GetColumnWidth(), 0))) {
// 				ImGui::OpenPopup("Component Menu");
// 			}

// 			if (ImGui::BeginPopup("Component Menu")) {
// 				if (ImGui::Selectable("Transform") && !transform.has_component) {
// 					registry.emplace<Transform>(selected_entity);
// 					transform.open = true;
// 				}
// 				if (ImGui::Selectable("Camera") && !camera.has_component) {
// 					registry.emplace<Camera>(selected_entity);
// 					camera.open = true;
// 				}
// 				if (ImGui::Selectable("Light") && !light.has_component) {
// 					registry.emplace<Light>(selected_entity);
// 					light.open = true;
// 				}
// 				if (ImGui::Selectable("SpriteRenderer") && !spriterenderer.has_component) {
// 					registry.emplace<SpriteRenderer>(selected_entity);
// 					spriterenderer.open = true;
// 				}
// 				if (ImGui::Selectable("MeshRenderer") && !meshrenderer.has_component) {
// 					registry.emplace<MeshRenderer>(selected_entity);
// 					meshrenderer.open = true;
// 				}

// 				ImGui::EndPopup();
// 			}
// 		}
// 	}
// 	ImGui::End();
// }
