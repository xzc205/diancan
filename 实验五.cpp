#include <stdio.h>
#include <stdlib.h>
#include <string.h> 
#define MAXSIZE 50
int max=0;
int count;
typedef char ElemType;
typedef struct BiTNode{//二叉树的二叉链表存储表示 
	ElemType data;
	struct BiTNode *lchild,*rchild;//左右孩子指针 
}BiTNode,*BiTree;
typedef struct SQueue{//队列的单向链表存储表示 
	BiTree *base;
	int front;
	int rear;
}Squeue;
void InitBiTree(BiTree *BT)//构造空二叉树 
{
	*BT=NULL;
}
void PreCreatBiTree(BiTree *BT)//先序创建二叉树 
{
	ElemType ch;
	printf("输入数据:\n");
	getchar();
	ch=getchar();
	if(ch=='#')
		*BT=NULL;
	else
	{
		*BT=(BiTree)malloc(sizeof(BiTNode));
		(*BT)->data=ch;
		PreCreatBiTree(&(*BT)->lchild);
		PreCreatBiTree(&(*BT)->rchild);
	}
}
void PreOrderTraverse(BiTree BT)//先序遍历 
{
	if(BT)
	{
		if(!(BT->data))
			return;
		printf("%c",BT->data);
		PreOrderTraverse(BT->lchild);
		PreOrderTraverse(BT->rchild);
	}
}
void InOrderTraverse(BiTree BT)//中序遍历 
{
	if(BT)
	{
		if(!(BT->data))
			return;
		InOrderTraverse(BT->lchild);
		printf("%c",BT->data);
		InOrderTraverse(BT->rchild);
	}
}
void PostOrderTraverse(BiTree BT)//后序遍历 
{
	if(BT)
	{
		if(!(BT->data))
			return;
		PostOrderTraverse(BT->lchild);
		PostOrderTraverse(BT->rchild);
		printf("%c",BT->data);
	}
}
void InitQueue(Squeue *Q)//初始化队列 
{
	(*Q).base=(BiTree *)malloc(sizeof(BiTNode)*MAXSIZE);
	(*Q).front=(*Q).rear=0;
}
void EnQueue(Squeue *Q,BiTree BT)//入队列 
{
	(*Q).base[(*Q).rear++]=BT;
}
int EmptyQueue(Squeue Q)//判断队列是否已满 
{
	if(Q.front==Q.rear)
		return 1;
	return 0;
}
void Dequeue(Squeue *Q,BiTree *pt)//出队列 
{
	if((*Q).front==(*Q).rear)
		return;
	*pt=(*Q).base[(*Q).front];
	(*Q).front=((*Q).front +1) % MAXSIZE;
}
void leverTraverse(BiTree BT)//层次非递归遍历 
{
	Squeue Q;
	BiTree pt=BT;
	InitQueue(&Q);
	EnQueue(&Q,pt);
	while(!EmptyQueue(Q))
	{
		Dequeue(&Q,&pt);
		printf("%c",pt->data);
		if(pt->lchild)
			EnQueue(&Q,pt->lchild);
		if(pt->rchild)
			EnQueue(&Q,pt->rchild);
	}
}
void NRPreOrderTraverse(BiTree BT)//先序非递归遍历为 
{
	BiTree pt=BT,stack[MAXSIZE];
	int top=0;
	while(pt || top)
	{
		if(pt)
		{
			printf("%c",pt->data);
			stack[top++]=pt;
			pt=pt->lchild;
		}
		else
		{
			pt=stack[--top];
			pt=pt->rchild;
		}
	}
}
int BiTreedepth(BiTree BT,int depth)//树的深度 
{
	if(BT)
	{
		if(BT->lchild)
			BiTreedepth(BT->lchild,depth+1);
		if(BT->rchild)
			BiTreedepth(BT->rchild,depth+1);
	}
	if(depth>max)
		max=depth;
	return depth;
}
int LeafNumber(BiTree BT)//叶子结点数目 
{
	if(!BT)
		return 0;
	else
	{
		if((!BT->lchild) && (!BT->rchild))
			return 1;
		else
			return LeafNumber(BT->lchild)+LeafNumber(BT->rchild);
	}
}
int singleBiTree(BiTree BT)//单分支结点数目 
{
	if(!BT)
		return 0;
	else
	{
		if(BT->lchild && !BT->rchild)
			return singleBiTree(BT->lchild)+1;
		else
		{
			if(!BT->lchild && BT->rchild)
				return singleBiTree(BT->lchild)+1;
			else
				return singleBiTree(BT->lchild)+singleBiTree(BT->rchild);
		}
	}
}
int doubleBiTree(BiTree BT)//双分支结点数目 
{
	int book=0;
	if(!BT)
		return 0;
	if(BT->lchild && BT->rchild)
		book=1;
	return book+doubleBiTree(BT->lchild)+doubleBiTree(BT->rchild);
}
void revoluteBiTree(BiTree *BT)//交换二叉树 
{
	BiTree T;
	if(!(*BT)->lchild && !(*BT)->rchild)
		return;
	else
	{
		T=(*BT)->lchild;
		(*BT)->lchild=(*BT)->rchild;
		(*BT)->rchild=T;
	}
	if((*BT)->lchild)
	{
		revoluteBiTree(&(*BT)->lchild);
	}
	if((*BT)->rchild)
	{
		revoluteBiTree(&(*BT)->rchild);
	}
}
int main()
{
	BiTree BT;
	int tmp;
	int flag=1,S;
	ElemType str[MAXSIZE];
	InitBiTree(&BT);
	while(flag)
	{
		printf("\n请选择:\n");
		printf("0. 先序创建二叉树用#代表空结点\n");
		printf("1. 先序遍历\n");
		printf("2. 中序遍历\n");
		printf("3. 后序遍历\n");
		printf("4. 非递归层次遍历\n");
		printf("5. 非递归先序遍历\n");
		printf("6. 二叉树高度\n");
		printf("7. 叶结点数目\n");
		printf("8. 单分支结点数目\n");
		printf("9. 双分支结点数目\n");
		printf("10. 交换二叉树\n");
		printf("请输入要执行的操作：\n");
		scanf("%d",&S);
		switch(S)
		{
			case 0:
				printf("先序创建二叉树用#代表空结点\n");
				PreCreatBiTree(&BT);
				break;
			case 1:
				printf("\n先序遍历为:\n");
				PreOrderTraverse(BT);
				break;
			case 2:
				printf("\n中序遍历为:\n");
				InOrderTraverse(BT);
				break;
			case 3:
				printf("\n后序遍历为:\n");
				PostOrderTraverse(BT);
				break;
			case 4:
				printf("\n层次非递归遍历为:\n");
				leverTraverse(BT);
				break;
			case 5:
				printf("\n先序非递归遍历为:\n");
				NRPreOrderTraverse(BT);
				break;
			case 6:
				printf("\n高度为:   ");
				BiTreedepth(BT,1);
				printf("%d\n",max);
				break;
			case 7:
				printf("\n叶结点数目为: ");
				tmp=LeafNumber(BT);
				printf("%d\n",tmp);
				break;
			case 8:
				printf("\n单分支结点数目为: ");
				tmp=singleBiTree(BT);
				printf("%d\n",tmp);
				break;
			case 9:
				printf("\n双分支结点数目为: ");
				tmp=doubleBiTree(BT);
				printf("%d\n",tmp);
				break;
			case 10:
				printf("\n交换二叉树\n");
				revoluteBiTree(&BT);
				break;
			default:
				flag=0;
				printf("Press any key to exit!\n");
				break;
		}
	}
	printf("\n");
	return 0;
}
