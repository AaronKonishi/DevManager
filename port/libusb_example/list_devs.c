#include <stdio.h>

#include "libusb.h"

static void print_devs(libusb_device **devs)
{
    int ret = -1;
    uint8_t path[8];
    int i = 0, j = 0;
    libusb_device *dev = NULL;

    while((dev = devs[i++]) != NULL)
    {
        struct libusb_device_descriptor desc;
        ret = libusb_get_device_descriptor(dev, &desc);
        if(ret < 0)
        {
            fprintf(stderr, "failed to get device descriptor!\n");
            return ;
        }

        printf("%04x:%04x (bus %d, device %d, port %d)",
            desc.idVendor, desc.idProduct,
            libusb_get_bus_number(dev),
            libusb_get_device_address(dev),
            libusb_get_port_number(dev));

        ret = libusb_get_port_numbers(dev, path, sizeof(path));
        if(ret > 0)
        {
            printf("  path:%d",path[0]);
            for(j = 1; j < ret; j++)
                printf("%d",path[j]);
        }
        printf("\n");
    }
}

int main(void)
{
    int ret = -1;
    ssize_t cnt = 0;
    libusb_device **devs = NULL;
    
    ret = libusb_init(NULL);
    if(ret < 0)
    {
        printf("Error: libusb_init failed!\n");
        return -1;
    }

    libusb_set_debug(NULL,LIBUSB_LOG_LEVEL_WARNING);

    cnt = libusb_get_device_list(NULL, &devs);
    if(cnt < 0)
        return (int)cnt;
    printf("On this system there has %d USB Device.\n",cnt);

    print_devs(devs);
    libusb_free_device_list(devs, 1);

    libusb_exit(NULL);
    return 0;
}

