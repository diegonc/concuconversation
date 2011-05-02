#include <system/SharedBuffer.h>
#include <system/System.h>

SharedBuffer::SharedBuffer (IPCName name, size_t size)
{
	key_t token = ftok (name.path, name.index);
	System::check (token);

	id = shmget (token, size, 0666 | IPC_CREAT);
	System::check (id);

	ptr = shmat (id, NULL, 0);
	if (ptr == (void *)-1) {
		shmctl (id, IPC_RMID, NULL);
	}
}

SharedBuffer::~SharedBuffer ()
{
	shmdt (ptr);
	shmctl (id, IPC_RMID, NULL);
}
