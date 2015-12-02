/*==============================================================================\
* Copyright(C)2015 Chudai.
*
* File name    : IPC_dgcli_bca.c
* Version      : v1.0.0
* Author       : ����
* Date         : 2015/08/26
* Description  : ʹ�ô��źŴ����������غ����Ĺܵ���ΪIPC;
* Function list: 1.
*                2.
*                3.
* History      :
\*==============================================================================*/

#include "my.h"


static void recvfrom_alarm(int);
static int  pipefd[2];


/*******************************************************************************
 *������: dg_cli
 *����: ���������ַ���, ���͸�������,�ಥ���������ش��ַ���&ʱ��&�Լ���mac��ַ
 *����:
 *     1.
 *     2.
 *����:
 ******************************************************************************/
void dg_cli(FILE *fp, int sockfd, const SA *pservaddr, socklen_t servlen)
{
    int     n = 0;
    int     maxfdp1 = 0;
    const   int     on = 1;
    char    sendline[MAXLINE] = {0};
    //+64����Ϊ�Զ˻�����mac��ַ,��ʱ�����
    char    recvline[MAXLINE + 64] = {0};       
    fd_set  rset;
    socklen_t   len;
    struct  sockaddr    *preply_addr = NULL;

    preply_addr = my_malloc(servlen);

    //�����׽���ѡ��;
    //SO_BROADCAST ����㲥���ݱ�
    //SOL_SOCKET�Ǽ���(level)[�׽��ּ���?]
    //���Բ�Ҫ
//    my_setsockopt(sockfd, SOL_SOCKET, SO_BROADCAST, &on, sizeof(on));

    //�����ܵ�
    my_pipe(pipefd);
//    printf("pipefd[0] = %d\n", pipefd[0]); //+

    maxfdp1 = max(sockfd, pipefd[0]) + 1; //max��һ����, Ӧ�øĴ�д��.

    FD_ZERO(&rset);     //����ļ���������;�׽���Ҳ���ļ���������һ��

    my_signal(SIGALRM, recvfrom_alarm);     //����ʱ���źŹ���

    while (my_fgets(sendline, MAXLINE, fp) != NULL )  //���������ַ�
    {
         my_sendto(sockfd, sendline, strlen(sendline),
                    0, pservaddr, servlen);             //���͸�������

         alarm(3);  //���ö�ʱ3��

         while (1)
         {
              FD_SET(sockfd, &rset);        //������������
              FD_SET(pipefd[0], &rset);

              //I/O����
              if ( (n = select(maxfdp1, &rset, NULL, NULL, NULL)) < 0 )
              {
                  if (errno == EINTR)
                  {
                       DEBUG;           //һ����, ������
                       printf("select errno = EINTR\n");    //selectʧ�ܵ�errnoֵ
                       continue;        //���Դ���, ����ѭ��
                  }
                  else
                  {
                      err_sys("select error");
                  }
              }
//                printf("kankan!\n");
              if ( FD_ISSET(sockfd, &rset) ) //�׽��ֿɶ�, ��ʾ����Ϣ����
              {
                   len = servlen;
                   n = my_recvfrom(sockfd, recvline, MAXLINE,
                                    0, preply_addr, &len);      //������Ϣ
                   recvline[n] = '\0';
                   printf("\nfrom %s: %s",
                           my_sock_ntop(preply_addr, len),      //������ת10����
                           recvline);           //��ӡ������IP�ͷ��ص���Ϣ
              }

              if ( FD_ISSET(pipefd[0], &rset) )
              {
//                   printf("read ����\n");
                   my_read(pipefd[0], &n, 1);   //timer expired
//                   printf("read ����!\n");
                   break;       //�˳�ѭ��
              }
         }
    }

    free(preply_addr);      

}


/*******************************************************************************
 *������: recvfrom_alarm()
 *����: ���ö�ʱ��Ϊ��Ӧ��������̫������.
 *      Ԥ���㹻��ʱ����ͻ��˽��շ�������������Ϣ,
 *      д�ܵ�, ʹ�ܵ���Ϊ�ɶ�, select����, �˳�ѭ��.
 *����:
 *     1. �ź���
 *     2.
 *����:
 ******************************************************************************/
static void recvfrom_alarm(int signo)
{
    printf("ʱ�䵽!\n");                    //+
//    printf("pipefd[1] = %d\n", pipefd[1]);  //+
    my_write(pipefd[1], "", 1);
return ;
}
