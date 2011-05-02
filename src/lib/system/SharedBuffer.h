#ifndef SHAREDBUFFER_H
#define SHAREDBUFFER_H

#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>

#include <utils/NonCopyable.h>

#include <system/IPCName.h>

class SharedBuffer : private NonCopyable
{
	private:
		int id;
		char *ptr;

	public:
		SharedBuffer (IPCName name, size_t size);
		~SharedBuffer ();

		char &operator[] (const int subscript)
		{
			return ptr[subscript];
		}
};

#endif
