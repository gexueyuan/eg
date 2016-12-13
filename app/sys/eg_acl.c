/*****************************************************************************
 Copyright(C) Tendyron Corporation
 All rights reserved.
 
 @file   : eg_acl.c
 @brief  : acl list process
 @author : gexueyuan
 @history:
           2016-12-11    gexueyuan    Created file
           ...
******************************************************************************/
#include "cv_cms_def.h"
#include <queue_msg.h>



/*****************************************************************************
 * declaration of variables and functions                                    *
*****************************************************************************/


/*****************************************************************************
 * implementation of functions                                               *
*****************************************************************************/
void acl_main_proc(sys_msg_t *p_msg)
{





}



void * acl_thread_entry (void *parameter)
{





}






void acl_proc_init(void)
{

    osal_task_t *tid;



    tid = osal_task_create("tk_acl",
                        acl_thread_entry,
                        NULL,RT_SYS_THREAD_STACK_SIZE, RT_SYS_THREAD_PRIORITY);

    osal_assert(tid != NULL)



}
