#ifndef SEMAPHORE_H
#define SEMAPHORE_H

#include <sys/types.h>

#include <system/IPCName.h>

class Semaphore
{
	private:
		int id;

		void initialize (key_t, int, int);

	public:
		Semaphore (key_t key, int nsems);
		Semaphore (IPCName name, int nsems);

		void set (int idx, int value);
		void wait (int idx, int value = 1);
		void signal (int idx, int value = 1);
};

#endif
