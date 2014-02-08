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

	class File {
	public:
		File(Filesystem &fs) : filesys(fs) {}
		virtual ~File();

		virtual bool isOpen();
		virtual bool Open();
		virtual bool Open(std::string);
		virtual void Close();
	private:
		Filesystem & filesys;
	};

	class LocalFile : public File {
	public:
		LocalFile();
		LocalFile(std::string);
		~LocalFile();
	};
}
