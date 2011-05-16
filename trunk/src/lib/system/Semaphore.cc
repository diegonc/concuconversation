#include <stdexcept>

#include <errno.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <iostream>

#include <system/Semaphore.h>
#include <system/System.h>

Semaphore::Semaphore (IPCName name, int nsems, int flags) : nsems (nsems)
{
	std::cout << "initializing [" << nsems <<"] semaphores with params [" << name.path << "] [" << name.index << "]." << std::endl;
	key_t token = ftok (name.path, name.index);
	System::check (token);
	id = semget (token, nsems, flags);
	System::check (id);
	std::cout << "Semaphore created: " << id << std::endl;
}

Semaphore::Semaphore (key_t key, int nsems, int flags) : nsems (nsems)
{
	id = semget (key, nsems, flags);
	System::check (id);
}

Semaphore::~Semaphore ()
{
	semctl (id, 0, IPC_RMID);
}

void Semaphore::initialize ()
{
	std::cout << "initializing semaphore" << id << std::endl;
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
	std::cout << "set semaphore " << id << " value" << idx << value << std::endl;
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
		std::cout << "wait semaphore " << id << " value" << idx << value << std::endl;
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
	std::cout << "signal semaphore " << id << " value" << idx << value << std::endl;
	System::check (semop (id, &ops, 1));
}
