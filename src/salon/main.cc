#include <stdexcept>
#include <iostream>
#include <typeinfo>

#include <ArgParser.h>
#include <SalonServer.h>

#include <log4cxx/consoleappender.h>
#include <log4cxx/fileappender.h>
#include <log4cxx/logger.h>
#include <log4cxx/logmanager.h>
#include <log4cxx/patternlayout.h>
#include <log4cxx/helpers/pool.h>

static void configure_root_logger (bool debug)
{
	log4cxx::LoggerPtr root = log4cxx::Logger::getRootLogger ();
	log4cxx::LogString TTCC_CONVERSION_PATTERN (
			LOG4CXX_STR("%r %p %c - %m%n"));
	log4cxx::LayoutPtr layout (new log4cxx::PatternLayout (
				TTCC_CONVERSION_PATTERN));
	log4cxx::FileAppenderPtr appender(new log4cxx::FileAppender(layout, "salon.txt", true));
	//log4cxx::ConsoleAppenderPtr appender (new log4cxx::ConsoleAppender ());


	if (debug)
		root->setLevel (log4cxx::Level::getDebug ());
	else
		root->setLevel (log4cxx::Level::getDebug ());

	appender->setLayout (layout);

	//log4cxx::helpers::Pool pool;
	//appender->activateOptions (pool);

	root->addAppender (appender);

	log4cxx::LogManager::getLoggerRepository()->setConfigured (true);
	LOG4CXX_DEBUG (root, "log4cxx inicializado.");
}

int main (int argc, char **argv)
{
	try {
		ArgParser args(argc, argv);

		configure_root_logger (args.debug ());

		SalonServer server (ArgParser (argc, argv));
		server.run ();
	} catch (std::exception& e) {
		std::cout << typeid (e).name () << ": " << e.what () << std::endl;
		return 1;
	} catch (...) {
		/* correr destructores por favor. */
		return 1;
	}
	return 0;
}
