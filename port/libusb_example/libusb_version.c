#include <stdio.h>

#include "libusb.h"

int main(void)
{
    int ret = -1;
    const struct libusb_version *libusb_v = NULL;
    
    ret = libusb_init(NULL);

    libusb_v = libusb_get_version();
    printf("libusb version : V%d.%d.%d.%d\n",libusb_v->major,libusb_v->minor,
                                             libusb_v->micro,libusb_v->nano);

    libusb_exit(NULL);

    return 0;
}

