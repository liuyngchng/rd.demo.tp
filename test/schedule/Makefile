CC = gcc
CFLAGS = -g
LFLAGS = 
OBJS = scheduler.o
all : _scheduler
_scheduler : $(OBJS)
	$(CC) $^ -o $@ $(LFLAGS)
	
%*.o:%*.c
	$(CC) $(CFLAGS) $< -o $@

.PHNOY: clean
clean:
	rm -f *.o _scheduler

