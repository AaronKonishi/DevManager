
all: main lsusb

main: main.o
	gcc main.o -o main

main.o: main.c
	gcc main.c -c -o main.o

INC += -I../port/libusb_build/include/
LIB += -L../port/libusb_build/lib/ -lusb-1.0

lsusb: lsusb.o
	gcc lsusb.o $(INC) $(LIB) -o lsusb 

lsusb.o: lsusb.c
	gcc lsusb.c $(INC) $(LIB) -c -o lsusb.o
