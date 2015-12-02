/*
 * =====================================================================================
 *
 *       Filename:  my_ioctl.c
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  2015��08��03�� ����һ 11�r05��07�� CST
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  YOUR NAME (), 
 *   Organization:  
 *
 * =====================================================================================
 */
//#include <sys/ioctl.h> 	//���ļ��еĺ����õ��ĺ��Ŀ⺯�����������ͷ�ļ�
#include "my.h"

int my_ioctl(int fd, int request, void *arg)
{
	int		n;

	if ( (n = ioctl(fd, request, arg)) == -1)
		err_sys("ioctl error");
	return(n);	/* streamio of I_LIST returns value */
}

