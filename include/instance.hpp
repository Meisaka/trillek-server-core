#pragma once

#include <memory>
#include <string>
#include "net/network.h"
#include "server.hpp"

namespace Server {

	class Instance {
		friend class Host;
	public:
		Instance();
		~Instance();

		void SendRaw(const char *, int);
		void SendRawString(std::string);
	protected:
		std::unique_ptr<network::TCPConnection> tcpremote;
	};
}
