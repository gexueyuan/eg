/*****************************************************************************
 Copyright(C) Tendyron Corporation
 All rights reserved.
 
 @file   : eg_acl_store.c
 @brief  : acl store thread,only once
 @author : gexueyuan
 @history:
           2016-12-11    gexueyuan    Created file
           ...
******************************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <unistd.h> 
#include <fcntl.h>
#include <queue_msg.h>
#include "cv_cms_def.h"

/*****************************************************************************
 * declaration of variables and functions                                    *
*****************************************************************************/
FILE *fd;


/*****************************************************************************
 * implementation of functions                                               *
*****************************************************************************/

    
    struct bin_tree {
        int data;
        struct bin_tree * right, * left;
    };
    typedef struct bin_tree node;

void insert(node ** tree, int val)
{
    node *temp = NULL;
    if(!(*tree))
    {
        temp = (node *)malloc(sizeof(node));
        temp->left = temp->right = NULL;
        temp->data = val;
        *tree = temp;
        return;
    }

    if(val < (*tree)->data)
    {
        insert(&(*tree)->left, val);
    }
    else if(val > (*tree)->data)
    {
        insert(&(*tree)->right, val);
    }

}

void print_preorder(node * tree)
{
    if (tree)
    {
        printf("%d\n",tree->data);
        print_preorder(tree->left);
        print_preorder(tree->right);
    }

}

void print_inorder(node * tree)
{
    if (tree)
    {
        print_inorder(tree->left);
        printf("%d\n",tree->data);
        print_inorder(tree->right);
    }
}

void print_postorder(node * tree)
{
    if (tree)
    {
        print_postorder(tree->left);
        print_postorder(tree->right);
        printf("%d\n",tree->data);
    }
}

void deltree(node * tree)
{
    if (tree)
    {
        deltree(tree->left);
        deltree(tree->right);
        free(tree);
    }
}

node* search(node ** tree, int val)
{
    if(!(*tree))
    {
        return NULL;
    }

    if(val < (*tree)->data)
    {
        search(&((*tree)->left), val);
    }
    else if(val > (*tree)->data)
    {
        search(&((*tree)->right), val);
    }
    else if(val == (*tree)->data)
    {
        return *tree;
    }
}
    
//    void main()
//    {
//        node *root;
//        node *tmp;
//        //int i;
//    
//        root = NULL;
//        /* Inserting nodes into tree */
//        insert(&root, 9);
//        insert(&root, 4);
//        insert(&root, 15);
//        insert(&root, 6);
//        insert(&root, 12);
//        insert(&root, 17);
//        insert(&root, 2);
//    
//        /* Printing nodes of tree */
//        printf("Pre Order Display\n");
//        print_preorder(root);
//    
//        printf("In Order Display\n");
//        print_inorder(root);
//    
//        printf("Post Order Display\n");
//        print_postorder(root);
//    
//        /* Search node into tree */
//        tmp = search(&root, 4);
//        if (tmp)
//        {
//            printf("Searched node=%d\n", tmp->data);
//        }
//        else
//        {
//            printf("Data Not found in tree.\n");
//        }
//    
//        /* Deleting all nodes of tree */
//        deltree(root);
//    }

typedef struct _acl_op {
    ACL_SAVE = 0,
    ACL_SEARCH,
    ACL_DEL,
    ACL_LOCK,
    ACL_UNLOCK,
        
} acl_op_t;




void acl_local_main_proc(sys_msg_t *p_msg)
{





}



void * acl_local_thread_entry (void *parameter)
{
    int err;

    fd = fopen("acl.list","wr");

    if(fd < 0){

        printf("Fail to open acl file!\n");
    
        exit(1);

    } 

/*
    while(1){

        err = osal_queue_recv(p_vam->queue_vam, buf, &len, OSAL_WAITING_FOREVER);
        if (err == OSAL_STATUS_SUCCESS && len > 0){
            acl_local_main_proc(p_msg);           
        }
        else{
            OSAL_MODULE_DBGPRT(MODULE_NAME, OSAL_DEBUG_ERROR, "%s: osal_queue_recv error [%d]\n",\
                            __FUNCTION__, err);
        }



    }
*/


}






void acl_local_init(void)
{

    osal_task_t *tid;



    tid = osal_task_create("tk_acl_local",
                        acl_local_thread_entry,
                        NULL,RT_SYS_THREAD_STACK_SIZE, RT_SYS_THREAD_PRIORITY);

    osal_assert(tid != NULL)



}





