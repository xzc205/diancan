#include <stdio.h>
#include <stdlib.h>
#include <time.h>
typedef struct{
	int i,j;
	int v;
}Triple;
typedef struct{
	Triple data[100];
	int mu,nu,tu;
}TSMatrix;
int m,n;
int  createSMatrix(int X[10][10])
{
	int k,h,num=0;
	srand(time(NULL)); 
	scanf("%d %d",&m,&n);
	for(k=1;k<=m;k++){
		for(h=1;h<=n;h++){
			if(rand()%10>7){
				X[k][h]=rand()%50;
				num++;
			}
			else
				X[k][h]=0;
		}
	}	
	return num;
}
TSMatrix ConversionTSMatrix(int x[10][10],TSMatrix T)//矩阵转换成三元顺序表 
{
	int k,h,e=1;
	for(k=1;k<=T.mu;k++){
		for(h=1;h<=T.nu;h++){
			if(x[k][h]!=0){
				T.data[e].i=k;
				T.data[e].j=h;
				T.data[e].v=x[k][h];
				e++;
			}	
		}
	}
	return T;
}
TSMatrix AddSMtrix(TSMatrix M,TSMatrix T)//两个三元顺序表相加 
{
	TSMatrix C;
	C.mu=M.mu;	C.nu=M.nu;
	C.tu=0;
	int row,add,pa=1,pb=1,pc=1;
	for(row=1;row<=M.mu;row++){
		while(M.data[pa].i<row&&pa<=M.tu)
			pa++;
		while(T.data[pb].i<row&&pb<=T.tu)
			pb++;	
		while(M.data[pa].i==row&&T.data[pb].i==row&&pb<=M.tu&&pb<=T.tu){
			if(M.data[pa].j==T.data[pb].j){
				add=M.data[pa].v+T.data[pb].v;
				if(add){
					C.data[pc].i=row;
					C.data[pc].j=M.data[pa].j;
					C.data[pc].v=add;
					pa++;	pb++;	pc++;
				}
			}
			else if(M.data[pa].j>T.data[pb].j){
				C.data[pc].i=row;
				C.data[pc].j=T.data[pb].j;
				C.data[pc].v=T.data[pb].v;
				pb++;	pc++;
				}
				else {
					C.data[pc].i=row;
					C.data[pc].j=M.data[pa].j;
					C.data[pc].v=M.data[pa].v;
					pa++;	pc++;
				}
			}
		while(M.data[pa].i==row&&pa<=M.tu){
			C.data[pc].i=row;
			C.data[pc].j=M.data[pa].j;
			C.data[pc].v=M.data[pa].v;
			pa++;	pc++;	
		}
		while(T.data[pb].i==row&&pb<=T.tu){
			C.data[pc].i=row;
			C.data[pc].j=T.data[pb].j;
			C.data[pc].v=T.data[pb].v;
			pb++;	pc++;
		}
	}
	C.tu=pc-1;
	return C;
}
TSMatrix FastSMattrix(TSMatrix M,TSMatrix T)//快速转置 
{
	int col,cpot[10],num[10];
	int t,p,q;
	T.mu=M.nu;	T.nu=M.mu;	T.tu=M.tu;
	if(T.tu){
		for(col=1;col<=M.nu;++col)
			num[col]=0;
		for(t=1;t<=M.tu;++t)	
			++num[M.data[t].j];
		cpot[1]=1;
		for(col=2;col<=M.nu;++col)
			cpot[col]=cpot[col-1]+num[col-1];
		for(p=1;p<=M.tu;++p)
		{
			col=M.data[p].j;		q=cpot[col];
			T.data[q].i=M.data[p].j;	T.data[q].j=M.data[p].i;
			T.data[q].v=M.data[p].v;	++cpot[col];
		}
	}
	return T;
}
void zhSMatrix(TSMatrix T,int c[10][10])//三元顺序表转换成稀疏矩阵 
{
	int k,h,p,e=1;
	for(k=1;k<=T.mu;k++){
		for(h=1;h<=T.nu;h++){
			if(T.data[e].i==k&&T.data[e].j==h){
			
				c[k][h]=T.data[e].v;
				e++;
			}
			}
	}
}
void printSMatrix(int X[10][10])
{
	int k,h;
	for(k=1;k<=m;k++){
		for(h=1;h<=n;h++){
			printf("%3d",X[k][h]);
		}
		printf("\n");
	}	
	printf("\n");
}
void printfSq(TSMatrix T)
{
	int k;
	printf("\ni j v");
	printf("\n%d %d %d",T.mu,T.nu,T.tu);	
	printf("\n\n");
	for(k=1;k<=T.tu;k++){
		printf("%d %d %d\n",T.data[k].i,T.data[k].j,T.data[k].v);
	}
}
int main()
{
	TSMatrix A,A1,B,B1,C;
	int Num;
	int a[10][10],b[10][10],c[10][10]={0},a1[10][10]={0},b1[10][10]={0};
	printf("输入系数矩阵A的行数和列数:");
	Num=createSMatrix(a);
	A.mu=m,A.nu=n;A.tu=Num;
	
	A=ConversionTSMatrix(a,A);
	printf("输入系数矩阵B的行数和列数:");
	Num=createSMatrix(b);
	B.mu=m,B.nu=n;B.tu=Num;
	B=ConversionTSMatrix(b,B);
	
	C=AddSMtrix(A,B);
	
	A1=FastSMattrix(A,A1);
	B1=FastSMattrix(B,B1);
	
	zhSMatrix(C,c);
	zhSMatrix(A1,a1);
	zhSMatrix(B1,b1);
	printf("稀疏矩阵A:\n");
	printSMatrix(a);
	printf("稀疏矩阵B:\n");
	printSMatrix(b);
	printf("相加后的稀疏矩阵C:\n");
	printSMatrix(c);
	printf("稀疏矩阵A的转置矩阵:\n");
	printSMatrix(a1);
	printf("稀疏矩阵B的转置矩阵:\n");
	printSMatrix(b1);
	printf("稀疏矩阵A的三元顺序表:");
	printfSq(A);
	printf("稀疏矩阵B的三元顺序表:");
	printfSq(B);
	printf("稀疏矩阵A的转置三元顺序表:");
	printfSq(A1);
	printf("稀疏矩阵B的转置三元顺序表:");
	printfSq(B1);
	printf("A和B相加得到的C的三元顺序表:");
	printfSq(C);
	return 0;
}

