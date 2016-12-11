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
    struct sockaddr_in server;  
 
  
    if((sockfd=socket(AF_INET, SOCK_STREAM, 0))==-1){  
        printf("socket()error\n");  
        exit(1);  
    }  
    
    bzero(&server,sizeof(server));  
    server.sin_family= AF_INET;  
    server.sin_port = htons(PORT);  
    if( inet_pton(AF_INET, SERVERADDR, &server.sin_addr) <= 0){
        printf("inet_pton error for %s\n",SERVERADDR);
        exit(0);
    }
    
    if(connect(sockfd,(struct sockaddr *)&server,sizeof(server))==-1){  
        printf("connect()error\n");  
        exit(1);  
    } 
    while(1){
        printf("ready to get data!\n");
    if((num=recv(sockfd,buf,MAXDATASIZE,0)) == -1){  
        printf("recv() error\n");
        
        close(sockfd);  
        exit(1);  
    } 
    
    buf[num-1]='\0';  
    printf("Server Message: %s\n",buf); 
        }
    //if()

    
    close(sockfd);  
    return 0;  
}  



