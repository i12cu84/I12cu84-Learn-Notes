//PAT (Basic Level) Practice （中文）

//1002 写出这个数 （20 分）
/*
读入一个正整数 n，计算其各位数字之和，用汉语拼音写出和的每一位数字。
输入格式：
每个测试输入包含 1 个测试用例，即给出自然数 n 的值。这里保证 n 小于 10
100
。
输出格式：
在一行内输出 n 的各位数字之和的每一位，拼音数字间有 1 空格，但一行中最后一个拼音数字后没有空格。
输入样例：
1234567890987654321123456789
输出样例：
yi san wu
*/
/*#include<iostream>
#include<cmath>
#include<string>
using namespace std;
int main (){
	char a[200];
	int i=0,m=0,sum=0;
	int t,p;
	cin>>a;
	while(a[i]!='\0')
	{
		sum+=a[i]-48;
		i++;
	}
	p=sum;
	if(sum==0)printf("ling");
	while(sum!=0)
	{
	t=sum%10;
	sum/=10;
	m=m*10+t;	
	}
	while(m>0)
	{
		t=m%10;
		m/=10;
		switch(t)
		{
		case 0:cout<<"ling";break;
		case 1:cout<<"yi";break;
		case 2:cout<<"er";break;
		case 3:cout<<"san";break;
		case 4:cout<<"si";break;
		case 5:cout<<"wu";break;
		case 6:cout<<"liu";break;
		case 7:cout<<"qi";break;
		case 8:cout<<"ba";break;
		case 9:cout<<"jiu";
		}
		if(m!=0)printf(" ");
	}
	if(p>0)
	{
		while(p%10==0)
		{
			p/=10;
			cout<<" "<<"ling";
		}
	}
	return 0;
}

/*
#include <stdio.h>
#include <string.h>
int main(int argc, char *argv[]) 
{
	char n;
	int sum=0,i=0;
	while((n=getchar())!='\n'&&i<101)
		{
		sum+=(n-'0');
		i++;
		}
	char shu[10][5]={"ling","yi","er","san","si","wu","liu","qi","ba","jiu"};
	int s1,s2,s3;
	s1=sum/100;
	s2=(sum/10)%10;
	s3=sum%10;
	if(s1)
		printf("%s ",shu[s1]);
	if(s1!=0||(s1==0&&s2!=0))
		printf("%s ",shu[s2]);
	printf("%s",shu[s3]);
	return 0;
}
*/
//1004 成绩排名 （20 分）
/*
读入 n（ > 0）名学生的姓名、学号、成绩，分别输出成绩最高和成绩最低学生的姓名和学号。
输入格式：
每个测试输入包含 1 个测试用例，格式为
第 1 行：正整数 n
第 2 行：第 1 个学生的姓名 学号 成绩
第 3 行：第 2 个学生的姓名 学号 成绩
... ... ...
第 n + 1 行：第 n 个学生的姓名 学号 成绩
其中姓名和学号均为不超过 10 个字符的字符串，成绩为 0 到 100 之间的一个整数，这里保证在一组测试用例中没有两个学生的成绩是相同的。
输出格式：
对每个测试用例输出 2 行，第 1 行是成绩最高学生的姓名和学号，第 2 行是成绩最低学生的姓名和学号，字符串间有 1 空格。
输入样例：
3
Joe Math990112 89
Mike CS991301 100
Mary EE990830 95
输出样例：
Mike CS991301
Joe Math990112
*/
/*
#include <iostream>
#include <string>
using namespace std; 
int main() {
	int n(0); // 学生个数
	cin >> n;
	string max_name(""), max_id(""),min_name(""), min_id("");
	int max(0), min(101);  //记录最大最小分数
	for(int i=0;i<n;i++) {
	    string temp1, temp2;
	    int temp3;
	    cin >> temp1 >> temp2>>temp3;
	    if(temp3>max){
	    	max =temp3;
	    	max_name=temp1;
	    	max_id = temp2;
		}
		if(temp3<min){
			min = temp3;
			min_name=temp1;
			min_id=temp2;
		}
	}
	cout << max_name << " " << max_id<<endl;
	cout << min_name << " "<< min_id; 
	return 0;
}
*/
//1008 数组元素循环右移问题 （20 分）
/*
一个数组A中存有N（ > 0）个整数，在不允许使用另外数组的前提下，将每个整数循环向右移M（≥0）个位置，即将A中的数据由（A
0
A
1
?A
N?1
）变换为（A
N?M
?A
N?1
A
0
A
1
?A
N?M?1
）（最后M个数循环移至最前面的M个位置）。如果需要考虑程序移动数据的次数尽量少，要如何设计移动的方法？
输入格式 :
每个输入包含一个测试用例，第1行输入N（1≤N≤100）和M（≥0）；第2行输入N个整数，之间用空格分隔。
输出格式 :
在一行中输出循环右移M位以后的整数序列，之间用空格分隔，序列结尾不能有多余空格。
输入样例 :
6 2
1 2 3 4 5 6
输出样例 :
	5 6 1 2 3 4
	*/
/*
#include<iostream>
#include<stdio.h>
using namespace std;
void Change(int *Ary,int M,int N);
int main()
{
    int M,N;
    cin>>M;
    cin>>N;
    int NumAry[220]={0};
    for(int i=0;i<M;i++)
    {
        cin>>NumAry[i];
        NumAry[i+M]=NumAry[i];
    }
    Change(NumAry,M,N);
    for(int i=0;i<M;i++)
    {
        if(i!=0)
        printf(" "); 
        cout<<NumAry[i];    
    }
}
void Change(int *Ary,int M,int N)
{
    int index=M-N;
    int count=N;
    if(N>=M)
    {       
        index=M-(N-M);
        count=N-M;
    }
    for(int i=0;i<M;i++)
    {
        if(i<count)
        {   
            Ary[i]=Ary[i+M+index];
            continue;
        }   
        Ary[i]=Ary[i+index];
    }
}
*/
/*
#include<iostream>
#include<cmath>
#include<string>
using namespace std;
int main (){
	char a[200];
	int n,m,i,j,t;
	cin>>n>>m;
	gets(a);
	for(i=0;a[i]!='0';i++) ;
	a[i]=' ';
	j=i;
	for(i++,t=0;i<=2*j-1;i++,t++)
		a[i]=a[t];
	for(i=n+m;i<=3*n+m-2;i++)
		cout<<a[i];	
	return 0;	
}
*/
/*
#include<iostream>
#include<cmath>
#include<string>
using namespace std;
int main (){
	char a[200];
	char b[200];
	int n,m,i,j;
	cin>>n>>m;
	gets(a);
	for(i=0,j=0;a[i]='\0';i++)
		if(a[i]!=' ')	
		{
		b[j]=a[i];
		j++;
		}
	for(i=n,j=0;i<=2*n-m;i++,j++)
		b[i]=b[j];
	for(i=0;i<n;i++)
		cout<<b[i]<<' ';
	cout<<b[n];
	return 0;	
} 
*/
//1009 说反话 （20 分）
/*
给定一句英语，要求你编写程序，将句中所有单词的顺序颠倒输出。
输入格式：
测试输入包含一个测试用例，在一行内给出总长度不超过 80 的字符串。字符串由若干单词和若干空格组成，其中单词是由英文字母（大小写有区分）组成的字符串，单词之间用 1 个空格分开，输入保证句子末尾没有多余的空格。
输出格式：
每个测试用例的输出占一行，输出倒序后的句子。
输入样例：
Hello World Here I Come
输出样例：
Come I Here World Hello
*/
/*
#include <string>
#include <iostream>
using namespace std;
int main()
{
	int i, l, j, k;
	int flag = 0;
	string s;
	getline(cin, s);
	s = ' ' + s;
	l = s.length();
	j = l - 1;
	for (i = l - 1; i >= 0; i--)
	{
		if (s[i] == ' ')
		{
			if (flag == 1)
				cout << ' ';
			else
				flag = 1;
			for (k = i + 1; k <= j; k++)
				cout << s[k];
			j = i - 1;
		}
	}
	return 0;
}
*/
//1011 A + B 和 C （15 分）
/*
给定区间[?2
31
, 2
31
] 内的 3 个整数 A、B 和 C，请判断 A + B 是否大于 C。
输入格式：
输入第 1 行给出正整数 T(≤10)，是测试用例的个数。随后给出 T 组测试用例，每组占一行，顺序给出 A、B 和 C。整数间以空格分隔。
输出格式：
对每组测试用例，在一行中输出 Case #X: true 如果 A + B > C，否则输出 Case #X: false，其中 X 是测试用例的编号（从 1 开始）。
输入样例：
4
1 2 3
2 3 4
2147483647 0 2147483646
0 - 2147483648 - 2147483647
输出样例：
Case #1: false
Case #2: true
Case #3: true
Case #4: false
*/
/*
#include <iostream>
using namespace std;
int main()
{
	int n, i;
	double a, b, c;
	cin >> n;
	for (i = 0; i < n; i++)
	{
		cin >> a >> b >> c;
		if (a + b > c)
			cout << "Case #" << i + 1 << ": true" << endl;
		else
			cout << "Case #" << i + 1 << ": false" << endl;
	}
	return 0;
}
*/
//1016 部分A + B （15 分）
/*
正整数 A 的“D
A
（为 1 位整数）部分”定义为由 A 中所有 D
A
组成的新整数 P
A
。例如：给定 A = 3862767，D
A
= 6，则 A 的“6 部分”P
A
是 66，因为 A 中有 2 个 6。
现给定 A、D
A
、B、D
B
，请编写程序计算 P
A
+ P
B
。
输入格式：
输入在一行中依次给出 A、D
A
、B、D
B
，中间以空格分隔，其中 0 < A, B < 10
	10
	。
	输出格式：
	在一行中输出 P
	A
	+ P
	B
	的值。
	输入样例 1：
	3862767 6 13530293 3
	输出样例 1：
	399
	输入样例 2：
	3862767 1 13530293 8
	输出样例 2：
	0
	*/
