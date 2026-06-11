#include <bits/stdc++.h>
using namespace std;
// 定义进程控制块 (PCB) 结构体
struct PCB
{
    string pname;// 进程名
    int level;// 优先级（数值越大，优先级越高）
    int rtime;// 运行时间
    int status;// 进程状态：0 表示就绪，1 表示运行，2 表示阻塞
    int next; // 指向下一个 PCB 的索引
    // 重载比较运算符，用于检查进程名是否相等
    bool operator==(const string &other) const{
        return pname==other;
    }
    void print()
    {
    	cout<<"进程名："<<pname<<" 优先级："<<level<<" 运行时间："<<rtime<<" 状态："<<status;
    	if(status==0) cout<<"就绪";
        else if(status==1) cout<<"运行";
        else cout<<"阻塞";
        cout<<"\n";
	}
};
const int N=11;// 定义 PCB 数组的最大大小
PCB pcb[N];// 存储所有进程的 PCB 数组
int idx;// 当前 PCB 数组的索引（用于新建进程）
int st[3];// 队列头指针数组，st[0] 就绪队列头，st[2] 阻塞队列头
int running;// 当前运行进程的索引

// 将 PCB 插入指定队列（a 为 PCB 索引，q 为队列编号：0 就绪，2 阻塞）
void add(int a,int q)
{
	// 如果队列为空  设置队列头为当前 PCB 索引
    if(st[q]==-1) st[q]=a;
    else
    {
    	// 遍历队列，找到队尾并插入
        for(int i=st[q];~i;i=pcb[i].next)
        {
            if(pcb[i].next==-1)// 找到队尾
            {
                pcb[i].next=a;// 队尾指向新 PCB
                pcb[a].status=q;// 设置 PCB 状态为队列对应状态
                pcb[a].next=-1;// 设置新 PCB 的 next 为 -1
                return ;
            }
        }
    }
}


// 检查指定队列中是否存在指定进程名的 PCB
bool check(string s,int q)
{
    for(int i=st[q];~i;i=pcb[i].next)
    {
        if(pcb[i].pname==s) return true;
    } 
    return false;
}
// 创建新进程
void fcreate()
{
    string pname;
    puts("输入进程名:");
    while(cin>>pname)
    {
        if(check(pname,0)||check(pname,2)||pname==pcb[running].pname)
        {
            puts("进程名重复，请重新输入：");
            continue;
        }
        else break;
    }
    int level;
    int rtime;
    puts("输入优先级:");
    cin>>level;
    puts("输入运行时间:");
    cin>>rtime;
    // 初始化新进程的 PCB
    PCB newPCB;
    newPCB.pname=pname;
    newPCB.level=level;
    newPCB.rtime=rtime;
    newPCB.next=-1;
    newPCB.status=0;
    pcb[++idx]=newPCB;// 将新 PCB 添加到数组中
    add(idx,0);// 将新进程加入就绪队列
    puts("进程创建成功！");
}
// 显示当前队列和运行进程的状态
void fshow()
{
    puts("就绪队列：");
    for(int i=st[0];~i;i=pcb[i].next)
    {
        cout<<pcb[i].pname<<" ";
    }
    cout<<"\n";

    puts("正在运行的进程:");
    if(running>0) cout<<pcb[running].pname<<"\n";
    else cout<<"无\n";
    
    puts("阻塞队列:");
    for(int i=st[2];~i;i=pcb[i].next)
    {
        cout<<pcb[i].pname<<" ";
    }
    cout<<"\n";
}

//优先级调度 
void priority_scheduling()
{
	if(st[0]==-1)
	{
		cout<<"无就绪进程可供调度\n";
		return ;
	} 
	int mx=-1,target=-1,last=-1;
	for(int i=st[0],prev=-1;~i;prev=i,i=pcb[i].next)
	{
		if(pcb[i].level>mx)
		{
			mx=pcb[i].level;
			target=i;
			last=prev;
		}
	}
	
	if(target!=-1)
	{
		if(last==-1) st[0]=pcb[target].next;// 更新队头
		else pcb[last].next=pcb[target].next;// 删除目标进程
		pcb[target].print(); // 打印该进程的 PCB 内容（即进程信息）
		pcb[target].status=-1; // 撤销该进程的 PCB，将其状态标记为已结束
		running=0; // 更新运行进程为0（没有正在运行的进程）
		cout<<"进程： "<<pcb[target].pname<<" 执行完毕，已撤销PCB\n";
	}
}

//时间片调度
void round_robin_scheduling()
{
	if(st[0]==-1)
	{
		cout<<"无就绪进程可供调度\n";
		return ;
	} 
	
	for(int i=st[0];~i;i=pcb[i].next)
	{
		pcb[i].print();
	} 
	if(running!=0&&pcb[running].rtime>0)
	{
		pcb[running].rtime--;
		if(pcb[running].rtime<=0)
		{
			for(int i=st[0],prev=-1;~i;prev=i,i=pcb[i].next)
			{
				if(i==running)
				{
					if(prev==-1) st[0]=pcb[i].next;
					else pcb[prev].next=pcb[i].next;
					cout<<"进程 "<<pcb[i].pname<<" 执行完毕，已撤销 PCB\n";
					running=0;
					break;
				}
			}
		}
		
	}
	
} 

//先来先服务 
void FCFS()
{
	if(st[0]!=-1)
	{
		running=st[0];
		st[0]=pcb[st[0]].next;// 删除队列头部进程
		pcb[running].status=1;// 设置该进程为正在运行
	}
}


void table1()
{
    puts("0:返回主菜单");
    puts("1:优先级调度");
    puts("2:时间片轮转");
    puts("3:先来先服务");
}


void scheduler(char ip)
{    
    if(st[0]==-1)
    {
    	cout<<"无就绪进程调度\n";
    	return ;
	}
	if(ip=='1') priority_scheduling();
	else if(ip=='2') round_robin_scheduling();
	else if(ip=='3') FCFS();
}


 
// 阻塞一个正在运行的进程
void fblock()
{
    puts("输入进程名:");
    string s;
    cin>>s;

    if(check(s,0))
    {
        cout<<"该进程处于就绪状态\n";
        return ;
    }
    


    if(check(s,2))
    {
        cout<<"该进程处于阻塞状态\n";
        return ;
    }
    

    if(running==0||pcb[running].pname!=s)
    {
        cout<<"无此进程\n";
        return ;
    }
    
    add(running,2);// 将正在运行的进程加入阻塞队列
    
    running=0;// 当前无运行进程
    
    puts("进程阻塞成功！");
    
    if(st[0]!=-1) priority_scheduling(); 
}

// 唤醒一个阻塞的进程
void fwakeup()
{
    cout<<"输入进程名\n";
    string s;
    cin>>s;
    if(check(s,0))
    {
        cout<<"该进程处于就绪状态\n";
        return ;
    }

    if(pcb[running].pname==s) 
    {
        cout<<"该进程处于执行状态\n";
        return ;
    }

	for(int i=st[2],last=-1;~i;last=i,i=pcb[i].next)
	{
		if(pcb[i].pname==s)
		{
			if(last==-1) st[2]=pcb[i].next;
			else pcb[last].next=pcb[i].next;
			
					
			if(running==0) running=i;
			else if(pcb[i].level>pcb[running].level)
			{
				add(running,0);//如果新进程level更大，则抢占 
				running=i;
			}
			else add(i,0);
			
			puts("进程唤醒成功！");
			return ;
			
		}
	} 

   
    cout<<"无此进程\n";
}
// 终止进程
void fterminate()
{
    cout<<"输入要终止的进程名\n";
    string s;
    cin>>s;
     // 遍历就绪和阻塞队列，寻找目标进程
    for(int j=0;j<3;j+=2)
    {
    	for(int i=st[j],last=-1;~i;last=i,i=pcb[i].next)
		{
			if(pcb[i].pname==s)
			{
				if(last==-1) st[j]=pcb[i].next;
				else pcb[last].next=pcb[i].next;
				pcb[i].status=-1;
				puts("进程终止成功！");
				return ;
			}
		} 
    }
     // 检查是否是正在运行的进程
    if(pcb[running].pname==s)
    {
        pcb[running].status=-1;
        running=0;
        puts("进程终止成功！");
        return ;
    }
    cout<<"无此进程\n";
}

void table()
{
    puts("1:创建进程create");
    puts("2:阻塞进程block");
    puts("3:唤醒进程wakeup");
    puts("4:终止进程terminate");
    puts("5:显示状态show");
    puts("6:进程调度scheduler");
    puts("0:退出exit");
}

void solve()
{
    char input;
    st[0]=-1;
    st[2]=-1;
    running=0;
    while(table(),cin>>input)
    {
        if(input=='1') fcreate();
        else if(input=='2') fblock();
        else if(input=='3') fwakeup();
        else if(input=='4') fterminate();
        else if(input=='5') fshow();
        else if(input=='6') 
		{
			char input1;
			while(table1(),cin>>input1)
		    {
		        if(input1=='0') break;
		        else if(input1>='1'&&input1<='3') scheduler(input1);
		        else puts("输入有误，请重新输入");
		    }
		}
        else if(input=='0') break;
        else puts("输入有误，请重新输入");
    }
}
 
int main()
{
    int T=1;
    while(T--) solve();
}



/*
1
aaa
2
1

1
bbb
3
2

1
ccc
1
3

1
ddd
1
3


6
1
2
0
0
*/ 
