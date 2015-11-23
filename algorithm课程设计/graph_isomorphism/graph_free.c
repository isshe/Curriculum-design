/*==============================================================================\
* Copyright(C)2015 Chudai.
*
* File name    : graph_free.c
* Version      : v1.0.0
* Author       : 初代
* Date         : 2015/11/23
* Description  :
* Function list: 1.
*                2.
*                3.
* History      :
\*==============================================================================*/


#include "graph_free.h"

void graph_free(int **graph, int *degree, int v_num)
{
     int i = 0;
     
     //释放图
     for (i = 0; i < v_num; i++)
     {
          free(graph[i]);
     }
     free(graph);
     
     //释放度
     free(degree);
}
