
#include "filesystem.hpp"

namespace Server {

	LocalFilesystem::LocalFilesystem() {
	}
	LocalFilesystem::~LocalFilesystem() {
	}

	File::~File() {
		Close();
	}
	bool File::isOpen() {
		return false;
	}
	bool File::Open() {
		return false;
	}
	bool File::Open(std::string) {
		return false;
	}
	void File::Close() {
	}

	LocalFile::LocalFile() : File(LocalFilesystem()) {
	}
	LocalFile::LocalFile(std::string v) : File(LocalFilesystem()) {
		File::Open(v);
	}
	LocalFile::~LocalFile() {
		File::Close();
	}

}
