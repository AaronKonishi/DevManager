
OBJS += list_devs
OBJS += libusb_version

LIB = -L../libusb_build/lib/ -lusb-1.0
INC = -I../libusb_build/include/libusb-1.0/

all: $(OBJS)

libusb_version: libusb_version.o
	gcc libusb_version.o $(INC) $(LIB) -o libusb_version
libusb_version.o: libusb_version.c
	gcc libusb_version.c -c $(INC) -o libusb_version.o

list_devs: list_devs.o
	gcc list_devs.o $(INC) $(LIB) -o list_devs
list_devs.o: list_devs.c
	gcc list_devs.c -c $(INC) -o list_devs.o
