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

#define    PORT 8020  
#define    MAXDATASIZE 10000
#define    SERVERADDR  "172.16.32.152"


#define    MSG_HEADER 0x01

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



