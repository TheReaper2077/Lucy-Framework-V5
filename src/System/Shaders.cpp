#include "MainRenderer.h"
#include <Components/Components.h>
#include <fstream>
#include <iostream>

static std::string read_file(const std::string& filename) {
	std::string line, text = "";
	std::fstream file(filename);

	if (!file.is_open()) return text;

	while (std::getline(file, line)) text += (line + '\n');

	file.close();

	return text;
}

static void replace_first(std::string& s, std::string const& toReplace, std::string const& replaceWith) {
	size_t pos = s.find(toReplace);
	if (pos == std::string::npos) return;

	s.replace(pos, toReplace.length(), replaceWith);
}

std::string sprite_shader_fs_create() {
	std::string layout = read_file("D:\\C++\\Lucy Framework V5\\src\\LucyRE\\Shaders\\layout_frag.glsl");

	std::string texture_func = read_file("D:\\C++\\Lucy Framework V5\\src\\LucyRE\\Shaders\\Functions\\texture.glsl");

	std::string sprite_logic = read_file("D:\\C++\\Lucy Framework V5\\src\\LucyRE\\Shaders\\Logic\\sprite.glsl");

	replace_first(layout, "#define FUNC_DEFINE_SET_VAR", texture_func + sprite_logic);
	replace_first(layout, "#define FUNC_SET_VAR", "result = sprite_logic();");

	return layout;
}

std::string mesh_shader_fs_create() {
	std::string layout = read_file("D:\\C++\\Lucy Framework V5\\src\\LucyRE\\Shaders\\layout_frag.glsl");

	std::string texture_func = read_file("D:\\C++\\Lucy Framework V5\\src\\LucyRE\\Shaders\\Functions\\texture.glsl");

	std::string sprite_logic = read_file("D:\\C++\\Lucy Framework V5\\src\\LucyRE\\Shaders\\Logic\\sprite.glsl");

	replace_first(layout, "#define FUNC_DEFINE_SET_VAR", texture_func + sprite_logic);
	replace_first(layout, "#define FUNC_SET_VAR", "result = sprite_logic();");

	return layout;
}

void lucy::MainRenderer::SetLightAndShaders(Registry& registry) {
	if (sprite_shader == nullptr) {
		auto vs = read_file("D:\\C++\\Lucy Framework V5\\src\\LucyRE\\Shaders\\vertex.glsl");
		auto fs = sprite_shader_fs_create();
		
		sprite_shader = new lgl::Shader(vs, fs, false);
	}

	if (screen_shader == nullptr) {
		auto vs = "D:\\C++\\Lucy Framework V5\\src\\LucyRE\\Shaders\\screen_vertex.glsl";
		auto fs = "D:\\C++\\Lucy Framework V5\\src\\LucyRE\\Shaders\\screen_frag.glsl";

		screen_shader = new lgl::Shader(vs, fs, true);
	}

	// renderer.directional_light_count = 0;
	// renderer.point_light_count = 0;
	
	// for (auto [entity, tag, transform, light]: registry.view<Tag, Transform, Light>().each()) {
	// 	renderer.directional_light_count += (light.mode == DIRECTIONAL_LIGHT);
	// 	renderer.point_light_count += (light.mode == POINT_LIGHT);
	// }

	// auto directional_light_count = renderer.directional_light_count;
	// auto point_light_count = renderer.point_light_count;

	// pbr_mesh_shader = renderer.GetPBRShader("pbrmesh");

	// int directional_light_count_temp = directional_light_count;
	// int point_light_count_temp = point_light_count;

	// pbr_mesh_shader->Bind();

	// for (auto [entity, tag, transform, light]: registry.view<Tag, Transform, Light>().each()) {
	// 	if (light.mode == DIRECTIONAL_LIGHT) {
	// 		auto direction = glm::normalize(transform.GetRotationQuat() * glm::vec3(0, -1.0, 0));
	// 		auto dir_light = "dir_light" + std::to_string(directional_light_count_temp);

	// 		directional_light_count_temp--;

	// 		pbr_mesh_shader->SetUniformVec3(dir_light + ".position", &transform.translation[0]);
	// 		pbr_mesh_shader->SetUniformVec3(dir_light + ".color", &light.color[0]);
	// 		pbr_mesh_shader->SetUniformVec3(dir_light + ".direction", &direction[0]);
	// 	}
	// 	if (light.mode == POINT_LIGHT) {
	// 		point_light_count_temp--;

	// 		auto point_light = "point_light" + std::to_string(point_light_count_temp);

	// 		pbr_mesh_shader->SetUniformVec3(point_light + ".position", &transform.translation[0]);
	// 		pbr_mesh_shader->SetUniformVec3(point_light + ".color", &light.color[0]);
	// 	}
	// }

	// pbr_mesh_shader->UnBind();

	lighting_entities.clear();
	mesh_material_entities.clear();

	for (auto [entity, tag, transform, meshrenderer]: registry.view<Tag, Transform, MeshRenderer>().each()) {
		if (meshrenderer.mesh == nullptr) continue;
		
		if (meshrenderer.enable_lighting) {
			lighting_entities.insert(entity);
		}

		mesh_material_entities[meshrenderer.material].push_back(entity);
	}

	sprite_material_entities.clear();

	for (auto [entity, tag, transform, spriterenderer]: registry.view<Tag, Transform, SpriteRenderer>().each()) {
		if (!spriterenderer.visible) continue;

		if (spriterenderer.enable_lighting) {
			lighting_entities.insert(entity);
		}

		sprite_material_entities[spriterenderer.material].push_back(entity);
	}
}