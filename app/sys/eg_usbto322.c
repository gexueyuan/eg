/*****************************************************************************
 Copyright(C) Tendyron Corporation
 All rights reserved.
 
 @file   : eg_usbto322.c
 @brief  : usbto322
 @author : gexueyuan
 @history:
           2016-12-9    gexueyuan    Created file
           ...
******************************************************************************/



/*****************************************************************************
 * declaration of variables and functions                                    *
*****************************************************************************/


/*****************************************************************************
 * implementation of functions                                               *
*****************************************************************************/




#include <stdio.h>
#include <stdlib.h>
#include "hidapi.h"

#include "cv_cms_def.h"


void usb_main_proc(sys_msg_t *p_msg)
{
    




}



/*****************************************************************************
 @funcname: eg_usbto322_thread_entry
 @brief   : thread function
 @param   : void *parameter  
 @return  : void
*****************************************************************************/
void *eg_usbto322_thread_entry(void *parameter)
{
    // Enumerate and print the HID devices on the system
    struct hid_device_info *devs, *cur_dev;

    devs = hid_enumerate(0x1780, 0x0312);
    cur_dev = devs; 
    //while (cur_dev) {
     printf("  Device Found\n  type: %04hx %04hx\n  path: %s\n  serial_number: %ls",
         cur_dev->vendor_id, cur_dev->product_id, cur_dev->path, cur_dev->serial_number);
     printf("\n");
     printf("  Manufacturer: %ls\n", cur_dev->manufacturer_string);
     printf("  Product:      %ls\n", cur_dev->product_string);
     printf("\n");
    // cur_dev = cur_dev->next;
    // }
    hid_free_enumeration(devs);
  

    while (1){
        osal_sleep(1000);

    printf("eg_usbto322_thread_entry \n");

        }
}




void usbto322_init()
{

    osal_task_t *tid;



    tid = osal_task_create("tk_usb322",
                        eg_usbto322_thread_entry,
                        NULL,RT_SYS_THREAD_STACK_SIZE, RT_SYS_THREAD_PRIORITY);

    osal_assert(tid != NULL)




}
