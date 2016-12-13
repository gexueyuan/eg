/*****************************************************************************
 Copyright(C) Tendyron Corporation
 All rights reserved.
 
 @file   : eg_tcp.c
 @brief  : tcp lclient
 @author : gexueyuan
 @history:
           2016-12-11    gexueyuan    Created file
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
#include <unistd.h>  
#include <string.h>  
#include <sys/types.h>  
#include <sys/socket.h>  
#include <netinet/in.h>  
#include <netdb.h>  
#include "cv_cms_def.h"
#include <time.h>

#define  USE_STR

#define    PORT 8020  
#define    MAXDATASIZE 100000
#define    SERVERADDR  "172.16.32.152"

#define    CONNECT_STR "01010101010006AABBCCDDEEFF0300E704"
#define    CONNECT_ACK_STR  "01010101010001000300E704"

#define    HBM_REC  "010101010500000300E704"
#define    HBM_SEND "0101010105001BAABBCCDDEEFF0300E704" 



int  sockfd;  
char  buf[MAXDATASIZE];  


char connect_array[] = {0x01,0x01,0x01,0x01,0x01,0x06,0x01,0xAA,0xBB,0xCC,0xDD,0xEE,0xFF,0x03,0x00,0xE7,0x04};

#ifdef USE_STR

    #define  MSG_HEAD "01010101"
    #define  ACL_DL "4B"
    
#else

    char MSG_HEAD[4]={0x01,0x01,0x01,0x01};

    #define    ACL_DL   0x4B

    
#endif



int print_time()
{

    time_t now;    //实例化time_t结构
    struct tm  *timenow;    //实例化tm结构指针

    time(&now);//time函数读取现在的时间(国际标准时间非北京时间)，然后传值给now
    timenow = localtime(&now);//localtime函数把从time取得的时间now换算成你电脑中的时间(就是你设置的地区)
    printf("Local time is %s\n",asctime(timenow));//asctime函数把时间转换成字符，通过printf()函数输出

    return 0;




}


int eg_tcp_send(char *data,int len)
{


    if( send(sockfd, data, len, 0) < 0){
        
        printf("send msg error: %s(errno: %d)\n", strerror(errno), errno);
        return -1;
        
    }else{

        printf("send msg is %s,len is %d\n",data,len);
    }

    return 1;


}

void eg_tcp_main_proc()
{





}

int eg_tcp_client(void)  
{  
    int  sockfd, num;  
    char  buf[MAXDATASIZE];  
    struct hostent *he;  
 
  //创建套接字
    if((sockfd=socket(AF_INET, SOCK_STREAM, 0)) < 0){  
        printf("socket()error\n");  
        exit(1);  
    }  

    //指定server地址    
    struct sockaddr_in server;  
    bzero(&server,sizeof(server));  
    server.sin_family= AF_INET;  
    server.sin_port = htons(PORT);  
    if( inet_pton(AF_INET, SERVERADDR, &server.sin_addr) <= 0){
        printf("inet_pton error for %s\n",SERVERADDR);
        exit(0);
    }

    //发起连接操作
    if(connect(sockfd,(struct sockaddr *)&server,sizeof(server))==-1){  
        printf("connect()error\n");  
        exit(1);  
    } 

    //读写操作
    while(1){
        printf("ready to get data!\n");
    if((num=recv(sockfd,buf,MAXDATASIZE,0)) == -1){  
        printf("recv() error\n");
        
        close(sockfd);  
        exit(1);  
    } 
    
    buf[num]='\0';  
    printf("Server Message: %s\n",buf); 
        }
    //if()

    
    close(sockfd);  
    return 0;  
}  

void * net_thread_entry (void *parameter)
{
    int ret;
    eg_tcp_send(CONNECT_STR,sizeof(CONNECT_STR)-1);
    //eg_tcp_send(connect_array,sizeof(connect_array));

    while(1){


        if((ret=recv(sockfd,buf,MAXDATASIZE,0)) == -1){  
            
                printf("recv() error\n");
                
                //close(sockfd);  
                //exit(1);  
        } 
        printf("ret is %d\n",ret);    
        buf[ret]='\0';  
        printf("Server Message: %s\n",buf);
        print_time();

        if(strncmp(CONNECT_ACK_STR,buf,sizeof(CONNECT_ACK_STR)) == 0 ){

            printf("connect success!\n");


        }
/*
        if(strncmp(HBM_REC,buf,sizeof(HBM_REC)) == 0 ){

            eg_tcp_send(HBM_SEND,sizeof(HBM_SEND));


        }
*/

    }







}

void eg_net_init(void)
{
    osal_task_t *tid;

    //创建套接字
      if((sockfd=socket(AF_INET, SOCK_STREAM, 0)) < 0){  
          printf("socket()error\n");  
          exit(1);  
      }  
    
      //指定server地址    
      struct sockaddr_in server;  
      bzero(&server,sizeof(server));  
      server.sin_family= AF_INET;  
      server.sin_port = htons(PORT);  
      if( inet_pton(AF_INET, SERVERADDR, &server.sin_addr) <= 0){
          printf("inet_pton error for %s\n",SERVERADDR);
          exit(0);
      }
    
      //发起连接操作
      if(connect(sockfd,(struct sockaddr *)&server,sizeof(server))==-1){  
          printf("connect()error\n");  
          exit(1);  
      }

    tid = osal_task_create("tk_net",
                        net_thread_entry,
                        NULL,RT_SYS_THREAD_STACK_SIZE, RT_SYS_THREAD_PRIORITY);

    osal_assert(tid != NULL)



}


