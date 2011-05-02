#include <stdexcept>

#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/sem.h>

#include <system/Semaphore.h>
#include <system/System.h>

Semaphore::Semaphore (IPCName name, int nsems)
{
	key_t token = ftok (name.path, name.index);
	System::check (token);

	initialize (token, nsems, 0666 | IPC_CREAT);
}

Semaphore::Semaphore (key_t key, int nsems)
{
	initialize (key, nsems, 0666 | IPC_CREAT);
}

void Semaphore::initialize (key_t key, int nsems, int flags)
{
	id = semget (key, nsems, flags);
	System::check (id);

	for (int i=0; i < nsems; i++)
		set (i, 0);
}

void Semaphore::set (int idx, int value)
{
	union  semun {
		int val;
		struct semid_ds *buf;
		unsigned short  *array;
	} arg;

	arg.val = value;
	semctl (id, idx, SETVAL, arg);
}

void Semaphore::wait (int idx, int value)
{
	if (value < 0)
		throw std::invalid_argument ("Semaphore::wait: value must be positive.");

	struct sembuf ops;

	ops.sem_num = idx;
	ops.sem_op = -value;
	ops.sem_flg = 0;
	
	bool retry = false;
	do {
		int ret = semop (id, &ops, 1);
		if (ret == -1)
			if (errno == EINTR)
				retry = true;
			else
				throw SystemErrorException ();
	} while (retry);
}

void Semaphore::signal (int idx, int value)
{
	if (value < 0)
		throw std::invalid_argument ("Semaphore::signal: value must be positive.");

	struct sembuf ops;

	ops.sem_num = idx;
	ops.sem_op = value;
	ops.sem_flg = 0;

	System::check (semop (id, &ops, 1));
}
