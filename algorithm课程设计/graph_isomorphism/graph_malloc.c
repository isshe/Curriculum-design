/*==============================================================================\
* Copyright(C)2015 Chudai.
*
* File name    : graph_malloc.c
* Version      : v1.0.0
* Author       : 初代
* Date         : 2015/11/23
* Description  :
* Function list: 1.
*                2.
*                3.
* History      :
\*==============================================================================*/


#include "graph_malloc.h"

//分配图的内存
int **graph_malloc(int v_num)
{
    int i = 0;
    int **temp_graph = NULL;

    
    //分配图
    temp_graph = (int **) malloc(v_num *sizeof(int *));
    if (temp_graph == NULL)
    {
        printf("图内存分配错误: 一!\n");
        exit(1);
    }
    
    for (i = 0; i < v_num; i++)
    {
        temp_graph[i] = (int *) malloc(v_num * sizeof(int));
        if (temp_graph[i] == NULL)
        {
            printf("图内存分配错误: 二!\n");
            exit(1);
        }
    }
    
    return temp_graph;
    
}

//分配度的内存
int *degree_malloc(int v_num)
{
    int *temp_degree = NULL;
    //分配度
    temp_degree = (int *)malloc(v_num *sizeof(int));
    if (temp_degree == NULL)
    {
        printf("度内存分配错误!\n");
        exit(1);
    }
    
    return temp_degree;
    
//    graph = temp_graph;
//    degree = temp_degree;
}



