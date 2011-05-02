#ifndef ARGPARSER_H
#define ARGPARSER_H

#include <string>

class ArgParser
{
	private:
		std::string _salon;
		bool _debug;

	public:
		ArgParser (int argc, char **argv);

		const std::string& salon () const;
		bool debug () const;
};

#endif
