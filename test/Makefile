
all: main listdevs

main: main.o
	gcc main.o -o main

main.o: main.c
	gcc main.c -c -o main.o

INC += -I../port/libusb_build/include/
LIB += -L../port/libusb_build/lib/ -lusb-1.0

listdevs: listdevs.o
	gcc listdevs.o $(INC) $(LIB) -o listdevs

listdevs.o: listdevs.c
	gcc listdevs.c $(INC) $(LIB) -c -o listdevs.o
