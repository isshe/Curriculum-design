#include "my_malloc.h"
#include "my_security.h"
#include "my_req.h"

#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>

int **my_malloc(int n, int m);

int security(int n, int m, int *available, int **need, int **allocation);

int main(void)
{
	int n = 0;
	int m = 0;
	int *all = NULL; 			//总资源
	int **max = NULL; 			//最大需求资源
	int **allocation = NULL; 	//已经分配的资源
	int i = 0;
	int j = 0;
	int k = 0;
	int *available = NULL;		//当前时刻的可利用资源向量available
	int **need = NULL; 			//还需要资源矩阵need
//	int *temp_all = NULL;
	int flag = 0;
	int *req = NULL;
	int **pre_alloc = NULL; 	//用于预分配
	int p_num = 0; 				//接受返回的进程号
	
	printf("输入进程个数：");
	scanf("%d", &n);
	printf("输入资源个数：");
	scanf("%d", &m);
	
	//分配一维数组all
	if ((all = (int *)malloc(m *sizeof(int))) == NULL)
	{
		perror("malloc all error");
		exit(1);
	}
	//availabel
	if ((available = (int *)malloc(m *sizeof(int))) == NULL)
	{
		perror("malloc available error");
		exit(1);
	}
	//分配一维数组req
	if ((req = (int *)malloc(m *sizeof(int))) == NULL)
	{
		perror("malloc req error");
		exit(1);
	}

	//分配2维数组 max
	max = my_malloc(n, m);

	//分配2维数组 allocation
	allocation = my_malloc(n, m);

	//分配2维数组 need
	need = my_malloc(n, m);
	
	//分配2维数组pre_alloc
	pre_alloc = my_malloc(n, m);

	printf("输入每类资源的最大数量：\n");
	for (i = 0; i < m; i++)
	{
		scanf("%d", all+i);
	}
	
	printf("输入进程的最大需求矩阵：\n");
	for (i = 0; i < n; i++)
	{
		for (j = 0; j < m; j++)
		{
			scanf("%d", &max[i][j]);
			///
		}
		
		for (k = 0; k<m; k++)
		{
			if(max[i][k] > all[k])
			{
				printf("输入有误！%d > %d\n", max[i][k], all[k]);
				exit(1); 		//
			}
		}
		
	}

	printf("输入进程的已分配资源矩阵：\n");
	for (i = 0; i < n; i++)
	{
		for (j = 0; j < m; j++)
		{
			scanf("%d", &allocation[i][j]);
			///
		}
		
		//这里有问题！！！判断是否有误还要再想。
		for (k = 0; k<m; k++)
		{
			if(allocation[i][k] > max[i][k])
			{
				printf("输入有误！%d > %d\n", allocation[i][k], max[i][k]);
				exit(1); 		//
			}
		}
		
	}
	
	//计算并输出系统当前时刻的可利用资源向量available
	for(i = 0; i < m; i++)
	{
		available[i] = all[i];
	}
	for (i = 0; i < n; i++)
	{
		for (j = 0; j < m; j++)
		{
			available[j] = available[j] - allocation[i][j];
			if (available[j] < 0)
			{
				printf("可用资源不足\n");
				exit(1);
			}	
		}	
	}
	printf("当前时刻的可利用资源:\n");	
	for (i = 0; i < m; i++)
	{
		printf("%d ", available[i]);
	}
	printf("\n");
	
	//计算并输出当前时刻n个进程的还需要资源矩阵need
	for (i = 0; i < n; i++)
	{
		for (j = 0; j < m; j++)
		{
			need[i][j] = max[i][j] - allocation[i][j];
		}
	}
	printf("当前时刻n个进程的还需要资源:\n");
	for (i = 0; i < n; i++)
	{
		printf("p%d: ", i);
		for (j = 0; j < m; j++)
		{
			printf("%d ", need[i][j]);
		}
		printf("\n");
	}
	
	if (security(n, m, available, need, allocation) == 1)
	{
		printf("初始状态安全!\n");
	}
	else
	{
		printf("初始状态不安全!\n");
	}
	
	//把已分配赋给预分配数组
	for (i = 0; i < n; i++)
	{
		for (j = 0; j < m; j++)
		{
			pre_alloc[i][j] = allocation[i][j];
		}
	}
	
	
	while (1)
	{
		//下面输入资源请求, 判断可行性和合理性
		if ((p_num = my_req(n, m, need, available, req)) == -1)
		{
			continue;
		} 			
		//预分配predistribution, available数组和need数组要相应的减。
		for (i = 0; i < m; i++)
		{
			pre_alloc[p_num][i] = req[i] + allocation[p_num][i];
			available[i] -= req[i];
			need[p_num][i] -= req[i];
//			printf("%d ", available[i]);
		}
//		printf("\n");
		
		//判断是否安全
		//如果安全则分配并显示分配成功， 否则不分配并显示不安全。
		if (security(n, m, available, need, pre_alloc) == 1)
		{
			printf("此次资源分配安全!\n");
			
			//更新已分配资源数组
			for (i = 0; i < m; i++)
			{
				allocation[p_num][i] = pre_alloc[p_num][i];
			}
		}
		else
		{
			printf("此次资源分配不安全!取消分配!\n");
			for (i = 0; i < m; i++)
			{
				pre_alloc[p_num][i] = allocation[p_num][i];
				available[i] += req[i];
				need[p_num][i] += req[i];
			}
		}
		
		
	}
	//hai yao free!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
	
	return 0;
}

