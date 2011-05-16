#include <log4cxx/helpers/thread.h>
#include <log4cxx/helpers/loglog.h>
#include <log4cxx/CursesAppender.h>

using namespace log4cxx;
using namespace log4cxx::helpers;

IMPLEMENT_LOG4CXX_OBJECT(CursesAppender)

void CursesAppender::append (const spi::LoggingEventPtr& event, Pool& p)
{
	if (checkEntryConditions ()) {
		log4cxx::LogString msg;
		layout->format (msg, event, p);

		LOG4CXX_ENCODE_CHAR (str, msg);
		waddstr (cm->getLoggingWindow (), str.c_str ());
		cm->refresh ();
	}
}

void CursesAppender::close()
{
        if (this->closed)
        {
                return;
        }

        this->closed = true;
}

bool CursesAppender::checkEntryConditions() const {
	static bool warnedClosed = false;
	static bool warnedNoWindow = false;
	if (closed) {
		if(!warnedClosed) {
			log4cxx::helpers::LogLog::warn (LOG4CXX_STR("Not allowed to write to a closed appender."));
			warnedClosed = true;
		}
		return false;
	}

	if (cm == NULL) {
		if (!warnedNoWindow) {
			log4cxx::helpers::LogLog::error(LogString (
			  LOG4CXX_STR("No console manager set for the appender named ["))
			+ name + LOG4CXX_STR("]."));
			
			warnedNoWindow = true;
		}
		return false;
	}
	
	return true;
}

