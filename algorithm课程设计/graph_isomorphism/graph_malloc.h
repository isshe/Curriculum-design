/*==============================================================================\
* Copyright(C)2015 Chudai.
*
* File name    : graph_malloc.h
* Version      : v1.0.0
* Author       : 初代
* Date         : 2015/11/23
* Description  :
* Function list: 1.
*                2.
*                3.
* History      :
\*==============================================================================*/

#ifndef GRAPH_MALLOC_H
#define GRAPH_MALLOC_H

//#include "main.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//分配图的内存
int **graph_malloc(int v_num);

//分配度的内存
int *degree_malloc(int v_num);


#endif
