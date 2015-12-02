/*==============================================================================\
* Copyright(C)2015 Chudai.
*
* File name    : ser_udp_mcast.c
* Version      : v1.0.0
* Author       : 初代
* Date         : 2015/08/27
* Description  : 多播服务器, 回射, 时间获取, mac地址等
* Function list: 1.
*                2.
*                3.
* History      :
\*==============================================================================*/


#include "my.h"
#include "gd_echo.h"

#define     MCAST_IP    "224.22.22.22"

int main(void)
{
     int    sockfd = 0;
     struct sockaddr_in     servaddr;   //服务器结构
     struct sockaddr_in     grpaddr;    //多播组结构
     struct sockaddr_in     cliaddr;    //客户端结构
     const  int on = 1;                 //用于开启选项

     sockfd = my_socket(AF_INET, SOCK_DGRAM, 0);

    //初始化结构体并填充服务器信息
     bzero(&servaddr, sizeof(servaddr));
     servaddr.sin_family        = AF_INET;
     servaddr.sin_addr.s_addr   = htonl(INADDR_ANY);    //主机转网络
     servaddr.sin_port          = htons(SERV_PORT);     //主机转网络
     
     //SO_REUSEADDR地址复用;
     //如果不使用这句, 则同一台主机中,则无法开启两个服务器
     //bind的时候会失败:address already in use
     //另一个方案"随机分配端口号"应该也可以
     my_setsockopt(sockfd, SOL_SOCKET, SO_REUSEADDR, &on, sizeof(on));
     //把一个本地协议的地址赋予一个套接字
     my_bind(sockfd, (SA *) &servaddr, sizeof(servaddr));

     //初始化结构体并填充多播组信息
     bzero(&grpaddr, sizeof(servaddr));
     grpaddr.sin_family     = AF_INET;
     grpaddr.sin_addr.s_addr = inet_addr(MCAST_IP);

     //加入多播组
     mcast_join(sockfd, (SA *)&grpaddr, sizeof(grpaddr), NULL, 0);

     //回射发来的信息, 以及时间, mac地址
     dg_echo(sockfd, (SA *)&cliaddr, sizeof(cliaddr));
     
    
     return 0;
}
