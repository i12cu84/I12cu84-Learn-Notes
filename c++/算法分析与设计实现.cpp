// 1.统计求最大、最小元素的平均比较次数
// 2.分治法解决大整数乘法问题
// 3.动态规划策略实现最长公共子序列
// 4.动态规划法解决背包问题
// 5.贪心法解决多机调度问题
// 6.贪心法解决文件压缩问题

//1.
/*
统计求最大、最小元素的平均比较次数
一、实验目的及要求
1、掌握算法分析的基本思想；
2、学会求解算法的时间复杂度。
二、实验内容
编写程序实现：
1、设计一个求解最大元素和最小元素的高效算法，并在随机产生的10个1~20整数中实现最大、最小值寻找；
2、统计元素之间的比较次数，并求出执行10次调用算法的平均比较次数，试分析比较次数与算法性能的关系。
*/
#include<iostream>
#include<cstdlib>
using namespace std;
int time = 0;
void qSort(int s[], int n, int m) {
int t, i = n - 1, p = n;
if (n < m) {
while (p < m) {
time++;
if (s[p] < s[m]) {
i++;
t = s[i];
s[i] = s[p];
s[p] = t;
}
p++;
}
i++;
t = s[p];
s[p] = s[i];
s[i] = t;
qSort(s, n, i - 1);
qSort(s, i + 1, m);
}
}
int main() {
int i,k=10,code[10];
for (i = 0; i < k; i++)
code[i] = rand()%21;
int n = sizeof(code) / sizeof(int);
for (i = 0; i < n; i++)
cout << code[i] << " ";
qSort(code, 0, n - 1);
cout << endl << "qSort:" << endl;
for (i = 0; i < n; i++)
cout << code[i] << " ";
cout<<endl<<"timer was :"<<time;
return 0;
}

//2.
/*
分治法解决大整数乘法问题
一、实验目的及要求
1、掌握分治法的基本思想；
2、掌握大整数乘法的分治法实现方法；
3、学会分析算法的时间复杂度；
4、学会用分治法解决实际问题。
二、实验内容
编写程序实现：
1、输入两个2n位大整数X和Y, 用分治法实现乘积运算，并输出运算结果和计算时间；
2、逐渐增加输入大整数的位数，分析运算时间的变化。
3、用分治法的变形方式实现乘积运算，使时间复杂为O（n1.59）
*/
#include<iostream>
#include<cstring>
#include<cstdlib>
#include<string>
#include<cmath>
using namespace std;
int main(){
unsigned long long sum=0;
string x,y;
while(cin>>x>>y){
for(int i=0;i<x.length();i++){
for(int j=0;j<y.length();j++){
sum+=int(x[i]-'0')*int(y[j]-'0')*pow(10,(x.length()-j-1))*pow(10,(y.length()-
i-1));
}
}
cout<<sum<<endl;
cout<<stoll(x)*stoll(y)<<endl<<endl;
}
return 0;
}
int main(){
long long sum=0;
char x[10],y[10];
cin>>x>>y;
for(int i=0;i<strlen(x);i++){
for(int j=0;j<strlen(y);j++){
sum+=int(x[i]-'0')*int(y[j]-'0')*pow(10,(strlen(x)-j-1))*pow(10,(strlen(y)-i-1));
}
}
cout<<sum<<endl;
cout<<stoll(x)*stoll(y);
return 0;
}

//3.
/*
动态规划策略实现最长公共子序列
一、实验目的及要求
1、掌握动态规划法的基本思想；
2、掌握最长公共子序列问题的动态规划解决方法；
3、学会设计状态转移方程；
4、学会用动态规划法解决实际问题。
二、实验内容
编写程序实现：
1、输入两个字符序列X和Y，设计状态转移方程，计算出用于存储最长公共子序列长度的动态规划数组；
2、用动态规划法实现最长公共子序列的求解过程，输出最长公共子序列长度及字符，并分析算法复杂度。
*/
#include <iostream>
using namespace std;
int main(){
    char a[]="0ABCD",b[]="0ADCB";
    int c[sizeof(a)][sizeof(b)]={0};
    for(int i=1;i<sizeof(a)-1;i++)
        for(int j=1;j<sizeof(b)-1;j++)
            if(a[i]==b[j])c[i][j]=max(c[i-1][j],c[i-1][j-1]+1);
            else c[i][j]=max(c[i-1][j],c[i][j-1]);
    for(int i=0;i<sizeof(a)-1;i++){
        for(int j=0;j<sizeof(b)-1;j++){
            cout<<c[i][j]; 
        }
        cout<<endl;
    }
    int maxc=c[sizeof(a)-2][sizeof(b)-2],n=maxc,t=0;
    cout<<maxc<<endl;
    char save[maxc];
    for(int i=sizeof(a)-2;0<i;i--)
        for(int j=sizeof(b)-2;0<j;j--)
            if((c[i][j]==maxc)&&(c[i-1][j]==(maxc-1))&&c[i][j-1]==(maxc-1)){
                n=maxc;
                while(n){
                    for(int p=i;0<p;p--)
                        for(int q=j;0<q;q--){
                            if((c[p][q]==n)&&(c[p-1][q]==(n-1))&&c[p][q-1]==(n-1)){
                                save[t]=a[p];t++;n--;p--;
                                if(t==maxc){
                                    t=0;
                                    for(int i=maxc-1;i>=0;i--)cout<<save[i];
                                }
                            }
                        }
                }
                cout<<endl;
            }
    return 0;
}

//4.
/*
动态规划法解决背包问题
一、实验目的及要求
1、理解0-1背包问题和完全背包问题的异同；
2、掌握背包问题的动态规划解决方法的设计思路；
3、学会不同算法解决实际问题时的算法性能比较。
二、实验内容
编写程序实现：
1、<验证>
输入背包容量，物品数量、价值及重量，利用动态规划法解决0-1背包问题，要求输出装入物品的对应指示向量，并分析该算法性能。
2、<探索>
当背包允许物品部分装入时，重新设计动态规划策略，满足背包承载最大时价值最高，输出指示向量，并与问题1结果相比较，同时分析算法性能差异。	
*/
#include<iostream>
using namespace std;
int main(){
	//公共代码
    int t,m;cin>>t>>m;//t代表背包容量 m代表有多少物品
    int w[m+1]={0}, val[m+1]={0};
    for(int i=1;i<=m;i++)cin>>w[i]>>val[i];//w代表所需容量 val代表物品价值
    //代码1:一维dp
    int dp[t+1]={0};
    for(int i=1;i<=m;i++)
        for(int j=t;j>=0;j--)
            if(j>=w[i])dp[j]=max(dp[j-w[i]]+val[i], dp[j]);
                //如果放得下,就取 放得下这次的方式和不放这次方式的最大值
    cout<<dp[t];//输出当t容量的时候,价值的最大值
    //代码2:二维dp
    // int dp[m+1][1005]={0};
    // for(int i=1;i<=m;i++) 
    //     for(int j=t;j>=0;j--)
    //         if(j>=w[i]) 
    //          dp[i][j]=max(dp[i-1][j-w[i]]+val[i],dp[i-1][j]);
    //         //如果放得下,就取 放得下这次的方式和不放这次方式的最大值
    //         else dp[i][j]=dp[i-1][j];//如果放不下就顺延上一次的最大值
    // cout<<dp[m][t];//输出前m个物体、t容量的时候,价值的最大值
    return 0;
}
// 总结:
// 公共代码+代码1可以满足在t容量下,所取价值最大值的01背包dp算法,可以控制输出容量小于等于t情况下,最终所取价值的最大值;
// 公共代码+代码2可以满足在t容量下,锁定前m个物体中,所取价值最大值的01背包dp算法,可以控制输出物品小于等于m且容量小于等于t情况下,最终所取价值的最大值.
// 算法性能差异:
// 代码1采用一维数组的方式计算,所耗空间小,但是只能控制输出容量小于等于t的情况;
// 代码2采用二维数组的方式计算,所耗空间大,但是还能控制输出物品小于等于m的情况.

//5.
/*
贪心法解决多机调度问题
一、实验目的及要求
1、掌握贪心法算法设计原理；
2、学会应用贪心思路解决实际问题；
3、分析贪心算法处理多机调度问题的算法性能。
二、实验内容
编写程序实现：
1、<验证>
设n个独立的作业{1,2,…,n}，由m台相同的机器{1,2,…,m}进行加工，作业i需要处理的时间为ti，每个作业均可在任何一台机器加工，未加工完前不允许中断机器，任何作业也不能拆分成更小的子作业，设计一种作业调度算法，使得在尽可能短的时间内完成加工处理
2、<探索>
针对上述结果，若每台机器在工作s时间后需要进行检修，检修时需中断机器，但检修后作业仍可以继续进行。试设计一种算法，使得中断机器的次数最少。	
*/
//code1：
#include<bits/stdc++.h>
using namespace std;
bool cmp(int a,int b){return a>b;}
int main(){
    int ans=0,n=4,m=2;//n表示作业个数 m表示机器个数
    int s[n+m]={1,3,1,1};
    sort(s,s+n,cmp);
    int t=m; 
    while(t<n+m){
        for(int i=0;i<m;i++){
            s[i]--;
            if(s[i]==0){
                s[i]=s[t];
                t++; 
            }
        }
        ans++;
    }
    cout<<ans;
    return 0;
} 
//code2：
bool cmp(int a,int b){return a>b;}
int main(){
    int t[]={10,7,3,2,1,1,1,1,1,1,1,1},s=10,p=sizeof(t)/sizeof(int),num=0,x=0;
    for(int i=0;i<p;i++)
        if(t[i]>s){cout<<"error"<<endl;return 0;}
        else if(t[i]==s){t[i]=0;num++;}
    sort(t,t+p,cmp);
    for(int i=0;i<p;i++)
        if(t[i]==0)continue;
        else for(int j=i+1;j<p;j++)
            if(t[i]==0 || t[j]==0)continue;
            else if(t[i]+t[j]>s){t[i]=0;num++;}
            else if(t[i]+t[j]==s){t[i]=0;t[j]=0;num++;}
            else {
                num++,x=t[i]+t[j],t[i]=0,t[j]=0;
                for(int k=j+1;k<p;k++)
                    if(t[k]==0)continue;
                    else if(x+t[k]<=s)x+=t[k],t[k]=0;
            }
    cout<<num;
    return 0;
}

//6.
/*
贪心法解决文件压缩问题
一、实验目的及要求
1、掌握贪心法算法设计思想；
2、理解哈夫曼编码原理；
3、学会应用贪心法实现哈夫曼编码；
4、分析基于贪心法的文件压缩算法性能。
二、实验内容
设需要编码的字符集为{d1, d2, …, dn}，它们出现的频率为{w1, w2, …, wn}，应用哈夫曼树可以构造出由0、1构成的、不等长的编码方案。试编写程序实现哈夫曼编码实现文本文件的压缩。
*/
#include<bits/stdc++.h>
using namespace std; 
char Arr[10000];
class HuffmanTree{
    private:
        int weight;
        string Huffmancode;
        HuffmanTree* lchild;
        HuffmanTree* rchild;
    public:     
        void Set(int num,HuffmanTree* left ,HuffmanTree* right){
            this->weight = num;
            this->lchild = left;
            this->rchild = right;
        }
        int getWeight(){return this->weight;}
        bool isLeaf(HuffmanTree* root){return !root->lchild && !root->rchild;}
        void Create_HuffmanCode(HuffmanTree* root,char* Arr,int top){
            if(root->lchild)Arr[top] = '0',Create_HuffmanCode(root->lchild,Arr,top+1);
            if(root->rchild)Arr[top] = '1',Create_HuffmanCode(root->rchild,Arr,top+1);
            if(this->isLeaf(root)){
                int i;
                for(int i = 0 ; i < top ; i++)if(Arr[i-1] == ' ' &&Arr[i] != ' ')break;
                string code(Arr,top);
                int index;
                while( (index = code.find(' ')) != code.npos)code = code.erase(index,1);
                root->Huffmancode = code;
            }
        }
        void PrintHuffmanTree(HuffmanTree* root){
            queue<HuffmanTree*> q;
            q.push(root);
            while(!q.empty()){
                HuffmanTree* cur = q.front();
                q.pop();
                if(cur->lchild)q.push(cur->lchild);
                if(cur->rchild)q.push(cur->rchild);
                if(this->isLeaf(cur))cout<<cur->weight<<"->"<<cur->Huffmancode<<endl;
            }
        }
};
struct cmp{
    bool operator() (HuffmanTree* node1, HuffmanTree* node2){
        return node1->getWeight()>node2->getWeight();
    }
};
HuffmanTree* Create_HuffmanTree(int* data,int size){
    priority_queue<HuffmanTree*,vector<HuffmanTree*>,cmp> Q;
    for(int i = 0 ; i < size ; i++){
        HuffmanTree* root = new HuffmanTree;
        root->Set(data[i],NULL,NULL);
        Q.push(root);
    }
    while(Q.size() != 1){
        HuffmanTree* left = Q.top();
        Q.pop();
        HuffmanTree* right = Q.top();
        Q.pop();
        HuffmanTree* root = new HuffmanTree;
        root->Set(left->getWeight()+right->getWeight(),left,right);
        Q.push(root);
    }
    HuffmanTree* root = Q.top();
    Q.pop();
    return root;
}
int main(){
    int N,*data;cin>>N;
    data = new int[N];
    for(int i = 0 ; i < N ; i++)cin>>data[i];
    HuffmanTree *root;
    root = Create_HuffmanTree(data,N);
    root->Create_HuffmanCode(root,Arr,N);
    root->PrintHuffmanTree(root);
    return 0;
}
