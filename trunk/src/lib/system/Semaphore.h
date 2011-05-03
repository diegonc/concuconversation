#ifndef SEMAPHORE_H
#define SEMAPHORE_H

#include <sys/types.h>

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
		void wait (int idx, int value = 1);
		void signal (int idx, int value = 1);
};

#endif
