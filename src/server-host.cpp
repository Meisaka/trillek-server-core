
#include "server.hpp"

namespace Server {
	Host::Host() {}
	Host::~Host() {}

	bool Host::Init(const Configuration &, LocalFilesystem &) {
		return true;
	}
	bool Host::Start() {
		return true;
	}
	bool Host::Tick(double delta) {
		return true;
	}
	bool Host::Stop() {
		return true;
	}
	bool Host::Save(Configuration &, LocalFilesystem &) {
		return true;
	}
	bool Host::Destroy() {
		return true;
	}
}
