#pragma once

#include "Panel.h"

namespace lucy {
	struct PanelRegistry {
	private:
		std::unordered_map<uint32_t, std::shared_ptr<PanelTemplate>> panel_map;

	public:
		PanelRegistry() {}
		~PanelRegistry() {}

		void Init();

		template <unsigned int T>
		void Add() {
			panel_map[T] = std::static_pointer_cast<PanelTemplate>(std::make_shared<Panel<T>>());
		}

		template <unsigned int T>
		std::shared_ptr<Panel<T>>& Get() {
			assert(panel_map.find(T) != panel_map.end());

			return std::static_pointer_cast<Panel<T>>(panel_map[T]);
		}

		void Render() {
			for (auto& pair: panel_map) {
				pair.second->Render();
			}
		}
	};
}