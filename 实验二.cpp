#include <stdio.h>
#include<stdlib.h> 
#include<malloc.h>
#define LIST_INIT_SIZE    10
#define LISTINCREMENT   10
#define OK  1

typedef struct Polynode{
	int coef;  //系数 
	int expn;	//指数 
	struct Polynode *next;
}polynode,*list;
