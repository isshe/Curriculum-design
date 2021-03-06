/*==============================================================================\
* Copyright(C)2015 Chudai.
*
* File name    : main.c
* Version      : v1.0.0
* Author       : 初代
* Date         : 2015/11/22
* Description  :
* Function list: 1.
*                2.
*                3.
* History      :
\*==============================================================================*/

#include "main.h"

int main(void)
{
     int **graph_a = NULL;  //指向a图
     int **graph_b = NULL;  //指向b图
     int *ga_degree = NULL; //指向"存储a图的度的数组"
     int *gb_degree = NULL; //指向"存储b图的度的数组"
     int va_num = 0;        //a图的顶点个数
     int vb_num = 0;        //b图的顶点个数
     int ea_num = 0;        //a图的边数
     int eb_num = 0;        //b图的边数
     int ga_rand = 0;       //a图的秩
     int gb_rand = 0;       //b图的秩
     int i = 0;


     printf("-----本程序判断两个无向图是否同构-----\n");

     printf("请输入第一个图的顶点数: ");
     scanf("%d", &va_num);

     printf("请输入第二个图的顶点数: ");
     scanf("%d", &vb_num);

     if (va_num != vb_num)
     {
          printf("不同构! 顶点数不相等!\n");
          return 0;
     }
/*
     ////////////////////////试试放在函数里//////////////
     //分配内存
     //第一个图
     graph_a = (int **)malloc(va_num * sizeof(int *));
     for (i = 0; i < va_num; i++)
     {
          graph_a[i] = (int *) malloc(va_num * sizeof(int));
     }

     //第一个图的度
     ga_degree = (int *)malloc(va_num * sizeof(int));

     //分配第二个图
     graph_b = (int **)malloc(vb_num * sizeof(int *));
     for (i = 0; i < vb_num; i++)
     {
          graph_b[i] = (int *) malloc(vb_num * sizeof(int));
     }

     //第二图的度
     gb_degree = (int *) malloc(vb_num *sizeof(int));

*/
     graph_a = graph_malloc(va_num);
     ga_degree = degree_malloc(va_num);
     graph_b = graph_malloc(vb_num);
     gb_degree = degree_malloc(vb_num);

     //输入数据(邻接矩阵) & 检查是否输入有误
     printf("输入第一个图的邻接矩阵:\n");
     ea_num = graph_input(graph_a, va_num);

     printf("输入第二个图的邻接矩阵:\n");
     eb_num = graph_input(graph_b, vb_num);

     //判断边数是否相等
     if(ea_num != eb_num)
     {
         printf("不同构! 边数不相等!\n");
         return 0;
     }

     //求两图每个点的度, 排序后判断每个顶点的度
     //ga_degree 是值-结果参数
     graph_degree(graph_a, ga_degree, va_num);
     graph_degree(graph_b, gb_degree, vb_num);

     //判断
     for (i = 0; i < va_num; i++)
     {
         if (ga_degree[i] != gb_degree[i])
         {
             printf("不同构! 各个顶点的度不对应!\n");
             return 0;
         }
     }



     //求矩阵的秩
     ga_rand = graph_rand(graph_a, va_num);
     gb_rand = graph_rand(graph_b, vb_num);

     //判断矩阵的4是否相等
     if (ga_rand != gb_rand)
     {
//         printf("%d %d\n", ga_rand, gb_rand);
         printf("不同构! 秩不相等!\n");
     }
     else
     {
          printf("同构!\n");
     }

/*
     //释放内存
     for (i = 0; i < va_num; i++)
     {
          free(graph_a[i]);
     }
     free(graph_a);
     free(ga_degree);

     for (i = 0; i < vb_num; i++)
     {
         free(graph_b[i]);
     }
     free(graph_b);
     free(gb_degree);
*/
     graph_free(graph_a, ga_degree, va_num);
     graph_free(graph_b, gb_degree, vb_num);
     
     return 0;


}
