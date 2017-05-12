#include <stdio.h>
#include <unistd.h>
#include <libusb-1.0/libusb.h>

//First, use 'lsusb' commond see vid and pid
// there is my printer(hp deskjet 1010) vid and pid.
#define VID 0x03F0
#define PID 0xB511

static int device_status(libusb_device_handle *hd)
{
	int interface = 0;
	unsigned char byte;
	libusb_control_transfer(hd, LIBUSB_ENDPOINT_IN | LIBUSB_REQUEST_TYPE_CLASS | LIBUSB_RECIPIENT_INTERFACE, LIBUSB_REQUEST_CLEAR_FEATURE, 0, interface, &byte, 1, 5000);

	printf("Status: 0x%x\n",byte);
	/* byte: normal: 0x18; other: 0x10 */
	return 0;
}

int main(void)
{
	int ret; // for return values
	ssize_t cnt; // holding number of devices in list
	libusb_device **devs;  // retrieve a list of device
	libusb_device_handle *dev_handle;  // a device handle
	libusb_context *ctx = NULL; // a libusb session
	const struct libusb_version * version;

	ret = libusb_init(&ctx);
	if(ret < 0)
	{
		perror("Init error\n");
		return -1;
	}

	libusb_set_debug(ctx, LIBUSB_LOG_LEVEL_INFO);  // set verbosity level to 3, as suggested in the documentation

	version = libusb_get_version();
	printf("libusb version:%d.%d.%d.%d rc:%s:  %s\n",version->major, version->minor, version->micro, version->nano,
        version->rc, version->describe);

	cnt = libusb_get_device_list(ctx, &devs);  // get the list of devices
	if(cnt < 0)
	{
		perror("Get device error\n");
		return -1;
	}
	printf("%d Devices in list:\n",cnt);

	dev_handle = libusb_open_device_with_vid_pid(ctx, VID, PID); // these are vendorID and ProductID I found for my HP
	if(dev_handle == NULL)
	{
		libusb_exit(ctx); // needs to be called to end
		perror("Cannot open device\n");
		return -1;
	}

	printf("Device opened.\n");
	libusb_free_device_list(devs, 1);

	if(libusb_kernel_driver_active(dev_handle, 0) == 1) // find out if kernel driver is attached
	{
		printf("Kernel Driver Active\n");
		if(libusb_detach_kernel_driver(dev_handle, 0) == 0) // detach it
			printf("Kernel Driver Detached\n");
	}

	printf("libusb_kernel_driver_active\n");
	ret = libusb_claim_interface(dev_handle, 0); // claim interface 0(the first) of device
	if(ret < 0)
	{
		perror("Cannot Claim interface\n");
		return -1;
	}
	printf("Claimed interface\n");

	device_status(dev_handle);

	libusb_close(dev_handle); // close the device we opened
	libusb_exit(ctx); // needs to be called to end

	return 0;
}
