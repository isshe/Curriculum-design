/*
 * =====================================================================================
 *
 *       Filename:  my_error.c
 *
 *    Description:  һЩ�����������ο���unix�����̡�
 *
 *        Version:  1.0
 *        Created:  2015��08��01�� ������ 11�r43��12�� CST
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  YOUR NAME (), 
 *   Organization:  
 *
 * =====================================================================================
 */

#include "my.h"

/* ��ӡ������Ϣ */
static void err_doit(int, int, const char *, va_list);

int daemon_proc;

/* 1.ϵͳ����,��������,��ֹ����ӡ������Ϣ */
void err_sys(const char *fmt, ...)
{
	va_list ap;

	va_start(ap, fmt);
	err_doit(1, LOG_ERR, fmt, ap);
	va_end(ap);

	exit(1);
}

/* 2.ϵͳ����,��������,��ֹ����ӡ�δ������Ϣ */
void err_dump(const char *fmt, ...)
{
	va_list ap;
	va_start(ap, fmt);
	err_doit(1, LOG_ERR, fmt, ap);
	va_end(ap);
	
	abort();	//dump core and terminate
	
	exit(1);
}

/* 3.ϵͳ����,����������, ��ӡ������Ϣ,���� */
void err_ret(const char *fmt, ...)
{
	va_list ap;

	va_start(ap, fmt);
	err_doit(1, LOG_INFO, fmt, ap);
	va_end(ap);

	return ;
}

/* 4.������������,����ϵͳ����,��ӡ������Ϣ������ */
void err_msg(const char *fmt, ...)
{
	va_list ap;

	va_start(ap, fmt);
	err_doit(0, LOG_INFO, fmt, ap);
	va_end(ap);

	return;
}

/* 5.��������,����ϵͳ����,��ӡ������Ϣ����ֹ */
void err_quit(const char *fmt, ...)
{
	va_list ap;
	
	va_start(ap, fmt);
	err_doit(0, LOG_ERR, fmt, ap);
	va_end(ap);

	exit(1);
}

/* ��ӡ������Ϣ */
static void err_doit(int errnoflag, int level, const char *fmt, va_list ap)
{
	int 	errno_save = 0;
	int 	n = 0;
	char	buf[MAXLINE + 1];

	errno_save = errno;	//�������

#ifdef HAVE_VSNPRINTF
	vsnprintf(buf, MAXLINE, fmt, ap);	//safe
#else
	vsprintf(buf, fmt, ap);				//not safe
#endif

	n = strlen(buf);
	if (errnoflag)
	{
		snprintf(buf + n, MAXLINE - n, ": %s ", strerror(errno_save));
	}
	
	strcat(buf, "\n");		//�Ѳ���2���ַ�����ӵ�����1�ĺ���
	
	if (daemon_proc)	//��һ�鲻��!!!д��ϵͳ��־
	{
		//��syslog(level, buf); �ĳ�����, ���������ٸĻ���!
		syslog(level, "%s", buf);	//д��ϵͳ��־! �����о���!!!
	}
	else
	{
		fflush(stdout);
		fputs(buf, stderr);
		fflush(stderr);
	}

}

const char *
hstrerror(int err)
{
	if (0 == err)
	{
		return ("no error");
	}
	if (HOST_NOT_FOUND == err)
	{
		return ("Unknown host");
	}
	if (TRY_AGAIN == err)
	{
		return ("Hostname lookup failure");
	}
	if (NO_RECOVERY == err)
	{
		return ("Unknown server error");
	}
	if (NO_DATA == err)
	{
		return ("No address associated with name");
	}
	
	return ("unknown error");
}





