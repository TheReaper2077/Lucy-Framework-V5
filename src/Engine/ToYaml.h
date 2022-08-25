#pragma once

#include "ECS.h"
#include <Registry/Registry.h>
#include "yaml-cpp/yaml.h"
#include "yaml-cpp/emitter.h"
#include <Components/Components.h>

YAML::Emitter& operator<<(YAML::Emitter& out, const glm::vec2& v);
YAML::Emitter& operator<<(YAML::Emitter& out, const glm::vec3& v);
YAML::Emitter& operator<<(YAML::Emitter& out, const glm::vec4& v);
YAML::Emitter& operator<<(YAML::Emitter& out, const glm::bvec2& v);
YAML::Emitter& operator<<(YAML::Emitter& out, const glm::bvec3& v);
YAML::Emitter& operator<<(YAML::Emitter& out, const glm::bvec4& v);

YAML::Emitter& operator<<(YAML::Emitter& out, const lucy::Tag* v);
YAML::Emitter& operator<<(YAML::Emitter& out, const lucy::Transform* v);
YAML::Emitter& operator<<(YAML::Emitter& out, const lucy::Camera* v);
YAML::Emitter& operator<<(YAML::Emitter& out, const lucy::Light* v);
YAML::Emitter& operator<<(YAML::Emitter& out, const lucy::SpriteRenderer* v);
YAML::Emitter& operator<<(YAML::Emitter& out, const lucy::MeshRenderer* v);
YAML::Emitter& operator<<(YAML::Emitter& out, const lucy::RawTexture* v);
YAML::Emitter& operator<<(YAML::Emitter& out, const lucy::Sprite* v);

namespace YAML {
	template<>
	struct convert<glm::bvec2> {
		static Node encode(const glm::bvec2& rhs) {
			Node node;
			node.push_back(rhs.x);
			node.push_back(rhs.y);
			return node;
		}

		static bool decode(const Node& node, glm::bvec2& rhs) {
			if(!node.IsSequence() || node.size() != 2) {
				return false;
			}

			rhs.x = node[0].as<bool>();
			rhs.y = node[1].as<bool>();

			return true;
		}
	};

	template<>
	struct convert<glm::bvec3> {
		static Node encode(const glm::bvec3& rhs) {
			Node node;
			node.push_back(rhs.x);
			node.push_back(rhs.y);
			node.push_back(rhs.z);
			return node;
		}

		static bool decode(const Node& node, glm::bvec3& rhs) {
			if(!node.IsSequence() || node.size() != 3) {
				return false;
			}

			rhs.x = node[0].as<bool>();
			rhs.y = node[1].as<bool>();
			rhs.z = node[2].as<bool>();

			return true;
		}
	};

	template<>
	struct convert<glm::bvec4> {
		static Node encode(const glm::bvec4& rhs) {
			Node node;
			node.push_back(rhs.x);
			node.push_back(rhs.y);
			node.push_back(rhs.z);
			node.push_back(rhs.w);
			return node;
		}

		static bool decode(const Node& node, glm::bvec4& rhs) {
			if(!node.IsSequence() || node.size() != 4) {
				return false;
			}

			rhs.x = node[0].as<bool>();
			rhs.y = node[1].as<bool>();
			rhs.z = node[2].as<bool>();
			rhs.w = node[4].as<bool>();

			return true;
		}
	};

	template<>
	struct convert<glm::vec2> {
		static Node encode(const glm::vec2& rhs) {
			Node node;
			node.push_back(rhs.x);
			node.push_back(rhs.y);
			return node;
		}

		static bool decode(const Node& node, glm::vec2& rhs) {
			if(!node.IsSequence() || node.size() != 2) {
				return false;
			}

			rhs.x = node[0].as<float>();
			rhs.y = node[1].as<float>();

			return true;
		}
	};

	template<>
	struct convert<glm::vec3> {
		static Node encode(const glm::vec3& rhs) {
			Node node;
			node.push_back(rhs.x);
			node.push_back(rhs.y);
			node.push_back(rhs.z);
			return node;
		}

		static bool decode(const Node& node, glm::vec3& rhs) {
			if(!node.IsSequence() || node.size() != 3) {
				return false;
			}

			rhs.x = node[0].as<float>();
			rhs.y = node[1].as<float>();
			rhs.z = node[2].as<float>();

			return true;
		}
	};

	template<>
	struct convert<glm::vec4> {
		static Node encode(const glm::vec4& rhs) {
			Node node;
			node.push_back(rhs.x);
			node.push_back(rhs.y);
			node.push_back(rhs.z);
			node.push_back(rhs.w);
			return node;
		}

		static bool decode(const Node& node, glm::vec4& rhs) {
			if(!node.IsSequence() || node.size() != 4) {
				return false;
			}

			rhs.x = node[0].as<float>();
			rhs.y = node[1].as<float>();
			rhs.z = node[2].as<float>();
			rhs.w = node[3].as<float>();

			return true;
		}
	};

	template<>
	struct convert<lucy::Tag> {
		static Node encode(const lucy::Tag& rhs) {
			Node node;
			node["name"] = rhs.name;
			node["id"] = rhs.id;
			return node;
		}

		static bool decode(const Node& node, lucy::Tag& rhs) {
			if (!node.IsMap()) {
				return false;
			}
			
			rhs.id = node["id"].as<std::string>();
			rhs.name = node["name"].as<std::string>();

			return true;
		}
	};

	template<>
	struct convert<lucy::Transform> {
		static Node encode(const lucy::Transform& rhs) {
			Node node;
			node["translation"] = rhs.translation;
			node["rotation"] = rhs.rotation;
			node["scale"] = rhs.scale;
			return node;
		}

		static bool decode(const Node& node, lucy::Transform& rhs) {
			if (!node.IsMap()) {
				return false;
			}

			rhs.translation = node["translation"].as<glm::vec3>();
			rhs.rotation = node["rotation"].as<glm::vec3>();
			rhs.scale = node["scale"].as<glm::vec3>();

			return true;
		}
	};

	template<>
	struct convert<lucy::Camera> {
		static Node encode(const lucy::Camera& rhs) {
			Node node;
			node["position"] = rhs.position;
			node["up"] = rhs.up;
			node["front"] = rhs.front;
			node["world_up"] = rhs.world_up;
			node["world_front"] = rhs.world_front;
			node["type"] = (uint32_t)rhs.mode;
			node["mode"] = (uint32_t)rhs.type;
			node["enable"] = rhs.enable;
			return node;
		}

		static bool decode(const Node& node, lucy::Camera& rhs) {
			if (!node.IsMap()) {
				return false;
			}

			rhs.position = node["position"].as<glm::vec3>();
			rhs.up = node["up"].as<glm::vec3>();
			rhs.front = node["front"].as<glm::vec3>();
			rhs.world_up = node["world_up"].as<glm::vec3>();
			rhs.world_front = node["world_front"].as<glm::vec3>();
			rhs.type = (lucy::Projection_Type)node["type"].as<uint32_t>();
			rhs.mode = (lucy::ViewMode)node["mode"].as<uint32_t>();
			rhs.enable = node["enable"].as<bool>();

			return true;
		}
	};

	template<>
	struct convert<lucy::Light> {
		static Node encode(const lucy::Light& rhs) {
			Node node;
			node["enable"] = rhs.enable;
			node["color"] = rhs.color;
			node["mode"] = (uint32_t)rhs.mode;
			return node;
		}

		static bool decode(const Node& node, lucy::Light& rhs) {
			if (!node.IsMap()) {
				return false;
			}

			rhs.enable = node["enable"].as<bool>();
			rhs.color = node["color"].as<glm::vec4>();
			rhs.mode = (lucy::LightMode)node["mode"].as<uint32_t>();

			return true;
		}
	};

	template<>
	struct convert<lucy::SpriteRenderer> {
		static Node encode(const lucy::SpriteRenderer& rhs) {
			Node node;
			node["visible"] = rhs.visible;
			node["color"] = rhs.color;
			if (rhs.material != nullptr)
				node["material_id"] = rhs.material->id;
			else
				node["material_id"] = 0;
			// if (rhs.sprite != nullptr)
			// 	node["sprite_id"] = rhs.sprite->id;
			// else
			// 	node["sprite_id"] = 0;
			node["uv0"] = rhs.uv0;
			node["uv1"] = rhs.uv1;
			return node;
		}

		static bool decode(const Node& node, lucy::SpriteRenderer& rhs) {
			auto& materialregistry = lucy::Registry::Instance().store<lucy::MaterialRegistry>();
			auto& spriteregistry = lucy::Registry::Instance().store<lucy::SpriteRegistry>();

			if (!node.IsMap()) {
				return false;
			}

			rhs.visible = node["visible"].as<bool>();
			rhs.color = node["color"].as<glm::vec4>();
			rhs.material = materialregistry.GetMaterial(node["material_id"].as<std::string>());
			// rhs.sprite = spriteregistry.GetTextureById(node["sprite_id"].as<std::string>());
			rhs.uv0 = node["uv0"].as<glm::vec2>();
			rhs.uv1 = node["uv1"].as<glm::vec2>();

			return true;
		}
	};

	template<>
	struct convert<lucy::MeshRenderer> {
		static Node encode(const lucy::MeshRenderer& rhs) {
			Node node;
			node["visible"] = rhs.visible;
			if (rhs.material != nullptr)
				node["material_id"] = rhs.material->id;
			else
				node["material_id"] = 0;
			return node;
		}

		static bool decode(const Node& node, lucy::MeshRenderer& rhs) {
			auto& materialregistry = lucy::Registry::Instance().store<lucy::MaterialRegistry>();

			if (!node.IsMap()) {
				return false;
			}

			rhs.visible = node["visible"].as<bool>();
			rhs.material = materialregistry.GetMaterial(node["material_id"].as<std::string>());
			// rhs.custom_flags = node["custom_flags"].as<uint32_t>();

			return true;
		}
	};
}