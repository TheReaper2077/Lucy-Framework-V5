#pragma once

#include "Panel.h"
#include <string>
#include <Registry/Registry.h>

namespace lucy {
	class Explorer {
	private:
		std::string tree_path, explorer_path, treeinit_path, selectedtree_path, selectedexploreritem_path;
		std::unordered_map<std::string, bool> node_state;

	public:
		Explorer();
		~Explorer() {}

		void SetTreePath(std::string path);
		void SetExplorerPath(std::string path);
		void SetTreeInitPath(std::string path);
		std::string GetSelectedTreePath();
		std::string GetSelectedExplorerItemPath();

		void RenderTree();
		void RenderTree(const std::string& dirpath);
		void ShortcutMenu();
		void RenderExplorer();

		void Render();
	};
}