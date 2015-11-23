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
    int flag2 = 0;
    int rand_num = v_num;           //存图的秩

    //计算相等且不为0的行
    //计算前n行中为0的行
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

                 //用于判断为0的行
                 if (temp_graph[i][k] > 0)
                 {
                     flag2 = 1;
                 }
             }

             //行不全为0, 但相同
             if ((flag == 0) && (flag2 == 1) &&(k == v_num))//这里k要注意!
             {
                rand_num--;        //行相同,秩减一
             }
             else if ((flag2 == 0) &&(k == v_num))  //整行为0
             {
                rand_num--;       //空行
                
             }
//             printf("shishi %d\n", rand_num);
             flag = 0;
             flag2 = 0;
         }
    }

    //判断图的最后一行是否全为0
    flag2 = 0;
    for (k = 0; k < v_num; k++)
    {
        if(temp_graph[i][k] > 0)
        {
            flag2 = 1;
        }
    }

    if (flag2 == 0 && k == v_num)
    {
        rand_num--;
    }

//    printf("秩为:%d\n", rand_num);

    return rand_num;
}

