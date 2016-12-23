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


#define USB_FAILED    0x6E00
#define USB_OK        0x9000 


typedef enum _USB_CMD {
    USB_CMD_CON = 0,
    USB_CMD_DATA,        
    USB_CMD_CHK,   
    USB_CMD_DIS,
    USB_CMD_ACL,
    USB_CMD_LOG,
} E_USB_CMD;


char USB_CMD[][4] = {

                        {0x00,0x10,0x00,0x00},
                        {0x00,0x10,0x01,0x00},
                        {0x00,0x10,0x02,0x00},
                        {0x00,0x10,0x03,0x00},
                        {0x00,0x20,0x00,0x00},
                        {0x00,0x30,0x00,0x00},
                            
};

char USB_GET[64];


//first element in data is 0
int eg_write_to_322(hid_device * dev,const unsigned char * data,int length)
{

    return hid_write(dev,data,length);


}

void eg_usb_main_proc(char *data,int len)
{

    int msg;
    
    if(len >= 4){

        if(data[1] == 0x10){

            msg = data[2];
                
        }else if(data[1] == 0x20){
            msg =  USB_CMD_ACL;   

        }else if(data[1] == 0x30){

            msg = USB_CMD_LOG;

        }
        

    }else{


        printf("data length form usb is not enough\n");



    }
    
switch (msg) {
    
    case USB_CMD_CON: 
        
        
        break;


    case USB_CMD_DATA:
        
        break;

    case USB_CMD_CHK:
        
        break;

    case USB_CMD_DIS:
        
        break;
        
    case USB_CMD_ACL:
        
        break;
        
    case USB_CMD_LOG:
        
        break;
    default:
        break;
}


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
    
    hid_device *handle;

    int ret = 0;

    int i = 0;


    devs = hid_enumerate(0, 0);
    cur_dev = devs; 
    while (cur_dev) {
     printf("  Device Found\n  type: %04hx %04hx\n  path: %s\n  serial_number: %ls",
         cur_dev->vendor_id, cur_dev->product_id, cur_dev->path, cur_dev->serial_number);
     printf("\n");
     printf("  Manufacturer: %ls\n", cur_dev->manufacturer_string);
     printf("  Product:      %ls\n", cur_dev->product_string);
     printf("\n");
     cur_dev = cur_dev->next;
     }
    hid_free_enumeration(devs);

    // Open the device using the VID, PID,
	// and optionally the Serial number.

    do{
        
    	handle = hid_open(0x1780, 0x0312, NULL);

        if(handle == NULL){

            printf("can not find 322!\n");
            osal_sleep(2000);

        }
        else {

            
            printf("open 322 success!\n");

        }
    } while(handle == NULL);


    hid_set_nonblocking(handle,0);

    memset(USB_GET,0,sizeof(USB_GET));
    
    while (1){
        //osal_sleep(1000);

    //printf("eg_usbto322_thread_entry \n");

       ret =  hid_read(handle,USB_GET,sizeof(USB_GET));

        if(ret){

            for(;i < ret;i++){

                printf("get data from 322 is %02X ");

            }
            printf("\n");
            
            eg_usb_main_proc(USB_GET,ret);

        }
        else{

            printf("get 0 length data!\n");
        }
    }
}




void eg_usbto322_init()
{

    osal_task_t *tid;



    tid = osal_task_create("tk_usb322",
                        eg_usbto322_thread_entry,
                        NULL,RT_SYS_THREAD_STACK_SIZE, RT_SYS_THREAD_PRIORITY);

    osal_assert(tid != NULL)




}
