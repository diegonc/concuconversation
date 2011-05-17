#ifndef SHAREDVARIABLE_H
#define SHAREDVARIABLE_H

#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>

#include <log4cxx/logger.h>

#include <system/IPCName.h>
#include <system/System.h>
#include <utils/NonCopyable.h>

template <typename T>
class SharedVariable : private NonCopyable
{
	private:
		static log4cxx::LoggerPtr logger;

		int id;
		T *ptr;

	public:
		SharedVariable (IPCName name, int flags);
		~SharedVariable ();

				void set (const T& t) { *ptr = t; }
				T& get () { return *ptr; }

};

template <typename T>
log4cxx::LoggerPtr SharedVariable<T>::logger (
	log4cxx::Logger::getLogger ("SharedVariable"));

template <typename T>
SharedVariable<T>::SharedVariable (IPCName name, int flags)
{
	LOG4CXX_DEBUG(logger, "Creating SharedVariable from ["
		<< name.path << "] [" << name.index << "]");

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
