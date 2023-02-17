include ./Makefile.in
ifeq ($(findstring FreeBSD, $(UNIXNAME)), FreeBSD)
	EXTLIBS += -L/usr/local/lib -liconv
endif
CFLAGS += -I../../include
#CFLAGS += -std=c++11
#EXTLIBS += -L/usr/local/lib64 -lssl -lcrypto -Wl,-rpath,/usr/local/lib64
EXTLIBS += -L$(SSL_LIB) -lmbedtls_all -Wl,-rpath,$(SSL_LIB)
PROG = cert
