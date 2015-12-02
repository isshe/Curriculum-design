/* �������������һ�б��ע��,��Ϊ��Ԥ��λ��д˵��.����ȥ��Ӧ�û���ÿ�*/

/* =====================================================================================
 *
 *       Filename:  my.h
 *
 *    Description:  һЩ�����������ο���unix�����̡�
 *
 *        Version:  1.0
 *        Created:  2015��08��01�� ������ 11�r43��12�� CST
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  chudai
 *   Organization:
 *
 * =====================================================================================
 */

#ifndef _MY_H_
#define _MY_H_

#include <stdlib.h>
#include <stdarg.h> 	//ANSI C header file.����va_list�Ⱥ궨��.
#include <syslog.h> 	//for syslog()
#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <error.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>	//htons();
#include <unistd.h>		//my_process.c, my_readwrite.c,
#include <sys/stat.h>	//my_readwrite.c
#include <fcntl.h>		//my_readwrite.c
#include <sys/ioctl.h>	//my_ioctl.c
#include <sys/time.h>	//my_time.c
#include <sys/wait.h>	//my_process.c
#include <sys/utsname.h>//utsname�ṹ!
#include <netinet/in.h>
#include <time.h>
#include <signal.h>
#include <poll.h>       //poll()
#include <sys/stropts.h>
#include <netinet/sctp.h>    	//sctp, �����ʱ��� -lsctp
#include <netdb.h> 				//gethostbyname()
#include <sys/un.h> 			//unix���,����:sockaddr_un{};
#include <net/if.h>
#include <pthread.h>            //�����ʱ��ǵü� -lpthread

#define MAXLINE 			4096
#define SCTP_MAXLINE 		800
#define BUFFSIZE 			8192
#define SA 					struct sockaddr
#define SA_IN 				struct sockaddr_in
#define SA_IN6 				struct sockaddr_in6
#define SA_DL 				struct sockaddr_dl
#define SERV_MAX_SCTP_STRM 	10

#define	LISTENQ				1024			// 2nd argument to listen()
#define	SERV_PORT			9877
#define	SERV_PORT_STR		"9877"			// TCP and UDP client-servers

#define max(a, b)           ((a) > (b) ? (a) : (b))
#define DEBUG 				(printf("#%s:%d: \n", __FILE__, __LINE__))

/*һ�������my_error.c�ж���!*/
/* 1.ϵͳ����,��������,��ֹ����ӡ������Ϣ */
void 	err_sys(const char *fmt, ...);

/* 2.ϵͳ����,��������,��ֹ����ӡ�δ������Ϣ */
void 	err_dump(const char *fmt, ...);

/* 3.ϵͳ����,����������, ��ӡ������Ϣ,���� */
void 	err_ret(const char *fmt, ...);

/* 4.������������,����ϵͳ����,��ӡ������Ϣ������ */
void 	err_msg(const char *fmt, ...);

/* 5.��������,����ϵͳ����,��ӡ������Ϣ����ֹ */
void 	err_quit(const char *fmt, ...);

const char *hstrerror(int err);


/*���� ��my_socket.c�ж���*/
int 	my_socket(int family, int type, int protocol);
int		my_accept(int fd, struct sockaddr *sa, socklen_t *salenptr);
void 	my_bind(int fd, const struct sockaddr *sa, socklen_t salen);
void 	my_connect(int fd, const struct sockaddr *sa, socklen_t salen);
void 	my_listen(int fd, int backlog);
void 	my_getpeername(int fd, struct sockaddr *sa, socklen_t *salenptr);
void 	my_getsockname(int fd, struct sockaddr *sa, socklen_t *salenptr);
void 	my_getsockopt(int fd, int level, int optname,
						void *optval, socklen_t *optlenptr);
void 	my_setsockopt(int fd, int level, int optname,
						const void *optval, socklen_t optlen);
void 	my_shutdown(int fd, int how);

/* my_sock.c */
//������������ʵ���, _host()���,��ҪӦ������Ҳ����, �����ϵ�!!!
char*	my_sock_ntop(const struct sockaddr *sa, socklen_t salen);
char* 	my_sock_ntop_host(const struct sockaddr *sa, socklen_t salen);



/* my_malloc.c */
void*	my_malloc(size_t size);
void*	my_calloc(size_t n, size_t size);


/* my_process.c */
pid_t	my_fork(void);
pid_t 	my_wait(int *iptr);
pid_t 	my_waitpid(pid_t pid, int *iptr, int options);


/* my_ioctl.c */
/* 1. */
int		my_ioctl(int fd, int request, void *arg);



/* my_time.c */
void 	my_gettimeofday(struct timeval *tv, void *foo);



/* my_readwrite.c */
int 	my_open(const char *pathname, int oflag, mode_t mode);
void 	my_close(int fd);
ssize_t my_read(int fd, void *ptr, size_t nbytes);
void 	my_write(int fd, void *ptr, size_t nbytes);


/* my_fcntl.c */
int 	my_fcntl(int fd, int cmd, int arg);


/* my_sendrecv.c */
ssize_t my_recv(int fd, void *ptr, size_t nbytes, int flags);
ssize_t my_recvfrom(int fd, void *ptr, size_t nbytes, int flags,
					struct sockaddr *sa, socklen_t *salenptr);
ssize_t my_recvmsg(int fd, struct msghdr *msg, int flags);
int 	 my_sctp_recvmsg(int s, void *msg, size_t len,
						 struct sockaddr *from, socklen_t *fromlen,
						 struct sctp_sndrcvinfo *sinfo, int *msg_flags);

void 	my_send(int fd, const void *ptr, size_t nbytes, int flags);
void 	my_sendto(int fd, const void *ptr, size_t nbytes, int flags,
					const struct sockaddr *sa, socklen_t salen);
void 	my_sendmsg(int fd, const struct msghdr *msg, int flags);
int		 my_sctp_sendmsg(int s, void *data, size_t len,
							struct sockaddr *to, socklen_t tolen,
							uint32_t ppid, uint32_t flags,
							uint16_t stream_no, uint32_t timetolive,
							uint32_t context);

/* my_stdio.c */
char* my_fgets(char *ptr, int n, FILE *stream);
void  my_fputs(const char *ptr, FILE *stream);
void  my_fclose(FILE *fp);
FILE* my_fopen(const char *filename, const char *mode);
FILE* my_fdopen(int fd, const char *type);

/* my_readline.c */
ssize_t my_readline(int fd, void *ptr, size_t maxlen);

/* my_writen.c */
/*һ��дn���ֽ� */
void my_writen(int fd, void *ptr, size_t nbytes);

/* my_inet.c */
void my_inet_pton(int family, const char *strptr, void *addrptr);
const char* my_inet_ntop(int family, const void *addrptr,
						 char *strptr, size_t len);

/* my_signal.c */
/*Ϊ�˰�
 *    void (*signal(int signo, void (*func)(int)))(int);
 *��.��������һ��typedef!
 */
typedef void Sigfunc(int);

Sigfunc * my_signal(int signo, Sigfunc *func);
void my_sigaddset(sigset_t *set, int signo);
void my_sigdelset(sigset_t *set, int signo);

/*sigemptyset()����������set�źż���ʼ������ա�
 * ִ�гɹ��򷵻�0������д����򷵻�-1��
 */
void my_sigemptyset(sigset_t *set);

/*sigfillset()����������set�źż���ʼ����
 * Ȼ������е��źż��뵽���źż��Ｔ�����е��źű�־λ��Ϊ1���������е��źš�
 * ����һ����ʵ��.
 */
void my_sigfillset(sigset_t *set);

/*sigismember()�������Բ���signum ������ź��Ƿ��Ѽ���������set�źż��
 *  ����źż������и��ź��򷵻�1�����򷵻�0������д����򷵻�-1��
 */
int my_sigismember(const sigset_t *set, int signo);
void my_sigpending(sigset_t *set);

/*һ�����̵��ź������ֹ涨�˵�ǰ���������ܵ��͸��ý��̵��źż���
   sigprocmask()������������ı�Ŀǰ���ź������֣�
   �����������how���������������oldset����NULLָ�룬
   ��ôĿǰ���ź������ֻ��ɴ�ָ�뷵��..
   ���set��һ���ǿ�ָ�룬�����howָʾ����޸ĵ�ǰ�ź������֡�
   ÿ�����̶���һ������������Щ�źŵ��͵�����ʱ�����������źż���
   ���źż��е������ź��ڵ��͵����̺󶼽���������
����how��ȡֵ��ͬ�������Ĳ�����ΪҲ��ͬ���ò�����ѡֵ���£�
    1��SIG_BLOCK:����ֵ����Ĺ����ǽ�newset��ָ����źż������������ź�
    �ӵ���ǰ���ź������У���Ϊ�µ��ź������֡�
    2��SIG_UNBLOCK:������newset��ָ����źż��е��źŴӵ�ǰ���ź��������Ƴ���
    3��SIG_SETMASK:���õ�ǰ�ź�����Ϊ����newset��ָ����źż������������źš�
ע�����sigprocmask()����ֻΪ���̵߳Ľ��̶���ģ�
        �ڶ��߳���Ҫʹ��pthread_sigmask��������ʹ��֮ǰ��Ҫ�����ͳ�ʼ��..
    ִ�гɹ�����0��ʧ�ܷ���-1��
*/
void my_sigprocmask(int how, const sigset_t *set, sigset_t *oset);


/* my_select.c */

//#ifdef	HAVE_POLL
int 	my_poll(struct pollfd *fdarray, unsigned long nfds, int timeout);
//#endif

int 	my_select(int nfds, fd_set *readfds,
					fd_set *writefds, fd_set *exceptfds,
					struct timeval *timeout);

/* sctp_getnostrms.c */ //  ��<<unix������(1)>>p224ҳ�õ�.
//��ȡ�������//
int 	sctp_get_no_strms(int sock_fd,
						  struct sockaddr *to,
						  socklen_t tolen);

/* my_tcp.c */
//ʹ��getaddrinfo()
//���ڼ򻯷���getaddrinfo()��TCP�ӿں���
int tcp_connect(const char *host, const char *serv);
int	tcp_listen(const char *hostname,
				  const char *service,
				  socklen_t *addrlenp);

/* my_udp.c */
//ʹ��getaddrinfo()
//���ڼ򻯷���getaddrinfo��UDP�ӿں���
int udp_client(const char *host, const char *serv,
				SA **saptr, socklen_t *lenp);
int udp_connect(const char *hostname, const char *service);
int udp_server(const char *hostname,
				const char *service,
				socklen_t *lenptr);


/* my_pipe.c */
void my_pipe(int *fds);


/* mcast_XXX.c ϵ�� */
/* mcast_join_leave.c */
int mcast_join(int sockfd, const SA *grp, socklen_t grplen,
               const char *ifname, u_int ifindex);

/* family_to_level.c */
//��mcast_join()����//
int my_family_to_level(int family);

/* sockfd_to_family.c */
//��mcast_set_loop()����//
int my_sockfd_to_family(int sockfd);


/* my_pthread.c */
void my_pthread_create(pthread_t *tid, const pthread_attr_t *attr,
                       void * (*func)(void *), void *arg);

void my_pthread_join(pthread_t tid, void **status);
void my_pthread_detach(pthread_t tid);
void my_pthread_kill(pthread_t tid, int signo);
void my_pthread_mutexattr_init(pthread_mutexattr_t *attr);
void my_pthread_mutexattr_setpshared(pthread_mutexattr_t *attr,
                                     int flag);
void my_pthread_mutex_init(pthread_mutex_t *mptr,
                           pthread_mutexattr_t *attr);
void my_pthread_mutex_lock(pthread_mutex_t *mptr);
void my_pthread_mutex_unlock(pthread_mutex_t *mptr);
void my_pthread_cond_broadcast(pthread_cond_t *cptr);
void my_pthread_cond_signal(pthread_cond_t *cptr);
void my_pthread_cond_wait(pthread_cond_t *cptr,
                          pthread_mutex_t *mptr);
void my_pthread_cond_timewait(pthread_cond_t *cptr,
                              pthread_mutex_t *mptr,
                              const struct timespec *tsptr);
void my_pthread_once(pthread_once_t *ptr, void (*func)(void));
void my_pthread_key_create(pthread_key_t *key,
                           void (*func)(void *));
void my_pthread_setspecific(pthread_key_t key, const void *value);

#endif
