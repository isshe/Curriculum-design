/*==============================================================================\
* Copyright(C)2015 Chudai.
*
* File name    : graph_degree.c
* Version      : v1.0.0
* Author       : 初代
* Date         : 2015/11/22
* Description  :
* Function list: 1.
*                2.
*                3.
* History      :
\*==============================================================================*/


#include "graph_degree.h"

static int
compare(const void *a, const void *b)
{
    return *(int *)b - *(int *)a;
}


void graph_degree(int **graph, int *degree, int v_num)
{
    //求度
    int i = 0;
    int j = 0;
    int degree_num = 0;
    int **temp_graph = graph;
    int *temp_degree = degree;

    for (i = 0; i < v_num; i++)
    {
        for (j = 0; j < v_num; j++)
        {
            if (temp_graph[i][j] == 1)
            {
                 degree_num++;
            }
        }
        temp_degree[i] = degree_num;
        degree_num =0;
    }

    //排序
    qsort(temp_degree, v_num, sizeof(int), compare);

    //试试输出
    printf("测试一下排序后的度: \n");
    for (i = 0; i < v_num; i++)
    {
         printf("%d ", temp_degree[i]);
    }
    printf("\n");

}
