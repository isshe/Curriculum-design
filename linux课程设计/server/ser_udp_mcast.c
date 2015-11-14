/*==============================================================================\
* Copyright(C)2015 Chudai.
*
* File name    : ser_udp_mcast.c
* Version      : v1.0.0
* Author       : ����
* Date         : 2015/08/27
* Description  : �ಥ������, ����, ʱ���ȡ, mac��ַ��
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
     struct sockaddr_in     servaddr;   //�������ṹ
     struct sockaddr_in     grpaddr;    //�ಥ��ṹ
     struct sockaddr_in     cliaddr;    //�ͻ��˽ṹ
     const  int on = 1;                 //���ڿ���ѡ��

     sockfd = my_socket(AF_INET, SOCK_DGRAM, 0);

    //��ʼ���ṹ�岢����������Ϣ
     bzero(&servaddr, sizeof(servaddr));
     servaddr.sin_family        = AF_INET;
     servaddr.sin_addr.s_addr   = htonl(INADDR_ANY);    //����ת����
     servaddr.sin_port          = htons(SERV_PORT);     //����ת����
     
     //SO_REUSEADDR��ַ����;
     //�����ʹ�����, ��ͬһ̨������,���޷���������������
     //bind��ʱ���ʧ��:address already in use
     //��һ������"�������˿ں�"Ӧ��Ҳ����
     my_setsockopt(sockfd, SOL_SOCKET, SO_REUSEADDR, &on, sizeof(on));
     //��һ������Э��ĵ�ַ����һ���׽���
     my_bind(sockfd, (SA *) &servaddr, sizeof(servaddr));

     //��ʼ���ṹ�岢���ಥ����Ϣ
     bzero(&grpaddr, sizeof(servaddr));
     grpaddr.sin_family     = AF_INET;
     grpaddr.sin_addr.s_addr = inet_addr(MCAST_IP);

     //����ಥ��
     mcast_join(sockfd, (SA *)&grpaddr, sizeof(grpaddr), NULL, 0);

     //���䷢������Ϣ, �Լ�ʱ��, mac��ַ
     dg_echo(sockfd, (SA *)&cliaddr, sizeof(cliaddr));
     
    
     return 0;
}
