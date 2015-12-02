/*==============================================================================\
* Copyright(C)2015 Chudai.
*
* File name    : family_to_level.c
* Version      : v1.0.0
* Author       : ����
* Date         : 2015/08/27
* Description  :
* Function list: 1.family_to_level();
*                2.
*                3.
* History      :
\*==============================================================================*/

#include "my.h"


/*==============================================================================\
* Function   (����): family_to_level()
* Description(����): ����Э�����Ӧ��.......IPP....
* Called By  (����): 1.mcast_join();
* Calls list (����): 1.
* Input      (����): 1.family;
* Output     (���): 1.IPPROTO_IP; IPPROTO_IPV6
* Return     (����):
*         success  :
*         error    : -1
* Others     (����): 1.
\*==============================================================================*/
int family_to_level(int family)
{
     switch(family)
     {
         case AF_INET:
             return IPPROTO_IP;
#ifdef  IPV6
         case AF_INET6:
             return IPPROTO_IPV6;
#endif
         default:
             return -1;
     }
}

int my_family_to_level(int family)
{
     int    rc = 0;

     if ( (rc = family_to_level(family)) < 0 )
     {
         err_sys("family_to_level error");
     }

     return (rc);
}
