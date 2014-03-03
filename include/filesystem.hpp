#pragma once

#include <string>
#include <iostream>
#include "net/network.h"
#include <memory>
#include <fstream>

namespace Server {
	class Filesystem {
	public:
		Filesystem() {}
		virtual ~Filesystem() {}
	};

	class LocalFilesystem : public Filesystem {
	public:
		LocalFilesystem();
		~LocalFilesystem();
	};

	template <class T>
	class File {
	public:
		File(T &fs) : filesys(fs) {}
		virtual ~File() {
			Close();
		}

		virtual bool isOpen() {
			return false;
		}
		virtual bool Open() {
			return false;
		}
		virtual bool Open(std::string) {
			return false;
		}
		virtual void Close() {
		}
	private:
		T &filesys;
	};

	typedef File<LocalFilesystem> LocalFile;
}
