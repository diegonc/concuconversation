#ifndef ARGPARSER_H
#define ARGPARSER_H

#include <string>
#include <iostream>

class ArgParser
{
	private:
		std::string _salon;
		bool _debug;

	public:
		ArgParser (int argc, char **argv);

		bool debug () const;
		const std::string& salon () const;
};

#endif
