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
#define EUSB_SEND_PERIOD  200 



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

unsigned char USB_GET[64];

const uint8_t  usb_poll[] = {0x55,0xAA,0x5A,0xA5,0x00};

const uint8_t  usb_t[] = {0xfc,0xd5,0x18,0x00,0x00};
hid_device *handle;

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
    int ret = 0;
    int i = 0;
    
    hid_set_nonblocking(handle,0);

    memset(USB_GET,0,sizeof(USB_GET));
    
    while (1){
        //osal_sleep(1000);

    //printf("eg_usbto322_thread_entry \n");

       ret =  hid_read(handle,USB_GET,sizeof(USB_GET));

        if(ret){

            printf("get data from 322 len is %d:\n",ret); 
            for(i = 0;i < ret;i++){

                if(i%8 == 0) 
                    printf("\n");

                printf("%02X ",USB_GET[i]);

            }
            printf("\n");
            
            eg_usb_main_proc(USB_GET,ret);

        }
        else{

            printf("get 0 length data!\n");
        }
    }
}

uint8_t usb_wb;
void timer_usb_callback(void)
{
    int i;
   usb_wb =  hid_write(handle,usb_t,sizeof(usb_poll));

   if(usb_wb != sizeof(usb_poll)) {

        printf("write poll  failed!\n");
   }
/*
   for(i = 0;i < sizeof(usb_poll);i++){

        printf("%X ",usb_poll[i]);
   }
*/
   printf("\n\r");

}


void eg_usbto322_init()
{

    osal_task_t *tid;

    osal_timer_t *timer_usb;

    // Enumerate and print the HID devices on the system
    struct hid_device_info *devs, *cur_dev;

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
    
    eg_write_to_322(handle,usb_t,sizeof(usb_t));

    memset(USB_GET,0,sizeof(USB_GET));

    hid_get_feature_report(handle,USB_GET,64);

    int j;

    for(j = 0;j < 64;j++){
        printf("%X ",USB_GET[j]);

    }
    printf("\n");

    tid = osal_task_create("tk_usb322",
                        eg_usbto322_thread_entry,
                        NULL,RT_SYS_THREAD_STACK_SIZE, RT_SYS_THREAD_PRIORITY);

    osal_assert(tid != NULL)

    
    timer_usb = osal_timer_create("tm-usb",timer_usb_callback,NULL,\
                        EUSB_SEND_PERIOD, TIMER_INTERVAL|TIMER_STOPPED, TIMER_PRIO_NORMAL);
    osal_assert(timer_usb != NULL);
    
    //osal_timer_start(timer_usb);

}
