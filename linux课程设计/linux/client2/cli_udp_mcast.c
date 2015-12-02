/*==============================================================================\
* Copyright(C)2015 Chudai.
*
* File name    : cli_udp_mcast.c
* Version      : v1.0.0
* Author       : 初代
* Date         : 2015/08/27
* Description  : 多播客户端
* Function list: 1.
*                2.
*                3.
* History      :
\*==============================================================================*/

#include "my.h"
#include "dg_cli.h"

#define     MCAST_IP    "224.22.22.22"

int main(int argc, char **argv)
{
     int    sockfd = 0;
     struct sockaddr_in     servaddr;

     if (argc < 2)
     {
          err_quit("usage: ./a.out <IPaddress>");
     }

     bzero(&servaddr, sizeof(servaddr));
     servaddr.sin_family = AF_INET;
     servaddr.sin_port = htons(SERV_PORT); //将一个无符号短整型的主机数值转换为网络字节顺序
     my_inet_pton(AF_INET, MCAST_IP, &servaddr.sin_addr); //十进制IP转二进制

     //创建一个套接字
     sockfd = my_socket(AF_INET, SOCK_DGRAM, 0);

     dg_cli(stdin, sockfd, (SA *) &servaddr, sizeof(servaddr));

     exit(0);
}
