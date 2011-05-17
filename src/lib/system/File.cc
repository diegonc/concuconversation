#include <system/File.h>
#include <string.h>
#include <system/System.h>

log4cxx::LoggerPtr File::logger (log4cxx::Logger::getLogger ("File"));

File::File (const std::string &path, int flags)
{
	inicializar (path.c_str(), flags);
}

File::File (const char *path, int flags)
{
	inicializar (path, flags);
}

void File::inicializar (const char *path, int flags)
{
	LOG4CXX_DEBUG(logger,"Creando un pipe " << path );
	strcpy ( this->nombre,nombre );
		// se crea el fifo
	int result= mknod ( nombre,S_IFIFO|0666,0 );
		// se inicializa el descriptor en -1
	System::check(result);
	fd = open (path, flags);
	/* TODO: errores */
}

File::~File()
{
	if (fd != -1)
		close (fd);
	unlink(this->nombre);
}

int File::write (size_t n, const char *data)
{
	return ::write (fd, data, n);	
}

int File::read (size_t n, char *data)
{
	return ::read (fd, data, n);	
}
