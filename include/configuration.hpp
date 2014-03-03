#pragma once

#include <string>
#include "filesystem.hpp"

namespace Server {
	class Configuration {
	public:
		Configuration();
		~Configuration();

		template<typename T>
		bool Load(File<T> &) {
			return false;
		}
		template<typename T>
		bool Save(File<T> &) {
			return false;
		}

		template<typename T>
		T Get(std::wstring section, std::wstring item) const {
		}
	};
}
