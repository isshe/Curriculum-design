/*==============================================================================\
* Copyright(C)2015 Chudai.
*
* File name    : graph_rand.c
* Version      : v1.0.0
* Author       : 初代
* Date         : 2015/11/22
* Description  :
* Function list: 1.
*                2.
*                3.
* History      :
\*==============================================================================*/

#include "graph_rand.h"

int graph_rand(int **graph, int v_num)
{
    int **temp_graph = graph;       //注意这里!
    int i = 0;
    int j = 0;
    int k = 0;
    int flag = 0;
    int rand_num = v_num;           //存图的秩

    for (i = 0; i < v_num-1; i++)
    {
         for (j = i+1; j < v_num; j++)
         {
             for (k = 0; k < v_num; k++)
             {
                 if (temp_graph[i][k] != temp_graph[j][k])
                 {
                     flag = 1;
                     break;
                 }
             }

             if ((flag == 0) && (k == v_num))       //这里k要注意!
             {
                rand_num--;        //行相同,秩减一
             }

             flag = 0;
         }
    }

    printf("秩为:%d\n", rand_num);

    return rand_num;
}

