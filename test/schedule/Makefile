CC = gcc
CFLAGS = -g
LFLAGS = 
OBJS = scheduler.o
all : scheduler
scheduler : $(OBJS)
	$(CC) $^ -o $@ $(LFLAGS)
	
%*.o:%*.c
	$(CC) $(CFLAGS) $< -o $@

.PHNOY: clean
clean:
	rm *.o scheduler

