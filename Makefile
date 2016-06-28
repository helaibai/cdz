Target=sproxy.exe

CC = gcc
STRIP=strip
CFLAGS += -g -Wall
CFLAGS += -I./include
LDLIBEVENT+= -levent -levent_core -levent_extra
LDFLAGS += -L./libs $(LDLIBEVENT)

OBJS = main.o util.o timer.o 

all: $(Target)

$(Target):$(OBJS)
	$(CC) -o $(Target) $(LDFLAGS) $(OBJS)
	$(STRIP) $(Target) 
%.o:%.c
	$(CC) $(CFLAGS) -c $< -o $@
clean:
	rm -rf $(OBJS) $(Target) &> /dev/null
