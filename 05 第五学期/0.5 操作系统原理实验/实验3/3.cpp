#include <bits/stdc++.h>  // 引入C++标准库头文件，包含了常用的标准库，如iostream, vector等
using namespace std;

typedef struct
{
    int add;    // 起始地址
    int size;   // 内存块大小
    int status; // 状态：0表示未分配，1表示已分配
} EMP;  // 未分配区说明表

typedef struct
{
    string name;  // 作业名
    int add;      // 起始地址
    int size;     // 内存块大小
    int status;   // 状态：0表示未分配，1表示已分配
} USE;  // 已分配区说明表

const int N = 1000;  // 定义常量N，表示最大内存块数目
EMP emp_list[N];     // 未分配区的内存块数组
USE use_list[N];     // 已分配区的内存块数组
int add = 60;        // 用户的起始地址
int sz = [[濮撳悕宸茶劚鏁廬宸茶劚鏁廬0;        // 默认大小

// 初始化未分配区
void EMPinit()
{
    emp_list[1] = {add, sz, 1};  // 初始化第一个未分配区，起始地址为add，大小为sz，状态为1（已分配）
    for (int i = 2; i < N; i++)  // 其余未分配区的状态为0
        emp_list[i].status = 0;
}

// 初始化已分配区
void USEinit()
{
    for (int i = 1; i < N; i++)  // 设置所有已分配区的状态为0（未分配）
        use_list[i].status = 0;
}

// 打印显示未分配区和已分配区信息
void show()
{
    cout << "未分配区说明表\n";
    for (int i = 1; i < N; i++)  // 遍历未分配区
    {
        auto& t = emp_list[i];
        if (t.status)  // 如果区块已分配，显示信息
            cout << i << " 始址:" << t.add << " 长度" << t.size << "\n";
    }
    cout << "\n";

    cout << "已分配区说明表\n";
    for (int i = 1; i < N; i++)  // 遍历已分配区
    {
        auto& t = use_list[i];
        if (t.status)  // 如果区块已分配，显示信息
            cout << "作业名:" << t.name << " 始址:" << t.add << " 长度" << t.size << "\n";
    }
    cout << "\n";
}
int m=5;
// 检查是否存在过小的碎片
void check()
{
    for (auto t : emp_list)
        if (t.size < m)  // 如果内存块小于m，则视为碎片并标记为未分配
            t.status = 0;
}

// 合并空闲区
void merge(int emp_sum, int tsz, string name)
{
    int use_sum = 0;
    for (int i = 1; i < N; i++)  // 计算已分配区的总大小
    {
        auto& p = use_list[i];
        if (p.status)
            use_sum += p.size;
    }
    EMPinit();  // 重新初始化未分配区
    emp_list[1] = {add + use_sum + tsz, emp_sum - tsz, 1};  // 设置新的空闲区
    int last = add;
    for (int i = 1; i < N; i++)  // 遍历已分配区，调整内存块的地址
    {
        auto& p = use_list[i];
        if (p.status)
        {
            p.add = last;
            last = p.add + p.size;
        }
    }

    for (int i = 1; i < N; i++)  // 找到一个未分配区，将其分配
    {
        auto& p = use_list[i];
        if (!p.status)
        {
            p.status = 1;
            p.size = tsz;
            p.add = last;
            p.name = name;
            break;
        }
    }
}

// 首次适用分配算法
void allocate_frist()
{
    string name;
    int tsz;
    cout << "输入分配空间的作业名和所需空间的大小\n";
    cin >> name >> tsz;  // 用户输入作业名和所需空间大小
    int emp_sum = 0;
    for (int i = 1; i < N; i++)  // 遍历未分配区
    {
        auto& t = emp_list[i];
        if (t.status)
        {
            if (t.size >= tsz)  // 找到足够大的空闲区
            {
                for (int j = 1; j < N; j++)  // 将空闲区分配给作业
                {
                    auto& p = use_list[j];
                    if (!p.status)
                    {
                        p.status = 1;
                        p.add = t.add;
                        p.size = tsz;
                        p.name = name;
                        if (t.size == tsz)  // 如果完全分配，标记空闲区为空闲
                            t.status = 0;
                        else
                        {
                            t.add += tsz;
                            t.size -= tsz;
                        }
                        break;
                    }
                }
                return;
            }
            emp_sum += t.size;
        }
    }

    cout << "无法直接分配\n";
    if (emp_sum >= tsz)  // 如果总的空闲区足够大，则进行合并
        merge(emp_sum, tsz, name);
    else
        cout << "合并之后仍无法分配\n";
}

// 比较函数，按地址升序排序
bool cmp(EMP e1, EMP e2)
{
    return e1.add < e2.add;
}

// 最佳适应算法的比较函数，按内存块大小升序排序
bool cmp2(EMP e1, EMP e2)
{
    return e1.size < e2.size;
}

// 最差适应算法的比较函数，按内存块大小降序排序
bool cmp3(EMP e1, EMP e2)
{
    return e1.size > e2.size;
}

// 最佳适应算法
void allocate_best()
{
    string name;
    int tsz;
    cout << "输入分配空间的作业名和所需空间的大小\n";
    cin >> name >> tsz;
    int emp_sum = 0;
    sort(emp_list + 1, emp_list + N - 1, cmp2);  // 按照最佳适应算法的策略对空闲区进行排序

    for (int i = 1; i < N; i++)  // 遍历空闲区
    {
        auto& t = emp_list[i];
        if (t.status)
        {
            if (t.size >= tsz)  // 找到足够大的空闲区
            {
                for (int j = 1; j < N; j++)  // 将空闲区分配给作业
                {
                    auto& p = use_list[j];
                    if (!p.status)
                    {
                        p.status = 1;
                        p.add = t.add;
                        p.size = tsz;
                        p.name = name;
                        if (t.size == tsz)  // 如果完全分配，标记空闲区为空闲
                            t.status = 0;
                        else
                        {
                            t.add += tsz;
                            t.size -= tsz;
                        }
                        break;
                    }
                }
                return;
            }
            emp_sum += t.size;
        }
    }
    cout << "无法直接分配\n";
    if (emp_sum >= tsz)  // 如果总的空闲区足够大，则进行合并
        merge(emp_sum, tsz, name);
    else
        cout << "合并之后仍无法分配\n";
}

// 最差适应算法
void allocate_worst()
{
    string name;
    int tsz;
    cout << "输入分配空间的作业名和所需空间的大小\n";
    cin >> name >> tsz;
    int emp_sum = 0;
    sort(emp_list + 1, emp_list + N - 1, cmp3);  // 按照最差适应算法的策略对空闲区进行排序

    for (int i = 1; i < N; i++)  // 遍历空闲区
    {
        auto& t = emp_list[i];
        if (t.status)
        {
            if (t.size >= tsz)  // 找到足够大的空闲区
            {
                for (int j = 1; j < N; j++)  // 将空闲区分配给作业
                {
                    auto& p = use_list[j];
                    if (!p.status)
                    {
                        p.status = 1;
                        p.add = t.add;
                        p.size = tsz;
                        p.name =name;
						if(t.size==tsz) t.status=0;
						else 
						{
							t.add+=tsz;
							t.size-=tsz;
						}
						break;
					}
				}
				return ;
			}
			emp_sum+=t.size;
		}
	}
	cout<<"无法直接分配\n";
	if(emp_sum>=tsz) merge(emp_sum,tsz,name);
	else cout<<"合并之后仍无法分配\n";
	
}
//回收 
void callback()
{
	string name;
	cin>>name;
	for(int i=1;i<N;i++)
	{
		auto &p=use_list[i];
		if(p.status&&p.name==name)
		{
			int down=p.add;
			int up=p.add+p.size;
			p.status=0;//已分配分区，status变成0 
			int fd=0;//下届是否相邻 
			int fu=0;//上届是否相邻
			for(int j=1;j<N;j++)
			{
				auto &t=emp_list[j];
				if(t.add+t.size==down) fd=j;
				if(t.add==up) fu=j;
			}
			
			if(fu&&fd)
			{
				emp_list[fd].size+=p.size+emp_list[fu].size;
				emp_list[fu].status=0;
			}else if(fu)
			{
				emp_list[fu].add-=p.size;
				emp_list[fu].size+=p.size;
			}
			else if(fd)
			{
				emp_list[fd].size+=p.size;
			}
			else//再开一个 
			{
				for(int j=1;j<N;j++)
				{
					if(!emp_list[j].status)
					{
						emp_list[j].status=1;
						emp_list[j].add=p.add;
						emp_list[j].size=p.size;
						break;
					}
				}
				sort(emp_list,emp_list+N-1,cmp);//保持顺序 
			}
			return ;
		}
	}
	cout<<"没有找到该进程\n";
}
void menu()
{
	cout<<"0 退出\n";
	cout<<"1 分配\n";
	cout<<"2 回收\n";
	cout<<"3 显示\n";
}
void solve()
{
	EMPinit();
	USEinit();
 	char op;
    while(1)
	{
		menu();
        cin>>op;
        if(op=='0') break;
        else if(op=='1') allocate_frist();
		else if(op=='2') callback();
        else if(op=='3') show();
    }
}
/*
1
a 100
1
b 50
1
c 30

3

2
b

3

1
f 60
3

0
*/
int main()
{
//	ios::sync_with_stdio(0);
//	cin.tie(0);cout.tie(0);
	int T=1;
	while(T--) solve();
} 
