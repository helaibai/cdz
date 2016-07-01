Target=sproxy.exe

CC = gcc
STRIP=strip
OS=$(shell uname)
MACHINE=$(shell uname -m)
CFLAGS += -g -Wall
CFLAGS += -I./include
LDLIBEVENT= -levent -levent_core -levent_extra
LIBEVENT=./libs/$(OS)/$(MACHINE) $(LDLIBEVENT) 
LDFLAGS += -L$(LIBEVENT) 
OBJS = main.o util.o timer.o gprs_module.o 

all: $(Target)

$(Target):$(OBJS)
	$(CC) -o $(Target) $(OBJS) $(LDFLAGS) 
	$(STRIP) $(Target) 
%.o:%.c
	$(CC) $(CFLAGS) -c $< -o $@
clean:
	rm -rf $(OBJS) $(Target) &> /dev/null
