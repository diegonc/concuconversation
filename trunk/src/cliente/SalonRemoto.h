#ifndef SALONREMOTO_H
#define SALONREMOTO_H

#include <string>

#include <chat/Message.h>
#include <chat/TextMessage.h>
#include <io/FifoOutputStream.h>
#include <system/Semaphore.h>

class SalonRemoto
{
	private:
		FifoOutputStream *fifo;
		Semaphore *lock;

		FifoOutputStream *iniciar (const std::string& salon);

		void doPost (const Message& msg);

	public:
		SalonRemoto (const std::string& salon);
		virtual ~SalonRemoto ();

		virtual void join (const std::string& name, pid_t pid, const std::string& ipcNamespace);
		virtual void quit (const std::string& name);
		virtual void post (const TextMessage& msg);
};

#endif
