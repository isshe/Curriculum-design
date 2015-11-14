/*
 * =====================================================================================
 *
 *       Filename:  my_ioctl.c
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  2015年08月03日 星期一 11時05分07秒 CST
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  YOUR NAME (), 
 *   Organization:  
 *
 * =====================================================================================
 */
//#include <sys/ioctl.h> 	//此文件中的函数用到的核心库函数都来自这个头文件
#include "my.h"


/*******************************************************************************
 *函数名: 
 *功能:
 *参数:
 *     1.
 *     2.
 *返回:
 ******************************************************************************/
int my_ioctl(int fd, int request, void *arg)
{
	int		n;

	if ( (n = ioctl(fd, request, arg)) == -1)
		err_sys("ioctl error");
	return(n);	/* streamio of I_LIST returns value */
}

