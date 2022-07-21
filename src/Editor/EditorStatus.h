#pragma once

#include <Engine/ECS.h>
#include <string>

namespace lucy {
	struct EditorStatus {
	private:
		Entity selected_entity = (Entity)0;

		std::string selected_texture = "", selected_sprite = "";

		bool texture_changed, entity_changed, sprite_changed;

		std::string sprite_editor_select_texture;

	public:
		Entity editor_camera = (Entity)0;

		void SetTexture(std::string texture);
		bool IsTextureChanged();
		std::string GetTextureID();

		void SetEntity(Entity entity);
		bool IsEntityChanged();
		Entity GetEntityID();

		void SetSprite(std::string sprite);
		bool IsSpriteChanged();
		std::string GetSpriteID();

		void OpenSpriteEditor(std::string texture);
		void CloseSpriteEditor();
		std::string SpriteEditorTexture();
		bool IsOpenSpriteEditor();
	};
}