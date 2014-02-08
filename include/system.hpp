#pragma once

#include "filesystem.hpp"
#include "configuration.hpp"

namespace Server {
	class System {
	public:
		System() {}
		virtual ~System() {}

		// all system functions return true on success
		virtual bool Init(const Configuration &, LocalFilesystem &) = 0;
		virtual bool Start() = 0;
		virtual bool Tick(double) = 0;
		virtual bool Stop() = 0;
		virtual bool Save(Configuration &, LocalFilesystem &) = 0;
		virtual bool Destroy() = 0;
	};
}
