/*==============================================================================*\
* Copyright(C)2015 Chudai.
*
* File name    : gd_echo.c
* Version      : v1.0.0
* Author       : ����
* Date         : 2015/08/27
* Description  : ���䷢������Ϣ, ��ʱ��, ����mac!
*                   ע��: ��ȡmac��ַʱ, �ǹ̶��˽ӿں�"eth0"!!!
* Function list: 1.
*                2.
*                3.
* History      :
\*==============================================================================*/

#include "my.h"

//ͼ8-20
static void recvfrom_int(int);
static int 	count;

void dg_echo(int sockfd, SA *pcliaddr, socklen_t clilen)
{
	socklen_t 	len;
	char 		msg[MAXLINE];
//	int         n = 0;
	char        buf[MAXLINE + 64] ;
	time_t      ticks;                  //���ڻ�ȡʱ��
	struct      ifreq   ifr ;           //���ڻ�ȡmac��ַ
	u_char      *hwaddr = NULL;         //����ָ���ȡ��mac��ַ
	
	my_signal(SIGINT, recvfrom_int);    
	//signal(SIGINT, recvfrom_int);
	while(1)
	{
		len = clilen;
		my_recvfrom(sockfd, msg, MAXLINE, 0, pcliaddr, &len); //������������
		
		count++;
		printf("%d. recvfrom %s: %s\n", 
		        count, 
		        my_sock_ntop(pcliaddr, len), 
		        msg);
		//��ȡʱ��, Ȼ���ȡmac��ַ, Ȼ�����
		//��ȡʱ��:
		ticks = time(NULL);
		
		//��ȡmac��ַ
		//���!!!����: Ҫ��ô�Ĳ��ܶ�̬��ȡ��?�����������eth0�ͻ�ʧ��.
		//����, �����г���ǰ,���û�ָ���ӿ�?!
		memcpy(ifr.ifr_name, "eth0", sizeof(ifr.ifr_name) - 1);  
		my_ioctl(sockfd, SIOCGIFHWADDR, &ifr);      //�����ȡMAC��ַ
		hwaddr = (u_char *)ifr.ifr_hwaddr.sa_data;//ifr_hwaddr��һ��"SA"�ṹ
		
		snprintf(buf, MAXLINE + 64, 
		         "%s\r"
		         "     %.24s\r\n"
		         "     hwaddr=%x:%x:%x:%x:%x:%x\r\n",
		         msg, 
		         ctime(&ticks),
		         *(hwaddr), *(hwaddr + 1), *(hwaddr + 2),
		         *(hwaddr + 3), *(hwaddr + 4), *(hwaddr + 5));
		printf("%s\n", buf);
		my_sendto(sockfd, buf, sizeof(buf), 0, pcliaddr, len);
	}
}

static void recvfrom_int(int signo)
{
	printf("\nreceived %d datagrams\n", count);     //��ӡ���յ�����Ϣ����
	exit(0);
}

