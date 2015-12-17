/*
实验内容：
编程实现银行家算法中的安全性检查子算法，要求：
(1) 本程序要能描述n个并发进程共享m类资源，在某一时刻的资源分配状态；n、m自定，但都不能小于3；
(2) 本程序功能：
① 联机输入：系统拥有的每类资源的最大数量all、n个进程的最大需求矩阵max、当前时刻n个进程的已分配资源矩阵allocation；
② 如果①中出现不合理的输入，直接检查指出，并不进行后续步骤，程序结束；
③ 计算并输出系统当前时刻的可利用资源向量available；
④ 计算并输出当前时刻n个进程的还需要资源矩阵need；
⑤ 根据安全性检查算法，判定当前系统状态是否安全，输出检查结论。

注意：
(1) 这里所指的“不合理的输入”是：某进程对某资源的最大需求大于系统拥有该类资源的最大数量；某进程在某类资源上，已分配资源大于它的最大需求等。
(2) 这个算法是“银行家算法”的子算法，其中用到的数据结构必须采用与银行家算法相同的数据结构(见教材)，以方便下次实验使用


设计、运行程序，观察并记录运行结果。运行时的输入数据，应该包含合理输入和不合理输入两种情况。

*/


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
		perror("malloc all error");
		exit(1);
	}

	//分配2维数组 max
	max = my_malloc(n, m);

	//分配2维数组 allocation
	allocation = my_malloc(n, m);

	//分配2维数组 need
	need = my_malloc(n, m);

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
		printf("safe!\n");
	}
	else
	{
		printf("unsafe!\n");
	}
	
	//hai yao free!!!!!
	
	return 0;
}


int **my_malloc(int n, int m)
{
	int i = 0;
    int **temp = NULL;

    
    //分配图
    temp = (int **) malloc(n *sizeof(int *));
    if (temp == NULL)
    {
        printf("分配错误1!\n");
        exit(1);
    }
    
    for (i = 0; i < n; i++)
    {
        temp[i] = (int *) malloc(m * sizeof(int));
        if (temp[i] == NULL)
        {
            printf("分配错误2!\n");
            exit(1);
        }
    }
    
    return temp;
}

int security(int n, int m, int *available, int **need, int **allocation)
{
	int *work = NULL;
	int *finish = NULL;
	int i = 0;
	int j = 0;
	int k = 0;
	int num = 0;
	
	//分配一维数组work
	if ((work = (int *)malloc(m *sizeof(int))) == NULL)
	{
		perror("malloc all error");
		exit(1);
	}
	
	//分配一维数组finish
	if ((finish = (int *)malloc(n *sizeof(int))) == NULL) //zhu yi shi n!!!
	{
		perror("malloc all error");
		exit(1);
	}
	
	//chu shi hua
//	printf("keyong :");
	for (i = 0; i < m; i++)
	{
		work[i] = available[i];
//		printf("%d ", work[i]);
//		finish[i] = 0; 				//zhe ge keyi yong memset;
	}
//	printf("\n");
//	memset(finish, 0, n);
	for (i = 0; i < n; i++)
	{
		finish[i] = 0;
	}
	
//	flag = 0;
	printf("sequence:\n");	
	for (i = 0; i < n; i++)
	{
		if (finish[i] == 0) 		//0 dai biao false
		{
			for (j = 0; j < m; j++)
			{
				if (need[i][j] <= work[j])
				{
					num++;
				}
				else
				{
					break;
				}
			}	
			
			if (num == m)
			{
				num = 0;
				printf("p%d: ", i);
				for (k = 0; k < m; k++)
				{
					work[k] = work[k] + allocation[i][k];
					printf("%d ", work[k]);
				}
				printf("\n");
				finish[i] = 1;
				i = -1; 				//zai cong tou kai shi , zhuyi !!!!!!!
			}		     
			else
			{
				continue;
			}                                                                                    
		}
		else 
		{
			continue;
		}
	}
	
	for (i = 0; i < n; i++)
	{
		if (finish[i] != 1)
		{
//			printf("bu anquan\n");
			return 0; 				//bu an quan 
		}
	}
	
//	printf("anquan\n");
	return 1; 						//an quan 

}


