#include <stdio.h>
#include <stdlib.h>
#define stack_init_size 100
#define stackincrement 10
#define LIST_INIT_SIZE 100//线性表存储空间的初始分配量 
#define LISEINCREMENT 10//线性表存储空间的分配增量 
#define OK 1
#define ERROR -1
typedef char SElemType;
typedef struct stu1{
	SElemType *base;
	SElemType *top;
	int stacksize;
}SqStack;
int initstack(SqStack &s)
{
	s.base=(SElemType *)malloc(stack_init_size *(sizeof(SElemType)));
	s.top=s.base;
	s.stacksize=stack_init_size;
	return OK;
}
int gettop(SqStack s,SElemType &e)
{
	if(s.top==s.base)
		return ERROR;
	e=*(s.top-1);
	return OK;
}
int push(SqStack &s,SElemType e) 
{
	if(s.top-s.base >= s.stacksize)
	{
		s.base=(SElemType *)realloc(s.base,(s.stacksize+stackincrement)*sizeof(SElemType));
		s.top=s.base+stackincrement;
		s.stacksize+=stackincrement;
	}
	*s.top++=e;
	return OK;
}
int pop(SqStack &s,SElemType &e)//取出 
{
	if(s.top==s.base) return ERROR;
	e=*--s.top;
	return OK;
}
char pre(char e,char c)
{


char prior[8][8]={{'>','>','<','<','<','>','>'},
{'>','>','<','<','<','>','>'},
{'>','>','>','>','<','>','>'},
{'>','>','>','>','<','>','>'},
{'<','<','<','<','<','=',' '},
{'>','>','>','>',' ','>','>'},
{'<','<','<','<','<',' ','='}};
	int i,j;			
	char s[7]={'+','-','*','/','(',')','#'};
	for(i = 0; i < 7; i++){
		for( j = 0; j < 7; j++){
				if(e == s[i] && c == s[j])
					return prior[i][j];
			}
		}
}
int in(char c)
{
	char s[8]={'+','-','*','/','(',')','#'};
	int i;
	for(i=0;i<7;i++)
	{
		if(c==s[i])
			return 0;
	}
	return 1;	
}
char js(char a,char b,char c)
{
	int aa,bb;
	aa=a-'0';
	bb=b-'0';
	switch(c)
	{
		case '+':
			aa=aa+bb;
			break;
		case '-':
			aa=aa-bb;
			break;
		case '*':
			aa=aa*bb;
			break;
		case '/':
			aa=aa/bb;
			break;
		default :
			printf("eorr");
	}
	c=aa+'0';
	return c;
}
char op(SqStack &la,SqStack &lc)
{
	char ch;
	char e;
	char theta;
	char a,b;
	initstack(la); push(la,'#');
	initstack(lc); ch=getchar();
	gettop(la,e);

	while(ch!='#'||e!='#')
	{
		if(in(ch)==1) 
		{
			push(lc,ch);
			ch=getchar();
		}
		else
		{
			gettop(la,e);
			switch (pre(e,ch))
			{
				case '<' :
					push(la,ch);
					ch=getchar();
					break;
				case '=' :
					pop(la,e);
					ch=getchar();
					break;
				case '>' :
					pop(la,theta);
					pop(lc,b);
					pop(lc,a);
					e=js(a,b,theta);
					push(lc,e);
					break;
			} 
		}
		
		gettop(la,e);
	}
	gettop(lc,e);
	
	return e;
}

int main()
{
	
	char e;
	int x;
	SqStack la,lc;
	initstack(la);
	initstack(lc);
	printf("输入表达式以#结束输入："); 
	e=op(la,lc);
	x=e-'0';
	printf("%d",x);
	
	return 0;
 } 
