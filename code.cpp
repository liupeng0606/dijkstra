//主要使用dijkstra算法

#include<iostream>
#include<queue>
#include<cstring>
#include<stdio.h>
using namespace std;
typedef long long ll;
ll INF=1e18;
const int N=505;
bool vis[N];//记录结点i是否被访问 
ll dist[N];//记录最短路径
ll sum[N];//sum[i]记录最短路径中以i结尾的连续小路的长度和 
struct Edge{//边 
	int v,t;//到结点v的距离为w ,t是道路的类型 
	ll w;
	Edge(int v,int w,int t):v(v),w(w),t(t){}
}; 
struct Node{
	int u;//结点的编号，源点到结点的最短距离 
	ll w;
	Node(){}
	Node(int u,ll w):u(u),w(w){}
	bool operator<(const Node &a)const//使用优先队列，因此把小于重载为大于含义 
	{
		return w>a.w;
	} 
};
vector<Edge>g[N];//图的邻接表形式 
 
void dijkstra(int s,int n)
{
	priority_queue<Node>q;
	memset(vis,false,sizeof(vis));
	memset(sum,0,sizeof(sum));
	for(int i=1;i<=n;i++)
	  dist[i]=INF;
	dist[0]=dist[s]=0;
	q.push(Node(s,0));
	while(!q.empty()){
		Node e=q.top();
		q.pop();
		int u=e.u;
		if(!vis[u]){//如果此结点没有被访问 
			vis[u]=true;
			int num=g[u].size();//与结点u相连的结点个数 
			for(int i=0;i<num;i++){//如果结点已经访问了就跳过 
			    int v=g[u][i].v;
				if(vis[v])
				  continue;
				ll cost=0;
				if(g[u][i].t){//如果u到i是小道 
				  ll temp=sum[u]+g[u][i].w;
				  cost=dist[u]-sum[u]*sum[u]+temp*temp;
			    }
				else
				  cost=dist[u]+g[u][i].w;
				if(cost<dist[v]){//如果距离比原来小就更新 
					dist[v]=cost;
					//更新最短路中以i结尾的连续小路长度 
					if(g[u][i].t)
					  sum[v]=sum[u]+g[u][i].w;
					else
					  sum[v]=0;
					q.push(Node(v,cost));
				}
			}
		}
	}
}
 
int main()
{
	int n,m,t,a,b,c;
	scanf("%d%d",&n,&m);
	while(m--){
		scanf("%d%d%d%d",&t,&a,&b,&c);
		g[a].push_back(Edge(b,c,t));
		g[b].push_back(Edge(a,c,t));
	}
	dijkstra(1,n);
	printf("%lld\n",dist[n]);
	return 0;
}
