/*==============================================================================\
* Copyright(C)2015 Chudai.
*
* File name    : mcast_join.c
* Version      : v1.0.0
* Author       : 初代
* Date         : 2015/08/26
* Description  : 加入一个多播组
* Function list: 1.
*                2.
*                3.
* History      :
\*==============================================================================*/

#include "my.h"
//#include "mcast_join_leave.h"
//#include <net/if.h>


/*******************************************************************************
 * 函数名: mcast_join()
 * 功能: 加入一个多播组
 * 参数说明: 
 *      1.ifname: 接口名称
 *      2.ifindex:接口索引
 *      3.
 * 返回:
 ******************************************************************************/

//第一部分:加入一个多播组:IP无关套接字//
int mcast_join(int sockfd, const SA *grp, socklen_t grplen,
               const char *ifname, u_int ifindex)
{
#ifdef  MCAST_JOIN_GROUP        //编译的时候手工指定?

/*************************************************************************
    struct group_req{
        unsigned    int     gr_interface;   //interface index, or 0
        struct sockaddr_storage     gr_group; 
    }

    struct sockaddr_storage{
        uint8_t     ss_len;     //length of this struct
        sa_family_t ss_family;
    }
***************************************************************************/
    struct  group_req   req;

    if (ifindex > 0)
    {
         req.gr_interface = ifindex;
    }
    else if (ifname != NULL)
    {
         if ( (req.gr_interface = if_nametoindex(ifname)) == 0)
         {
              errno = ENXIO;        //i/f name not found
              DEBUG;
              printf("#errno = ENXIO!\n");      //+
              return(-1);
         }
    }
    else
    {
         req.gr_interface = 0;
    }

    //为了防止下面复制的时候溢出, 先检查大小
    if (grplen > sizeof(req.gr_group))
    {
         errno = EINVAL;    //22, invalid argument
         DEBUG;
         printf("#errno = EINVAL!\n");
         return (-1);
    }

    memcpy(&req.gr_group, grp, grplen);

    //setsockopt执行加入操作
    //my_family_to_level用来确定协议类型
    return (setsockopt(sockfd, my_family_to_level(grp->sa_family),
                       MCAST_JOIN_GROUP, &req, sizeof(req)));
//第一部分:加入一个多播组:IP无关套接字//

#else       //默认用了这个

//第二部分:加入一个多播组:IPv4套接字//
    switch (grp->sa_family)
    {
         case AF_INET:
             struct     ip_mreq     mreq;       //多播组地址+ifreq结构
             struct     ifreq       ifreq;      //接口名称+union(地址, 目的地址...)

             //填充多播地址
             memcpy(&mreq.imr_multiaddr,
                    &((const SA_IN *) grp)->sin_addr,
                    sizeof(struct in_addr));

             //通过接口索引或者接口名字获取接口地址!
             //接口地址是主要的.
             if (ifindex > 0)
             {
                  if (if_indextoname(ifindex, ;ifreq.ifr_name) == NULL)
                  {
                      errno = ENXIO;        //6, no such device or address
                      DEBUG;
                      printf("errno = ENXIO!\n");
                      return(-1);
                  }

                  goto doioctl;     //转成名字了, 跳下去执行
             }
             else if (ifname != NULL)
             {
                  //复制名字到ifreq结构
                  strncpy(ifreq.ifr_name, ifname, IFNAMSIZ);
                  
doioctl:
                  //请求返回与接口名称关联的单播地址
                  if (ioctl(sockfd, SIOCGIFADDR, &ifreq) < 0)
                  {
                       DEBUG;
                       printf("ioctl error!\n");    //+
                       return (-1);
                  }

                  //复制单播地址到ip_mreq结构的imr_interface成员
                  memcpy(&mreq.imr_interface,
                         &((SA_IN *) &ifreq.ifr_addr)->sin_addr,
                         sizeof(struct in_addr));
             }
             else
             {
                  //如果接口索引和接口名字都没给定, 
                  //则用INADDR_ANY告知内核去选择接口
                  mreq.imr_interface.s_addr = htonl(INADDR_ANY);
             }

            //加入多播组
             return (setsockopt(sockfd, IPPROTO_IP,
                                IP_ADDR_MEMBERSHIP,
                                &mreq, sizeof(mreq)));

//第二部分:加入一个多播组:IPv4套接字//

//第三部分:加入一个多播组:IPv6套接字//
#ifdef  IPV6
         case AF_INET6:
             struct ipv6_mreq   mreq6;

             memcpy(&mreq6, ipv6mr_multiaddr,
                    &((const SA_IN6 *) grp)->sin6_addr,
                    sizeof(struct in6_addr));

             if (ifindex > 0)
             {
                  mreq6.ipv6mr_interface = ifindex;
             }
             else if (ifname != NULL)
             {
                  if ((mreq6.ipv6mr_interface
                              = if_nametoindex(ifname)) == 0)
                  {
                      errno = ENXIO;
                      DEBUG;
                      printf("#errno = ENXIO!\n");  //+
                      return (-1);
                  }
             }
             else
             {
                  mreq6.ipv6mr_interface = 0;
             }

             return(setsockopt(sockfd, IPPROTO_IPV6,
                               IPV6_JOIN_GROUP,
                               &mreq6, sizeof(mreq60)));
#endif

         default:
             errno = EAFNOSUPPORT;  //97: address family not supported by protocol
             DEBUG;
             printf("errno = EAFNOSUPPORT!\n");
             return (-1);
    }

#endif
}

//第三部分: 加入一个多播组:IPv6套接字//
