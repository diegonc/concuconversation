#ifndef ARGPARSER_H
#define ARGPARSER_H

#include <string>

class ArgParser
{
	private:
		std::string _salon;
		std::string _nombre;
		bool _debug;

	public:
		ArgParser (int argc, char **argv);

		bool debug () const;
		const std::string& nombre () const;
		const std::string& salon () const;
};

#endif
