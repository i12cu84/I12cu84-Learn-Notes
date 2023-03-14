#include<iostream>
using namespace std;

/*
//冒泡

void mp(int s[], int n, int m){
	int i,j,k;
	for(i=n;i<m;i++){
		for(j=n;j<m-i;j++){
			if(s[j]<s[j+1]){
				k=s[j];s[j]=s[j+1];s[j+1]=k;}}}}
int main(){
	int i,code[]={3574,8865,6712,8543,6367,8495,5708,3150,7833,6770};
	int n=sizeof(code)/sizeof(int);
	for(i=0;i<n;i++)cout<<code[i]<<" ";
	mp(code,0,n-1);
	cout<<endl<<"mp:"<<endl;
	for(i=0;i<n-1;i++)cout<<code[i]<<">";
	cout<<code[n-1];}
*/

/*
//分治有点问题
void px(int s[],int n,int q,int m){
	int i,j,k,n1=n-q+1,n2=m-q,L[11],R[11];
	for(i=1;i<n1;i++)L[i]=s[m+i-1];
	for(j=1;j<n2;j++)R[j]=s[q+j];
	L[n1]=R[n2]=999999;
	i=j=0;
	for(k=n;k<m;k++){
		if(L[i]<=R[j] && j!=n2){
			s[k]=L[i];
			i++;
		}else{
			s[k]=R[j];
			j++;
		}
	}
}
void fz(int s[], int n, int m){
	int q;
	if(n<m){
		q=(n+m)/2;
		fz(s,n,q);
		fz(s,q+1,m);
		px(s,n,q,m);
	}
}
int main(){
	int i,code[]={3574,8865,6712,8543,6367,8495,5708,3150,7833,6770};
	int n=sizeof(code)/sizeof(int);
	for(i=0;i<n;i++)cout<<code[i]<<" ";
	fz(code,0,n-1);
	cout<<endl<<"qSort:"<<endl;
	for(i=0;i<n-1;i++)cout<<code[i]<<">";
	cout<<code[n-1];
	return 0;
}
*/

/*
//分治快排
void qSort(int s[],int n,int m){
	if(n<m){
		int i=n,j=m,x=s[n];
		while(i<j){
			while(i<j && s[j]>=x)j--;
			if(i<j)s[i++]=s[j];
			while(i<j && s[i]< x)i++;
			if(i<j)s[j--]=s[i];
		}
		s[i]=x;
		qSort(s,n,i-1);
		qSort(s,i+1,m);
	}
}
int main(){
	int i,code[]={3574,8865,6712,8543,6367,8495,5708,3150,7833,6770};
	int n=sizeof(code)/sizeof(int);
	for(i=0;i<n;i++)cout<<code[i]<<" ";
	qSort(code,0,n-1);
	cout<<endl<<"qSort:"<<endl;
	for(i=0;i<n-1;i++)cout<<code[i]<<">";
	cout<<code[n-1];
}
*/

//快排 
void qSort(int s[], int n, int m) {
	int t, i = n - 1, p = n;
	if (n < m) {
		while (p < m) {
			if (s[p] < s[m]) {
				i++;
				t = s[i]; s[i] = s[p]; s[p] = t;
			}
			p++;
		}
		i++;
		t = s[p]; s[p] = s[i]; s[i] = t;
		qSort(s, n, i - 1);
		qSort(s, i + 1, m);
	}
}
int main() {
	int i, code[] = { 3574,8865,6712,8543,6367,8495,5708,3150,7833,6770 };
	int n = sizeof(code) / sizeof(int);
	for (i = 0; i < n; i++)cout << code[i] << " ";
	qSort(code, 0, n - 1);
	cout << endl << "qSort:" << endl;
	for (i = 0; i < n - 1; i++)cout << code[i] << ">";
	cout << code[n - 1]<<endl;
}
//以上快排过不了洛谷题，很奇怪 三个样例TLE，盲猜是参数传入导致速度降低了
#include <bits/stdc++.h>
using namespace std;
int n, a[1000001];
void qsort(int l, int r) {
	int mid = a[(l + r) / 2], i = l, j = r;
	do {
		while (a[i] < mid)i++;
		while (a[j] > mid)j--;
		if (i <= j) {
			swap(a[i], a[j]);
			i++;
			j--;
		}
	} while (i <= j);
	if (l < j)qsort(l, j);
	if (i < r)qsort(i, r);
}
int main() {
	cin >> n;
	for (int i = 1; i <= n; i++)cin >> a[i];
	qsort(1, n);
	for (int i = 1; i <= n; i++)cout << a[i] << " ";
}