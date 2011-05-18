#include <stdexcept>

#include <errno.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <iostream>

#include <system/Semaphore.h>
#include <system/System.h>

namespace {
	union  semun {
		int val;
		struct semid_ds *buf;
		unsigned short  *array;
	} arg;
}

log4cxx::LoggerPtr Semaphore::logger (log4cxx::Logger::getLogger ("Semaphore"));

Semaphore::Semaphore (IPCName name, int nsems, int flags) : nsems (nsems)
{
	LOG4CXX_DEBUG(logger,
		"initializing [" << nsems <<"] semaphores with params ["
		<< name.path << "] [" << name.index << "].");

	key_t token = ftok (name.path, name.index);
	System::check (token);
	id = semget (token, nsems, flags);
	System::check (id);

	LOG4CXX_DEBUG(logger, "Semaphore created: set:" << id);
}

Semaphore::Semaphore (key_t key, int nsems, int flags) : nsems (nsems)
{
	id = semget (key, nsems, flags);
	System::check (id);
}

Semaphore::~Semaphore ()
{
	union semun arg = {0};
	semctl (id, 0, IPC_RMID, arg);
}

void Semaphore::initialize ()
{
	LOG4CXX_DEBUG(logger, "initializing semaphore set:" << id);

	for (int i=0; i < nsems; i++)
		set (i, 0);
}

void Semaphore::set (int idx, int value)
{
	arg.val = value;
	semctl (id, idx, SETVAL, arg);

	LOG4CXX_DEBUG(logger,
		"set semaphore set:" << id 
		<< " index:" << idx
	       	<< " value:" << value);
}

void Semaphore::wait (int idx, int value)
{
	if (value < 0)
		throw std::invalid_argument ("Semaphore::wait: value must be positive.");

	struct sembuf ops;

	ops.sem_num = idx;
	ops.sem_op = -value;
	ops.sem_flg = 0;
	
	bool retry;
	do {
		LOG4CXX_DEBUG(logger,
			"wait semaphore set:" << id
		       	<< " index:" << idx
			<< " value:" << value);

		retry = false;

		int ret = semop (id, &ops, 1);
		if (ret == -1)
			if (errno == EINTR)
			{
				LOG4CXX_DEBUG(logger, "wait interrupted.");
				retry = true;
			} else
				throw SystemErrorException ();
	} while (retry);
}

void Semaphore::signal (int idx, int value)
{
	if (value < 0)
		throw std::invalid_argument ("Semaphore::signal: value must be positive.");

	LOG4CXX_DEBUG(logger,
		"signal semaphore set:" << id
	       	<< " index:" << idx
	       	<< " value:" << value);

	struct sembuf ops;

	ops.sem_num = idx;
	ops.sem_op = value;
	ops.sem_flg = 0;
	System::check (semop (id, &ops, 1));
}
