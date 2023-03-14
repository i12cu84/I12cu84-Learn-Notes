#include <bits/stdc++.h>
#include <initializer_list>
#include <unordered_map>
#include <bits/stdc++.h>
#include <stdexcept>
#include <algorithm>
#include <iostream>
#include <string.h>
#include <stdio.h>
#include <fstream>
#include <sstream>
#include <cstdlib>
#include <cstring>
#include <cstdio>
#include <vector>
#include <memory>
#include <string>
#include <ctime>
#include <cmath>
#include <deque>
#include <list>
#include <map>
#include <cctype>

using namespace std;

/*
B3601 [图论与代数结构 201] 最短路问题_1

题目描述

给定一张 nnn 个点、mmm 条边的有向图，求 111 号点到每个点的最短路径长度。

注意，图可能存在重边和自环，保证不存在负环。
输入格式

第一行两个整数 n,mn, mn,m。

接下来 mmm 行，每行三个整数 ui,vi,wiu_i, v_i, w_iui?,vi?,wi?。表示一条从 uiu_iui? 到 viv_ivi? 长度为 wiw_iwi? 的有向边。
输出格式

一行 nnn 个整数，第 iii 个整数表示 111 到 iii 的最短路径长度，如果不存在从 111 到 iii 的路径则第 iii 个整数用 ?1-1?1 替代。
输入输出样例
输入 #1

4 5
1 2 1
2 3 4
1 3 3
4 1 5
3 1 2

输出 #1

0 1 3 -1

输入 #2

10 50
5 9 6
1 3 10
3 1 1
10 2 5
8 5 1
10 10 6
6 5 2
1 5 10
2 5 5
10 1 4
1 5 2
8 8 7
7 2 7
9 2 8
3 1 4
6 2 5
3 9 9
4 9 5
5 10 9
10 1 9
5 4 5
9 1 2
5 10 6
3 8 7
10 3 7
5 8 8
9 2 6
9 8 6
3 2 8
1 3 8
1 10 1
7 8 4
9 4 5
4 6 2
2 7 6
10 1 5
9 9 7
6 7 4
1 1 7
8 3 10
8 3 9
10 9 8
3 9 1
7 4 8
1 5 4
8 4 4
3 4 4
9 9 2
2 10 4
8 9 6

输出 #2

0 6 8 7 2 9 12 10 8 1

说明/提示

本题没有部分分。

对于所有数据，1≤n,m≤2×1031\leq n,m \leq 2\times 10^31≤n,m≤2×103，?109≤wi≤109-10^9\leq w_i\leq 10^9?109≤wi?≤109。

请注意答案上界的大小，可能需要使用 C++ 中的 long long int 类型。

code:
int n, m;
long long dis[2001];
struct P {
	int x, y, z;
} a[2001];
int main() {//有向图 贝尔曼-福特算法 Bellman_Ford
    cin>>n>>m;
	for (int i = 1; i <= n; ++i) 
        dis[i] = 1e18;
	dis[1] = 0;
	for (int i = 1; i <= m; ++i) 
        cin>>a[i].x>>a[i].y>>a[i].z;
	for (int i = 1; i <= n; ++i) {
		for (int j = 1; j <= m; ++j)
			if (dis[a[j].y] > dis[a[j].x] + a[j].z) 
                dis[a[j].y] = dis[a[j].x] + a[j].z;
	}
	for (int i = 1; i <= n; ++i)
        dis[i]==1e18?cout<<-1<<" ":cout<<dis[i]<<" "; 
    return 0;
}

*/

/*
B3603 [图论与代数结构 301] 最短树问题_1

题目描述

在离散数学课程的学习中，大家学习了最短树相关的知识，现在来检查一下大家的学习情况。

给定一张 nnn 个点 mmm 条边的带权连通无向图，点的编号从 111 到 nnn，可能存在重边和自环。现在，请你求出这张图总边权和最小的支撑树（最短树）的边权之和。即，找到一颗支撑树，满足选用边的边权和最小，输出这个边权和。
输入格式

第一行两个正整数 n,mn, mn,m ，分别表示给定无向图的点数和边数。

接下来 mmm 行，每行三个非负整数 u,v,wu, v, wu,v,w 表示一条连接 uuu 和 vvv 这两个点的无向边和这条边的边权 www。
输出格式

输出仅一行一个非负整数，表示最短树的边权之和。
输入输出样例
输入 #1

4 5
1 3 1
1 2 2
2 3 0
3 4 3
1 4 8

输出 #1

4

说明/提示

【样例解释】

选择 (1,3)(1,3)(1,3)、(2,3)(2,3)(2,3) 和 (3,4)(3,4)(3,4) 这三条边构成一颗支撑树。

【数据范围】

对于所有数据，满足 1≤n≤20001\leq n \leq 20001≤n≤2000，1≤m≤30001 \leq m \leq 30001≤m≤3000，边权均是 [0,109][0, {10}^9][0,109] 中的整数，保证输入的图合法且满足题目中的限制条件。

请注意答案上界的大小，可能需要使用 C++ 中的 long long int 类型。

code:
int fa[5001],n,m,sum,cnt;
struct Edge{
	int u,v,value;
	bool operator < (const Edge rhs)const{
		return value<rhs.value;
	}
}edge[3001];
int find_root(int x){ //并查集
	return x==fa[x]?x:fa[x]=find_root(fa[x]);
}
int main(){//无向图 最小生成树 克鲁斯卡尔 Kruskal + 并查集 + 快排
	cin>>n>>m;
	for(int i=0;i<m;++i)
		cin>>edge[i].u>>edge[i].v>>edge[i].value;
	for(int i=0;i<=n;++i)
		fa[i]=i;
	sort(edge,edge+m);
    cnt=n;
	for(int i=0;i<=m;++i){
		int a=find_root(edge[i].u),b=find_root(edge[i].v);
		if(a!=b){
			fa[a]=b;
			cnt--;
			sum+=edge[i].value;
		}
	}
	cout<<sum;
	return 0;
}

*/

/*
B3604 [图论与代数结构 302] 最短树问题_2

题目描述

在离散数学课程的学习中，大家学习了最短树相关的知识，现在来检查一下大家的学习情况。

给定一张 nnn 个点 mmm 条边的带权连通无向图，点的编号从 111 到 nnn，可能存在重边和自环。现在，请你求出这张图总边权和最小的支撑树（最短树）的边权之和。即，找到一颗支撑树，满足选用边的边权和最小，输出这个边权和。
输入格式

第一行两个正整数 n,mn, mn,m ，分别表示给定无向图的点数和边数。

接下来 mmm 行，每行三个非负整数 u,v,wu, v, wu,v,w 表示一条连接 uuu 和 vvv 这两个点的无向边和这条边的边权 www。
输出格式

输出仅一行一个非负整数，表示最短树的边权之和。
输入输出样例
输入 #1

4 5
1 3 1
1 2 2
2 3 0
3 4 3
1 4 8

输出 #1

4

说明/提示

对于所有数据，满足 1≤n≤1000001\leq n \leq 1000001≤n≤100000，1≤m≤3000001 \leq m \leq 3000001≤m≤300000，边权均是 [0,109][0, {10}^9][0,109] 中的整数，保证输入的图合法且满足题目中的限制条件。

请注意答案上界的大小，可能需要使用 C++ 中的 long long int 类型。

code:
struct Edge{
    int from,to,w;
}edge[300001];
int n,m,num,num_edge,u,v,w,f[100001];
long long ans;
void add_edge(int from,int to,int w){
	edge[++num_edge]=(Edge){from,to,w};
}
bool cmp(Edge a,Edge b){return a.w<b.w;}
int findf(int u){return f[u]==u?u:f[u]=findf(f[u]);}
int main(){//无向图 最小生成树 克鲁斯卡尔 Kruskal + 并查集 + 快排 + 优化
    cin>>n>>m;
	for(int i=1;i<=n;i++)
        f[i]=i;
	for(int i=1;i<=m;i++){
        cin>>u>>v>>w;
		add_edge(u,v,w);
	}
    sort(edge+1,edge+m+1,cmp);
    for(int i=1;i<=m;i++){
        if(num==n-1)break;
        int from=edge[i].from,to=edge[i].to,w=edge[i].w,from_father=findf(from),to_father=findf(to);
        if(from_father==to_father)continue;
        f[from_father]=to_father;
        ans+=w;
        num++;
    }
    cout<<ans;
	return 0;
}

*/