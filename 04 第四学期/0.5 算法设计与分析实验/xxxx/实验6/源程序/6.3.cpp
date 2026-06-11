#include <bits/stdc++.h>
using namespace std;
int x,y,sx,sy,ex,ey,s,e,n,m,c;
int a[10][10];// 网格，用于标记障碍物
pair<int,int>pre[10][10];// 前驱节点，用于记录路径
int dis[10][10];// 距离数组，记录起点到每个节点的最短距离
int dx[]={0,0,-1,1};// 四个方向的x偏移量
int dy[]={-1,1,0,0};// 四个方向的y偏移量
void bfs(int nx,int ny)
{
	// 最小堆，存储当前距离和对应的坐标
	priority_queue<pair<int,pair<int,int>>,vector<pair<int,pair<int,int>>>,greater<pair<int,pair<int,int>>>>pq;
	pq.push({0,{nx,ny}});
	dis[nx][ny]=0;// 起点到自己的距离为0
	pre[nx][ny]={-1,-1};// 起点没有前驱节点
	while(!pq.empty())
	{
		auto tp=pq.top();// 取出堆顶元素
		pq.pop();
		int d=tp.first;// 当前距离
		int x=tp.second.first;// 当前节点的x坐标
		int y=tp.second.second;// 当前节点的y坐标
		if(d>dis[x][y]) continue;// 如果当前距离大于已知的最短距离，则跳过
		for(int i=0;i<4;i++)// 遍历四个方向
		{
			int nx=x+dx[i];
			int ny=y+dy[i];
			if(nx<1||nx>n||ny<1||ny>n||a[nx][ny]==1) continue;// 检查新位置是否在网格范围内以及是否是障碍物
			if(d+1<dis[nx][ny]) // 分枝操作：如果通过当前节点到达新位置的距离更短，则更新
			{
				dis[nx][ny]=d+1;// 更新距离
				pq.push({d+1,{nx,ny}});// 将新位置推入优先队列
				pre[nx][ny]={x,y};// 更新前驱节点
			}
		}
	}
	cout<<dis[ex][ey]<<"\n";// 输出终点的最短距离
	vector<pair<int,int>>path;
	for(pair<int,int>at={ex,ey};at!=make_pair(-1,-1);at=pre[at.first][at.second]) path.push_back(at);// 回溯路径
	reverse(path.begin(),path.end());// 反转路径，使其从起点到终点
	cout<<"path:"; // 输出路径
	for(auto i:path) cout<<"("<<i.first<<","<<i.second<<")";
}

int main()
{
	cin>>n>>m>>c;// 读取网格大小和障碍物数量
	for(int i=1;i<=n;i++) for(int j=1;j<=m;j++) dis[i][j]=INT_MAX; // 初始化距离数组
	while(c--)  // 读取障碍物位置
	{
		cin>>x>>y;
		a[x][y]=1;// 标记障碍物
	}
	cin>>sx>>sy>>ex>>ey; // 读取起点和终点
	bfs(sx,sy);
}
/*
7 7
14
1 3
1 4
2 4
3 5
4 4
4 5
5 1
5 5
6 1
6 2
6 3
7 1
7 2
7 3
3 2 4 6
*/
