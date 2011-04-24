AUTOMAKE_OPTIONS = subdir-objects

AM_CPPFLAGS = -I$(srcdir)/lib

libSources = \
	lib/System.cc \
	lib/File.h \
	lib/FifoOutputStream.h \
	lib/FifoOutputStream.cc \
	lib/System.h \
	lib/Salon.h \
	lib/FileExistsException.h 

clienteSources = \
	src/cliente/SalonRemoto.cc \
	src/cliente/SalonRemoto.h

salonSources = 

bin_PROGRAMS = cliente/cliente salon/salon

cliente_cliente_SOURCES = $(clienteSources) $(libSources)
salon_salon_SOURCES = $(salonSources) $(libSources)
