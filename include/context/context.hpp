#pragma once

#include <vector>
#include <memory>
#include "instance.hpp"

namespace Server {

	class Context {
	public:
		Context();
		~Context();
	protected:
		std::vector<std::weak_ptr<Instance>> attachments;
	};
}
