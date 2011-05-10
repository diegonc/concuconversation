#ifndef SHAREDVARIABLE_H
#define SHAREDVARIABLE_H

#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>

#include <utils/NonCopyable.h>

#include <system/IPCName.h>
#include <system/System.h>

template <typename T>
class SharedVariable : private NonCopyable
{
	private:
		int id;
		T *ptr;

	public:
		SharedVariable (IPCName name, int flags);
		~SharedVariable ();

				void set (T t) { *ptr = t; }
				const T& get () { return *ptr; }

};

template <typename T>
SharedVariable<T>::SharedVariable (IPCName name, int flags)
{
	key_t token = ftok (name.path, name.index);
	System::check (token);

	id = shmget (token, sizeof(T), flags);
	System::check (id);

	ptr = static_cast<T *>(shmat (id, NULL, 0));
	if (ptr == (T *)-1) {
		int err = errno;
		shmctl (id, IPC_RMID, NULL);
		throw SystemErrorException (err);
	}
}

template <typename T>
SharedVariable<T>::~SharedVariable ()
{
	shmdt (ptr);
	shmctl (id, IPC_RMID, NULL);
}

#endif

