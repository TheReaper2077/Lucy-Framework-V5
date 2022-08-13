#pragma once

#include <stddef.h>
#include <string>
#include <unordered_map>

namespace lgl {
	typedef unsigned int ShaderId;

	struct Shader {
		ShaderId program;
		std::unordered_map<std::string, unsigned int> uniform_location_map;

		bool textures = false;
		bool texture_array = false;
		bool material = false;
		bool light = false;
	
	public:
		Shader(const std::string &vs_filename, const std::string &fs_filename, bool file);
		Shader(const std::string &vs_filename, const std::string &fs_filename);
		Shader();
		~Shader();

		void Bind();
		void UnBind();

		void BindUniformBlock(std::string name, unsigned int index);
		unsigned int GetUniformLoc(std::string name);

		bool SetUniformi(std::string uniform, int v0);
		bool SetUniformf(std::string uniform, float v0);
		bool SetUniformVec2(std::string uniform, const float* v);
		bool SetUniformVec3(std::string uniform, const float* v);
		bool SetUniformVec4(std::string uniform, const float* v);
		bool SetUniformMat4(std::string uniform, const float* matrix);
		bool SetUniformArray(std::string uniform, size_t count, const float* v);
		bool SetUniformArray(std::string uniform, size_t count, const unsigned int* v);
		bool SetUniformArray(std::string uniform, size_t count, const int* v);
	};
}