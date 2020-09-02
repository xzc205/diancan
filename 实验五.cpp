#include <stdio.h>
#include <stdlib.h>
#include <string.h> 
#define MAXSIZE 50
int max=0;
int count;
typedef char ElemType;
typedef struct BiTNode{//�������Ķ�������洢��ʾ 
	ElemType data;
	struct BiTNode *lchild,*rchild;//���Һ���ָ�� 
}BiTNode,*BiTree;
typedef struct SQueue{//���еĵ�������洢��ʾ 
	BiTree *base;
	int front;
	int rear;
}Squeue;
void InitBiTree(BiTree *BT)//����ն����� 
{
	*BT=NULL;
}
void PreCreatBiTree(BiTree *BT)//���򴴽������� 
{
	ElemType ch;
	printf("��������:\n");
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
void PreOrderTraverse(BiTree BT)//������� 
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
void InOrderTraverse(BiTree BT)//������� 
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
void PostOrderTraverse(BiTree BT)//������� 
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
void InitQueue(Squeue *Q)//��ʼ������ 
{
	(*Q).base=(BiTree *)malloc(sizeof(BiTNode)*MAXSIZE);
	(*Q).front=(*Q).rear=0;
}
void EnQueue(Squeue *Q,BiTree BT)//����� 
{
	(*Q).base[(*Q).rear++]=BT;
}
int EmptyQueue(Squeue Q)//�ж϶����Ƿ����� 
{
	if(Q.front==Q.rear)
		return 1;
	return 0;
}
void Dequeue(Squeue *Q,BiTree *pt)//������ 
{
	if((*Q).front==(*Q).rear)
		return;
	*pt=(*Q).base[(*Q).front];
	(*Q).front=((*Q).front +1) % MAXSIZE;
}
void leverTraverse(BiTree BT)//��ηǵݹ���� 
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
void NRPreOrderTraverse(BiTree BT)//����ǵݹ����Ϊ 
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
int BiTreedepth(BiTree BT,int depth)//������� 
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
int LeafNumber(BiTree BT)//Ҷ�ӽ����Ŀ 
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
int singleBiTree(BiTree BT)//����֧�����Ŀ 
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
int doubleBiTree(BiTree BT)//˫��֧�����Ŀ 
{
	int book=0;
	if(!BT)
		return 0;
	if(BT->lchild && BT->rchild)
		book=1;
	return book+doubleBiTree(BT->lchild)+doubleBiTree(BT->rchild);
}
void revoluteBiTree(BiTree *BT)//���������� 
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
		printf("\n��ѡ��:\n");
		printf("0. ���򴴽���������#����ս��\n");
		printf("1. �������\n");
		printf("2. �������\n");
		printf("3. �������\n");
		printf("4. �ǵݹ��α���\n");
		printf("5. �ǵݹ��������\n");
		printf("6. �������߶�\n");
		printf("7. Ҷ�����Ŀ\n");
		printf("8. ����֧�����Ŀ\n");
		printf("9. ˫��֧�����Ŀ\n");
		printf("10. ����������\n");
		printf("������Ҫִ�еĲ�����\n");
		scanf("%d",&S);
		switch(S)
		{
			case 0:
				printf("���򴴽���������#����ս��\n");
				PreCreatBiTree(&BT);
				break;
			case 1:
				printf("\n�������Ϊ:\n");
				PreOrderTraverse(BT);
				break;
			case 2:
				printf("\n�������Ϊ:\n");
				InOrderTraverse(BT);
				break;
			case 3:
				printf("\n�������Ϊ:\n");
				PostOrderTraverse(BT);
				break;
			case 4:
				printf("\n��ηǵݹ����Ϊ:\n");
				leverTraverse(BT);
				break;
			case 5:
				printf("\n����ǵݹ����Ϊ:\n");
				NRPreOrderTraverse(BT);
				break;
			case 6:
				printf("\n�߶�Ϊ:   ");
				BiTreedepth(BT,1);
				printf("%d\n",max);
				break;
			case 7:
				printf("\nҶ�����ĿΪ: ");
				tmp=LeafNumber(BT);
				printf("%d\n",tmp);
				break;
			case 8:
				printf("\n����֧�����ĿΪ: ");
				tmp=singleBiTree(BT);
				printf("%d\n",tmp);
				break;
			case 9:
				printf("\n˫��֧�����ĿΪ: ");
				tmp=doubleBiTree(BT);
				printf("%d\n",tmp);
				break;
			case 10:
				printf("\n����������\n");
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
