#ifndef FILEUNLINKER_H
#define FILEUNLINKER_H

#include <unistd.h>

#include <string>
#include <iostream>

class FileUnlinker
{
	private:
		const std::string path;

	public:
		FileUnlinker (const std::string& path)
			: path (path) {}

		~FileUnlinker ()
		{
			unlink (path.c_str ());
		}
};

#endif
