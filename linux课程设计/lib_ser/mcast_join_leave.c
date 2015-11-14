/*==============================================================================\
* Copyright(C)2015 Chudai.
*
* File name    : mcast_join.c
* Version      : v1.0.0
* Author       : ����
* Date         : 2015/08/26
* Description  : ����һ���ಥ��
* Function list: 1.
*                2.
*                3.
* History      :
\*==============================================================================*/

#include "my.h"
//#include "mcast_join_leave.h"
//#include <net/if.h>


/*******************************************************************************
 * ������: mcast_join()
 * ����: ����һ���ಥ��
 * ����˵��: 
 *      1.ifname: �ӿ�����
 *      2.ifindex:�ӿ�����
 *      3.
 * ����:
 ******************************************************************************/

//��һ����:����һ���ಥ��:IP�޹��׽���//
int mcast_join(int sockfd, const SA *grp, socklen_t grplen,
               const char *ifname, u_int ifindex)
{
#ifdef  MCAST_JOIN_GROUP        //�����ʱ���ֹ�ָ��?

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

    //Ϊ�˷�ֹ���渴�Ƶ�ʱ�����, �ȼ���С
    if (grplen > sizeof(req.gr_group))
    {
         errno = EINVAL;    //22, invalid argument
         DEBUG;
         printf("#errno = EINVAL!\n");
         return (-1);
    }

    memcpy(&req.gr_group, grp, grplen);

    //setsockoptִ�м������
    //my_family_to_level����ȷ��Э������
    return (setsockopt(sockfd, my_family_to_level(grp->sa_family),
                       MCAST_JOIN_GROUP, &req, sizeof(req)));
//��һ����:����һ���ಥ��:IP�޹��׽���//

#else       //Ĭ���������

//�ڶ�����:����һ���ಥ��:IPv4�׽���//
    switch (grp->sa_family)
    {
         case AF_INET:
             struct     ip_mreq     mreq;       //�ಥ���ַ+ifreq�ṹ
             struct     ifreq       ifreq;      //�ӿ�����+union(��ַ, Ŀ�ĵ�ַ...)

             //���ಥ��ַ
             memcpy(&mreq.imr_multiaddr,
                    &((const SA_IN *) grp)->sin_addr,
                    sizeof(struct in_addr));

             //ͨ���ӿ��������߽ӿ����ֻ�ȡ�ӿڵ�ַ!
             //�ӿڵ�ַ����Ҫ��.
             if (ifindex > 0)
             {
                  if (if_indextoname(ifindex, ;ifreq.ifr_name) == NULL)
                  {
                      errno = ENXIO;        //6, no such device or address
                      DEBUG;
                      printf("errno = ENXIO!\n");
                      return(-1);
                  }

                  goto doioctl;     //ת��������, ����ȥִ��
             }
             else if (ifname != NULL)
             {
                  //�������ֵ�ifreq�ṹ
                  strncpy(ifreq.ifr_name, ifname, IFNAMSIZ);
                  
doioctl:
                  //���󷵻���ӿ����ƹ����ĵ�����ַ
                  if (ioctl(sockfd, SIOCGIFADDR, &ifreq) < 0)
                  {
                       DEBUG;
                       printf("ioctl error!\n");    //+
                       return (-1);
                  }

                  //���Ƶ�����ַ��ip_mreq�ṹ��imr_interface��Ա
                  memcpy(&mreq.imr_interface,
                         &((SA_IN *) &ifreq.ifr_addr)->sin_addr,
                         sizeof(struct in_addr));
             }
             else
             {
                  //����ӿ������ͽӿ����ֶ�û����, 
                  //����INADDR_ANY��֪�ں�ȥѡ��ӿ�
                  mreq.imr_interface.s_addr = htonl(INADDR_ANY);
             }

            //����ಥ��
             return (setsockopt(sockfd, IPPROTO_IP,
                                IP_ADDR_MEMBERSHIP,
                                &mreq, sizeof(mreq)));

//�ڶ�����:����һ���ಥ��:IPv4�׽���//

//��������:����һ���ಥ��:IPv6�׽���//
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

//��������: ����һ���ಥ��:IPv6�׽���//
