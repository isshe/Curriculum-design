
#include "my_security.h"
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>

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

