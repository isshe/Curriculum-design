/*==============================================================================\
* Copyright(C)2015 Chudai.
*
* File name    : cli_udp_mcast.c
* Version      : v1.0.0
* Author       : ����
* Date         : 2015/08/27
* Description  : �ಥ�ͻ���
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
     servaddr.sin_port = htons(SERV_PORT); //��һ���޷��Ŷ����͵�������ֵת��Ϊ�����ֽ�˳��
     my_inet_pton(AF_INET, MCAST_IP, &servaddr.sin_addr); //ʮ����IPת������

     //����һ���׽���
     sockfd = my_socket(AF_INET, SOCK_DGRAM, 0);

     dg_cli(stdin, sockfd, (SA *) &servaddr, sizeof(servaddr));

     exit(0);
}
