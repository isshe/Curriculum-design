/*==============================================================================\
* Copyright(C)2015 Chudai.
*
* File name    : test_input.c
* Version      : v1.0.0
* Author       : 初代
* Date         : 2015/11/15
* Description  : 看如何输入一个图
* Function list: 1.
*                2.
*                3.
* History      :
\*==============================================================================*/

#include <stdio.h>
#include <stdlib.h>


int main(void)
{
    int i = 0;
    int j = 0;
    int a = 0;
    int b = 0;
    int **g_array = NULL;

    printf("输入一个图的顶点个数:");
    scanf("%d", &a);

    printf("输入图的邻接矩阵:\n");

    g_array = (int **)malloc(a*sizeof(int*));

    for (i = 0; i < a; i++)
    {
        g_array[i] = (int *)malloc(a*sizeof(int));
    }

    for (i = 0; i < a; i++ )
    {
        for (j = 0; j < a; j++)
        {
            scanf("%d", (*(g_array+i)+j));
//            printf("%d ", *(*(g_array+i)+j));
        }
    }

    for ( i = 0; i < a; i++ )
    {
        for (j = 0; j < a; j++)
        {
             printf("%d ", g_array[i][j]);
        }
        printf("\n");
    }

    return 0;

}
