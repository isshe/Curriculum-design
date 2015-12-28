
#include "my_req.h"

#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>


int my_req(int n, int m, int **need, int *available, int *req) 	//req是值-结果参数
{
	int p_num = 0;  			
	int *temp_req = req;
	int i = 0;
	

	
	printf("下面输入一次资源请求\n");
	printf("请输入资源请求的进程号: ");
	scanf("%d", &p_num);
	
	printf("请输入资源请求向量: \n");
	for (i = 0; i < m; i++)
	{
		scanf("%d", &temp_req[i]);
	}
	
	//判断合理性:请求是否小于进程的need向量
	for (i = 0; i < m; i++)
	{
		if (temp_req[i] > need[p_num][i])
		{
			printf("合理性不符合要求！\n");
			return -1; 						//不用exit是为了下一次输入
		}
	}
	printf("资源请求合理！\n");
	
	//判断可行性请求是否小于系统当前可用资源向量
	for (i = 0; i < m; i++)
	{
		if (temp_req[i] > available[i])
		{
			printf("可行性不符合要求！\n");
			return -1;
		}
	}
	printf("资源请求可行!\n");
	
	return p_num;
	
}


