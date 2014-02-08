#pragma once

#include <string>
#include "filesystem.hpp"

namespace Server {
	class Configuration {
	public:
		Configuration();
		~Configuration();

		bool Load(File &);
		bool Save(File &);

		template<typename T>
		T Get(std::wstring section, std::wstring item) const {
		}
	};
}
