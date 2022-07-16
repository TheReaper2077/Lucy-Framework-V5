#pragma once

#include <string>
#include <fstream>

namespace lucy::util {
	std::string read_file(const std::string& filename) {
		std::string line, text = "";
		std::fstream file(filename);

		if (!file.is_open()) return text;

		while (std::getline(file, line)) text += (line + '\n');

		file.close();

		return text;
	}

	bool write_file(const std::string& filename, const std::string& source) {
		return write_file(filename, source.c_str());
	}

	bool write_file(const std::string& filename, const char* source) {
		std::ofstream fout(filename.c_str());

		if (!fout.is_open()) return false;

		fout << source;
		fout.close();

		return true;
	}

	void replace_first(std::string& s, std::string const& toReplace, std::string const& replaceWith) {
		size_t pos = s.find(toReplace);
		if (pos == std::string::npos) return;

		s.replace(pos, toReplace.length(), replaceWith);
	}
}