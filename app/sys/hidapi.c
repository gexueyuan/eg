#ifdef WIN32
#include <windows.h>
#endif
#include <stdio.h>
#include <stdlib.h>
#include "hidapi.h"

#define MAX_STR 255


int hidapi_v(){

    printf("test");


}

int hidapi_test(void)
{

    int res;
        unsigned char buf[65];
	#define MAX_STR 255
        wchar_t wstr[MAX_STR];
        hid_device *handle;
        int i;
    
        // Enumerate and print the HID devices on the system
        struct hid_device_info *devs, *cur_dev;
        
        devs = hid_enumerate(0x0, 0x0);
        cur_dev = devs; 
        while (cur_dev) {
            printf("Device Found\n  type: %04hx %04hx\n  path: %s\n  serial_number: %ls",
                cur_dev->vendor_id, cur_dev->product_id, cur_dev->path, cur_dev->serial_number);
            printf("\n");
            printf("  Manufacturer: %ls\n", cur_dev->manufacturer_string);
            printf("  Product:      %ls\n", cur_dev->product_string);
            printf("\n");
            cur_dev = cur_dev->next;
        }
        hid_free_enumeration(devs);


    handle = hid_open(0x1780, 0x0312, NULL);
    if(handle == NULL)
        printf("none handle\n");
    else printf("report number is %d,%d,%d\n",handle->device_handle,handle->blocking,handle->uses_numbered_reports);
	// Read the Manufacturer String
	res = hid_get_manufacturer_string(handle, wstr, MAX_STR);
	printf("Manufacturer String: %s\n", wstr);

	// Read the Product String
	res = hid_get_product_string(handle, wstr, MAX_STR);
	printf("Product String: %s\n", wstr);

	// Read the Serial Number String
	res = hid_get_serial_number_string(handle, wstr, MAX_STR);
	printf("Serial Number String: (%d) %s\n", wstr[0], wstr);

	// Read Indexed String 1
	res = hid_get_indexed_string(handle, 1, wstr, MAX_STR);
	printf("Indexed String 1: %s\n", wstr);

    hid_close(handle);

	return 0;
}
