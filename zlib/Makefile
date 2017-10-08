SHELL = /bin/sh
CC      = gcc
CC	= ${ENV_CC}
AR      = ${ENV_AR}
ARFL    = rv
#ARFL    = cru
RANLIB  = ${ENV_RANLIB}

FLAGS   = ${ENV_FLAGS}

# default lib name
LIB_NAME  = libacl.a

#-fno-strict-aliasing \
#CFLAGS = -c -g -W -Wall -Wcast-qual -Wcast-align

CFLAGS = -c -g -W \
-O3 \
-fPIC \
-Wall \
-Werror \
-Wshadow \
-Wpointer-arith \
-D_REENTRANT \
-D_USE_FAST_MACRO \
-DACL_WRITEABLE_CHECK \
-Wno-long-long \
-Wuninitialized \
-D_POSIX_PTHREAD_SEMANTICS \
-DACL_PREPARE_COMPILE \
-Winvalid-pch \
#-fstack-protector-all \
#-DDEBUG_MEM
#-DUSE_EPOLL \
#-Wno-tautological-compare \
#-Wno-invalid-source-encoding \
#-Wno-extended-offsetof
#-Wcast-align
#-Winvalid-pch -DACL_PREPARE_COMPILE

###########################################################
#Check system:
#       Linux, SunOS, Solaris, BSD variants, AIX, HP-UX
SYSLIB = -lpthread
CHECKSYSRES = @echo "Unknow system type!";exit 1
#UNIXNAME = $(shell uname -sm)
UNIXNAME = $(shell uname -s)
UNIXTYPE = LINUX
#OSTYPE = $(shell uname -p)
OSTYPE = $(shell uname -m)
RPATH =

ifeq ($(CC),)
        CC = gcc
endif

ifeq ($(AR),)
	AR = ar
endif

ifeq ($(RANLIB),)
	RANLIB = ranlib
endif

ifeq ($(findstring gcc, $(CC)), gcc)
	CFLAGS += -Wstrict-prototypes
	GCC_VERSION=$(shell gcc --version | grep ^gcc | sed 's/^.* //g')
	GCC_MAJOR:=$(shell echo "$(GCC_VERSION)" | cut -d'.' -f1)
	GCC_MINOR:=$(shell echo "$(GCC_VERSION)" | cut -d'.' -f2)
	GCC_SUB:=$(shell echo "$(GCC_VERSION)" | cut -d'.' -f3)
	GCC_VER:=$(shell [ $(GCC_MAJOR) -gt 4 -o \( $(GCC_MAJOR) -eq 4 -a $(GCC_MINOR) -gt 4 \) ] && echo true)
	ifeq ($(GCC_VER), true)
		CFLAGS += -Wno-implicit-fallthrough
	endif
endif

ifeq ($(findstring clang, $(CC)), clang)
	CFLAGS += -Wstrict-prototypes \
		  -Wno-invalid-source-encoding \
		  -Wno-extended-offsetof
endif

ifeq ($(findstring clang++, $(CC)), clang)
	CFLAGS += -Wno-invalid-source-encoding \
		  -Wno-extended-offsetof
endif

# For FreeBSD
ifeq ($(findstring FreeBSD, $(UNIXNAME)), FreeBSD)
	UNIXTYPE = FREEBSD
	RPATH = freebsd
endif

# For Darwin
ifeq ($(findstring Darwin, $(UNIXNAME)), Darwin)
	CFLAGS += -Wno-invalid-source-encoding \
		  -Wno-extended-offsetof
	UNIXTYPE = MACOSX
	RPATH = macos
endif

# For Linux
ifeq ($(findstring Linux, $(UNIXNAME)), Linux)
	UNIXTYPE = LINUX
	ifeq ($(findstring i686, $(OSTYPE)), i686)
		CFLAGS += -march=i686
		RPATH = linux32
	endif
	ifeq ($(findstring x86_64, $(OSTYPE)), x86_64)
#		CFLAGS += -m64
		RPATH = linux64
	endif
endif

ifeq ($(findstring HAS_TRACE, $(FLAGS)), HAS_TRACE)
	CFLAGS += -DHAS_TRACE
endif

EXECINFO_H = /usr/include/execinfo.h
EXECINFO_H_EXIST = $(shell if [ -f $(EXECINFO_H) ]; \
		   then echo "exist"; else echo "notexist"; fi;)

ifeq ($(findstring exist, $(EXECINFO_H_EXIST)), exist)
	CFLAGS += -DHAS_EXECINFO_HEAD
endif

# For MINGW
ifeq ($(findstring MINGW, $(UNIXNAME)), MINGW)
	CFLAGS += -DLINUX2 -DMINGW
	UNIXTYPE = LINUX
	SYSLIB = -lpthread-2
	RPATH = mingw
endif

# For MSYS
ifeq ($(findstring MSYS, $(UNIXNAME)), MSYS)
	CFLAGS += -DLINUX2 -DMINGW
	UNIXTYPE = LINUX
	SYSLIB = -lpthread-2
	RPATH = mingw
endif

# For SunOS
ifeq ($(findstring SunOS, $(UNIXNAME)), SunOS)
	ifeq ($(findstring 86, $(OSTYPE)), 86)
		SYSLIB += -lsocket -lnsl -lrt
	endif
	ifeq ($(findstring sun4u, $(OSTYPE)), sun4u)
		SYSLIB += -lsocket -lnsl -lrt
	endif
	CFLAGS += -DSUNOS5 -fPIC -Werror
	UNIXTYPE = SUNOS5
	RPATH = sunos5_x86
endif

# For HP-UX
ifeq ($(findstring HP-UX, $(UNIXNAME)), HP-UX)
	CFLAGS += -DHP_UX -DHPUX11 -fPIC -Werror
	UNIXTYPE = HPUX
	RPATH = hpux
endif

#CCARGS =
#ifeq ($(findstring HAS_MYSQL, $(CCARGS)), HAS_MYSQL)
#        CFLAGS += -DHAS_MYSQL
#	LIB_NAME = lib_acl.a
#endif

#CFLAGS += -DHAS_MYSQL

#Find system type.
ifneq ($(SYSPATH),)
	CHECKSYSRES = @echo "System is $(shell uname -sm)"
endif
###########################################################

OUT_PATH = .
OBJ_PATH_DST = $(OUT_PATH)/debug
LIB_PATH_DST = $(OUT_PATH)

CFLAGS += -I. -I./include

$(shell mkdir -p $(OBJ_PATH_DST))

###########################################################

#Project's objs
SRC     = $(wildcard src/*.c)
OBJ     = $(patsubst %.c, $(OBJ_PATH_DST)/%.o, $(notdir $(SRC)))
OBJS    = $(OBJ)

###########################################################
.PHONY = all static shared clean cl clean_lib rebuild rb

STATIC_LIBNAME = libz.a

all: static

ifneq ($(MAKECMDGOALS),clean)
-include $(OBJS_DEF)
endif

clean cl:
	rm -f $(OBJS)
	rm -f $(STATIC_LIBNAME)

rebuild rb: clean all

PCH = StdAfx.h.gch

###########################################################

COMPILE = $(CC) $(CFLAGS)
COMPILE_OBJ = @(echo 'building $<'; $(COMPILE) $< -o $@)
CREATE_DEF = @(echo 'creating $@'; rm -f $@; \
	$(COMPILE) -MM $< > $@.$$$$; \
	sed 's,.*.o\( \)*:,$(patsubst %.inc,%.o,$@) $@ :,g' < $@.$$$$ > $@; \
	rm -f $@.$$$$)

static: $(OBJS)
	@echo 'creating $(LIB_PATH_DST)/$(STATIC_LIBNAME)'
	@$(AR) $(ARFL) $(LIB_PATH_DST)/$(STATIC_LIBNAME) $(OBJS)
	@$(RANLIB) $(LIB_PATH_DST)/$(STATIC_LIBNAME)
	@echo 'build $(LIB_PATH_DST)/$(STATIC_LIBNAME) ok!'

###########################################################

$(OBJ_PATH_DST)/%.o: ./src/%.c
	$(COMPILE_OBJ)
