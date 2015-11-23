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
    int **temp_graph = graph;

    //输入数据
    for (i = 0; i < v_num; i++)
    {
        for (j = 0; j < v_num; j++)
        {
             scanf("%d", &temp_graph[i][j]);

             if (temp_graph[i][j] != 0 && temp_graph[i][j] != 1)
             {
                 printf("输入数据不为0或1!\n");
                 exit(1);
             }

             if (temp_graph[i][j] == 1)
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
             if(temp_graph[i][j] != temp_graph[j][i])
             {
                 printf("输入的图有错!\n");
                 exit(1);
             }
         }
    }

/*
    /////debug
    printf("\n");
    for (i = 0; i < v_num; i++)
    {
         for (j = 0; j < v_num; j++)
         {
             printf("%d ", temp_graph[i][j]);
         }
         printf("\n");
    }
*/
    edge_num /= 2;      ////

    return edge_num;
}
