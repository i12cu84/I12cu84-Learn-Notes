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
P2626 斐波那契数列（升级版）

题目背景

大家都知道，斐波那契数列是满足如下性质的一个数列：

    f(1)=1f(1) = 1f(1)=1
    f(2)=1f(2) = 1f(2)=1
    f(n)=f(n?1)+f(n?2)f(n) = f(n-1) + f(n-2)f(n)=f(n?1)+f(n?2)（n≥2n \geq 2n≥2 且 nnn 为整数）。

题目描述

请你求出第 nnn 个斐波那契数列的数 ?mod??231\bmod\,2^{31}mod231 之后的值，并把它分解质因数。
输入格式

输入一个正整数 nnn。
输出格式

把第 nnn 个斐波那契数列的数分解质因数。
输入输出样例
输入 #1

5

输出 #1

5=5

输入 #2

6

输出 #2

8=2*2*2

说明/提示

n≤48n \le 48n≤48

code:
long long MOD=pow(2,31),n,f[101],x;
int main(){//模拟
	cin>>n;
	f[1]=1;f[2]=1;
	for(int i=3;i<=n;i++)
		f[i]=(f[i-1]+f[i-2])%MOD;
	cout<<f[n]<<"=";
	for(int i=2;i<=f[n];i++)
		while(f[n]%i==0){
			x++;
            x==1?cout<<i:cout<<"*"<<i;
			f[n]/=i;
		}
	return 0;
}

*/

/*
P2628 冒险岛

题目背景

冒险岛是费老师新开发的一种情景模拟电脑的游戏，通过掷骰子（1~6个数字之间），让一种人物（棋子）在棋纸上从左至右的行走，从而模拟冒险的故事……
题目描述

棋纸上有一条从左至右的很长的路，整条路是一连串符号组成，表明路的状况，棋子必须在符号组成的路上行走。每掷一下骰子得到的数字，棋子就可以走掷得的数字所对应的步数，比如掷3，就可以走3步。

路上有两种特殊符号可以改变棋子的行走。

一种是“>”符号，一旦棋子走完了掷骰子的步数，最终停留在这个符号上，后面有紧跟着2个以上“>”，那么棋子就可以获得前进奖励，可以沿着“>”一直一步步前进，直到遇到一个不是“>”的符号位置停下来。

还有一种是“*”符号，一旦棋子走完了掷骰子的步数，最终停留在这个符号上，后面又紧跟着两个以上“*”，就要受到后退惩罚，需要退后k步，这个k步就是从当前“*”开始的连续的“*”的数量。

每次掷数后，奖励或惩罚至多一次，如果奖励或惩罚后棋子又落在第二种特殊符号上，则不能再受到奖励或惩罚。

如果走的棋子超出棋纸右边界最后一个符号，则停在最后一个符号上；如果超出左边界，则停在第一个符号上。

若干次掷骰子后，请问游戏中的人物（棋子）走到了哪步？离终点还差几步？
输入格式

第一行为一个字符串s，字符串中的每个字符表示棋纸的路的状况。

第二行是一个n，表示掷了n次骰子。

第三行是n个整数（1~6的范围），表明掷了n次骰子得到的数字，数字之间有一个空格。
输出格式

只有两个数字，表明目前所在符号的序号和离终点符号的步数，数子中间有一个空格。注意输出末尾有换行。
输入输出样例
输入 #1

yhfA>>>fhsdfa***>>>foaoad

3

5 6 6

输出 #1

20 5

说明/提示

【样例说明】

在游戏中，第一次掷的是5，则走到第一个>的位置，获得奖励前进至左起第二个f处。第二次掷的是6，则走到*的位置，受惩罚退3步，至d处。第三次掷的是6，则走至左起第四个>号处，获奖励前进至f。最终棋子停留的符号是第20个（从左至右的数），离终点符号d（含）相差5步数。

【数据范围】

对于50%的数据，1<=s的长度<=255,0<=n<=1000。

对于100%的数据，256<=s的长度<=1000000,0<=n<=100000。

code:
int main(){
	string s;
	getline(cin,s);//行内可能会有空格或者/t因此需要getline Linux和win的差别
	int n,a,len=s.length(),top=-1;cin>>n;
	for(int i=1;i<=n;i++){
        cin>>a;
		top+=a;
		top=min(top,len-2);
		if(s[top]=='>' && s[top+1]=='>' && s[top+2]=='>'){
            for(int j=top;j<len;j++)
                if(s[j]!='>'){
                    top=j;
                    break;
                }
        }
		else if(s[top]=='*' && s[top+1]=='*' && s[top+2]=='*'){
			int m=0;
			for(int j=top;j<len;j++)
			    if(s[j]=='*') m++;
			    else break;
			top-=m;
		}
		top=max(min(top,len-2),0);
	}
    cout<<top+1<<" "<<len-top-2;
}

*/

/*
P2639 [USACO09OCT]Bessie's Weight Problem G

题目描述

Bessie像她的诸多姊妹一样，因为从Farmer John的草地吃了太多美味的草而长出了太多的赘肉。所以FJ将她置于一个及其严格的节食计划之中。她每天不能吃多过H (5 <= H <= 45,000)公斤的干草。 Bessie只能吃一整捆干草；当她开始吃一捆干草的之后就再也停不下来了。她有一个完整的N (1 <= N <= 500)捆可以给她当作晚餐的干草的清单。她自然想要尽量吃到更多的干草。很自然地，每捆干草只能被吃一次（即使在列表中相同的重量可能出现2次，但是这表示的是两捆干草，其中每捆干草最多只能被吃掉一次）。 给定一个列表表示每捆干草的重量S_i (1 <= S_i <= H), 求Bessie不超过节食的限制的前提下可以吃掉多少干草（注意一旦她开始吃一捆干草就会把那一捆干草全部吃完）。
输入格式

* 第一行: 两个由空格隔开的整数: H 和 N * 第2到第N+1行: 第i+1行是一个单独的整数，表示第i捆干草的重量S_i。
输出格式

* 第一行: 一个单独的整数表示Bessie在限制范围内最多可以吃多少公斤的干草。
输入输出样例
输入 #1

56 4
15
19
20
21

输出 #1

56

说明/提示

输入说明:

有四捆草，重量分别是15, 19, 20和21。Bessie在56公斤的限制范围内想要吃多少就可以吃多少。

输出说明:

Bessie可以吃3捆干草（重量分别为15, 20, 21）。恰好达到她的56公斤的限制。

code:
int f[45001],w[10001],c[10001],n,m;
int main(){
	cin>>m>>n;
	for(int i=1;i<=n;i++)
		cin>>c[i],w[i]=c[i];
	for(int i=1;i<=n;i++)
		for(int j=m;j>=c[i];j--)
			if(f[j-c[i]]+w[i]>f[j])
			    f[j]=f[j-c[i]]+w[i];
	cout<<f[m];
	return 0;
}

*/

/*
P2640 神秘磁石

题目背景

在遥远的阿拉德大陆，有一种神秘的磁石，是由魔皇制作出来的，
题目描述

    若给他一个一维坐标系，那么他的磁力一定要在素数坐标的位置上才能发挥的最大（不管位置坐标的大小，只要是素数那么磁力就一样大）。
    若两个磁石相距为 kkk，那么磁石间的破坏力将会达到当前磁力的峰值

显然，两磁石间最大破坏力取决于磁力大小和磁石间距，那么请问给出长度不超过 nnn 的一维坐标系，有哪几对坐标间磁石破坏力最大。
输入格式

两个正整数 n,kn,kn,k。
输出格式

所有小于等于 nnn 的素数对。每对素数对输出一行，中间用单个空格隔开。若没有找到任何素数对，输出 empty。
输入输出样例
输入 #1

6924 809

输出 #1

2 811

说明/提示

对于 100%100\%100% 的数据，1≤k≤n≤1041\leq k\leq n\leq 10^41≤k≤n≤104。

code:
int a[10001],n,k,t;
int main(){
    cin>>n>>k;
    a[1]=1;
    for(int i=2;i<=n;i++)
        for(int j=2;j*j<=i;j++)
            if(i%j==0)
                a[i]=1;
    for(int i=1;i<=n-k;i++)
        if(a[i]==0 && a[i+k]==0){
            t=1;
            cout<<i<<' '<<i+k<<endl;
        }
    if(t==0)cout<<"empty";
    return 0;
}

*/

/*
P2645 斯诺克

题目背景

镇海中学开设了很多校本选修课程，有体育类、音乐类、美术类、无线电测向、航空航海航天模型制作等，力争使每位学生高中毕业后，能学到一门拿得出手的兴趣爱好，为将来的终身发展打下基础。在体育类的校本选修课程中，有一门课程是斯诺克台球。
题目描述

斯诺克台球比赛中有21个球，其中有15个红球，6个彩球（黄、绿、棕、蓝、粉、黑）。甲乙二人轮流打球。打一个红球得1分，打一个彩球的得分如下：

黄球：2分； 绿球：3分； 棕球：4分；

蓝球：5分； 粉球：6分； 黑球：7分；

最后以得分高者为胜。

简化后的打球规则如下：

1．如果有红球，第奇数次必须打红球，打过的红球从桌面上拿走；

2．每打一个红球后，可以任意选一个彩球打，打红球后接着打的彩球不从桌面上拿走；

    如果桌面上已经没有红球可打了，那么按照分值从小到大的次序打彩球，这时候每打一个彩球都从桌面上拿走。

打球时犯规的判罚如下：

    没有打中球，给对方加4分；

2．没有按照打球规则打该打的球，即打中了错误的球时：

（1）如果这个错误的球的分值大于4，那么给对方加等于这个球的分值；

（2）如果这个错误的球的分值不大于4，那么给对方加4分；

打中的错误球不从桌面上拿走。

请统计某局比赛进行到现在为止的比分。
输入格式

输入有两行，第一行有二个整数n和m，表示甲打了n个球，乙打了m个球。n和m之间以一个空格分隔。

第二行，有n个以空格分隔的整数，表示甲的n次连续打球情况。

第三行，有m个以空格分隔的整数，表示乙的m次连续打球情况。

第二行和第三行中：

（1）1至7的整数表示打了相应分值的球；

（2）最后一个数字是0,表示没有打中球犯规，0只会出现在这二行的最后一个数字处；

（3）打了错误球的犯规也只会出现在这二行最后一个数字处；

输入数据保证是正确，不会出现打到桌面上不存在的球的情况，数据不必检验。
输出格式

输出仅有一行，该行有二个整数(互相之间以一个空格分隔)，表示比赛进行到现在为止甲乙二人的得分（先打的甲在前）。
输入输出样例
输入 #1

4 3
1 7 1 6
1 7 1

输出 #1

15 9

说明/提示

【样例说明】

甲依次打了红球、黑球、红球、粉球，甲得15分（1+7+1+6）。

乙依次打了红球、黑球、红球，乙得9分（1+7+1）。

【数据范围】

80%的数据，每次总是打中球的，并且每次打中的球总是正确的，没有犯规情况。100%的数据，会有未打中或犯规情况。

保证输出不超过2^64-1.

没有什么难的，从头到尾除了判断就是循环，但是要特别细心，注意这道题强大的特判！

code:
int a,n,m,x,y;
int main(){//模拟
	cin>>n>>m;
    while(n--){
		cin>>a;
		x+=a;
		if(a==0)y+=4;
	}
    while(m--){
		cin>>a;
		y+=a;
		if(a==0)x+=4;
	}
	cout<<x<<" "<<y;
}

*/

/*
P2646 数数zzy

题目描述

zzy 自从数学考试连续跪掉之后，上数学课就从来不认真听了（事实上他以前也不认真听）。于是他开始在草稿纸上写写画画，比如写一串奇怪的字符串。然后他决定理♂性♂愉♂悦♂一下：统计这串字符串当中共有多少个为 zzy 的子序列，注意是子序列而非子串。但是由于他写的字符串实在是太长啦，而且他是个超级大蒟蒻，根本就数不过来。所以他决定请求你这个超级大神犇的帮助。你可以帮帮他吗？
输入格式

一行仅含小写字母的字符串 sss。
输出格式

一行，一个非负整数，表示输入的字符串中为 zzy 的子序列的个数。
输入输出样例
输入 #1

zlzhy

输出 #1

1

说明/提示
数据规模与约定

约定 ∣s∣|s|∣s∣ 表示字符串 sss 的长度。

    对于 70%70\%70% 的数据，保证 ∣s∣≤100|s| \le 100∣s∣≤100。
    对于 100%100\%100% 的数据，保证 1≤∣s∣≤1061 \le |s| \le 10^61≤∣s∣≤106，答案不超过 263?12^{63}-1263?1。

code:
int main(){
    long long z=0,zzy=0;//不开longlong 见祖宗是真的
    char c;
    while(cin>>c){
        if(c=='z')z++;
        if(c=='y')zzy+=z*(z-1)/2;
    }
    cout<<zzy;
	return 0;
}

*/

/*
P2651 添加括号III

题目描述

现在给出一个表达式，形如 a1/a2/a3/.../ana_{1}/a_{2}/a_{3}/.../a_{n}a1?/a2?/a3?/.../an?。

如果直接计算，就是一个个除过去，比如 1/2/1/4=1/81/2/1/4 = 1/81/2/1/4=1/8。

然而小A\text{A}A看到一个分数感觉很不舒服，希望通过添加一些括号使其变成一个整数。一种可行的办法是 (1/2)/(1/4)=2(1/2)/(1/4)=2(1/2)/(1/4)=2 。

现在给出这个表达式，求问是否可以通过添加一些括号改变运算顺序使其成为一个整数。
输入格式

一个测试点中会有多个表达式。

第一行 ttt ，表示表达式数量。

对于每个表达式，第一行是 nnn，第二行 nnn 个数，第 iii 个数表示 aia_{i}ai?。
输出格式

输出 ttt 行。

对于每个表达式，如果可以通过添加括号改变顺序使其变成整数，那么输出 Yes，否则输出 No。
输入输出样例
输入 #1

2
4
1 2 1 4
5
6 5 7 9 12

输出 #1

Yes
No

说明/提示

    对于 40%40\%40% 的数据，n≤16n \le 16n≤16。
    对于 70%70\%70% 的数据，n≤100n \le 100n≤100。
    对于 100%100\%100% 的数据， 2≤n≤100002 \le n \le 100002≤n≤10000，1≤t≤1001 \le t \le 1001≤t≤100，1≤ai≤231?11 \le a_{i}\le 2^{31}-11≤ai?≤231?1。

code:
long long t,n,num[10001];
int main(){
    cin>>t;
    while(t--){
        cin>>n;
        for(int i=0;i<n;i++)
            cin>>num[i];
        num[1]/=__gcd(num[0],num[1]);
        for(int i=2;i<n;i++)
            num[1]/=__gcd(num[1],num[i]);
        if(num[1]==1)cout<<"Yes"<<endl;
        else cout<<"No"<<endl;
    }
	return 0;
}

*/

/*
P2660 zzc 种田

题目背景

可能以后 zzc就去种田了。
题目描述

田地是一个巨大的矩形，然而zzc 每次只能种一个正方形,而每种一个正方形时zzc所花的体力值是正方形的周长，种过的田不可以再种，zzc很懒还要节约体力去泡妹子，想花最少的体力值去种完这块田地，问最小体力值
输入格式

两个正整数x,y，表示田地的长和宽
输出格式

输出最小体力值
输入输出样例
输入 #1

1 10

输出 #1

40

输入 #2

2 2 

输出 #2

8

说明/提示

1<=x,y<=10^16

code:
long long x,y,ans;
int main(){
    cin>>x>>y;
    while(x && y){
        swap(x,y);
        ans+=4*y*(x/y);
        x%=y;
    }
    cout<<ans;
	return 0;
}

*/

/*
P2663 越越的组队 题解

题目描述

班级要组织一场综合能力竞赛，班里共有 nnn 位学生，将分成两队互相竞争。

老师找到了越越并给了越越一张全班同学综合能力测试的成绩，要求他从全班同学中选出一半，并要求这些同学综合能力测试的成绩之和在不超过班级总分一半的前提下尽量达到最高。这样分成的两队实力是最平均的。越越堆着满脸的笑容找到了你，你就帮他写一个程序吧。
输入格式

第一行有一个整数，表示班级的学生人数 nnn。

第 222 到第 (n+1)(n + 1)(n+1) 行，每行一个整数，第 (i+1)(i + 1)(i+1) 行的整数 aia_iai? 表示第 iii 位同学的成绩。
输出格式

输出一行一个整数表示答案。
输入输出样例
输入 #1

8
77
77
56
77
84
77
56
46

输出 #1

273

说明/提示
样例 1 解释

班级总分为 550550550，总分的一半是 275275275，选则成绩分别为 56,77,84,5656,77,84,5656,77,84,56 的同学可以达到总分 273273273，是不超过 275275275 的最大值。
数据规模与约定

对于全部的测试点，保证 1≤n≤1001 \leq n \leq 1001≤n≤100，0≤ai≤1000 \leq a_i \leq 1000≤ai?≤100，数据保证 nnn 均为偶数。

code:
int n,a[101],dp[101][10001],sum;
int main() {
    cin>>n;
	for(int i=1;i<=n;i++)
		cin>>a[i],
        sum+=a[i];
	dp[0][0]=1; 
	for(int i=1;i<=n;i++) 
		for(int j=i;j>=1;j--) 
			for(int k=sum/2;k>=a[i];k--)
				dp[j][k]= dp[j][k] | dp[j-1][k-a[i]];
	for(int i=sum/2;i>=0;i--)
		if(dp[n/2][i])
            cout<<i,
            exit(0);
}

*/

/*
P2677 [USACO07DEC]Bookshelf 2 B

题目描述

Farmer John最近为奶牛们的图书馆添置了一个巨大的书架，尽管它是如此的大，但它还是几乎瞬间就被各种各样的书塞满了。现在，只有书架的顶上还留有一点空间。 所有N(1 <= N <= 20)头奶牛都有一个确定的身高H_i(1 <= H_i <= 1,000,000 - 好高的奶牛>_<)。设所有奶牛身高的和为S。书架的 高度为B，并且保证1 <= B <= S。 为了够到比最高的那头奶牛还要高的书架顶，奶牛们不得不象演杂技一般，一头站在另一头的背上，叠成一座“奶牛塔”。当然，这个塔的高度，就是塔中所有奶牛的身高之和。为了往书架顶上放东西，所有奶牛的身高和必须不小于书架的高度。 塔叠得越高便越不稳定，于是奶牛们希望找到一种方案，使得叠出的塔在高度不小于书架高度的情况下，高度尽可能小。你也可以猜到你的任务了：写一个程序，计算奶牛们叠成的塔在满足要求的情况下，最少要比书架高多少。
输入格式

* 第1行: 2个用空格隔开的整数：N 和 B * 第2..N+1行: 第i+1行是1个整数：H_i
输出格式

* 第1行: 输出1个非负整数，即奶牛们叠成的塔最少比书架高的高度
输入输出样例
输入 #1

5 16
3
1
3
5
6

输出 #1

1

说明/提示

输出说明:

我们选用奶牛1、3、4、5叠成塔，她们的总高度为3 + 3 + 5 + 6 = 17。任何方案都无法叠出高度为16的塔，于是答案为1。

code:
int n,b,tot,w,h[25],f[1000001];
int main(){
	cin>>n>>b;
	for(int i=1;i<=n;i++)
		cin>>h[i],tot+=h[i];
	w=tot-b;
	for(int i=1;i<=n;i++)
		for(int j=w;j>=h[i];j--)
			f[j]=max(f[j],f[j-h[i]]+h[i]);
	cout<<tot-f[w]-b;
	return 0;
}

*/

/*
P2681 众数

题目背景

Alice 和 Bob 玩游戏。
题目描述

Alice 现在有一个序列 a1,a2,...ana_1,a_2,...a_na1?,a2?,...an?。

现在她需要 Bob 支持询问一个区间内的众数,还要支持修改一个位置的 aia_iai?。
输入格式

第一行两个整数 n,mn,mn,m。

第二行 nnn 个整数，表示 a1,...,ana_1,...,a_na1?,...,an?。

接下来 mmm 行，每行三个整数 flag,x,yflag,x,yflag,x,y。

如果 flag=0flag=0flag=0，表示询问 [x,y]\big[x,y\big][x,y] 区间内的众数，如果有多个输出较小的。

如果 flag=1flag=1flag=1，表示将 axa_xax? 改为 yyy。
输出格式

对于每个 flag=0flag=0flag=0 的询问，每行输出一个整数表示答案。
输入输出样例
输入 #1

5 3
1 1 2 2 1
0 1 4
1 2 3
0 1 4

输出 #1

1
2

说明/提示

对于 100%100\%100% 的数据 n,m≤1000n,m \le 1000n,m≤1000。

对于查询操作满足 x≤yx\le yx≤y。

任意时刻 0<ai≤1090<a_i\le 10^90<ai?≤109。

code:
int n, m,a[1001], b[1001],flag, x, y;
int main () {
    cin>>n>>m;
    for (int i = 1; i <= n; i++) cin>>a[i];
    while (m--) {
        cin>>flag>>x>>y;
        if (flag == 0) {
            int cnt = 0;
            for (int i = x; i <= y; i++) b[++cnt] = a[i];
            sort (b + 1, b + cnt + 1);
            int num = 0, num1 = 0, ans = 0;
            for (int  i = 1; i <= cnt; i++) {
                if (b[i] != b[i - 1]) num1 = 0;
                num1++;
                if (num1 > num) num = num1,ans = b[i];
            }
            cout<<ans<<endl;
        }
        if (flag == 1) a[x] = y;
    }
}

*/

/*
P2692 覆盖

题目背景

WSR的学校有B个男生和G个女生都来到一个巨大的操场上扫地。
题目描述

操场可以看成是N 行M 列的方格矩阵，如下图(1)是一个4 行5 列的方格矩阵。每个男生负责打扫一些连续的行，每个女生负责打扫一些连续的列。比如有两个男生，第一个男生负责第1、2 两行、第二个男生负责第4 行，如图(2)的蓝色。打扫的区域可能重复，比如，又有两个女生，第一个女生负责打扫第3、4 两列，第二个女生负责打扫第4、5 两列，如图(3)的红色。从图(3)可以容易看出，有颜色覆盖的方格数为18，即这4 名学生总共打扫了18 个方格。

老师要WSR在学校给出打扫安排的数据后快速计算出这些学生总共打扫了多少方格？
输入格式

第一行4 个正整数：N,M,B,G，N 表示方阵行数，M 表示方阵列数，B 表示男生数，G 表示女生数。

接下来B 行，每行两个整数x y。表示相应某个男生负责打扫从第x 行到第y行（共y-x+1 行），保证1≤x≤y≤N。

再接下来G 行，每行两个整数x y。表示相应某个女生负责打扫从第x 列到第y 列（共y-x+1 列），保证1≤x≤y≤M。
输出格式

一个整数，表示所打扫的面积。（即格子的总数）
输入输出样例
输入 #1

4 5 2 2
1 2
4 4
3 4
4 5

输出 #1

18

说明/提示

不会可以自己画图。

数据范围：

8 个的数据：N,M,B,G 的范围都是[1…100]

2 个的数据：N,M,B,G 的范围都是[1…5,000]

code:
int n,m,a,b,start,last,a_sum,b_sum;
bool bj_a[5001],bj_b[5001];
int main(){
    cin>>n>>m>>a>>b;
	for(int i=1;i<=a;i++){
        cin>>start>>last;
		for(int j=start;j<=last;j++)
			if(bj_a[j]==false)
				a_sum++,bj_a[j]=true;
	}
	for(int i=1;i<=b;i++){
        cin>>start>>last;
		for(int j=start;j<=last;j++)
			if(bj_b[j]==false)
				b_sum++,bj_b[j]=true;
	}
	cout<<n*m-(n-a_sum)*(m-b_sum);
	return 0;
}

*/

/*
P2693 [USACO1.3]号码锁 Combination Lock

题目背景

感谢 @Fond_Dream 提供五道 USACO 题目的标准题面。
题目描述

农夫约翰的奶牛不停地从他的农场中逃出来，导致了很多损害。为了防止它们再逃出来，他买了一只很大的号码锁以防止奶牛们打开牧场的门。

农夫约翰知道他的奶牛很聪明，所以他希望确保它们不会在简单地试了很多不同的号码组合之后就能轻易开锁。锁上有三个转盘，每个上面有数字 111 ~ nnn，因为转盘是圆的，所以 111 和 nnn 是相邻的。有两种能开锁的号码组合，一种是农夫约翰设定的，还有一种“预设”号码组合是锁匠设定的。但是，锁有一定的容错性，所以，在每个转盘上的数字都与一个合法的号码组合中相应的数字相距两个位置以内时，锁也会打开。

比如说，如果农夫约翰的号码组合是 ( 111 , 222 , 333 )，预设号码组合是 ( 444 , 555 , 666 )，在转盘被设定为 ( 111 , 444 , 555)（因为这和农夫约翰的号码组合足够接近）或 ( 222 , 444 , 888 )（因为这和预设号码组合足够接近）时可以打开锁。注意，( 111 , 555 , 666 )并不会打开锁，因为它与任一号码组合都不够接近。

给出农夫约翰的号码组合和预设号码组合，请计算能够开锁的不同的号码组合的数目。号码是有序的，所以 ( 111 , 222 , 333 ) 与 ( 333 , 222 , 111 ) 不同。
输入格式

输入的第一行是一个整数 nnn，代表锁上的数字个数。

输入的第二行有三个整数 x,y,zx, y, zx,y,z，代表农夫约翰的号码组合。

输入的第三行有三个整数 a,b,ca, b, ca,b,c，代表预设的号码组合。
输出格式

输出一行一个整数代表能够开锁的组合数目。
输入输出样例
输入 #1

50
1 2 3
5 6 7

输出 #1

249

说明/提示
输入输出样例 1 解释

每个转盘的标号是 111 ~ 505050。农夫约翰的号码组合是 ( 111 , 222 , 333 )，预设号码组合是 ( 555 , 666 , 777 )。
数据规模与约定

对于 100%100\%100% 的数据，保证 1≤n≤1001 \leq n \leq 1001≤n≤100，1≤x,y,z,a,b,c≤n1 \leq x, y, z, a, b, c \leq n1≤x,y,z,a,b,c≤n。

code:
int n,a,b,c,d,e,f,ans;
int main(){
	cin>>n>>a>>b>>c>>d>>e>>f;
	 for(int i=1;i<=n;i++)
        for(int j=1;j<=n;j++)
            for(int k=1;k<=n;k++)
            	if(((abs(i-a)<=2||abs(i-a)>=n-2)
                &&(abs(j-b)<=2||abs(j-b)>=n-2)
                &&(abs(k-c)<=2||abs(k-c)>=n-2))
                ||((abs(i-d)<=2||abs(i-d)>=n-2)
                &&(abs(j-e)<=2||abs(j-e)>=n-2)
                &&(abs(k-f)<=2||abs(k-f)>=n-2)))
                    ans++;
	cout<<ans<<endl;
	return 0; 
} 

*/

/*
P2694 接金币

题目描述

在二维坐标系里，有N个金币，编号0至N-1。初始时，第i个金币的坐标是（Xi，Yi）。所有的金币每秒向下垂直下降一个单位高度，例如有个金币当前坐标是(xf, yf),那么t秒后金币所在的位置就是(xf, yf-t)。初始时，FJ在（0,0）坐标处，FJ每秒只能向左移动一个单位距离或者向右移动一个单位距离，当然FJ也可以不移动。如果在某个时刻某个金币和FJ所在的位置重合，那么FJ就能接住这个金币。FJ能否把所有的金币都接住？如果行输出Abletocatch，否则输出Notabletocatch。
输入格式

多组测试数据。

第一行，一个整数G，表示有G组测试数据。1 <= G <= 5。

每组测试数据格式如下：

第一行，一个整数N。 1 <= N <= 50。

接下来有Ｎ行，第i行两个整数表示Xi、Yi。

  -1000<=Xi<=1000。0<=Yi<=1000。

输出格式

共G行，每行输出Abletocatch或Notabletocatch。
输入输出样例
输入 #1

5
3
-1 1
1 3
0 4
1
-3 2
3
-1 1
1 2
0 4
3
0 9
-1 1
1 3
8
70 141
-108 299
52 402
-70 280
84 28
-29 363
66 427
-33 232

code:#include<bits/stdc++.h>
using namespace std;
int g,n;
struct node{
	int x,y;
}a[50];
bool cmp(node x,node y){
	return x.y<y.y;
}
int main(){
	cin>>g;
	while(g--){
		bool flag=0;
		cin>>n;
		for(int i=0;i<n;i++)
            cin>>a[i].x>>a[i].y;
		sort(a,a+n,cmp);
		if(abs(a[0].x)>a[0].y){
            cout<<"Notabletocatch"<<endl;
			continue;
		}
		for(int i=1;i<n;i++)
			if(abs(a[i].x-a[i-1].x)>a[i].y-a[i-1].y){
				cout<<"Notabletocatch"<<endl;
				flag=1;
				break;
			}
		if(!flag)
            cout<<"Abletocatch"<<endl;
	}
	return 0;
}

*/

/*
P2695 骑士的工作

题目背景

你作为一个村的村长，保卫村庄是理所当然的了.今天，村庄里来了一只恶龙，他有n个头，恶龙到处杀人放火。你着急了。不过天无绝人之路，现在来了一个骑士团。里面有m位成员（往下看）
题目描述

每个人都可以砍掉一个大小不超过（<=）z的头，要money个金币，求最小花费。
输入格式

第一行两个整数 n m

下接n行，一个整数 表示n个头的大小。

下接m行，每个人可以砍的头大小或金币(金币==头的大小）。
输出格式

一个整数，最小花费。如果无解，输出“you died!”
输入输出样例
输入 #1

2 3
5 
4
7 
8
4

输出 #1

11

说明/提示

1<=n,m<=20000

code:
int n,m,a[20000],b[20000],sum,p;
int main(){
    cin>>n>>m;
    for(int i=0;i<n;i++)
        cin>>a[i];
    for(int i=0;i<m;i++)
        cin>>b[i];
    sort(a,a+n);
    sort(b,b+m);
    for(int j=0;j<m;j++){
        if(b[j]>=a[p]){
            sum=sum+b[j];
            p++;
        }
        if(p==n){		
            cout<<sum<<endl;
            return 0;
        }
    }
    cout<<"you died!";
    return 0;
}

*/

/*
P2719 搞笑世界杯

题目背景

很久很久以后，一次世界杯。
题目描述

随着世界杯小组赛的结束，法国，阿根廷等世界强队都纷纷被淘汰，让人心痛不已。 于是有人组织了一场搞笑世界杯，将这些被淘汰的强队重新组织起来和世界杯一同比赛。你和你的朋友欣然去购买球票。不过搞笑世界杯的球票出售方式也很特别，它们只准备了两种球票。

    A 类票——免费球票
    B 类票——双倍价钱球票。

购买时由工作人员通过掷硬币决定，投到正面的买 A 类票， 反面的买 B 类票。由于是市场经济，主办方不可能倒贴钱，所以他们总是准备了同样多的 A 类票和 B 类票。你和你的朋友十分幸运的排到了某场精彩比赛的最后两个位置。

这时工作人员开始通过硬币售票。不过更为幸运的是当工作人员到你们面前时他发现已无需再掷硬币了，因为剩下的这两张票全是免费票。

你和你的朋友在欣喜之余，想计算一下排在队尾的两个人同时拿到一种票的概率是多少(包括同时拿 A 类票或 B 类票) 假设工作人员准备了 2n2n2n 张球票，其中 nnn 张 A 类票，nnn 张 B 类票，并且排在队伍中的人每人必须且只能买一张球票(不管掷到的是该买 A 还是该买 B)。
输入格式

输入文件仅一行，包含整数 2n2n2n，代表 A、B 类票各 nnn 张。其中，0≤n≤12500 \le n \le 12500≤n≤1250 ，nnn 为整数。
输出格式

输出文件只包含一个数，为拿到同一种票的概率，精确到小数点后 4 位。
输入输出样例
输入 #1

256

输出 #1

0.9500

code:
double pd[2501][2501];
int main() {//dp
	int n;
	cin >> n;
	n >>= 1;
	for (int i = 2; i <= n; i++)
		pd[0][i] = 1, pd[i][0] = 1;
	for (int i = 1; i <= n; i++)
		for (int j = 1; j <= n; j++)
			pd[i][j] = pd[i - 1][j] * 0.5 + pd[i][j - 1] * 0.5;
	printf("%.4f", pd[n][n]);
	return 0;
}

*/

/*
P2722 [USACO3.1]总分 Score Inflation

题目背景

选手在我们 USACO 的竞赛中的得分越多我们越高兴。

我们试着设计我们的竞赛以便人们能尽可能的多得分,这需要你的帮助。
题目描述

我们可以从几个种类中选取竞赛的题目,这里的一个"种类"是指一个竞赛题目的集合,解决集合中的题目需要相同多的时间并且能得到相同的分数。

你的任务是写一个程序来告诉 USACO 的职员,应该从每一个种类中选取多少题目，使得解决题目的总耗时在竞赛规定的时间里并且总分最大。
输入格式

输入的第一行是用空格隔开的两个整数，分别代表竞赛时间 mmm 和题目类 nnn。

第 222 到第 (n+1)(n + 1)(n+1) 行，每行两个用空格隔开的整数，第 (i+1)(i + 1)(i+1) 行的整数 pi,tip_i, t_ipi?,ti? 分别代表解决第 iii 类题得到的分数和需要花费的时间。

既然是某一类题目，那么这一类题目可以重复选择。
输出格式

输出一行一个整数，代表最大的总分。
输入输出样例
输入 #1

300 4
100 60
250 120
120 100
35 20

输出 #1

605

说明/提示
数据规模与约定

对于 100%100\%100% 的数据，保证 1≤n≤1041 \leq n \leq 10^41≤n≤104，1≤pi,ti≤1041 \leq p_i, t_i \leq 10^41≤pi?,ti?≤104。

code:
int m,n,v,i,c[10001],w[10001],f[10001];
int main(){//dp
    cin>>m>>n;
    for(i=1;i<=n;i++)
        cin>>c[i]>>w[i];
    for(i=1;i<=n;i++)
        for(v=w[i];v<=m;v++)
            if(f[v-w[i]]+c[i]>f[v])f[v]=f[v-w[i]]+c[i];
                cout<<f[m];
    return 0;
}

*/

/*
P2755 洗牌问题

题目描述

给你2N张牌，编号为1,2,3..n,n+1,..2n。这也是最初的牌的顺序。 一次洗牌是把序列变为n+1,1,n+2,2,n+3,3,n+4,4..2n,n。可以证 明，对于任意自然数N，都可以在经过M次洗牌后第一次重新得到 初始的顺序。编程对于小于1e8的自然数N，求出M的值。
输入格式

输入：N
输出格式

输出：M
输入输出样例
输入 #1

20

输出 #1

20

code:
int n,i=1,s;
int main(){//模拟
    cin>>n;
    do{
    	i>n?i=(i-n)*2-1:i=i*2;
	}while(s++,i!=1);
	cout<<s;
    return 0;
}

*/

/*
P2790 ccj与zrz之积木问题

题目背景

ccj和zrz无聊到了玩起了搭积木...(本题选自uva101，翻译来自《算法竞赛入门经典2》)
题目描述

从左到右有n个木块，编号从0到n-1，要求模拟以下4种操作（下面的a和B都是木块编号，归为表示比如1号木块归到1号位去）。

move a onto b 把a和b上方的木块全部归位，然后把a摞在b上面。

move a over b 把a上方的全部归位，然后把a放在b所在木块堆的顶部。

pile a onto b 把b上方的木块全部归位，然后把a及上面的木块整体摞在b上面

pile a over b 把a及上面的木块整体摞在b所在木块堆的顶部。

遇到quit停止。a和b在同一堆的指令时非法指令，应当忽略。

最后输出每个位置的木块列表，按照从底部到顶部的顺序排列。
输入格式

第一行:n。

接下来若干行：每行一个指令（语法不会错），遇到quit停止。
输出格式

n行，第i行输出一个i和冒号，然后一个空格，输出，它位置上的所有积木。
输入输出样例
输入 #1

10
move 9 onto 1
move 8 over 1
move 7 over 1
move 6 over 1
pile 8 over 6
pile 8 over 5
move 2 over 1
move 4 over 9
quit

输出 #1

0: 0
1: 1 9 2 4
2:
3: 3
4:
5: 5 8 7 6
6:
7:
8:
9:

说明/提示

0 < n < 25。

code:
int n,x,y,j,k,vis[30],a[30][30];
string s1,s2;
int main(){
	cin>>n;
	for (int i=0;i<n;i++) a[i][0]=1,a[i][1]=vis[i]=i;
	while (cin>>s1 && s1!="quit"){
		cin>>x>>s2>>y;
		if (vis[x]==vis[y]) continue;
		if (s1=="move" && s2=="onto"){
			while (a[vis[x]][a[vis[x]][0]]!=x && a[vis[x]][0]>0)vis[a[vis[x]][a[vis[x]][0]]]=a[a[vis[x]][a[vis[x]][0]]][++a[a[vis[x]][a[vis[x]][0]]][0]]=a[vis[x]][a[vis[x]][0]],a[vis[x]][0]--;
			while (a[vis[y]][a[vis[y]][0]]!=y && a[vis[y]][0]>0)vis[a[vis[y]][a[vis[y]][0]]]=a[a[vis[y]][a[vis[y]][0]]][++a[a[vis[y]][a[vis[y]][0]]][0]]=a[vis[y]][a[vis[y]][0]],a[vis[y]][0]--;
			a[vis[y]][++a[vis[y]][0]]=x;
			a[vis[x]][0]--;
			vis[x]=vis[y];
		}
		else if (s1=="move" && s2=="over"){
			while (a[vis[x]][a[vis[x]][0]]!=x && a[vis[x]][0]>0)vis[a[vis[x]][a[vis[x]][0]]]=a[a[vis[x]][a[vis[x]][0]]][++a[a[vis[x]][a[vis[x]][0]]][0]]=a[vis[x]][a[vis[x]][0]],a[vis[x]][0]--;
		    a[vis[y]][++a[vis[y]][0]]=x;
			a[vis[x]][0]--;
			vis[x]=vis[y];
		}
		else if (s1=="pile" && s2=="onto"){
			while (a[vis[y]][a[vis[y]][0]]!=y && a[vis[y]][0]>0)vis[a[vis[y]][a[vis[y]][0]]]=a[a[vis[y]][a[vis[y]][0]]][++a[a[vis[y]][a[vis[y]][0]]][0]]=a[vis[y]][a[vis[y]][0]],a[vis[y]][0]--;
		    j=1,k=vis[x];
		    while (j<=a[vis[x]][0] && a[vis[x]][j]!=x) j++;
		    for (int i=j;i<=a[k][0];i++)a[vis[y]][++a[vis[y]][0]]=a[k][i],vis[a[k][i]]=vis[y];
		    a[k][0]=j-1;
		}
		else if (s1=="pile" && s2=="over"){
		    j=1,k=vis[x];
		    while (j<=a[vis[x]][0] && a[vis[x]][j]!=x) j++;
		    for (int i=j;i<=a[k][0];i++)a[vis[y]][++a[vis[y]][0]]=a[k][i],vis[a[k][i]]=vis[y];
		    a[k][0]=j-1;
		}
	}
	for (int i=0;i<n;i++){
		cout<<i<<':';
		for (int j=1;j<=a[i][0];j++)
		    cout<<' '<<a[i][j];
		cout<<endl;
	}
	return 0;
}

*/

/*
P2799 国王的魔镜

题目描述

国王有一个魔镜，可以把任何接触镜面的东西变成原来的两倍——只是，因为是镜子嘛，增加的那部分是反的。比如一条项链，我们用AB来表示，不同的字母表示不同颜色的珍珠。如果把B端接触镜面的话，魔镜会把这条项链变为ABBA。如果再用一端接触的话，则会变成ABBAABBA（假定国王只用项链的某一端接触魔镜）。给定最终的项链，请编写程序输出国王没使用魔镜之前，最初的项链可能的最小长度。
输入格式

只有一个字符串，由大写英文字母组成（字母数<=100000），表示最终的项链。
输出格式

只有一个整数，表示国王没使用魔镜前，最初的项链可能的最小长度。
输入输出样例
输入 #1

ABBAABBA

输出 #1

2

code:
int l,r;
string s;
int jc(int n){
	if((n+1)%2)return n+1;
	if(n==0)return 1;
	l=0;
    r=n;
	while(l<r){
		if(s[l]!=s[r])
			return n+1;
		l++; 
        r--;
	}
	return jc(r);
}
int main(){
	cin>>s;
    cout<<jc(s.size()-1);
	return 0;
}

*/

/*
P2800 又上锁妖塔

题目背景

小D在X星买完了想要的东西,在飞往下一个目的地的途中,正无聊的他转头看了看身边的小A,发现小A正在玩<仙剑>
题目描述

可是小A很奇怪,他一直在锁妖塔的周围转来转去,可是就是不进去,于是小D问他:”你在干什么?怎么不上去?”小A说:”我在想怎么从锁妖塔外面爬上去”(倒…) 锁妖塔的建造很特别,塔总共有n层,但是高度却不相同,这造成了小A爬过每层的时间也不同.小A会用仙术,每用一次可以让他向上跳一层或两层,但是每次跳跃后小A都将用完灵力,必须爬过至少一层才能再次跳跃(你可以认为小A需要跳两次一层才休息),小A想用最短的时间爬到塔顶,可是他不能找到时间最短的方案,所以请你帮他找到一个时间最短的方案让他爬到塔顶,小A只关心时间,所以你只要告诉他最短时间是多少就可以了.你可以最后跳到塔外即超过塔高.
输入格式

第一行一个数n (n<=1000000),表示塔的层数.

第二行n个数(<=100),表示从下往上每层的高度.
输出格式

一个数,表示最短时间.
输入输出样例
输入 #1

5
3 5 1 8 4

输出 #1

1

code:
int n,a[1000001],f[1000001];
int main() {
	cin>>n;
	for(int i=1; i<=n; i++) 
		cin>>a[i];
	for(int i=1; i<=n+1; i++)
		f[i]=1e9;
	for(int i=1; i<=n+1; i++) {
		f[i]=min(min(f[i-1],f[i-2]),f[i-3]);
		f[i]+=a[i];
	}
	cout<<f[n+1];
	return 0;
}

*/

/*
P2802 回家

题目描述

小 H 在一个划分成了 n×mn \times mn×m 个方格的长方形封锁线上。 每次他能向上下左右四个方向移动一格（当然小 H 不可以静止不动）， 但不能离开封锁线，否则就被打死了。 刚开始时他有满血 666 点，每移动一格他要消耗 111 点血量。一旦小 H 的血量降到 000， 他将死去。 他可以沿路通过拾取鼠标（什么鬼。。。）来补满血量。只要他走到有鼠标的格子，他不需要任何时间即可拾取。格子上的鼠标可以瞬间补满，所以每次经过这个格子都有鼠标。就算到了某个有鼠标的格子才死去， 他也不能通过拾取鼠标补满 HP。 即使在家门口死去， 他也不能算完成任务回到家中。

地图上有五种格子：

0：障碍物。

1：空地， 小 H 可以自由行走。

2：小 H 出发点， 也是一片空地。

3：小 H 的家。

4：有鼠标在上面的空地。

小 H 能否安全回家？如果能， 最短需要多长时间呢？
输入格式

第一行两个整数 n,mn,mn,m， 表示地图的大小为 n×mn \times mn×m。

下面 nnn 行， 每行 mmm 个数字来描述地图。
输出格式

一行， 若小 H 不能回家， 输出 -1，否则输出他回家所需最短时间。
输入输出样例
输入 #1

3 3
2 1 1
1 1 0
1 1 3

输出 #1

4

说明/提示

对于所有数据，1≤n,m≤91 \le n,m \le 91≤n,m≤9。

2021.9.2 增添一组 hack 数据 by @囧仙

code:
bool vis[15][15][7][105];
int n, m, a[15][15], sx, sy, fx, fy, mini = 1e9,dx[10] = {0, 0, -1, 1},dy[10] = {-1, 1, 0, 0};
void dfs(int x, int y, int xue, int ans){
	if(x < 1 || x > n || y < 1 || y > m || a[x][y] == 0 || xue == 0 || ans > 100 || vis[x][y][xue][ans])return ;
	vis[x][y][xue][ans] = true;
	if(a[x][y] == 4)xue = 6;
	if(x == fx && y == fy){
		mini = min(mini, ans);
		return ;
	}
	for(int i = 0; i < 4; i++)dfs(x + dx[i], y + dy[i], xue - 1, ans + 1);
}
int main(){//dfs
	cin >> n >> m;
	for(int i = 1; i <= n; i++)
		for(int j = 1; j <= m; j++){
			cin >> a[i][j];
			if(a[i][j] == 2)sx = i,sy = j;
			if(a[i][j] == 3)fx = i,fy = j;
		}
	dfs(sx, sy, 6, 0);
	cout << (mini == 1e9 ? -1 : mini);   //三目运算符，如果mini为1e9，输出-1，否则，输出mini 
	return 0;
}

*/

/*
P2807 三角形计数

题目背景

三角形计数(triangle) 递推
题目描述

把大三角形的每条边n等分，将对应的等分点连接起来（连接线分别平行于三条边），这样一共会有多少三角形呢？编程来解决这个问题。
输入格式

第一行为整数t(≤100)，表示测试数据组数；接下来t行，每行一个正整数n(≤500)。
输出格式

对于每个n，输出一个正整数，表示三角形个数。
输入输出样例
输入 #1

3
1
2
3

输出 #1

1
5
13

说明/提示

n(≤500)

t(≤100)

code:
int main(){
	int t,i,n,s[501],f[501];
	cin>>t;
	for(i=1;i<=500;i++)s[i]=i*(i+1)/2;
	f[1]=1;f[2]=5;f[3]=13;
	for(i=4;i<=500;i++){
		f[i]=f[i-1]+2*i-1+s[i-1];
		i%2==1?f[i]+=(i-1)*(i-3)/4:f[i]+=(i-2)*(i-2)/4;
	}
	for(i=1;i<=t;i++)
		cin>>n,cout<<f[n]<<endl;
	return 0;
}

*/

/*
P2813 母舰

题目背景

广东汕头聿怀初中 Train#3 Problem 1

（有没有红警既视感~）
题目描述

在小A的星际大战游戏中，一艘强力的母舰往往决定了一场战争的胜负。一艘母舰的攻击力是普通的MA(Mobile Armor)无法比较的。

对于一艘母舰而言，它是由若干个攻击系统和若干个防御系统组成的。两艘母舰对决时，一艘母舰会选择用不同的攻击系统去攻击对面母舰的防御系统。当这个攻击系统的攻击力大于防御系统的防御力时，那个防御系统会被破坏掉。当一艘母舰的防御系统全部被破坏掉之后，所有的攻击都会攻击到敌方母舰本身上去造成伤害。

这样说，一艘母舰对对面的伤害在一定程度上是取决于选择的攻击对象的。

在瞬息万变的战场中，选择一个最优的攻击对象是非常重要的。所以需要写出一个战斗系统出来，判断出你的母舰最多能对对手造成多少伤害并加以实现。
输入格式

输入第一行两个整数M和N，表示对方母舰的防御系统数量和你的母舰的攻击系统数量。

接着M行每行一个整数每一个表示对方防御系统的防御力是多少。

接着N行每行一个整数每一个表示己方攻击系统的攻击力是多少。
输出格式

输出仅有一行，表示可以造成的最大伤害。
输入输出样例
输入 #1

3 5 
1000 
2000 
1200 
2100 
2000 
1200 
1000 
1000

输出 #1

2000

说明/提示

对于80%的数据有 1 <= N , M <= 1000

对于100%的数据有 1 <= N , M <= 100000

对样例的解释：

对方防御系统有3个，防御值为1000(a),2000(b),1200(c)，己方攻击系统有5个，攻击值为2100(d)，2000(e),1200(f),1000(g),1000(h)。第1轮攻击的最优方案是d攻击b，e攻击c，f攻击a，g和h攻击对方母舰本身，造成2000点伤害。

本题为转载题目~

code:
int m,n,s,i,t,tf[100005],wf[100005];//注：空间开太小会出问题 原因未知 特此写明
int main(){
    cin>>m>>n;
    for(i=0;i<m;i++)cin>>tf[i];
    for(i=0;i<n;i++)cin>>wf[i];
    sort(tf,tf+m);
    sort(wf,wf+n);
    for(t=0,i=0;i<n;i++){
        if(tf[t]==0)t++;
        if(tf[t]<wf[i] && tf[t]!=0)wf[i]=0,t++;
    }
    if(t+1<=m)cout<<0;
    else{
        for(i=0;i<n;i++)
            s+=wf[i];
    cout<<s;}
    return 0;
}

*/

/*
P2819 图的m着色问题

题目背景

给定无向连通图G和m种不同的颜色。用这些颜色为图G的各顶点着色，每个顶点着一种颜色。如果有一种着色法使G中每条边的2个顶点着不同颜色，则称这个图是m可着色的。图的m着色问题是对于给定图G和m种颜色，找出所有不同的着色法。
题目描述

对于给定的无向连通图G和m种不同的颜色，编程计算图的所有不同的着色法。
输入格式

第1行有3个正整数n，k 和m，表示给定的图G有n个顶点和k条边，m种颜色。顶点编号为1，2，…，n。接下来的k行中，每行有2个正整数u,v，表示图G 的一条边(u,v)。
输出格式

程序运行结束时，将计算出的不同的着色方案数输出。
输入输出样例
输入 #1

5 8 4
1 2
1 3
1 4
2 3
2 4
2 5
3 4
4 5

输出 #1

48

说明/提示

n<=100;k<=2500;

在n很大时保证k足够大。

保证答案不超过20000。

code:
int n,k,m,i,j,u,v,ans,g[101][101],color[10001];
bool b = 0;
void dfs(int x){
	if(x > n)ans++;
	else for(int i = 1;i <= m;i++){
            color[x] = i;
            for(int j = 1;j <= x;j++){
                if(g[j][x] && color[j] == color[x]){
                    b = 1;
                    break;
                }
            }
            if(b)b = 0;
            else dfs(x + 1);
        }
}
int main(){
	cin>>n>>k>>m;
	for(i = 1;i <= k;i++){
		cin>>u>>v;
		g[u][v] = 1;
		g[v][u] = 1;
	}
	dfs(1);
	cout<<ans;
	return 0;
}

*/

/*
P2837 [USACO08FEB]Dining Cows B

题目描述

为了避免餐厅过分拥挤，FJ要求奶牛们分2批就餐。每天晚饭前，奶牛们都会在餐厅前排队入内，按FJ的设想，所有第2批就餐的奶牛排在队尾，队伍的前半部分则由设定为第1批就餐的奶牛占据。由于奶牛们不理解FJ的安排，晚饭前的排队成了一个大麻烦。 第i头奶牛有一张标明她用餐批次D_i(1 <= D_i <= 2)的卡片。虽然所有N头奶牛排成了很整齐的队伍，但谁都看得出来，卡片上的号码是完全杂乱无章的。 在若干次混乱的重新排队后，FJ找到了一种简单些的方法：奶牛们不动，他沿着队伍从头到尾走一遍，把那些他认为排错队的奶牛卡片上的编号改掉，最终得到一个他想要的每个组中的奶牛都站在一起的队列，例如112222或111122。有的时候，FJ会把整个队列弄得只有1组奶牛（比方说，1111或222）。 你也晓得，FJ是个很懒的人。他想知道，如果他想达到目的，那么他最少得改多少头奶牛卡片上的编号。所有奶牛在FJ改卡片编号的时候，都不会挪位置。
输入格式

第1行: 1个整数：N * 第2..N+1行: 第i+1行是1个整数，为第i头奶牛的用餐批次D_i
输出格式

一行: 输出1个整数，为FJ最少要改几头奶牛卡片上的编号，才能让编号变成他设想中的样子。
输入输出样例
输入 #1

7
2
1
1
1
2
2
1

输出 #1

2

输入 #2

5
2
2
1
2
2

输出 #2

1

说明/提示

1 <= N <= 30000

code:
int n,i,d[30001],dp[30001][2];
int main(){//dp
    cin>>n;
    for (i=1;i<=n;++i)cin>>d[i];
    dp[1][2-d[1]]=1;
    dp[1][d[1]-1]=0;
    for (i=2;i<=n;++i)
        if (d[i]==1) dp[i][0]=dp[i-1][0],dp[i][1]=min(dp[i-1][1],dp[i-1][0])+1;
        else dp[i][0]=dp[i-1][0]+1,dp[i][1]=min(dp[i-1][1],dp[i-1][0]);
    dp[n][0]>dp[n][1]?printf("%d",dp[n][1]):printf("%d",dp[n][0]);
    return 0;
}

*/

/*
P2871 [USACO07DEC]Charm Bracelet S

题目描述

Bessie has gone to the mall's jewelry store and spies a charm bracelet. Of course, she'd like to fill it with the best charms possible from the N (1 ≤ N ≤ 3,402) available charms. Each charm i in the supplied list has a weight Wi (1 ≤ Wi ≤ 400), a 'desirability' factor Di (1 ≤ Di ≤ 100), and can be used at most once. Bessie can only support a charm bracelet whose weight is no more than M (1 ≤ M ≤ 12,880).

Given that weight limit as a constraint and a list of the charms with their weights and desirability rating, deduce the maximum possible sum of ratings.

有 NNN 件物品和一个容量为 MMM 的背包。第 iii 件物品的重量是 WiW_iWi?，价值是 DiD_iDi?。求解将哪些物品装入背包可使这些物品的重量总和不超过背包容量，且价值总和最大。
输入格式

* Line 1: Two space-separated integers: N and M

* Lines 2..N+1: Line i+1 describes charm i with two space-separated integers: Wi and Di

第一行：物品个数 NNN 和背包大小 MMM。

第二行至第 N+1N+1N+1 行：第 iii 个物品的重量 WiW_iWi? 和价值 DiD_iDi?。
输出格式

* Line 1: A single integer that is the greatest sum of charm desirabilities that can be achieved given the weight constraints

输出一行最大价值。
输入输出样例
输入 #1

4 6
1 4
2 6
3 12
2 7

输出 #1

23

code:
int n,v,f[12881],i,j,w,m;
int main(){
    cin>>n>>v;
    for(i=1;i<=n;i++){
        cin>>w>>m;
        for(j=v;j>0;j--)
            if(w<=j) 
                f[j]=max(f[j],f[j-w]+m); 
    }
    printf("%d",f[v]); 
    return 0;    
}

*/

/*
P2873 [USACO07DEC]Mud Puddles S

题目描述

Farmer John is leaving his house promptly at 6 AM for his daily milking of Bessie. However, the previous evening saw a heavy rain, and the fields are quite muddy. FJ starts at the point (0, 0) in the coordinate plane and heads toward Bessie who is located at (X, Y) (-500 ≤ X ≤ 500; -500 ≤ Y ≤ 500). He can see all N (1 ≤ N ≤ 10,000) puddles of mud, located at points (Ai, Bi) (-500 ≤ Ai ≤ 500; -500 ≤ Bi ≤ 500) on the field. Each puddle occupies only the point it is on.

Having just bought new boots, Farmer John absolutely does not want to dirty them by stepping in a puddle, but he also wants to get to Bessie as quickly as possible. He's already late because he had to count all the puddles. If Farmer John can only travel parallel to the axes and turn at points with integer coordinates, what is the shortest distance he must travel to reach Bessie and keep his boots clean? There will always be a path without mud that Farmer John can take to reach Bessie.

清早6：00，Farmer John就离开了他的屋子，开始了他的例行工作：为贝茜挤奶。前一天晚上，整个农场刚经受过一场瓢泼大雨的洗礼，于是不难想见，FJ 现在面对的是一大片泥泞的土地。FJ的屋子在平面坐标(0, 0)的位置，贝茜所在的牛棚则位于坐标(X,Y) (-500 <= X <= 500; -500 <= Y <= 500)处。当然咯， FJ也看到了地上的所有N(1 <= N <= 10,000)个泥塘，第i个泥塘的坐标为 (A_i, B_i) (-500 <= A_i <= 500；-500 <= B_i <= 500)。每个泥塘都只占据了它所在的那个格子。 Farmer John自然不愿意弄脏他新买的靴子，但他同时想尽快到达贝茜所在的位置。为了数那些讨厌的泥塘，他已经耽搁了一些时间了。如果Farmer John 只能平行于坐标轴移动，并且只在x、y均为整数的坐标处转弯，那么他从屋子门口出发，最少要走多少路才能到贝茜所在的牛棚呢？你可以认为从FJ的屋子到牛棚总是存在至少一条不经过任何泥塘的路径。
输入格式

* Line 1: Three space-separate integers: X, Y, and N.

* Lines 2..N+1: Line i+1 contains two space-separated integers: Ai and Bi
输出格式

* Line 1: The minimum distance that Farmer John has to travel to reach Bessie without stepping in mud.
输入输出样例
输入 #1

1 2 7
0 2
-1 3
3 1
1 1
4 2
-1 1
2 2

输出 #1

11

code:
int ex,ey,n,nx,ny,front=1,rear=1,dx[]={-1,0,0,1},dy[]={0,-1,1,0};
map<int,map<int,bool>>mud;
struct node{
    int x,y,step;
}q[1000001];//非常极限 容易RE爆 建议少用stl
int main(){//bfs 广度搜索
    cin>>ex>>ey>>n;
    for(int i=0,a,b;i<n;i++)
        cin>>a>>b,mud[a][b]=true;
    while(front<=rear){
        node f=q[front++];
        for(int i=0;i<4;i++){
            nx=f.x+dx[i],ny=f.y+dy[i];
            if(nx<-500||ny<-500||nx>500||ny>500||mud[nx][ny])continue;
            mud[nx][ny]=true;
            q[++rear]=(node){nx,ny,f.step+1};
            if(nx==ex&&ny==ey){
                printf("%d",q[rear].step);
                return 0;
            }
        }
    }
    return 0;
}

*/

/*
P2908 [USACO08OPEN]Word Power S

题目描述

Farmer John wants to evaluate the quality of the names of his N (1 <= N <= 1000) cows. Each name is a string with no more than 1000 characters, all of which are non-blank.

He has created a set of M (1 <= M <= 100) 'good' strings (no

longer than 30 characters and fully non-blank). If the sequence letters of a cow's name contains the letters of a 'good' string in the correct order as a subsequence (i.e., not necessarily all next to each other), the cow's name gets 1 quality point.

All strings is case-insensitive, i.e., capital letters and lower case letters are considered equivalent. For example, the name 'Bessie' contains the letters of 'Be', 'sI', 'EE', and 'Es' in the correct order, but not 'is' or 'eB'. Help Farmer John determine the number of quality points in each of his cow's names.

约翰想要计算他那N(l < =N <= 1000)只奶牛的名字的能量.每只奶牛的名字由不超过1000个字 符构成，没有一个名字是空字体串.

约翰有一张“能量字符串表”，上面有M(1 < =M < =100)个代表能量的字符串.每个字符串 由不超过30个字体构成，同样不存在空字符串.一个奶牛的名字蕴含多少个能量字符串，这个名 字就有多少能量.所谓“蕴含”，是指某个能量字符串的所有字符都在名字串中按顺序出现（不 一定一个紧接着一个）.

所有的大写字母和小写字母都是等价的.比如，在贝茜的名字“Bessie”里，蕴含有“Be” “si” “EE”以及“Es”等等字符串，但不蕴含“Ls”或“eB” .请帮约翰计算他的奶牛的名字 的能量.
输入格式

* Line 1: Two space-separated integers: N and M

* Lines 2..N+1: Line i+1 contains a string that is the name of the ith cow

* Lines N+2..N+M+1: Line N+i+1 contains the ith good string
输出格式

* Lines 1..N+1: Line i+1 contains the number of quality points of the ith name
输入输出样例
输入 #1

5 3 
Bessie 
Jonathan 
Montgomery 
Alicia 
Angola 
se 
nGo 
Ont 

输出 #1

1 
1 
2 
0 
1 

说明/提示

There are 5 cows, and their names are "Bessie", "Jonathan", "Montgomery", "Alicia", and "Angola". The 3 good strings are "se", "nGo", and "Ont".

"Bessie" contains "se", "Jonathan" contains "Ont", "Montgomery" contains both "nGo" and "Ont", Alicia contains none of the good strings, and "Angola" contains "nGo".

code:
int n,m,tot[1001]={0};
string nx[1001],en[101];
int f(string n,string e){
    int now=-1,po=0;
    for(int i=0;i<e.size();i++){
        po=n.find(e[i],now+1);
        if(po==n.npos)return 0;
        now=po;
    }
    return 1;
}
int main(){
    cin>>n>>m;
    for(int i=1;i<=n;i++){
        cin>>nx[i];
        for(int j=0;j<nx[i].size();j++)
            if(nx[i][j]>96)
                nx[i][j]-=32;
    }
    for(int i=1;i<=m;i++){
        cin>>en[i];
        for(int j=0;j<en[i].size();j++)
            if(en[i][j]>96)
                en[i][j]-=32;
        for(int j=1;j<=n;j++)
            if(f(nx[j],en[i]))
                tot[j]++;
    }
    for(int i=1;i<=n;i++)
        cout<<tot[i]<<endl;
    return 0;
}

*/

/*
P2909 [USACO08OPEN]Cow Cars S

题目描述

N (1 <= N <= 50,000) cows conveniently numbered 1..N are driving in separate cars along a highway in Cowtopia. Cow i can drive in any of M different high lanes (1 <= M <= N) and can travel at a maximum speed of S_i (1 <= S_i <= 1,000,000) km/hour.

After their other bad driving experience, the cows hate collisions and take extraordinary measures to avoid them. On this highway, cow i reduces its speed by D (0 <= D <= 5,000) km/hour for each cow in front of it on the highway (though never below 0 km/hour). Thus, if there are K cows in front of cow i, the cow will travel at a speed of max[S_i - D * K, 0]. While a cow might actually travel faster than a cow directly in front of it, the cows are spaced far enough apart so crashes will not occur once cows slow down as

described,

Cowtopia has a minimum speed law which requires everyone on the highway to travel at a a minimum speed of L (1 <= L <= 1,000,000) km/hour so sometimes some of the cows will be unable to take the highway if they follow the rules above. Write a program that will find the maximum number of cows that can drive on the highway while obeying the minimum speed limit law.

编号为 111 到 NNN 的 NNN 只奶牛正各自驾着车打算在牛德比亚的高速公路上飞驰．高速公路有 M(1≤M≤N)M(1\leq M\leq N)M(1≤M≤N) 条车道．奶牛 iii 有一个自己的车速上限Si(1≤Si≤106)S_i(1\leq S_i\leq 10^6)Si?(1≤Si?≤106)．

在经历过糟糕的驾驶事故之后，奶牛们变得十分小心，避免碰撞的发生．每条车道上，如果某一只奶牛 iii 的前面有 kkk 只奶牛驾车行驶，那奶牛 iii 的速度上限就会下降 k×Dk\times Dk×D 个单位，也就是说，她的速度不会超过 Si?k×D(0≤D≤5000)S_i - k \times D(0\leq D\leq 5000)Si??k×D(0≤D≤5000)，当然如果这个数是负的，那她的速度将是 000．牛德比亚的高速会路法规定，在高速公路上行驶的车辆时速不得低于(1≤L≤1,000,000)(1\leq L\leq 1,000,000)(1≤L≤1,000,000)．那么，请你计算有多少奶牛可以在高速公路上行驶呢？
输入格式

* Line 1: Four space-separated integers: N, M, D, and L

* Lines 2..N+1: Line i+1 describes cow i's initial speed with a single integer: S_i
输出格式

* Line 1: A single integer representing the maximum number of cows that can use the highway
输入输出样例
输入 #1

3 1 1 5 
5 
7 
5 

输出 #1

2 

说明/提示

There are three cows with one lane to drive on, a speed decrease of 1, and a minimum speed limit of 5.

Two cows are possible, by putting either cow with speed 5 first and the cow with speed 7 second.

code:
int n,m,d,l,s,ans,a[50001];
int main(){
    cin>>n>>m>>d>>l;
    for(int i=1;i<=n;i++)
        cin>>a[i];
    sort(a+1,a+1+n);
    for(int i=1;i<=m;i++){
        ans=0;
        for(int j=1;j<=n;j++)
            if(a[j] && (a[j]-ans*d>=l || (a[j]<ans*d && l==0)))
                ans++,s++,a[j]=0;
    }
    cout<<s;
    return 0;
}

*/

/*
P2910 [USACO08OPEN]Clear And Present Danger S

题目描述

Farmer John is on a boat seeking fabled treasure on one of the N (1 <= N <= 100) islands conveniently labeled 1..N in the Cowribbean Sea.

The treasure map tells him that he must travel through a certain sequence A_1, A_2, ..., A_M of M (2 <= M <= 10,000) islands, starting on island 1 and ending on island N before the treasure will appear to him. He can visit these and other islands out of order and even more than once, but his trip must include the A_i sequence in the order specified by the map.

FJ wants to avoid pirates and knows the pirate-danger rating (0 <= danger <= 100,000) between each pair of islands. The total danger rating of his mission is the sum of the danger ratings of all the paths he traverses.

Help Farmer John find the least dangerous route to the treasure that satisfies the treasure map's requirement.
输入格式

* Line 1: Two space-separated integers: N and M

* Lines 2..M+1: Line i+1 describes the i_th island FJ must visit with a single integer: A_i

* Lines M+2..N+M+1: Line i+M+1 contains N space-separated integers that are the respective danger rating of the path between island i and islands 1, 2, ..., and N, respectively. The ith integer is always zero.
输出格式

* Line 1: The minimum danger that Farmer John can encounter while obtaining the treasure.
题意翻译

农夫约翰正驾驶一条小艇在牛勒比海上航行．

海上有 N(1≤N≤100)N(1\leq N\leq 100)N(1≤N≤100) 个岛屿，用 111 到 NNN 编号．约翰从 111 号小岛出发，最后到达 NNN 号小岛．

一张藏宝图上说，如果他的路程上经过的小岛依次出现了 A1,A2,…,AM(2≤M≤10000)A_1,A_2,\dots ,A_M(2\leq M\leq 10000)A1?,A2?,…,AM?(2≤M≤10000) 这样的序列（不一定相邻），那他最终就能找到古老的宝藏． 但是，由于牛勒比海有海盗出没．约翰知道任意两个岛屿之间的航线上海盗出没的概率，他用一个危险指数 Di,j(0≤Di,j≤100000)D_{i,j}(0\leq D_{i,j}\leq 100000)Di,j?(0≤Di,j?≤100000) 来描述．他希望他的寻宝活动经过的航线危险指数之和最小．那么，在找到宝藏的前提下，这个最小的危险指数是多少呢？

输入输出格式

输入格式：

第一行：两个用空格隔开的正整数 NNN 和 MMM。

第二到第 M+1M+1M+1 行：第 i+1i+1i+1 行用一个整数 AiA_iAi? 表示 FJ 必须经过的第 iii 个岛屿

第 M+2M+2M+2 到第 N+M+1N+M+1N+M+1 行：第 i+M+1i+M+1i+M+1 行包含 NNN 个用空格隔开的非负整数分别表示 iii 号小岛到第 1…N1\dots N1…N 号小岛的航线各自的危险指数。保证第 iii 个数是 000。

输出格式 第一行：FJ 在找到宝藏的前提下经过的航线的危险指数之和的最小值。

说明 这组数据中有三个岛屿，藏宝图要求 FJ 按顺序经过四个岛屿：111 号岛屿、222 号岛屿、回到 111 号岛屿、最后到 333 号岛屿。每条航线的危险指数也给出了：航路(1,2),(2,3),(3,1)(1,2),(2,3),(3,1)(1,2),(2,3),(3,1) 和它们的反向路径的危险指数分别是 5,2,15,2,15,2,1。

FJ 可以通过依次经过 1,3,2,3,1,31,3,2,3,1,31,3,2,3,1,3 号岛屿以 777 的最小总危险指数获得宝藏。这条道路满足了奶牛地图的要求 (1,2,1,3)(1,2,1,3)(1,2,1,3)。我们避开了 111 号和 222 号岛屿之间的航线，因为它的危险指数太大了。

注意：测试数据中 aaa 到 bbb 的危险指数不一定等于 bbb 到 aaa 的危险指数！

Translated by @LJC00125
输入输出样例
输入 #1

3 4 
1 
2 
1 
3 
0 5 1 
5 0 2 
1 2 0 

输出 #1

7 

说明/提示

There are 3 islands and the treasure map requires Farmer John to visit a sequence of 4 islands in order: island 1, island 2, island 1 again, and finally island 3. The danger ratings of the paths are given: the paths (1, 2); (2, 3); (3, 1) and the reverse paths have danger ratings of 5, 2, and 1, respectively.

He can get the treasure with a total danger of 7 by traveling in the sequence of islands 1, 3, 2, 3, 1, and 3. The cow map's requirement (1, 2, 1, and 3) is satisfied by this route. We avoid the path between islands 1 and 2 because it has a large danger rating.

输入输出格式

输入格式：

第一行：两个用空格隔开的正整数N和M

第二到第M+1行：第i+1行用一个整数Ai表示FJ必须经过的第i个岛屿

第M+2到第N+M+1行：第i+M+1行包含N个用空格隔开的非负整数分别表示i号小岛到第1...N号小岛的航线各自的危险指数。保证第i个数是0。

输出格式

第一行：FJ在找到宝藏的前提下经过的航线的危险指数之和的最小值。

说明

这组数据中有三个岛屿，藏宝图要求FJ按顺序经过四个岛屿：1号岛屿、2号岛屿、回到1号岛屿、最后到3号岛屿。每条航线的危险指数也给出了：航路(1，2)、(2，3)、(3，1)和它们的反向路径的危险指数分别是5、2、1。

FJ可以通过依次经过1、3、2、3、1、3号岛屿以7的最小总危险指数获得宝藏。这条道路满足了奶牛地图的要求（1，2，1，3）。我们避开了1号和2号岛屿之间的航线，因为它的危险指数太大了。

注意：测试数据中a到b的危险指数不一定等于b到a的危险指数！

code:
int n,m,ans,dis[101][101],a[10001];
int main(){//图论 Floyd
    cin>>n>>m;
	for(int i=1;i<=m;i++)
        cin>>a[i];
	for(int i=1;i<=n;i++)
		for(int j=1;j<=n;j++)
            cin>>dis[i][j];
	for(int k=1;k<=n;k++)
		for(int i=1;i<=n;i++)
			for(int j=1;j<=n;j++)
				dis[i][j]=min(dis[i][k]+dis[k][j],dis[i][j]);
	for(int i=2;i<=m;i++)
		ans+=dis[a[i-1]][a[i]];
    cout<<ans;
	return 0;
}

*/

/*
P2913 [USACO08OCT]Wheel Rotation G

题目描述

Farmer John has an old-time thresher (wheat harvester) that requires belts to be installed on various gears to turn the parts. The engine drives pulley 1 in a clockwise direction which attaches via a belt to pulley 2. Pulley 2 attaches via a belt to pulley 3 and so on through a total of N (2 <= N <= 1,000) pulleys (and N-1 belts).

The diagram above depicts the two ways a belt can be installed between two gears. In this illustration, pulley 1's belt directly drives pulley 2 (a 'straight' connection) and thus they will rotate in the same direction. Pulley 3 drives pulley 4 via a 'crossed belt' that reverses the direction of the rotation.

Given a list of the belt types that connect the pulleys along with the fact that pulley 1 is driven in a clockwise direction by the engine, determine the drive direction of pulley N. Each belt is described by three integers:

* S_i -- the driving (source) pulley 
* D_i -- the driven (destination) pulley 
* C_i -- the connection type (0=straight, 1=crossed) 
Unfortunately, FJ lists the belts in random order. 
By way of example, consider the illustration below. N = 4, and pulley 1 is driven clockwise by the thresher engine. Straight 
belts drive pulley 2 and then pulley 3, so they rotate clockwise. The crosswise belt reverses the rotation direction so pulley 4 (pulley N) rotates counterclockwise. 

POINTS: 70 约翰有一个过时的收割机，需要在它的各种滑轮上装配皮带才能让收割机的各个部分运作起 来.引擎能够驱动滑轮1向顺时针方向转动，滑轮1通过一条皮带又连接到滑轮2.滑轮2又通过一 条皮带连接到滑轮3，等等，总共有N(2 <= N <= 1000)个滑轮和N - 1条皮带.

皮带连接两个滑轮有两种方式：直接连接和交叉连接.直接连接的两个滑轮旋转方向相同， 即同为顺时针或同为逆时针.交叉连接的两个滑轮旋转方向相反.

现在给出一个列表，里面列出所有皮带的连接方式.已经知道滑轮1被引擎驱动着向顺时针方 向转动.每一条皮带由下面三个数定义：

?驱动滑轮S，输入驱动力的滑轮.

?被驱动滑轮D;，被驱使转动的滑轮.

?连接类型C，0表示直接连接，1表示交叉连接.

不幸的是，约翰的这个列表中，皮带的顺序是混乱的.所以请你写一个程序来求出滑轮N的 转动方向.
输入格式

* Line 1: A single integer: N

* Lines 2..N: Each line describes a belt with three integers: S_i, D_i, and C_i
输出格式

* Line 1: A single integer that is the rotation direction for pulley N (0=clockwise, 1=counterclockwise)
输入输出样例
输入 #1

4 
2 3 0 
3 4 1 
1 2 0 

输出 #1

1 

说明/提示

As in the example illustration.

code:#include<bits/stdc++.h>
using namespace std;
int n,a,b,c,d[1001],e[1001],f[1001],g[1001],h[1001],ans;
int main(){
    cin>>n;
	for(int i=1;i<n;i++){
        cin>>a>>b>>c;
        f[i]=e[a];
        e[a]=i;
		h[b]++;
		d[i]=b;
        g[i]=c;
	}
	for(int i=1;i<=n;i++){
		if(h[i]==0)
			for(int j=i;j;j=d[e[j]])
				ans=ans^g[e[j]];
        cout<<ans;
		return 0;
	}
}

*/

/*
P2925 [USACO08DEC]Hay For Sale S

题目描述

Farmer John suffered a terrible loss when giant Australian cockroaches ate the entirety of his hay inventory, leaving him with nothing to feed the cows. He hitched up his wagon with capacity C (1 <= C <= 50,000) cubic units and sauntered over to Farmer Don's to get some hay before the cows miss a meal.

Farmer Don had a wide variety of H (1 <= H <= 5,000) hay bales for sale, each with its own volume (1 <= V_i <= C). Bales of hay, you know, are somewhat flexible and can be jammed into the oddest of spaces in a wagon.

FJ carefully evaluates the volumes so that he can figure out the largest amount of hay he can purchase for his cows.

Given the volume constraint and a list of bales to buy, what is the greatest volume of hay FJ can purchase? He can't purchase partial bales, of course. Each input line (after the first) lists a single bale FJ can buy.

约翰遭受了重大的损失：蟑螂吃掉了他所有的干草，留下一群饥饿的牛．他乘着容量为C(1≤C≤50000)个单位的马车，去顿因家买一些干草． 顿因有H(1≤H≤5000)包干草，每一包都有它的体积Vi(l≤Vi≤C).约翰只能整包购买，

他最多可以运回多少体积的干草呢？
输入格式

* Line 1: Two space-separated integers: C and H

* Lines 2..H+1: Each line describes the volume of a single bale: V_i
输出格式

* Line 1: A single integer which is the greatest volume of hay FJ can purchase given the list of bales for sale and constraints.
题意翻译

题目描述
农民john面临一个很可怕的事实，因为防范失措他存储的所有稻草给澳大利亚蟑螂吃光了，他将面临没有稻草喂养奶牛的局面。在奶牛断粮之前，john拉着他的马车到农民Don的农场中买一些稻草给奶牛过冬。已知john的马车可以装的下C(1 <= C <=50,000)立方的稻草。
农民Don有H(1 <= H <= 5,000)捆体积不同的稻草可供购买，每一捆稻草有它自己的体积(1 <= V_i <= C)。面对这些稻草john认真的计算如何充分利用马车的空间购买尽量多的稻草给他的奶牛过冬。
现在给定马车的最大容积C和每一捆稻草的体积Vi，john如何在不超过马车最大容积的情况下买到最大体积的稻草？他不可以把一捆稻草分开来买。

输入输出格式
输入格式：
第一行两个整数，分别为C和H
第2..H+1行:每一行一个整数代表第i捆稻草的体积Vi

输出格式：

一个整数，为john能买到的稻草的体积。
输入输出样例
输入样例#1：
7 3
2
6
5
输出样例#1：
7

翻译提供者：黑客集团_鬼
输入输出样例
输入 #1

7 3 
2 
6 
5 

输出 #1

7 

说明/提示

The wagon holds 7 volumetric units; three bales are offered for sale with volumes of 2, 6, and 5 units, respectively.

Buying the two smaller bales fills the wagon.

code:
int n,m,i,j,f[50001],a[5001];
int main(){
    cin>>m>>n;
    for (i=1;i<=n;i++) 
        cin>>a[i];
    for (i=1;i<=n;i++){
        for (j=m;j>=a[i];j--)
            f[j]=max(f[j],f[j-a[i]]+a[i]);
        if (f[m]==m) {
            cout<<f[m];
            return 0;
        }
    }
    cout<<f[m];
    return 0;
}

*/

/*
P2945 [USACO09MAR]Sand Castle S

题目描述

Farmer John has built a sand castle! Like all good castles, the walls have crennelations, that nifty pattern of embrasures (gaps) and merlons (filled spaces); see the diagram below. The N (1 <= N <= 25,000) merlons of his castle wall are conveniently numbered 1..N; merlon i has height M_i (1 <= M_i <= 100,000); his merlons often have varying heights, unlike so many.

He wishes to modify the castle design in the following fashion: he has a list of numbers B_1 through B_N (1 <= B_i <= 100,000), and wants to change the merlon heights to those heights B_1, ..., B_N in some order (not necessarily the order given or any other order derived from the data).

To do this, he has hired some bovine craftsmen to raise and lower the merlons' heights. Craftsmen, of course, cost a lot of money. In particular, they charge FJ a total X (1 <= X <= 100) money per unit height added and Y (1 <= Y <= 100) money per unit height

reduced.

FJ would like to know the cheapest possible cost of modifying his sand castle if he picks the best permutation of heights. The answer is guaranteed to fit within a 32-bit signed integer.

Note: about 40% of the test data will have N <= 9, and about 60% will have N <= 18.

约翰用沙子建了一座城堡．正如所有城堡的城墙，这城墙也有许多枪眼，两个相邻枪眼中间那部分叫作“城齿”． 城墙上一共有N(1≤N≤25000)个城齿，每一个都有一个高度Mi.(1≤Mi≤100000)．现在约翰想把城齿的高度调成某种顺序下的Bi，B2，…，BN(1≤Bi≤100000). -个城齿每提高一个单位的高度，约翰需要X(1≤X≤100)元；每降低一个单位的高度，约翰需要Y(1≤y≤100)元． 问约翰最少可用多少钱达到目的．数据保证答案不超过2^31-1．
输入格式

* Line 1: Three space-separated integers: N, X, and Y

* Lines 2..N+1: Line i+1 contains the two space-separated integers: M_i and B_i
输出格式

* Line 1: A single integer, the minimum cost needed to rebuild the castle
输入输出样例
输入 #1

3 6 5 
3 1 
1 2 
1 2 

输出 #1

11 

说明/提示

FJ's castle starts with heights of 3, 1, and 1. He would like to change them so that their heights are 1, 2, and 2, in some order. It costs 6 to add a unit of height and 5 to remove a unit of height.

FJ reduces the first merlon's height by 1, for a cost of 5 (yielding merlons of heights 2, 1, and 1). He then adds one unit of height to the second merlon for a cost of 6 (yielding merlons of heights 2, 2, and 1).

code:
int n,x,y,ans,a[25000],b[25000];
int main(){
    cin>>n>>x>>y;
    for(int i=0;i<n;i++)  
        cin>>a[i]>>b[i];
    sort(a,a+n);
    sort(b,b+n);
    for(int i=0;i<n;i++)
        if(a[i]<b[i])  ans+=(b[i]-a[i])*x;
        else  ans+=(a[i]-b[i])*y;
    cout<<ans;
    return 0;
}

*/

/*
P2952 [USACO09OPEN]Cow Line S

题目描述

Farmer John's N cows (conveniently numbered 1..N) are forming a line. The line begins with no cows and then, as time progresses, one by one, the cows join the line on the left or right side. Every once in a while, some number of cows on the left or right side of the line all leave the line to go graze in their favorite pasture.

FJ has trouble keeping track of all the cows in the line. Please help him.

The cows enter the line in numerical order 1..N, and once a cow leaves the line she never re-enters it. Your program will be given S (1 <= S <= 100,000) input specifications; each appears on a single line and is one of two types:

* A cow enters the line (a parameter indicates whether on the left or right).

* K cows leave the line from the left or right side (supplied parameters define both the number of cows and which side).

Input lines never request an operation that can not be performed.

After all the input lines have been processed, your program should print the cows in the line in order from left to right. The final line is guaranteed to be non-empty at the end of the input

specifications.

约翰的N只奶牛（编为1到N号）正在直线上排队．直线上开始的时候一只牛也没有．接下来发生了S(1≤S≤100000)次事件，一次事件可能是以下四种情况之一：

．一只奶牛加入队伍的左边（输入“AL”）．

．一只奶牛加入队伍的右边（输入“AR”）．

·K只队伍左边奶牛离开（输入“DLK”）．

·K只队伍右边奶牛离开（输入“DRK”）．

请求出最后的队伍是什么样．

数据保证离开的奶牛不会超过队伍里的奶牛数，最后的队伍不空
输入格式

* Line 1: A single integer: S

* Lines 2..S+1: Line i+1 contains specification i in one of four formats:

* A L -- a cow arrives on the Left of the line

* A R -- a cow arrives on the Right of the line

* D L K -- K cows depart the Left side of the line

* D R K -- K cows depart the Right side of the line

第1行输入S，之后S行每行描述一次事件，格式如题目描述所示
输出格式

* Lines 1..??: Print the numbers of the cows in the line in order from left to right, one number per line.

由左到右输出队伍最后的情况．
输入输出样例
输入 #1

10 
A L 
A L 
A R 
A L 
D R 2 
A R 
A R 
D L 1 
A L 
A R 

输出 #1

7 
2 
5 
6 
8 

说明/提示

Input Resulting Cow Line

A L 1

A L 2 1

A R 2 1 3

A L 4 2 1 3

D R 2 4 2

A R 4 2 5

A R 4 2 5 6

D L 1 2 5 6

A L 7 2 5 6

A R 7 2 5 6 8

感谢@ ws_fuweidong 提供翻译。

code:#include<bits/stdc++.h>
using namespace std;
deque < int > Q;
int main() {//stl deque 双向队列
	int n, c = 1, k;
	char a, b;
	cin >> n;
	for (int i = 1; i <= n; i++) {
		cin >> a >> b;
		if (a == 'A' && b == 'L') Q.push_front(c++);//前方推数
		else if (a == 'A' && b == 'R') Q.push_back(c++);//后方推数
        else if (a == 'D' && b == 'L') {
            cin >> k;
            for (int j = 1; j <= k; j++) 
                Q.pop_front();//前方丢数
        }
        else if (a == 'D' && b == 'R') {
            cin >> k;
            for (int j = 1; j <= k; j++) 
                Q.pop_back();//后方丢数
        }
	}
	while (!Q.empty()) {
        cout << Q.front() << endl;
        Q.pop_front();
    }
	return 0;
}

*/

/*
P2957 [USACO09OCT]Barn Echoes G

题目描述

The cows enjoy mooing at the barn because their moos echo back, although sometimes not completely. Bessie, ever the excellent

secretary, has been recording the exact wording of the moo as it goes out and returns. She is curious as to just how much overlap there is.

Given two lines of input (letters from the set a..z, total length in the range 1..80), each of which has the wording of a moo on it, determine the greatest number of characters of overlap between one string and the other. A string is an overlap between two other strings if it is a prefix of one string and a suffix of the other string.

By way of example, consider two moos:

moyooyoxyzooo

yzoooqyasdfljkamo

The last part of the first string overlaps 'yzooo' with the first part of the second string. The last part of the second string

overlaps 'mo' with the first part of the first string. The largest overlap is 'yzooo' whose length is 5.

POINTS: 50

奶牛们非常享受在牛栏中哞叫，因为她们可以听到她们哞声的回音。虽然有时候并不能完全听到完整的回音。Bessie曾经是一个出色的秘书，所以她精确地纪录了所有的哞叫声及其回声。她很好奇到底两个声音的重复部份有多长。

输入两个字符串（长度为1到80个字母），表示两个哞叫声。你要确定最长的重复部份的长度。两个字符串的重复部份指的是同时是一个字符串的前缀和另一个字符串的后缀的字符串。

我们通过一个例子来理解题目。考虑下面的两个哞声：

moyooyoxyzooo

yzoooqyasdfljkamo

第一个串的最后的部份"yzooo"跟第二个串的第一部份重复。第二个串的最后的部份"mo"跟第一个串的第一部份重复。所以"yzooo"跟"mo"都是这2个串的重复部份。其中，"yzooo"比较长，所以最长的重复部份的长度就是5。
输入格式

* Lines 1..2: Each line has the text of a moo or its echo
输出格式

* Line 1: A single line with a single integer that is the length of the longest overlap between the front of one string and end of the other.
输入输出样例
输入 #1

abcxxxxabcxabcd 
abcdxabcxxxxabcx 

输出 #1

11 

说明/提示

'abcxxxxabcx' is a prefix of the first string and a suffix of the second string.

code:
string a,b;
int main(){//stl string subtr
	cin>>a>>b; 
    if(a.size()>b.size())
        swap(a,b);
	for(int x=a.size()-1;x>0;x--){
		if(a.substr(0,x)==b.substr(b.size()-x,x) || b.substr(0,x)==a.substr(a.size()-x,x)){
            cout<<x;
            break;
        }
    }
    return 0;
}

*/

/*
P2958 [USACO09OCT]Papaya Jungle G

题目描述

Bessie has wandered off the farm into the adjoining farmer's land. He raises delicious papaya fruit, which is a delicacy for cows. The papaya jungle is partitioned into a grid of squares with R rows and C columns (1 <= R <= 40, 1 <= C <= 40), as is popular in Wisconsin. Bessie can travel from a given square to any existing adjacent square whose route is parallel to the X or Y axis. So in the

following diagram, if Bessie is at the square labeled 'B', she can travel to any of the squares labeled 'T':

.T. TBT .T. Bessie always starts out by munching the papayas in square

(row=1,col=1). After she's done with one square, Bessie always uses her trusty binoculars to count the low-hanging fruit in each of the adjacent squares. She then always moves to the square with the most visible uneaten fruit (a square that happily is always unique).

Sooner or later, following this rule, Bessie always ends up in square (R,C) and eats the fruit there.

Given the dimensions of the papaya jungle and the amount of fruit F_ij in each square (1 <= F_ij <= 100), determine the total number of fruit Bessie consumes for a given papaya jungle.

POINTS: 80

Bessie不小心游荡出Farmer John的田地，而走进了相邻的农民的地里。她举起一个木瓜，木瓜对奶牛来说可是不可多得得美味。这个木瓜林像一般的威斯康星州的田地一样被分割成一个R行C列的网格(1 <= R <= 40, 1 <= C <= 40)。Bessie可以从一个格沿着一条跟X轴或Y轴平行的直线走到邻接的另一个格。Bessie发现一开始她自己在木瓜林的(1,1)，也就是第一行第一列慢悠悠地咀嚼着木瓜。

Bessie总是用她最信赖地双筒望远镜去数每一个邻接的格里挂着的木瓜的数目。然后她就游荡到那个有最多没有被吃掉的木瓜的邻接的格子（保证这样的格子只有一个）。

按照这种移动方法，最终Bessie总是会在(R,C)停止然后吃掉那里的木瓜。

给定这个木瓜林的大小及每个格的木瓜数F_ij(1 <= F_ij <= 100), 要求Bessie一共吃了多少个木瓜。
输入格式

* Line 1: Two space-separated integers: R and C

* Lines 2..R+1: Line i+1 describes row i of the jungle with C

space-separated integers that tell how many fruit are in each square: F_i1, F_i2, ..., F_iC
输出格式

* Line 1: A single integer that is the total number of papayas that Bessie eats by the time she finishes off the papayas at the barn in the lower right corner at coordinate (R,C).
输入输出样例
输入 #1

3 4 
3 3 4 5 
4 5 3 2 
1 7 4 2 

输出 #1

39 

说明/提示

Three rows; four columns. Bessie starts in upper left corner at the '3'.

Bessie eats the papayas in the order given by the letters next to the numbers below:

(1,1) ---> (1,C)

(1,1) 3a 3 4g 5h (1,C)

| 4b 5c 3f 2i |

(R,1) 1 7d 4e 2j (R,C)

(R,1) ---> (R,C)

She declines to eat 4 of the papayas but consumes 39 (visiting all but two squares of the grid).

code:
int r,c,mx,my,tx,ty,sum,a[41][41],dx[4]={1,-1,0,0},dy[4]={0,0,1,-1};
void dfs(int x,int y){
	sum=sum+a[x][y];
	a[x][y]=0;
	if(x==r && y==c)
		return;
	for(int i=0,ans=0;i<4;i++)
		if(x+dx[i]>=1 && x+dx[i]<=r && y+dy[i]>=1 && y+dy[i]<=c && a[x+dx[i]][y+dy[i]]>ans)
			ans=a[x+dx[i]][y+dy[i]],mx=x+dx[i],my=y+dy[i];
	dfs(mx,my);	
}
int main(){
	cin>>r>>c;
	for(int i=1;i<=r;i++)
		for(int j=1;j<=c;j++)
			cin>>a[i][j];
	dfs(1,1);
	cout<<sum;
    return 0;
}

*/

/*
P2959 [USACO09OCT]The Leisurely Stroll G

题目描述

Bessie looks out the barn door at the beautiful spring day and thinks to herself, 'I'd really like to enjoy my walk out to the pastures for the tender spring grass.' She knows that once she leaves the barn, she will traverse a path for a while, take one of two choices that lead to other paths, follow one of them, take one of two other choices, and continue on until the path leads to a verdant pasture.

She decides to make the set of path choices that enables her to walk over the greatest number of cow paths on her way to breakfast. Given the description of these paths, determine how many cow paths she traverses, presuming that she commences choosing various paths as soon as she leaves the barn.

The farm has P (1 <= P <= 1,000) pastures that are lead to by P-1 choice-nodes (range 1..P-1) connected by paths. From the barn (which is node 1), only one set of path traversals exists to reach any choice-node or pasture.

Consider this set of paths (lines), pastures ('%'), and the highlighted ('#') route to a pasture on the right:


                 %                             %
                /                             /
      2----%   7----8----%          2----%   7####8----%
     / \      /      \             # #      #      #
    1   5----6        9----%      1   5####6        9----%
     \   \    \        \           \   \    \        #
      \   %    %        %           \   %    %        %
       \                             \
        3-----%                       3-----%
         \                             \
          4----%                        4----%
           \                             \
            %                             %

The pasture reached from choice-node 9 is one of two that enable Bessie to traverse seven different cowpaths on the way to breakfast. These are the 'furthest' pastures from node 1, the barn.

Three integers describe each node: Cn, D1, and D2. Cn is the

nodenumber (1 <= Cn <= P-1); D1 and D2 are the destinations from that node (0 <= D1 <= P-1; 0 <= D2 <= P-1). If D1 is 0, the node leads to a pasture in that direction; D2 has the same property.

POINTS: 100

Bessie透过牛棚的大门向外望去。发现今天是一个美丽的春季早晨。她想，“我真的好想好想沐浴着春风，走在草地之中，感受嫩草温柔地抚摸四蹄地的感觉。”她知道一旦她离开了牛棚，她将沿着一条小径走一段路，然后就会出现一个三岔路口，她必须在两条小径中选择一条继续走下去。然后她又会遇到更多的三岔路口，进行更多的选择，知道她到达一个青翠的牧场为止。

她决定作一个选择使得她在去吃早草的路途中可以走过最多的小径。给你这些小径的描述，求出Bessie最多可以走过多少条小径。假定Bessie一出牛棚就有2条路径，Bessie需要从中选择一条。

农场中有P-1 (1 <= P <= 1,000) 个分岔节点（范围是1..P），引向P片草地，它们之间由小径连接。对任意一个节点来说，只有一条从牛棚（被标记为节点1）开始的路径可以到达。

考虑下面的图。线段表示小径，"%"表示草地。右边的图中的"#"表示一条到达草地的高亮的路径。

从分岔节点9到达的草地是两个可以让Bessie走过最多小径的草地之一。在去吃早草的路上Bessie将走过7条不同的小径。这些草地是离牛棚也就是节点1最“远”的。

由3个整数来表示每一个节点：Cn, D1和D2，Cn是节点的编号(1 <= Cn <= P-1); D1和D2是由该节点引出的两条小径的终点(0 <= D1 <= P-1; 0 <= D2 <= P-1)。如果D1为0，表示这条小径引向的是一片牧草地；D2也一样。
输入格式

* Line 1: A single integer: P

* Lines 2..P: Line i+1 contains three space-separated integeres that describe a choice-node: Cn, D1, and D2
输出格式

* Line 1: A single integer that is the largest number of paths Bessie can traverse on the way to the furthest pasture.
输入输出样例
输入 #1

10 
7 8 0 
5 0 6 
9 0 0 
6 0 7 
3 4 0 
2 5 0 
8 0 9 
4 0 0 
1 2 3 

输出 #1

7 

说明/提示

This input describes the example farm layout in the task description.

1-2-5-6-7-8-9-P is one of the longest routes.

code:
int p,a[1001],b[1001],c,n;
void dfs(int m,int s){
	if(a[m]!=0)
        dfs(a[m],s+1);
	if(b[m]!=0)
        dfs(b[m],s+1);
	n=max(n,s);
}
int main(){//dfs
	cin>>p;
	for(int x=1;x<p;x++)
        cin>>c>>a[c]>>b[c];
	dfs(1,1);
    cout<<n;
	return 0;
}

*/

/*
P2965 [USACO09NOV]The Grand Farm-off S

题目描述

Farmer John owns 3*N (1 <= N <= 500,000) cows surprisingly numbered 0..3*N-1, each of which has some associated integer weight W_i (1 <= W_i <= d). He is entering the Grand Farm-off, a farming competition where he shows off his cows to the greater agricultural community.

This competition allows him to enter a group of N cows. He has given each of his cows a utility rating U_i (1 <= U_i <= h), which

represents the usefulness he thinks that a particular cow will have in the competition, and he wants his selection of cows to have the maximal sum of utility.

There might be multiple sets of N cows that attain the maximum utility sum. FJ is afraid the competition may impose a total weight limit on the cows in the competition, so a secondary priority is to bring lighter weight competition cows.

Help FJ find a set of N cows with minimum possible total weight among the sets of N cows that maximize the utility, and print the remainder when this total weight is divided by M (10,000,000 <= M <= 1,000,000,000).

Note: to make the input phase faster, FJ has derived polynomials which will generate the weights and utility values for each cow. For each cow 0 <= i < 3*N,

Wi=(a×i5+b×i2+c)mod??dW_i=(a\times i^5+b\times i^2+c)\mod d
Wi?=(a×i5+b×i2+c)modd

Ui=(e×i5+f×i3+g)mod??hU_i=(e\times i^5+f\times i^3+g)\mod h
Ui?=(e×i5+f×i3+g)modh

(0≤a,b,c,d,e,f,g,h≤109)(0\le a,b,c,d,e,f,g,h\le 10^9)
(0≤a,b,c,d,e,f,g,h≤109)

The formulae do sometimes generate duplicate numbers; your algorithm should handle this properly.

农夫约翰有3N(1 < N < 500000)头牛，编号依次为1..#N，每头牛都有一个整数值的体 重。约翰准备参加农场技艺大赛，向广大的农业社区展示他的奶牛. 大赛规则允许约翰带N头牛参赛.约翰给每头牛赋予了一个“有用度”Ui，它表 示了某头牛在比赛中的有用程度.约翰希望他选出的奶牛的有用度之和最大.

有可能选出很多组的N头牛都能达到有用度最大和.约翰害怕选出的N头牛的总重量会给大赛 带来震撼，所以，要考虑优先选择体重轻的奶牛.

帮助约翰选出N头总重量最轻，并且有用度之和最大的奶牛.输出体重模M后的余数.

注意：为了使输入更快，约翰使用了一个多项式来生成每头牛的体重和有用度.对每头牛/， 体重和有用度的计算公式为：

Wi=(a×i5+b×i2+c)mod??dW_i=(a\times i^5+b\times i^2+c)\mod d
Wi?=(a×i5+b×i2+c)modd

Ui=(e×i5+f×i3+g)mod??hU_i=(e\times i^5+f\times i^3+g)\mod h
Ui?=(e×i5+f×i3+g)modh

(0≤a,b,c,d,e,f,g,h≤109)(0\le a,b,c,d,e,f,g,h\le 10^9)
(0≤a,b,c,d,e,f,g,h≤109)
输入格式

* Line 1: Ten space-separated integers: N, a, b, c, d, e, f, g, h, and M
输出格式

* Line 1: A single integer representing the lowest sum of the weights of the N cows with the highest net utility.
输入输出样例
输入 #1

2 0 1 5 55555555 0 1 0 55555555 55555555 

输出 #1

51 

说明/提示

The functions generate weights of 5, 6, 9, 14, 21, and 30 along with utilities of 0, 1, 8, 27, 64, and 125.

The two cows with the highest utility are cow 5 and 6, and their combined weight is 21+30=51.

code:
long long n,a,b,c,d,f,e,g,h,m,ans;
struct node{
	long long w,u;
}l[1500003];
bool cmp(node a,node b){
	return (a.u==b.u?a.w<b.w:a.u>b.u);
}
int main(){
    cin>>n>>a>>b>>c>>d>>e>>f>>g>>h>>m;
	for(int i=0;i<3*n;i++)
		l[i].w=((a%d)*(((((i%d)*i%d)*i%d)*i%d)*i%d)+(b%d)*((i%d)*i%d)+(c%d))%d,
		l[i].u=((e%h)*(((((i%h)*i%h)*i%h)*i%h)*i%h)+(f%h)*(((i%h)*i%h)*i%h)+(g%h))%h;
	sort(l,l+3*n,cmp);
	for(int i=0;i<n;i++)
		ans+=l[i].w,
		ans%=m;
    cout<<ans;
	return 0;
}

*/

/*
P2969 [USACO09DEC]Music Notes S

题目描述

FJ is going to teach his cows how to play a song. The song consists of N (1 <= N <= 50,000) notes, and the i-th note lasts for B_i (1 <= B_i <= 10,000) beats (thus no song is longer than 500,000,000 beats). The cows will begin playing the song at time 0; thus, they will play note 1 from time 0 through just before time B_1, note 2 from time B_1 through just before time B_1 + B_2, etc.

However, recently the cows have lost interest in the song, as they feel that it is too long and boring. Thus, to make sure his cows are paying attention, he asks them Q (1 <= Q <= 50,000) questions of the form, 'In the interval from time T through just before time T+1, which note should you be playing?' The cows need your help to answer these questions which are supplied as T_i (0 <= T_i <=

end_of_song).

Consider this song with three notes of durations 2, 1, and 3 beats:

Beat:   0    1    2    3    4    5    6    ...
        |----|----|----|----|----|----|--- ...
        1111111111     :              :
                  22222:              :
                       333333333333333:

Here is a set of five queries along with the resulting answer:

Query Note

2 2

3 3

4 3

0 1

1 1

约翰准备教他的奶牛们弹一首歌.这首歌由N(1<=n<= 50000)个音阶组成，第i个音阶要敲 击Bi<=10000次.奶牛从第0时刻开始弹，因此他从0时刻到Bi-1时刻都是敲第1个音阶， 然后他从B1时刻到B1+B2-1时刻敲第2个音阶，从B1+B2到B1+B2+B3-1时刻敲第3个 音阶……现在有q(i<q<50000)个问题：在时间段区间t,T+1内，奶牛敲的是哪个音阶？
输入格式

* Line 1: Two space-separated integers: N and Q

* Lines 2..N+1: Line i+1 contains the single integer: B_i

* Lines N+2..N+Q+1: Line N+i+1 contains a single integer: T_i
输出格式

* Lines 1..Q: For each query, print a single integer that is the index of the note that the cows should be playing.
输入输出样例
输入 #1

3 5 
2 
1 
3 
2 
3 
4 
0 
1 

输出 #1

2 
3 
3 
1 
1 

code:
int m,n,a,b,c[50001],d[50001];
int main(){
    cin>>m>>n;
    for(int i=1;i<=m;i++)
        cin>>a,
        c[i]=c[i-1]+a;
    for(int i=1;i<=n;i++)
        cin>>b,
        d[i]=upper_bound(c,c+m+1,b)-c;
    for(int i=1;i<=n;i++)
        cout<<d[i]<<endl;
    return 0;
}

*/

/*
P2978 [USACO10JAN]Tea Time S

题目描述

N (1 <= N <= 1000) cows, conveniently numbered 1..N all attend a tea time every day. M (1 <= M <= 2,000) unique pairs of those cows have already met before the first tea time. Pair i of these cows who have met is specified by two differing integers A_i and B_i (1 <= A_i <= N; 1 <= B_i <= N). The input never indicates that cows have met each other more than once.

At tea time, any cow i and cow j who have met a mutual friend cow k will meet sometime during that tea time and thus expand their circle of known cows.

Determine whether Q (1 <= Q <= 100) pairs of cows have met after tea times are held for long enough that no new cow meetings are occurring. Query j consists of a pair of different cows X_j and Y_j (1 <= X_j <= N; 1 <= Y_j <= N).

For example, suppose that out of cows 1 through 5, we know that 2 has met 5, 2 has met 3, and 4 has met 5; see (a) below.

   2---3           2---3            2---3
    \              |\  |            |\ /|
1    \     -->  1  | \ |    -->  1  | X |
      \            |  \|            |/ \|
   4---5           4---5            4---5
    (a)             (b)              (c)

In the first tea time, cow 2 meets cow 4, and cow 3 meets cow 5; see (b) above. In the second tea time, cow 3 meets cow 4; see (c) above.

N(1 <= N <= 1000)头奶牛，编号为1..N，在参加一个喝茶时间活动。在喝茶时间活动开始之前，已经有M(1 <= M <= 2,000)对奶牛彼此认识（是朋友）。第i对彼此认识的奶牛通过两个不相同的整数Ai和Bi给定(1<= Ai <= N; 1 <= Bi <= N)。输入数据保证一对奶牛不会出现多次。 在喝茶时间活动中，如果奶牛i和奶牛j有一个相同的朋友奶牛k，那么他们会在某次的喝茶活动中去认识对方（成为朋友），从而扩大他们的社交圈。 请判断，在喝茶活动举办很久以后（直到没有新的奶牛彼此认识），Q(1 <= Q <= 100)对奶牛是否已经彼此认识。询问j包含一对不同的奶牛编号Xj和Yj(1 <= Xj <= N; 1 <= Yj <= N)。 例如，假设共有1..5头奶牛，我们知道2号认识5号，2号认识3号，而且4号认识5号；如下图(a)。

   2---3           2---3            2---3
    \              |\  |            |\ /|
1    \     -->  1  | \ |    -->  1  | X |
      \            |  \|            |/ \|
   4---5           4---5            4---5
    (a)             (b)              (c)

在某次的喝茶活动中，2号认识4号，3号认识5号；如上图(b)所示。接下来的喝茶活动中，3号认识4号，如上图(c)所示。
输入格式

* Line 1: Three space-separated integers: N, M, and Q

* Lines 2..M+1: Line i+1 contains two space-separated integers: A_i and B_i

* Lines M+2..M+Q+1: Line j+M+1 contains query j as two space-separated integers: X_j and Y_j

行1：三个空格隔开的整数：N，M，和Q

行2..M+1：第i+1行包含两个空格隔开的整数Ai和Bi

行M+2..M+Q+1：第j+M+1行包含两个空格隔开的整数Xj和Yj，表示询问j
输出格式

* Lines 1..Q: Line j should be 'Y' if the cows in the jth query have met and 'N' if they have not met.

行1..Q：如果第j个询问的两头奶牛认识， 第j行输出“Y”。如果不认识，第j行输出“N”
输入输出样例
输入 #1

5 3 3 
2 5 
2 3 
4 5 
2 3 
3 5 
1 5 

输出 #1

Y 
Y 
N 

说明/提示

感谢@蒟蒻orz神犇 提供翻译。

code:
int n,m,q,x,y,p[1001];
int sreach(int k){
    if(p[k]==k)return k;
    return p[k]=sreach(p[k]);
}
int main(){//并查集
    cin>>n>>m>>q;
    for(int i=1;i<=n;i++)
        p[i]=i;
    for(int i=1;i<=m;i++)
        cin>>x>>y,
        p[sreach(x)]=sreach(y);
    for(int i=1;i<=q;i++)
        cin>>x>>y,
        sreach(x)==sreach(y)?cout<<'Y'<<endl:cout<<'N'<<endl;
    return 0;
}

*/

/*
P3009 [USACO11JAN]Profits S

题目描述

The cows have opened a new business, and Farmer John wants to see how well they are doing. The business has been running for N (1 <= N <= 100,000) days, and every day i the cows recorded their net profit P_i (-1,000 <= P_i <= 1,000).

Farmer John wants to find the largest total profit that the cows have made during any consecutive time period. (Note that a consecutive time period can range in length from one day through N days.) Help him by writing a program to calculate the largest sum of consecutive profits.

奶牛们开始了新的生意，它们的主人约翰想知道它们到底能做得多好。这笔生意已经做了N（1≤N≤100,000）天，每天奶牛们都会记录下这一天的利润Pi（-1,000≤Pi≤1,000）。

约翰想要找到奶牛们在连续的时间期间所获得的最大的总利润。（注：连续时间的周期长度范围从第一天到第N天）。

请你写一个计算最大利润的程序来帮助他。
输入格式

* Line 1: A single integer: N

* Lines 2..N+1: Line i+1 contains a single integer: P_i
输出格式

* Line 1: A single integer representing the value of the maximum sum of profits for any consecutive time period.
输入输出样例
输入 #1

7 
-3 
4 
9 
-2 
-5 
8 
-3 

输出 #1

14 

说明/提示

The maximum sum is obtained by taking the sum from the second through the sixth number (4, 9, -2, -5, 8) => 14.

感谢@smartzzh 提供的翻译。

code:
int n, a[100001],ans=-214748364;
int main(){//dp
    cin>>n;
	for(int i=1;i<=n;i++) 
        cin>>a[i],
		a[i]=max(a[i],a[i]+a[i-1]),
		ans=max(a[i],ans);
    cout<<ans;
	return 0;
}

*/

/*
P3056 [USACO12NOV]Clumsy Cows S

题目描述

Bessie the cow is trying to type a balanced string of parentheses into her new laptop, but she is sufficiently clumsy (due to her large hooves) that she keeps mis-typing characters. Please help her by computing the minimum number of characters in the string that one must reverse (e.g., changing a left parenthesis to a right parenthesis, or vice versa) so that the string would become balanced.

There are several ways to define what it means for a string of parentheses to be "balanced". Perhaps the simplest definition is that there must be the same total number of ('s and )'s, and for any prefix of the string, there must be at least as many ('s as )'s. For example, the following strings are all balanced:

() (()) ()(()())

while these are not:

)( ())( ((())))

给出一个偶数长度的括号序列，问最少修改多少个括号可以使其平衡。
输入格式

* Line 1: A string of parentheses of even length at most 100,000 characters.
输出格式

* Line 1: A single integer giving the minimum number of parentheses that must be toggled to convert the string into a balanced string.
输入输出样例
输入 #1

())( 

输出 #1

2 

说明/提示

The last parenthesis must be toggled, and so must one of the two middle right parentheses.

code:
int ans,sum;
string s;
int main(){//压栈思维
	cin>>s;
	for(int i=0,lens=s.size();i<lens;i++)
		(s[i]=='(')?(sum++):((sum)?sum--:(ans++,sum++));
	cout<<ans+(sum>>1); 
	return 0;
}

*/

/*
P3131 [USACO16JAN]Subsequences Summing to Sevens S

题目描述

Farmer John's NNN cows are standing in a row, as they have a tendency to do from time to time. Each cow is labeled with a distinct integer ID number so FJ can tell them apart. FJ would like to take a photo of a contiguous group of cows but, due to a traumatic childhood incident involving the numbers 1…61 \ldots 61…6, he only wants to take a picture of a group of cows if their IDs add up to a multiple of 7.

Please help FJ determine the size of the largest group he can photograph.

给你n个数，分别是a[1],a[2],...,a[n]。求一个最长的区间[x,y]，使得区间中的数(a[x],a[x+1],a[x+2],...,a[y-1],a[y])的和能被7整除。输出区间长度。若没有符合要求的区间，输出0。
输入格式

The first line of input contains NNN (1≤N≤50,0001 \leq N \leq 50,0001≤N≤50,000). The next NNN

lines each contain the NNN integer IDs of the cows (all are in the range

0…1,000,0000 \ldots 1,000,0000…1,000,000).
输出格式

Please output the number of cows in the largest consecutive group whose IDs sum

to a multiple of 7. If no such group exists, output 0.
输入输出样例
输入 #1

7
3
5
1
6
2
14
10

输出 #1

5

说明/提示

In this example, 5+1+6+2+14 = 28.

code:
int n,pre[50001],first[7],last[7],len,mx=-1;
int main(){
	cin>>n;
	for(int i=1;i<=n;i++)
		cin>>pre[i],
		pre[i]=(pre[i]+pre[i-1])%7;
	for(int i=n;i>=1;i--)
		first[pre[i]]=i;
	first[0]=0;
	for(int i=1;i<=n;i++)
		last[pre[i]]=i;
	for(int i=0;i<=6;i++)
    	mx=max(last[i]-first[i],mx);
	cout<<mx;
    return 0;
} 

*/

/*
P3152 正整数序列

题目描述

kkk制造了一个序列，这个序列里的数全是由正整数构成的。你别认为她的数列很神奇——其实就是1, 2, …, n而已。当然，n是给定的。kkk的同学lzn认为0是一个好数字（看上去很饱满有木有），所以他机智的趁kkk不在把这个序列全变成了0（其实只是准备窝）~

可是kkk突然回来了！于是lzn的计划破灭了。但是他并不甘心，就和kkk说：我可以每次从这个序列中选取一些数，然后一起减去一个相同的数（当然也是正整数）。然后经过有(wu)限(qiong)次这样的操作后，这个序列就可以全变成0。

kkk当然不信咯，于是lzn就求出了他最少要做几次这样的操作，才能使这个序列全部变成0。
输入格式

一个正整数n
输出格式

最少操作次数

如果无解输出-1
输入输出样例
输入 #1

2

输出 #1

2

说明/提示

1<=n<=10^9

code:
int main(){//cmath
    int n;
    cin>>n;
    cout<<(int)log2(n)+1;
    return 0;
}

*/

/*
P3366 【模板】最小生成树

题目描述

如题，给出一个无向图，求出最小生成树，如果该图不连通，则输出 orz。
输入格式

第一行包含两个整数 N,MN,MN,M，表示该图共有 NNN 个结点和 MMM 条无向边。

接下来 MMM 行每行包含三个整数 Xi,Yi,ZiX_i,Y_i,Z_iXi?,Yi?,Zi?，表示有一条长度为 ZiZ_iZi? 的无向边连接结点 Xi,YiX_i,Y_iXi?,Yi?。
输出格式

如果该图连通，则输出一个整数表示最小生成树的各边的长度之和。如果该图不连通则输出 orz。
输入输出样例
输入 #1

4 5
1 2 2
1 3 2
1 4 3
2 3 4
3 4 3

输出 #1

7

说明/提示

数据规模：

对于 20%20\%20% 的数据，N≤5N\le 5N≤5，M≤20M\le 20M≤20。

对于 40%40\%40% 的数据，N≤50N\le 50N≤50，M≤2500M\le 2500M≤2500。

对于 70%70\%70% 的数据，N≤500N\le 500N≤500，M≤104M\le 10^4M≤104。

对于 100%100\%100% 的数据：1≤N≤50001\le N\le 50001≤N≤5000，1≤M≤2×1051\le M\le 2\times 10^51≤M≤2×105，1≤Zi≤1041\le Z_i \le 10^41≤Zi?≤104。

样例解释：

所以最小生成树的总边权为 2+2+3=72+2+3=72+2+3=7。

code:
int n,m,a,b,c,dis[10001],d,u,cnt,sum,vis[10001];
vector <int> E[200002],W[200002];
priority_queue <pair <int,int>,vector<pair <int,int>>,greater<pair <int,int> > > q;
int main() {//prim
    cin>>n>>m;
	for(int i=1; i<=m; i++) {
        cin>>a>>b>>c;
	    E[a].push_back(b),W[a].push_back(c);
	    E[b].push_back(a),W[b].push_back(c);
	}
	memset(dis,127,sizeof(dis));
	dis[1]=0;
	q.push(make_pair(dis[1],1));
	while(!q.empty()&&cnt<n) {
		d=q.top().first,u=q.top().second,q.pop();
		if(vis[u]) continue;
		cnt++,sum+=d,vis[u]=1;
		for(int i=0; i<E[u].size(); i++)
            if(W[u][i]<dis[E[u][i]])
                dis[E[u][i]]=W[u][i],
                q.push(make_pair(dis[E[u][i]],E[u][i]));
	}
	cnt==n?cout<<sum:cout<<"orz";
}

*/

/*
P3367 【模板】并查集

题目描述

如题，现在有一个并查集，你需要完成合并和查询操作。
输入格式

第一行包含两个整数 N,MN,MN,M ,表示共有 NNN 个元素和 MMM 个操作。

接下来 MMM 行，每行包含三个整数 Zi,Xi,YiZ_i,X_i,Y_iZi?,Xi?,Yi? 。

当 Zi=1Z_i=1Zi?=1 时，将 XiX_iXi? 与 YiY_iYi? 所在的集合合并。

当 Zi=2Z_i=2Zi?=2 时，输出 XiX_iXi? 与 YiY_iYi? 是否在同一集合内，是的输出 Y ；否则输出 N 。
输出格式

对于每一个 Zi=2Z_i=2Zi?=2 的操作，都有一行输出，每行包含一个大写字母，为 Y 或者 N 。
输入输出样例
输入 #1

4 7
2 1 2
1 1 2
2 1 2
1 3 4
2 1 4
1 2 3
2 1 4

输出 #1

N
Y
N
Y

说明/提示

对于 30%30\%30% 的数据，N≤10N \le 10N≤10，M≤20M \le 20M≤20。

对于 70%70\%70% 的数据，N≤100N \le 100N≤100，M≤103M \le 10^3M≤103。

对于 100%100\%100% 的数据，1≤N≤1041\le N \le 10^41≤N≤104，1≤M≤2×1051\le M \le 2\times 10^51≤M≤2×105，1≤Xi,Yi≤N1 \le X_i, Y_i \le N1≤Xi?,Yi?≤N，Zi∈{1,2}Z_i \in \{ 1, 2 \}Zi?∈{1,2}。

code:
int n,m,a,b,c,f[10001];
int find(int k){//并查集
    if(f[k]==k)return k;
    return f[k]=find(f[k]);
}
int main(){
    cin>>n>>m;
    for(int i=1;i<=n;i++)
        f[i]=i;
    for(int i=1;i<=m;i++){
        cin>>a>>b>>c;
        if(a==1) f[find(b)]=find(c);
        else (find(b)==find(c))?cout<<"Y"<<endl:cout<<"N"<<endl;
    }
    return 0;
}

*/

/*
P3370 【模板】字符串哈希

题目描述

如题，给定 NNN 个字符串（第 iii 个字符串长度为 MiM_iMi?，字符串内包含数字、大小写字母，大小写敏感），请求出 NNN 个字符串中共有多少个不同的字符串。

友情提醒：如果真的想好好练习哈希的话，请自觉，否则请右转PJ试炼场:)
输入格式

第一行包含一个整数 NNN，为字符串的个数。

接下来 NNN 行每行包含一个字符串，为所提供的字符串。
输出格式

输出包含一行，包含一个整数，为不同的字符串个数。
输入输出样例
输入 #1

5
abc
aaaa
abc
abcc
12345

输出 #1

4

说明/提示

对于 30%30\%30% 的数据：N≤10N\leq 10N≤10，Mi≈6M_i≈6Mi?≈6，Mmax≤15Mmax\leq 15Mmax≤15。

对于 70%70\%70% 的数据：N≤1000N\leq 1000N≤1000，Mi≈100M_i≈100Mi?≈100，Mmax≤150Mmax\leq 150Mmax≤150。

对于 100%100\%100% 的数据：N≤10000N\leq 10000N≤10000，Mi≈1000M_i≈1000Mi?≈1000，Mmax≤1500Mmax\leq 1500Mmax≤1500。

样例说明：

样例中第一个字符串(abc)和第三个字符串(abc)是一样的，所以所提供字符串的集合为{aaaa,abc,abcc,12345}，故共计4个不同的字符串。

Tip： 感兴趣的话，你们可以先看一看以下三题：

BZOJ3097：http://www.lydsy.com/JudgeOnline/problem.php?id=3097

BZOJ3098：http://www.lydsy.com/JudgeOnline/problem.php?id=3098

BZOJ3099：http://www.lydsy.com/JudgeOnline/problem.php?id=3099

如果你仔细研究过了（或者至少仔细看过AC人数的话），我想你一定会明白字符串哈希的正确姿势的^_^

code:
int n;
string p;
set<string> a;
int main(){
    cin>>n;
    for(int i=0;i<n;i++)
    	cin>>p,
    	a.insert(p);
	cout<<a.size();
    return 0;
}

*/

/*
P3378 【模板】堆

题目描述

给定一个数列，初始为空，请支持下面三种操作：

    给定一个整数 xxx，请将 xxx 加入到数列中。
    输出数列中最小的数。
    删除数列中最小的数（如果有多个数最小，只删除 111 个）。

输入格式

第一行是一个整数，表示操作的次数 nnn。
接下来 nnn 行，每行表示一次操作。每行首先有一个整数 opopop 表示操作类型。

    若 op=1op = 1op=1，则后面有一个整数 xxx，表示要将 xxx 加入数列。
    若 op=2op = 2op=2，则表示要求输出数列中的最小数。
    若 op=3op = 3op=3，则表示删除数列中的最小数。如果有多个数最小，只删除 111 个。

输出格式

对于每个操作 222，输出一行一个整数表示答案。
输入输出样例
输入 #1

5
1 2
1 5
2
3
2

输出 #1

2
5

说明/提示

【数据规模与约定】

    对于 30%30\%30% 的数据，保证 n≤15n \leq 15n≤15。
    对于 70%70\%70% 的数据，保证 n≤104n \leq 10^4n≤104。
    对于 100%100\%100% 的数据，保证 1≤n≤1061 \leq n \leq 10^61≤n≤106，1≤x<2311 \leq x \lt 2^{31}1≤x<231，op∈{1,2,3}op \in \{1, 2, 3\}op∈{1,2,3}。

code:
priority_queue<int,vector<int>,greater<int> > q; //定义优先队列，升序 
int n,a,b,ans;
int main(){//stl 优先队列
    cin>>n;
    for(int i=1;i<=n;i++){
        cin>>a;
        if(a==1)
            cin>>b,
            q.push(b);
        else if(a==2)
            ans=q.top(),
            cout<<ans<<endl;
        else if(a==3)
            q.pop();
    }
    return 0; 
}

*/

/*
P3383 【模板】线性筛素数

题目背景

本题已更新，从判断素数改为了查询第 kkk 小的素数
提示：如果你使用 cin 来读入，建议使用 std::ios::sync_with_stdio(0) 来加速。
题目描述

如题，给定一个范围 nnn，有 qqq 个询问，每次输出第 kkk 小的素数。
输入格式

第一行包含两个正整数 n,qn,qn,q，分别表示查询的范围和查询的个数。

接下来 qqq 行每行一个正整数 kkk，表示查询第 kkk 小的素数。
输出格式

输出 qqq 行，每行一个正整数表示答案。
输入输出样例
输入 #1

100 5
1
2
3
4
5

输出 #1

2
3
5
7
11

说明/提示

【数据范围】
对于 100%100\%100% 的数据，n=108n = 10^8n=108，1≤q≤1061 \le q \le 10^61≤q≤106，保证查询的素数不大于 nnn。

Data by NaCly_Fish.

code:
int x,n,h,ans[100000001],sum;
bool pd[100000001];
int main(){
   	scanf("%d%d",&x,&n);
   	pd[1]=1;
   	for(int i=2;i<=x;i++){
		if(!pd[i])ans[++sum]=i;
		for(int j=1;j<=sum&&i*ans[j]<=x;j++){
			pd[ans[j]*i]=1;
			if(i%ans[j]==0)break;
		}
	}
	for(int i=1;i<=n;i++)
		scanf("%d",&h),
		printf("%d\n",ans[h]);
    return 0;
}

*/

/*
P3392 涂国旗

题目描述

某国法律规定，只要一个由 N×MN \times MN×M 个小方块组成的旗帜符合如下规则，就是合法的国旗。（毛熊：阿嚏——）

    从最上方若干行（至少一行）的格子全部是白色的；
    接下来若干行（至少一行）的格子全部是蓝色的；
    剩下的行（至少一行）全部是红色的；

现有一个棋盘状的布，分成了 NNN 行 MMM 列的格子，每个格子是白色蓝色红色之一，小 a 希望把这个布改成该国国旗，方法是在一些格子上涂颜料，盖住之前的颜色。

小a很懒，希望涂最少的格子，使这块布成为一个合法的国旗。
输入格式

第一行是两个整数 N,MN,MN,M。

接下来 NNN 行是一个矩阵，矩阵的每一个小方块是W（白），B（蓝），R（红）中的一个。
输出格式

一个整数，表示至少需要涂多少块。
输入输出样例
输入 #1

4 5
WRWRW
BWRWB
WRWRW
RWBWR

输出 #1

11

说明/提示
样例解释

目标状态是：

WWWWW
BBBBB
RRRRR
RRRRR

一共需要改 111111 个格子。
数据范围

对于 100%100\%100% 的数据，N,M≤50N,M \leq 50N,M≤50。

code:
int n,m,h,ans=1e9;
char s[52][52];
int main(){
    cin>>n>>m;
    for (int i=0;i<n;i++)
        cin>>s[i];
    for (int i=0;i<n-2;i++)
        for (int j=i+1;j<n-1;j++){
            h=0;
            for (int k=0;k<=i;k++)
                for (int u=0;u<m;u++)
                    if (s[k][u]!='W')
                        h++;
            for (int k=i+1;k<=j;k++)
                for (int u=0;u<m;u++)
                    if (s[k][u]!='B')
                        h++;
            for (int k=j+1;k<n;k++)
                for (int u=0;u<m;u++)
                    if (s[k][u]!='R')
                        h++;
            if (h<ans)
                ans=h;
        }
    cout<<ans;
    return 0;
}

*/

/*
P3397 地毯

题目背景

此题约为NOIP提高组Day2T1难度。
题目描述

在 n×nn\times nn×n 的格子上有 mmm 个地毯。

给出这些地毯的信息，问每个点被多少个地毯覆盖。
输入格式

第一行，两个正整数 n,mn,mn,m。意义如题所述。

接下来 mmm 行，每行两个坐标 (x1,y1)(x_1,y_1)(x1?,y1?) 和 (x2,y2)(x_2,y_2)(x2?,y2?)，代表一块地毯，左上角是 (x1,y1)(x_1,y_1)(x1?,y1?)，右下角是 (x2,y2)(x_2,y_2)(x2?,y2?)。
输出格式

输出 nnn 行，每行 nnn 个正整数。

第 iii 行第 jjj 列的正整数表示 (i,j)(i,j)(i,j) 这个格子被多少个地毯覆盖。
输入输出样例
输入 #1

5 3
2 2 3 3
3 3 5 5
1 2 1 4

输出 #1

0 1 1 1 0
0 1 1 0 0
0 1 2 1 1
0 0 1 1 1
0 0 1 1 1

说明/提示
样例解释

覆盖第一个地毯后：
000 	000 	000 	000 	000
000 	111 	111 	000 	000
000 	111 	111 	000 	000
000 	000 	000 	000 	000
000 	000 	000 	000 	000

覆盖第一、二个地毯后：
000 	000 	000 	000 	000
000 	111 	111 	000 	000
000 	111 	222 	111 	111
000 	000 	111 	111 	111
000 	000 	111 	111 	111

覆盖所有地毯后：
000 	111 	111 	111 	000
000 	111 	111 	000 	000
000 	111 	222 	111 	111
000 	000 	111 	111 	111
000 	000 	111 	111 	111
数据范围

对于 20%20\%20% 的数据，有 n≤50n\le 50n≤50，m≤100m\le 100m≤100。

对于 100%100\%100% 的数据，有 n,m≤1000n,m\le 1000n,m≤1000。

code:
int t[1001][1001];
int main(){
	int n, m, x1, x2, y1, y2;
	cin >> n >> m;
	for (int k = 1; k <= m; ++k){
		cin >> x1 >> y1 >> x2 >> y2;
		for (int i = x1; i <= x2; ++i)
			for (int j = y1; j <= y2; ++j)
				t[i][j]++;
	}
	for (int i = 1; i <= n; ++i){
		for (int j = 1; j <= n; ++j){
			cout << t[i][j] << ' ';
        }
		cout << endl;
	}
}

*/

/*
P3405 [USACO16DEC]Cities and States S

题目描述

To keep his cows intellectually stimulated, Farmer John has placed a large map of the USA on the wall of his barn. Since the cows spend many hours in the barn staring at this map, they start to notice several curious patterns. For example, the cities of Flint, MI and Miami, FL share a very special relationship: the first two letters of "Flint" give the state code ("FL") for Miami, and the first two letters of "Miami" give the state code ("MI") for Flint.

Let us say that two cities are a "special pair" if they satisfy this property and come from different states. The cows are wondering how many special pairs of cities exist. Please help them solve this amusing geographical puzzle!

为了让奶牛在智力上受到刺激，农夫约翰在谷仓的墙上放了一张美国地图。由于奶牛在谷仓里花了很多时间盯着这张地图，他们开始注意到一些奇怪的关系。例如，城市Flint，在MI省，或者Miami在FL省，他们有一种特殊的关系：“Flint”市前两个字母就是“FL”省，迈阿密前两个字母是“MI”省。

让我们说，两个城市是一个“特殊的一对”，如果他们满足这个属性，来自不同的省。奶牛想知道有多少特殊的城市存在。请帮助他们解决这个有趣的地理难题！
输入格式

The first line of input contains NNN (1≤N≤200,0001 \leq N \leq 200,0001≤N≤200,000), the number ofcities on the map.

The next NNN lines each contain two strings: the name of a city (a string of at least 2 and at most 10 uppercase letters), and its two-letter state code (a string of 2 uppercase letters). Note that the state code may be something like ZQ, which is not an actual USA state. Multiple cities with the same name can exist, but they will be in different states.

输入的第一行包含（），地图上的城市数量。

下一行包含两个字符串：一个城市的名称（字符串至少2个最多10个大写字母），和它的两个字母的州代码（一串2个大写字母）。注意状态代码可能像ZQ，这并不是一个真正的美国。同一名称的多个城市可以存在，但它们将处于不同的州。
输出格式

Please output the number of special pairs of cities.

请输出特殊城市对数。
输入输出样例
输入 #1

6
MIAMI FL
DALLAS TX
FLINT MI
CLEMSON SC
BOSTON MA
ORLANDO FL

输出 #1

1

说明/提示

感谢@何炜华8864 的翻译，并经过kkksc03的修改

code:
int n,ans,j,k;
string a,b;
map<int,int>m[100001];
int main(){//stl map
    cin>>n;
    for(int i=1;i<=n;i++){
        cin>>a>>b;
        j=a[0]*26+a[1];
        k=b[0]*26+b[1];
        ans+=m[k][j];
        if(j==k)
            ans-=m[j][k];
        m[j][k]++;
    }
    cout<<ans;
    return 0;
}

*/

/*
P3612 [USACO17JAN]Secret Cow Code S

题目描述

The cows are experimenting with secret codes, and have devised a method for creating an infinite-length string to be used as part of one of their codes.

Given a string sss, let F(s)F(s)F(s) be sss followed by sss "rotated" one character to the right (in a right rotation, the last character of sss rotates around and becomes the new first character). Given an initial string sss, the cows build their infinite-length code string by repeatedly applying FFF; each step therefore doubles the length of the current string.

Given the initial string and an index NNN, please help the cows compute the character at the NNNth position within the infinite code string.

奶牛正在试验秘密代码，并设计了一种方法来创建一个无限长的字符串作为其代码的一部分使用。

给定一个字符串，让后面的字符旋转一次（每一次正确的旋转，最后一个字符都会成为新的第一个字符）。也就是说，给定一个初始字符串，之后的每一步都会增加当前字符串的长度。

给定初始字符串和索引，请帮助奶牛计算无限字符串中位置N的字符。
输入格式

The input consists of a single line containing a string followed by NNN. The string consists of at most 30 uppercase characters, and N≤1018N \leq 10^{18}N≤1018.

Note that NNN may be too large to fit into a standard 32-bit integer, so you may want to use a 64-bit integer type (e.g., a "long long" in C/C++).

第一行输入一个字符串。该字符串包含最多30个大写字母，并 N≤1018N \leq 10^{18}N≤1018 。

第二行输入N。请注意，数据可能很大，放进一个标准的32位整数可能不够，所以你可能要使用一个64位的整数类型（例如，在C / C++ 中是 long long）。
输出格式

Please output the NNNth character of the infinite code built from the initial string. The first character is N=1N=1N=1.

请输出从初始字符串生成的无限字符串中的位置的字符。第一个字符是 N=1N=1N=1.。
输入输出样例
输入 #1

COW 8

输出 #1

C

说明/提示

In this example, the initial string COW expands as follows:

COW -> COWWCO -> COWWCOOCOWWC

12345678

感谢@y_z_h 的翻译

code:
string s;
long long n,num,i;
int main(){
	cin>>s>>n;
	num=s.length(); 
	while(num<n){
		i=num;
		while(n>i)i=2*i;
		n=n-i/2-1; 
		if(n==0)n=i/2;
	}
	cout<<s[n-1];
    return 0;
}

*/

/*
P3613 【深基15.例2】寄包柜

题目描述

超市里有 n(n≤105)n(n\le10^5)n(n≤105) 个寄包柜。每个寄包柜格子数量不一，第 iii 个寄包柜有 ai(ai≤105)a_i(a_i\le10^5)ai?(ai?≤105) 个格子，不过我们并不知道各个 aia_iai? 的值。对于每个寄包柜，格子编号从 1 开始，一直到 aia_iai?。现在有 q(q≤105)q(q\le10^5)q(q≤105) 次操作：

    1 i j k：在第 iii 个柜子的第 jjj 个格子存入物品 k(0≤k≤109)k(0\le k\le 10^9)k(0≤k≤109)。当 k=0k=0k=0 时说明清空该格子。
    2 i j：查询第 iii 个柜子的第 jjj 个格子中的物品是什么，保证查询的柜子有存过东西。

已知超市里共计不会超过 10710^7107 个寄包格子，aia_iai? 是确定然而未知的，但是保证一定不小于该柜子存物品请求的格子编号的最大值。当然也有可能某些寄包柜中一个格子都没有。
输入格式

第一行 2 个整数 n 和 q，寄包柜个数和询问次数。

接下来 q 个整数，表示一次操作。
输出格式

对于查询操作时，输出答案。
输入输出样例
输入 #1

5 4
1 3 10000 114514
1 1 1 1
2 3 10000
2 1 1

输出 #1

114514
1

code:
long long n,m,p,i,j,k;
map<long long,long long> mp;
int main(){
    cin>>n>>m;
	while(m--){
        cin>>p>>i>>j;
		if(p==1) cin>>k,mp[i*pow(10,6)+j]=k;
		else cout<<mp[i*pow(10,6)+j]<<endl;
	}
	return 0;
}

*/

/*
P3650 [USACO1.3]滑雪课程设计Ski Course Design

题目描述

农民约翰的农场里有 nnn 座山峰，每座山都有一个在 000 到 100100100 之间的整数的海拔高度。在冬天,因为山上有丰富的积雪，约翰经常开办滑雪训练营。

不幸的是，约翰刚刚得知税法在滑雪训练营方面有新变化，明年开始实施。在仔细阅读法律后，他发现如果滑雪训练营的最高和最低的山峰海拔高度差大于 171717 就要收税。因此，如果他改变山峰的高度（使最高与最低的山峰海拔高度差不超过 171717 ），约翰可以避免支付税收。

如果改变一座山 xxx 单位的高度成本是 x2x^2x2 单位，约翰最少需要付多少钱才能使海拔最高的山峰与海拔最低的山峰的高度只差不超过 171717 约翰只愿意改变整数单位的高度。
输入格式

输入的第一行是一个整数，代表山峰的数量 nnn。

第 222 行到(n+1)(n + 1)(n+1) 行，每行一个整数。第 iii 行的整数 aia_iai? 代表第 iii 座山的海拔高度。
输出格式

输出一行一个整数，代表约翰需要支付修改山海拔高度的总金额。
输入输出样例
输入 #1

5
20
4
1
24
21

输出 #1

18

说明/提示
样例输入输出 1 解释

约翰保持高度为 444、202020 和 212121 的山的高度。他增高高度为 111 的山，变成高度 444 ，花费 32=93^2 = 932=9。他降低了高度为 242424 的山变成高度 212121，也花费 32=93 ^ 2 = 932=9。因此总共花费 9+9=189 + 9 = 189+9=18。
数据规模与约定

对于 100%100\%100% 的数据，1≤n≤10001 \le n \le 10001≤n≤1000，1≤ai≤1001 \leq a_i \leq 1001≤ai?≤100。

code:
int a[1001],n,minn,s=1e9+1,sum;
int main(){
    cin>>n;
    for(int i=1;i<=n;i++)
        cin>>a[i];
    sort(a+1,a+n+1);
    for(int j=a[1];j<=a[n];j++){
        sum=0;
        for(int i=1;i<=n;i++){
            if(a[i]-j>17) sum+=(a[i]-j-17)*(a[i]-j-17);
            if(a[i]<j) sum+=(a[i]-j)*(a[i]-j);
        }    
        s=min(sum,s);
    }
    cout<<s;
    return 0;
}

*/
