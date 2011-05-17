#ifndef JOINMESSAGE_H
#define JOINMESSAGE_H

class JoinMessage;

#include <string>

#include <unistd.h>

#include <chat/Message.h>
#include <chat/MessageVisitor.h>
#include <chat/Packet.h>
#include <log4cxx/logger.h>

class JoinMessage : public Message
{
	public:
		static const int MESSAGE_ID = 1;

	private:
		static log4cxx::LoggerPtr logger;
		std::string name;
		pid_t pid;
		std::string ipcNamespace;

	public:
		JoinMessage (const std::string& name, pid_t pid, const std::string& ipcNamespace);
		JoinMessage (Packet &pkt);

		const std::string& getNombre () const { return name; }
		pid_t getPID () const { return pid; }
		const std::string& getNamespace () const
		{
		       return ipcNamespace;
		}


		void write (OutputStream& stream) const;
		std::string toString () const;

		void accept (MessageVisitor& v) const;
};

#endif
