Target=sproxy.exe

CC = gcc
STRIP=strip
OS=$(shell uname)
MACHINE=$(shell uname -m)
CFLAGS += -g -Wall
CFLAGS += -I./include
LIBROOT=./libs/$(OS)/$(MACHINE)
LDLIBEVENT= -levent -levent_core -levent_extra
LIBEVENT=-L$(LIBROOT) $(LDLIBEVENT) 
LDFLAGS += $(LIBEVENT) -llog4c -lrt -lpthread 
OBJS = main.o util.o timer.o gprs.o cdz_socket.o cfg.o uart.o frame.o 

all: $(Target)

$(Target):$(OBJS)
	$(CC) -o $(Target) $(OBJS) $(LDFLAGS) 
	$(STRIP) $(Target) 
%.o:%.c
	$(CC) $(CFLAGS) -c $< -o $@
clean:
	rm -rf $(OBJS) $(Target) &> /dev/null
