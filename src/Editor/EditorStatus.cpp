#include "EditorStatus.h"

// static auto& r

void lucy::EditorStatus::SetTexture(std::string texture) {
	texture_changed = (texture == selected_texture);
	selected_texture = texture;

	if (texture_changed) {
		entity_changed = sprite_changed = false;
	}
}

bool lucy::EditorStatus::IsTextureChanged() {
	return texture_changed;
}

std::string lucy::EditorStatus::GetTextureID() {
	return selected_texture;
}

void lucy::EditorStatus::SetEntity(Entity entity) {
	entity_changed = (selected_entity == entity);
	selected_entity = entity;

	if (entity_changed) {
		texture_changed = sprite_changed = false;
	}
}

bool lucy::EditorStatus::IsEntityChanged() {
	return entity_changed;
}

lucy::Entity lucy::EditorStatus::GetEntityID() {
	return selected_entity;
}

void lucy::EditorStatus::SetSprite(std::string sprite) {
	sprite_changed = (selected_sprite == sprite);
	selected_sprite = sprite;

	if (sprite_changed) {
		entity_changed = texture_changed = false;
	}
}

bool lucy::EditorStatus::IsSpriteChanged() {
	return sprite_changed;
}

std::string lucy::EditorStatus::GetSpriteID() {
	return selected_sprite;
}

void lucy::EditorStatus::OpenSpriteEditor(std::string texture) {
	
}

void lucy::EditorStatus::CloseSpriteEditor() {
	
}

std::string lucy::EditorStatus::SpriteEditorTexture() {
	return "";
}

bool lucy::EditorStatus::IsOpenSpriteEditor() {
	return false;
}

