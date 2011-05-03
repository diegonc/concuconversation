#ifndef SEMAPHORE_H
#define SEMAPHORE_H

#include <sys/ipc.h>
#include <sys/types.h>
#include <sys/sem.h>

#include <system/IPCName.h>

class Semaphore
{
	protected:
		int id;
		const int nsems;

	public:
		Semaphore (key_t key, int nsems, int flags);
		Semaphore (IPCName name, int nsems, int flags);
		virtual ~Semaphore ();

		void set (int idx, int value);
		void wait (int idx = 0, int value = 1);
		void signal (int idx = 0, int value = 1);
};

#endif
