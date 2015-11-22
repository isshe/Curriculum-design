/*==============================================================================\
* Copyright(C)2015 Chudai.
*
* File name    : graph_input.c
* Version      : v1.0.0
* Author       : 初代
* Date         : 2015/11/22
* Description  :
* Function list: 1.
*                2.
*                3.
* History      :
\*==============================================================================*/

#include "graph_input.h"

int graph_input(int **graph, int v_num)
{
    int i = 0;
    int j = 0;
    int edge_num = 0;

    //输入数据
    for (i = 0; i < v_num; i++)
    {
        for (j = 0; j < v_num; j++)
        {
             scanf("%d", &graph[i][j]);

             if (graph[i][j] != 0 || graph[i][j] != 1)
             {
                 printf("输入有误!请重输此位!\n");
                 j--;                               //退一位
                 continue;
             }

             if (graph[i][j] == 1)
             {
                 edge_num++;            //再想想!
             }
        }
    }


    //判断输入是否有错
    for (i = 0; i < v_num; i++)
    {
         for (j = 0; j < v_num; j++)
         {
             if(graph[i][j] != graph[j][i])
             {
                 printf("输入的图有错!\n");
                 return 0;
             }
         }
    }

    edge_num /= 2;      ////

    return edge_num;
}
