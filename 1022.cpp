#include<stdio.h>
#include<malloc.h>
#include<stdlib.h>
#include<string.h>
typedef struct Polynode{
	int coef;  //系数 
	int expn;	//指数 
	struct Polynode *next;
}polynode,*list;
void Initlist(list *L)
{
	(*L)=(list)malloc(sizeof(struct Polynode));
	(*L)->next=NULL;
	//return 1; 
}

void creatlist(list L)
{
	
	int xsz=0,zsz=0;
	list p,tail;
	tail=L;
	printf("按指数值从小到大输入多项式的系数值，指数值。系数值为零时结束输入\n");
	scanf("%d %d",&xsz,&zsz);
	while (xsz!=0)
	{
		p=(list)malloc(sizeof(struct Polynode));
		p->coef=xsz;
		p->expn=zsz;
		p->next=NULL;
		p->next=L->next;
		L->next=p;
		//tail->next=p;
		//tail=p;
		scanf("%d %d",&xsz,&zsz); 
	}
	
}
int  addlist(list Q,list P,list *R)
{
	list p,q,r,pr;
	(*R)=(list)malloc(sizeof(struct Polynode));
	(*R)->next=NULL;
	q=Q->next;
	p=P->next;
	r=(*R);
	while(p!=NULL&&q!=NULL)
	{
		if(q->expn<p->expn)
		{
			pr=(list)malloc(sizeof(struct Polynode));
			pr->next=NULL;
			pr->coef=q->coef;
			pr->expn=q->expn;
			r->next=pr;
			r=pr;
			q=q->next;
		}
		else if(q->expn==p->expn)
			{
				int sum;
				sum=q->coef+p->coef;
				if(sum!=0)
				{
					pr=(list)malloc(sizeof(struct Polynode));
					pr->next=NULL;
					pr->coef=sum;
					pr->expn=q->expn;
					r->next=pr;
					r=pr;
				}
				q=q->next;
				p=p->next;
			}
		else if(q->expn>p->expn)
			{
				pr=(list)malloc(sizeof(struct Polynode));
				pr->next=NULL;
				pr->coef=p->coef;
				pr->expn=p->expn;
				r->next=pr;
				r=pr;
				p=p->next;
			}
		
	}
	if(q)
	{
		pr->next=q;
	}
	else if(p){
		pr->next=p;
	}
}
void reducelist(list *P)
{
	list p;
	p=(*P)->next;
	while(p!=NULL)
	{
		p->coef=-(p->coef);
		p=p->next;
	}
	
}
void reverse (list *L){//多项式逆置 
	list p,q,r;
	p=(*L);
	q=p->next;
	p->next=NULL; 
	while(q){
		r=q->next;
		q->next=p->next;
		p->next=q;
		q=r;
		if(r)
			r=r->next;
	}

}
void printlist(list L)
{
	list p;
	p=L->next;	
	while (p!=NULL)
	{
		if(p->expn!=0)
			printf("%dX^%d",p->coef,p->expn);
		else
			printf("%d",p->coef);
		if(p->next!=NULL)
			printf("+");
		p=p->next;
	 } 
}
void printlist1(list L)
{
	list p;
	p=L->next;
	while(p!=NULL)
	{
		if(p->coef>=0)
			printf("+");
		printf("%dX^%d",p->coef,p->expn);	
		p=p->next;	
	}
}
int main()
{
	list Q,P,R;
//	la=NULL;
	Initlist(&Q);
	Initlist(&P);
//	Initlist(&R);
	printf("输入Q:\n"); 
	creatlist(Q);
	printf("输入P:\n"); 
	creatlist(P);
	addlist(Q,P,&R);
	printf("\nP:  ");
	printlist(Q);
	printf("\nQ:  ");
	printlist(P);
	printf("\nP+Q:  ");
	printlist(R);
	reducelist(&P);
	addlist(Q,P,&R);
	printf("\nP-Q:  ");
	printlist1(R);
	printf("\nP-Q逆置:"); 
	reverse(&R);
	printlist1(R);
	return 0;	
}
