#include <stdio.h>
#include <stdlib.h>
#define N [[濮撳悕宸茶劚鏁廬宸茶劚鏁廬//图的顶点个数 
typedef enum{DG,DN,UDG,UDN}GraphKind;//有向图，有向网，无向图，无向网
typedef struct ArcNode
{
	int adjvex;//该弧指向顶点位置
	struct ArcNode *nextarc;//指向下一条弧的指针  
}ArcNode;
typedef struct VNode
{
	int data;//图的顶点信息 
	ArcNode *firstarc;//指向第一条邻接该顶点（以该顶点为弧尾）的弧的指针 
}VNode,Adjlist[N];//最多N个顶点 
typedef struct{
	Adjlist vertices;
	int vexnum,arcnum;//图的顶点数、弧数 
	GraphKind kind;//图的种类标志 
}ALGraph;//邻接表 
void CreateDG(ALGraph *G)
{
	int i,j,k;
	ArcNode *s;
	G->kind=DG;
	puts("分别输入顶点数和弧数:");
	scanf("%d %d",&G->vexnum,&G->arcnum);
	puts("输入顶点信息，从0开始，编号连续:");	
    for(int i=0;i<G->vexnum;i++)
    {
    	scanf("%d",&G->vertices[i].data);
    	G->vertices[i].firstarc=NULL;
	}
	printf("输入%d条弧，弧的信息格式:顶点信息，顶点信息\n",G->arcnum);
	for(k=0;k<G->arcnum;k++)
	{
		scanf("%d %d",&i,&j);
		s=(ArcNode*)malloc(sizeof(ArcNode));
		s->adjvex=j;
		s->nextarc=G->vertices[i].firstarc;
		G->vertices[i].firstarc=s;
	}
}
int InDegree(ALGraph G,int v)
{
	if(v>=G.vexnum||v<0) return -1;
	//如果顶点编号越界，返回 -1 表示异常情况
	int cnt=0;//初始化入度计数器
	for(int i=0;i<G.vexnum;i++)
	//遍历所有顶点，查找是否有指向该顶点的边
	{
	    ArcNode *p=G.vertices[i].firstarc;
		//获取第 i 个顶点的第一条边
	    while(p)
	    {
		    if(p->adjvex==v) cnt++;
			//如果找到一条边指向目标顶点 v，则增加入度计数
		    p=p->nextarc;//继续检查下一条边
	    }	
	}
	return cnt;//返回顶点 v 的入度
}
int OutputDegree(ALGraph G,int v)
{
	if(v>=G.vexnum||v<0) return -1; 
	//如果顶点编号越界，返回 -1 表示异常情况
	int cnt=0;// 初始化出度计数器
	ArcNode *p=G.vertices[v].firstarc;//获取目标顶点 v 的第一条边
	while(p)
	{
		cnt++;//每找到一条边，增加出度计数
		p=p->nextarc;//继续检查下一条边
	}
	return cnt;//返回顶点 v 的出度
}
int main()
{
	ALGraph G;
	CreateDG(&G);
	for(int i=0;i<G.vexnum;i++)
	printf("顶点%d的入度和出度为:%d %d\n",i,InDegree(G,i),OutputDegree(G,i));
}
