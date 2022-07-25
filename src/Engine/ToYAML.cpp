#include "ToYAML.h"

static auto& registry = lucy::Registry::Instance();
static auto& materialregistry = registry.store<lucy::MaterialRegistry>();
static auto& meshregistry = registry.store<lucy::MeshRegistry>();
static auto& spriteregistry = registry.store<lucy::SpriteRegistry>();

YAML::Emitter& operator<<(YAML::Emitter& out, const glm::bvec2& v) {
	out << YAML::Flow;
	out << YAML::BeginSeq << v.x << v.y << YAML::EndSeq;
	return out;
}

YAML::Emitter& operator<<(YAML::Emitter& out, const glm::bvec3& v) {
	out << YAML::Flow;
	out << YAML::BeginSeq << v.x << v.y << v.z << YAML::EndSeq;
	return out;
}

YAML::Emitter& operator<<(YAML::Emitter& out, const glm::bvec4& v) {
	out << YAML::Flow;
	out << YAML::BeginSeq << v.x << v.y << v.z << v.w << YAML::EndSeq;
	return out;
}

YAML::Emitter& operator<<(YAML::Emitter& out, const glm::vec2& v) {
	out << YAML::Flow;
	out << YAML::BeginSeq << v.x << v.y << YAML::EndSeq;
	return out;
}

YAML::Emitter& operator<<(YAML::Emitter& out, const glm::vec3& v) {
	out << YAML::Flow;
	out << YAML::BeginSeq << v.x << v.y << v.z << YAML::EndSeq;
	return out;
}

YAML::Emitter& operator<<(YAML::Emitter& out, const glm::vec4& v) {
	out << YAML::Flow;
	out << YAML::BeginSeq << v.x << v.y << v.z << v.w << YAML::EndSeq;
	return out;
}

YAML::Emitter& operator<<(YAML::Emitter& out, const lucy::Tag* v) {
	out << YAML::BeginMap;
	out << YAML::Key << "name";
	out << YAML::Value << v->name;
	out << YAML::Key << "id";
	out << YAML::Value << v->id;
	out << YAML::EndMap;
	return out;
}

YAML::Emitter& operator<<(YAML::Emitter& out, const lucy::Transform* v) {
	out << YAML::BeginMap;
	out << YAML::Key << "translation";
	out << YAML::Value << v->translation;
	out << YAML::Key << "rotation";
	out << YAML::Value << v->rotation;
	out << YAML::Key << "scale";
	out << YAML::Value << v->scale;
	out << YAML::EndMap;
	return out;
}

YAML::Emitter& operator<<(YAML::Emitter& out, const lucy::Camera* v) {
	out << YAML::BeginMap;
	out << YAML::Key << "up";
	out << YAML::Value << v->up;
	out << YAML::Key << "front";
	out << YAML::Value << v->front;
	out << YAML::Key << "world_up";
	out << YAML::Value << v->world_up;
	out << YAML::Key << "world_front";
	out << YAML::Value << v->world_front;
	out << YAML::Key << "ViewMode";
	out << YAML::Value << (uint32_t)v->mode;
	out << YAML::Key << "enable";
	out << YAML::Value << v->enable;
	out << YAML::EndMap;
	return out;
}

YAML::Emitter& operator<<(YAML::Emitter& out, const lucy::Light* v) {
	out << YAML::BeginMap;
	out << YAML::Key << "enable";
	out << YAML::Value << v->enable;
	out << YAML::Key << "color";
	out << YAML::Value << v->color;
	out << YAML::Key << "mode";
	out << YAML::Value << v->mode;
	out << YAML::EndMap;
	return out;
}

YAML::Emitter& operator<<(YAML::Emitter& out, const lucy::SpriteRenderer* v) {
	out << YAML::BeginMap;
	out << YAML::Key << "visible";
	out << YAML::Value << v->visible;
	out << YAML::Key << "color";
	out << YAML::Value << v->color;
	out << YAML::Key << "material_id";
	out << YAML::Value << materialregistry.GetMaterialID(v->material);
	out << YAML::Key << "uv0";
	out << YAML::Value << v->uv0;
	out << YAML::Key << "uv1";
	out << YAML::Value << v->uv1;
	out << YAML::EndMap;
	return out;
}

YAML::Emitter& operator<<(YAML::Emitter& out, const lucy::MeshRenderer* v) {
	out << YAML::BeginMap;
	out << YAML::Key << "visible";
	out << YAML::Value << v->visible;
	out << YAML::Key << "material_id";
	out << YAML::Value << materialregistry.GetMaterialID(v->material);
	out << YAML::EndMap;
	return out;
}

YAML::Emitter& operator<<(YAML::Emitter& out, const lucy::RawTexture* v) {
	out << YAML::BeginMap;
	out << YAML::Key << "filename";
	out << YAML::Value << v->filename;
	out << YAML::Key << "id";
	out << YAML::Value << v->id;
	out << YAML::Key << "name";
	out << YAML::Value << v->name;
	out << YAML::EndMap;
	return out;
}

YAML::Emitter& operator<<(YAML::Emitter& out, const lucy::Sprite* v) {
	out << YAML::BeginMap;
	out << YAML::Key << "id";
	out << YAML::Value << v->id;
	out << YAML::Key << "raw_texture_id";
	out << YAML::Value << v->texture_raw->id;
	out << YAML::Key << "name";
	out << YAML::Value << v->name;
	out << YAML::Key << "uv0";
	out << YAML::Value << v->uv0;
	out << YAML::Key << "uv1";
	out << YAML::Value << v->uv1;
	out << YAML::Key << "idx";
	out << YAML::Value << v->idx;
	out << YAML::EndMap;
	return out;
}
