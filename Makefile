program_NAME := map
program_C_SRCS := $(wildcard *.c)
program_CXX_SRCS := $(wildcard *.cpp)
program_C_OBJS := ${program_C_SRCS:.c=.o}
program_CXX_OBJS := ${program_CXX_SRCS:.cpp=.o}
program_OBJS := $(program_C_OBJS) $(program_CXX_OBJS)
program_INCLUDE_DIRS := /usr/local/include
program_LIBRARY_DIRS := /usr/local/lib /usr/local/bin
program_LIBRARIES := sfml-graphics sfml-window sfml-system

CC = g++

CPPFLAGS += $(foreach includedir,$(program_INCLUDE_DIRS),-I$(includedir))
LDFLAGS += $(foreach librarydir,$(program_LIBRARY_DIRS),-L$(librarydir))
LDFLAGS += $(foreach library,$(program_LIBRARIES),-l$(library))
#LDFLAGS += -static-libstdc++ -static-libgcc -static -lpthread

.PHONY: all debug release clean distclean

debug: CPPFLAGS += -g -DDEBUG
debug: all

release: all

all: $(program_NAME)

$(program_NAME): $(program_OBJS)
	$(CC) -o $(program_NAME) $(program_OBJS) $(CPPFLAGS) $(LDFLAGS) $(TARGET_ARCH)

clean:
	@- $(RM) $(program_NAME)
	@- $(RM) $(program_OBJS)

distclean: clean

cleanobjs:
	@- $(RM) $(program_OBJS)