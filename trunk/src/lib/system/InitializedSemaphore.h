#ifndef UNINITIALIZEDSEMAPHORE_H
#define UNINITIALIZEDSEMAPHORE_H

#include <sys/types.h>

#include <system/IPCName.h>
#include <system/Semaphore.h>

class InitializedSemaphore : public Semaphore
{
	private:
		void initialize ();

	public:
		InitializedSemaphore (key_t key, int nsems, int flags);
		InitializedSemaphore (IPCName name, int nsems, int flags);
};

#endif
