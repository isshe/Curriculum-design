
#include "my_malloc.h"
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>

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
