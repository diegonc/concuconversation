#include <stdexcept>

#include <errno.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/sem.h>

#include <system/InitializedSemaphore.h>
#include <system/System.h>

InitializedSemaphore::InitializedSemaphore (IPCName name, int nsems, int flags)
	: Semaphore (name, nsems, flags)
{
	initialize ();
}

InitializedSemaphore::InitializedSemaphore (key_t key, int nsems, int flags)
	: Semaphore (key, nsems, flags)
{
	initialize ();
}

void InitializedSemaphore::initialize ()
{
	for (int i=0; i < nsems; i++)
		set (i, 0);
}
