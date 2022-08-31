#pragma once

#include "UUID.h"
#include <string>

namespace lutil::undo {
	struct Data {
		std::string type = "";
		LUTIL_UUID id = 0;
		uint32_t temp_data;
		void* data = nullptr;
		uint32_t size = 0;
	};

	void Initialize(int size = 256);
	void IsInitialized();

	void Push(const Data& data);

	template <typename ...Args>
	void Push(const Args& ...args) {
		Push(Data{args...});
	}

	void Clear();
	int GetSize();

	void Free();
}