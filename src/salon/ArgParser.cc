#include <stdexcept>

#include <unistd.h>

#include <ArgParser.h>

namespace {
	std::string usage (const char *prg)
	{
		/* TODO ...*/
		throw std::runtime_error ("Invalid arguments.");
	}
}

ArgParser::ArgParser (int argc, char **argv)
{
	const char *prg = argv[0];

	if (argc == 1)
		usage (prg);

	_debug = false;
	argc--;
	argv++;
	bool room = false;
	while (argc > 0) {
		if (argv[0][0] == '-')
			if (argv[0][1] == 'd')
				_debug = true;
			else
				usage (prg);
		else {
			_salon.replace (_salon.begin (), _salon.end (),
					argv[0]);
			room = true;
		}
		argc--;
		argv++;
	}

	if (!room)
		usage (prg);
}

const std::string& ArgParser::salon () const
{
	return _salon;
}

bool ArgParser::debug () const
{
	return _debug;
}
