#pragma once

#include <memory>
#include "configuration.hpp"
#include "system.hpp"
#include "net/network.h"

namespace Server {

	class Host : public System {
	public:
		Host();
		~Host();

		bool Init(const Configuration &, LocalFilesystem &);
		bool Start();
		bool Tick(double);
		bool Stop();
		bool Save(Configuration &, LocalFilesystem &);
		bool Destroy();
	};
}
