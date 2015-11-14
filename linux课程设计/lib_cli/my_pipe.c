/*==============================================================================\
* Copyright(C)2015 Chudai.
*
* File name    : my_pipe.c
* Version      : v1.0.0
* Author       : ����
* Date         : 2015/08/26
* Description  :
* Function list: 1.my_pipe();
*                2.
*                3.
* History      :
\*==============================================================================*/

#include "my.h"

/*==============================================================================\
* Function   (����): my_pipe();
* Description(����):
* Called By  (����): 1.
* Calls list (����): 1.pipe();
* Input      (����): 1.
* Output     (���): 1.
* Return     (����):
*         success  :
*         error    :
* Others     (����): 1.
\*==============================================================================*/
void my_pipe(int *fds)
{
     if (pipe(fds) < 0)
     {
         err_sys("pipe error");
     }
}
