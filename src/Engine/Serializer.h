#pragma once

#include <string>
#include "ToYAML.h"

namespace lucy {
	void SerializeMaterialRegistry(YAML::Emitter& out);
	void SerializeMeshRegistry(YAML::Emitter& out);
	void SerializeMesh(YAML::Emitter& out);
	void SerializeSpriteRegistry(YAML::Emitter& out);
	void SerializeSprite(YAML::Emitter& out);
	void SerializeTexture(YAML::Emitter& out);
	void SerializeEntities(YAML::Emitter& out);

	void DeserializeMaterialRegistry(YAML::Node& text);
	void DeserializeMeshRegistry(YAML::Node& text);
	void DeserializeMesh(YAML::Node& text);
	void DeserializeSpriteRegistry(YAML::Node& text);
	void DeserializeSprite(YAML::Node& text);
	void DeserializeTexture(YAML::Node& text);
	void DeserializeEntities(YAML::Node& text);
}