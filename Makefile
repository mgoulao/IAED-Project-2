TARGET = Proj2
SOURCES = main.c task.c hashTable.c linkedList.c
OBJS = $(SOURCES:%.c=%.o)
HEADERS = task.h linkedList.h hashTable.h
CC = gcc
FLAGS = -Wall -pedantic -ansi
all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(FLAGS) $^ -o $(TARGET)
main.o: main.c $(HEADERS)
task.o: task.c $(HEADERS)
linkedList.o: linkedList.c $(HEADERS)
hashTable.o: hashTable.c $(HEADERS)

$(OBJS):
	$(CC) $(FLAGS) -c -o $@ $<

clean:
	@echo Cleaning.....
	rm -f $(TARGET) $(OBJS)