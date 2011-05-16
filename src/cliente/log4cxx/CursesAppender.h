
#include <curses.h>

#include <ConsoleManager.h>

#include <log4cxx/appenderskeleton.h>
#include <log4cxx/spi/loggingevent.h>

using namespace log4cxx;

class CursesAppender : public log4cxx::AppenderSkeleton
{
	public:
		DECLARE_LOG4CXX_OBJECT(CursesAppender)
		BEGIN_LOG4CXX_CAST_MAP()
			LOG4CXX_CAST_ENTRY(CursesAppender)
			LOG4CXX_CAST_ENTRY_CHAIN(AppenderSkeleton)
		END_LOG4CXX_CAST_MAP()

	//	#undef helpers

		ConsoleManager *cm;

		CursesAppender () : cm (NULL) { }
		CursesAppender (ConsoleManager *cm) : cm (cm) { }

		/**
		This method is called by the AppenderSkeleton#doAppend
		method.
		*/
		void append (const log4cxx::spi::LoggingEventPtr& event, log4cxx::helpers::Pool& p);

		void close ();

		bool isClosed () const
		{ return closed; }

		bool requiresLayout() const
		{ return true;   }
	private:
		bool checkEntryConditions () const;
};
typedef log4cxx::helpers::ObjectPtrT<CursesAppender> CursesAppenderPtr;
