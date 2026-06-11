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
int visited[N]={0};
void DFS(ALGraph G,int v)//顶点v出发，深度优先遍历 
{
	ArcNode *w;
	visited[v]=1;
	printf("%3d",G.vertices[v].data);//输出顶点信息 
	//找顶点v的邻接点，若未访问，则从相应的邻接点出发深度遍历 
	for(w=G.vertices[v].firstarc;w;w=w->nextarc)
	if(!visited[w->adjvex]) DFS(G,w->adjvex); 
}
int DeleteDegree(ALGraph *G,int i,int j)
{
	ArcNode *p=(*G).vertices[i].firstarc,*pre=NULL,*t;//指针 
	if(!p) return 0;//顶点i的出度为0，无法删除
	while(p)//查找指向j的边 
	{
		if(p->adjvex==j)
		{
			if(pre) pre->nextarc=p->nextarc;//更新前一个节点的指针 
			else (*G).vertices[i].firstarc=p->nextarc;//更新第一个节点的指针 
			free(p);//删除边 
			G->arcnum--;
			return 1;//删除成功 
		}
		pre=p;
		p=p->nextarc;
	} 
	return 0;//删除失败 
} 
int main()
{
	/*
	5 7
	0 1 2 3 4
	0 1
	0 2
	1 2
	1 3
	2 3
	3 4
	4 0
	*/
	ALGraph G;
	CreateDG(&G);
	puts("输入你想要删除的弧的狐尾和弧头:");
	int i,j;
	scanf("%d %d",&i,&j);
	if(DeleteDegree(&G,i,j)==0) puts("删除失败，该弧不存在");
	else puts("删除成功");
	printf("顶点%d的邻接点：",i);
	ArcNode *p=G.vertices[i].firstarc;//获取 i 的第一条边
	while(p)
	{
		printf("%3d",p->adjvex);
		p=p->nextarc;
	}
}
