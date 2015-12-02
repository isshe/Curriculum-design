/*==============================================================================\
* Copyright(C)2015 Chudai.
*
* File name    : IPC_dgcli_bca.c
* Version      : v1.0.0
* Author       : 初代
* Date         : 2015/08/26
* Description  : 使用从信号处理函数到主控函数的管道作为IPC;
* Function list: 1.
*                2.
*                3.
* History      :
\*==============================================================================*/

#include "my.h"


static void recvfrom_alarm(int);
static int  pipefd[2];


/*******************************************************************************
 *函数名: dg_cli
 *功能: 输入任意字符串, 发送给服务器,多播服务器返回此字符串&时间&自己的mac地址
 *参数:
 *     1.
 *     2.
 *返回:
 ******************************************************************************/
void dg_cli(FILE *fp, int sockfd, const SA *pservaddr, socklen_t servlen)
{
    int     n = 0;
    int     maxfdp1 = 0;
    const   int     on = 1;
    char    sendline[MAXLINE] = {0};
    //+64是因为对端还发送mac地址,和时间过来
    char    recvline[MAXLINE + 64] = {0};       
    fd_set  rset;
    socklen_t   len;
    struct  sockaddr    *preply_addr = NULL;

    preply_addr = my_malloc(servlen);

    //设置套接字选项;
    //SO_BROADCAST 允许广播数据报
    //SOL_SOCKET是级别(level)[套接字级别?]
    //可以不要
//    my_setsockopt(sockfd, SOL_SOCKET, SO_BROADCAST, &on, sizeof(on));

    //创建管道
    my_pipe(pipefd);
//    printf("pipefd[0] = %d\n", pipefd[0]); //+

    maxfdp1 = max(sockfd, pipefd[0]) + 1; //max是一个宏, 应该改大写的.

    FD_ZERO(&rset);     //清空文件描述符集;套接字也是文件描述符的一种

    my_signal(SIGALRM, recvfrom_alarm);     //设置时间信号规则

    while (my_fgets(sendline, MAXLINE, fp) != NULL )  //输入任意字符
    {
         my_sendto(sockfd, sendline, strlen(sendline),
                    0, pservaddr, servlen);             //发送给服务器

         alarm(3);  //设置定时3秒

         while (1)
         {
              FD_SET(sockfd, &rset);        //设置描述符集
              FD_SET(pipefd[0], &rset);

              //I/O复用
              if ( (n = select(maxfdp1, &rset, NULL, NULL, NULL)) < 0 )
              {
                  if (errno == EINTR)
                  {
                       DEBUG;           //一个宏, 测试用
                       printf("select errno = EINTR\n");    //select失败的errno值
                       continue;        //忽略错误, 继续循环
                  }
                  else
                  {
                      err_sys("select error");
                  }
              }
//                printf("kankan!\n");
              if ( FD_ISSET(sockfd, &rset) ) //套接字可读, 表示有消息到来
              {
                   len = servlen;
                   n = my_recvfrom(sockfd, recvline, MAXLINE,
                                    0, preply_addr, &len);      //接收信息
                   recvline[n] = '\0';
                   printf("\nfrom %s: %s",
                           my_sock_ntop(preply_addr, len),      //二进制转10进制
                           recvline);           //打印服务器IP和返回的信息
              }

              if ( FD_ISSET(pipefd[0], &rset) )
              {
//                   printf("read 上面\n");
                   my_read(pipefd[0], &n, 1);   //timer expired
//                   printf("read 下面!\n");
                   break;       //退出循环
              }
         }
    }

    free(preply_addr);      

}


/*******************************************************************************
 *函数名: recvfrom_alarm()
 *功能: 设置定时是为了应付服务器太多的情况.
 *      预留足够的时间给客户端接收服务器发来的信息,
 *      写管道, 使管道变为可读, select作用, 退出循环.
 *参数:
 *     1. 信号码
 *     2.
 *返回:
 ******************************************************************************/
static void recvfrom_alarm(int signo)
{
    printf("时间到!\n");                    //+
//    printf("pipefd[1] = %d\n", pipefd[1]);  //+
    my_write(pipefd[1], "", 1);
return ;
}
