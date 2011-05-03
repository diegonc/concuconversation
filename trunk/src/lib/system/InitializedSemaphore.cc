#include <stdexcept>

#include <errno.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/sem.h>

#include <system/InitializedSemaphore.h>
#include <system/System.h>

InitializedSemaphore::InitializedSemaphore (IPCName name, int nsems)
	: Semaphore (name, nsems, 0666 | IPC_CREAT)
{
	initialize ();
}

InitializedSemaphore::InitializedSemaphore (key_t key, int nsems)
	: Semaphore (key, nsems, 0666 | IPC_CREAT)
{
	initialize ();
}

void InitializedSemaphore::initialize ()
{
	for (int i=0; i < nsems; i++)
		set (i, 0);
}
