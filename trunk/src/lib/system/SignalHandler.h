#ifndef SIGNALHANDLER_H
#define SIGNALHANDLER_H

#include <signal.h>
#include <stdio.h>

#include <system/EventHandler.h>

class SignalHandler
{
	private :
		static SignalHandler instance;
		static EventHandler *signal_handlers[NSIG];

		SignalHandler (void);
		static void dispatcher (int signum);

	public :
		static SignalHandler& getInstance ();
		
		EventHandler* registrarHandler (int signum, EventHandler *eh);
		int removerHandler (int signum);
};

#endif /* SIGNALHANDLER_H */
