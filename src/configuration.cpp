
#include "configuration.hpp"

namespace Server {
	Configuration::Configuration() {}
	Configuration::~Configuration() {}

	bool Configuration::Load(File &) {
		return true;
	}
	bool Configuration::Save(File &) {
		return true;
	}
}
