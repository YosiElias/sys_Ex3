CC = gcc
CFLAGS = -Wall -g
AR=ar
OBJECTS_MAIN=main.o
OBJECT = advancedClassificationLoop.o basicClassification.o 
C2COMPILE = main.c
#make all
all: stringProg 

#make stringProg:
main.o: $(C2COMPILE) 
	$(CC) $(CFLAGS) -c $(C2COMPILE) -o main.o
stringProg: main.o
	$(CC) $(CFLAGS) -o stringProg main.o



.PHONY: clean all

clean:
	rm -f *.o *.a *.so stringProg