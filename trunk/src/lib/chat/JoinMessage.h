#ifndef JOINMESSAGE_H
#define JOINMESSAGE_H

class JoinMessage;

#include <string>

#include <unistd.h>

#include <chat/Message.h>
#include <chat/MessageVisitor.h>
#include <chat/Packet.h>

class JoinMessage : public Message
{
	public:
		static const int MESSAGE_ID = 1;

	private:
		std::string name;
		pid_t pid;
		/*IPCName acknowledgedMessages; */

	public:
		JoinMessage (const std::string& name);
		JoinMessage (Packet &pkt);

		const std::string& getNombre () const { return name; }
		const pid_t getPID () const { return pid; }

		void write (OutputStream& stream) const;
		std::string toString () const;

		void accept (MessageVisitor& v) const;
};

#endif
