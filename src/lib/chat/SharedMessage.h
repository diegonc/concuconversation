#ifndef SHAREDMESSAGE_H
#define SHAREDMESSAGE_H

#include <memory>
#include <chat/Message.h>
#include <system/SharedVariable.h>

class SharedMessage
{
	typedef char Buffer[4096];

	SharedVariable<Buffer> buffer;

	public:
		SharedMessage (IPCName name, int flags)
			: buffer (name, flags) {}
		~SharedMessage () {}

		void set (const Message& msg);
		std::auto_ptr<Message> get ();
};

#endif
