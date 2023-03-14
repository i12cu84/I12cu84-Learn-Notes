#include<bits/stdc++.h>
using namespace std;
//page 12 字符串转整数 
//注：边界条件 错误处理 正负号情况
//修改前
// int strtoint(char* string){
//     int number=0;
//     while(*string !='\0' ){
//         number=number*10+*string-'0';
//         string++;
//     }
//     cout<<number<<endl;//正常输出
//     return 0;
// }
// int main(){
//     char stringnumber[]="12";
//     strtoint(stringnumber);
//     return 0;
// }
//修改后 注：暂未考虑数据溢出
int strtoint(char* string){
    if(*string=='\0'){//空指针报错返回
        cerr<<"null"<<endl;
        return -1;
    }
    int number=0,sign=1;
    if(*string=='-'){//正负号判断
        sign=-1;
        string++;
    }
    while(*string !='\0' ){
        if((*string-'0'>9)||(*string-'0'<0)){//特判特殊字符
            cerr<<"error"<<endl;
            return -1;
        }
        number=number*10+*string-'0';
        string++;
    }
    cout<<number*sign<<endl;//正常输出
    return 0;
}
int main(){
    char stringnumber[]="-12";
    strtoint(stringnumber);
    return 0;
}

//page 13 链表的倒数第k个节点
//思路：让指针A先走k-1个节点 随后A、B指针同时行走 ->B所指即为所需
//注：若链表未长于k呢？
//修改前
ListNode* FindKthToTail(ListNode* pListHead,unsigned int k){
    if(pListHead==nullptr)return nullpte;//空表特判
    ListNode *pAhead=pListHead;
    ListNode *pBehind=nullptr;
    for(unsigned int i=0;i<k-1;i++)
        pAhead=pAhead->m_pNext;
    pBehind=pListHead;
    while(pAhead->m_pNext!=nullptr){
        pAhead=pAhead->m_pNext;
        pBehind=pBehind->m_pNext;
    }
    return pBehind;
}
//修改后
ListNode* FindKthToTail(ListNode* pListHead,unsigned int k){
    if(pListHead==nullptr)return nullptr;//空表特判
    ListNode *pAhead=pListHead；
    ListNode *pBehind=nullptr；
    for(unsigned int i=0;i<k-1;i++){
        if(pAhead->m_pNext==nullptr){//长度不足特判
            cerr<<"error"<<endl;
            return nullptr;
        }
        pAhead=pAhead->m_pNext;
    }
    pBehind=pListHead;
    while(pAhead->m_pNext!=nullptr){
        pAhead=pAhead->m_pNext;
        pBehind=pBehind->m_pNext;
    }
    return pBehind;
}
//page 24 出错实例 递归调用 造成栈溢出
class A{
    private:int value;
    public:
    A(int n){value=n;}
    A(A other){value=other.value;}//出错点
    A(const A& other){value=other.value;}//修正方案->传值参数改成常量引用
    void Print(){std::cout<<value<<std::endl;}
};
int _tmain(int argc,_TCHAR* argv[]){
    A a=10;
    A b=a;
    b.Print();
    return 0;
}
//page 25 添加赋值运算符函数
class CMyString{
    public:
        CMyString(char* pData=nullptr);
        CMyString(const CMyString& str);
        ~CMyString(void);
        //解
        CMyString& CmyString::operator =(const CMyString &str){//const可以不改变传入实例的状态
            if(this==&str)return *this;//如果是同一个实例 则不进行赋值操作
            delete []m_pData;//释放自身已有内存 避免内存泄漏
            m_pData=nullptr;
            m_pData=new char[strlen(str.m_pData)+1];
            strcpy(m_pData,str.m_pData);
            return *this;//可以连续赋值 否则str1=str2=str3无法编译
        }
        //思路参考->异常安全性原则
        CMyString& CMyString::operator =(const CMyString &str){
            if(this!=&str){//判断是否同一实例
                CMyString strTemp(str);//局部变量释放内存 相当于 调用析构函数释放实例内存
                char* pTemp=strTemp.m_pData;
                strTemp.m_pData=m_pData;
                m_pData=pTemp;
            }
            return *this;
        }
    private:
        char* m_pData;
}
//cpp中 struct和class区别：默认public和默认private
//cs 中 都默认private 而 struct定义值类型   实例在栈上分配内存 
//                       class定义引用类型 实例在堆上分配内存
//page 29 c#环境
class A{
    public A(string text){
        Console.WriteLine(text);//终端打印
    }
}
class B{
    static A a1=new A("a1");
    A a2=new A("a2");
    static B(){
        a1=new A("a3");
    }
    public B(){
        a2=new A("a4");
    }
}
class Program{
    static void Main(string[] args){
        B b=new B();
    }
}
//先后打印 a1 a3 a2 a4
//page 30 反射和应用程序域的代码 c#
[Serializable]
internal class A:MarshalByRefObject{
    public static int Number;
    public void SetNumber(int value){
        Number=value;
    }
}
[Serializable]
internal class B{
    public stitic int Number;
    public void SetNumber(int value){
        Number=value;
    }
}
class Program{
    static void Main(string[] args){
        String assambly=Assembly.GetEntryAssembly().FullName;
        AppDomain domain=AppDomain.CreateDomain("NewDomain");//应用程序域创建
        //继承不同 效果将会不同
        A.Number=10;
        String nameOfA=typeof(A).FullName;
        A a=domain.CreateInstanceAndUnwrap(assambly,nameOfA) as A;
        a.SetNumber(20);//不受改变
        Console.WriteLine("Number in class A is {0}",A.Number);
        //输出10
        B.Number=10;
        String nameOfB=typeof(B).FullName;
        B b=domain.CreateIntanceAndUnwarp(assambly,nameOfB) as B;
        b.SetNumber(20);
        Console.WriteLine("Number in class B is {0}",B.Number);
        //输出20
    }
}
//gape 32 c# 设计一个类 只能生成该类的一个实例
//局限：只限于单线程环境
public sealed class Singleton1{
    private Singleton1(){
    }
    private static Singleton1 instance=null;
    public static Singleton1 Instance{
        get{
            if(instance==null)instance==new Singleton1();
            return instance;
        }
    }
}
//局限：可多线程但效率不高
public sealed class Stingleton2{
    private Singleton2(){
    }
    private static readonly object syncObj=new object();
    private static Singleton2 instance=null;
    public static Singleton2 Instance{
        get{
            lock(syncObj){//添加同步锁达成多线程目地
                if(instance==null)instance=new Singleton2();
                //由于第一个线程运行后已经创建实例 则第二线程将不会重复创建实例
                //但加锁十分耗时，应当尽量避免
            }
            return instance;
        }
    }
}
//可行解 前后两次判断实例是否存在 比ton2 效率略高
public sealed class Singleton3{
    private Singleton3(){
    }
    private static object syncObj=new object();
    private static Singleton3 instance=null;
    public static Singleton3 Instance{
        get{
            if(instance==null){//如果空则加锁
                lock(syncObj){
                    if(instance==null)
                        instance=new Singleton3();
                }
            }
            return instance;
        }
    }
}
//推荐解法1 -> 利用静态构造函数
public sealed class Singleton4{
    private Singleton4(){
    }
    private static Singleton4 instance=new Singleton4();
    public static Singleton4 Instance{//静态构造函数 只会调用一次
        get{
            return instance;//因而只将初始化一次
        }
    }
}
//推荐解法2 -> 按需创建实例
public sealed class Singleton5{
    Singleton5(){
    }
    public static Singleton5 Instance{
        get{
            return Nested.instance;
        }
    }
    class Nested{
        static Nested(){
        }
        internal static readonly Singleton5 instance=new Singleton5();
    }
}
//page 38 数组与指针区别
int GetSize(int data[]){
    return sizeof(data);
}
int _tmain(int argc,_TCHAR* argv[]){
    int data1[]={1,2,3,4,5};
    int size1=sizeof(data1);//求数组的大小
    int* data2=data1;
    int size2=sizeof(data2);//指针大小
    int size3=GetSize(data1);//同上
    print("%d,%d,%d",size1,size2,size3);
}
//输出 20,4,4 
//page 40 数组中重复的数字(条件：数字大小不超过数组长度)
//概括：    从头开始寻找， 
//          如果当前数组与数组中数据相符则跳过
//          如果当前数组与数组中数据不符则与第"数据"个数组互换位置  时间、空间复杂度：O(n) O(1)
bool duplicate(int numbers[],int length,int* duplication){
    if(numbers==nullptr||length<=0)return false;
    for(int i=0;i<length;i++)
        if(numbers[i]<0||numbers[i]>length-1)
            return false;
    for(int i=0;i<length;i++)
        while(numbers[i]!=i){
            if(numbers[i]==numbers[number[i]]){
                *duplication=numbers[i];
                return true;
            }
            //swap numbers[i] ans numbers[numbers[i]]
            int temp=numbers[i];
            numbers[i]=numbers[temp];
            numbers[temp]=templ
            //swap(numbers[i],numbers[numbers[i]]);
        }
    return false;
}
//page 42 不修改数组找出重复的数字(条件：1~n范围内,至少有一个数重复,不能改输入数组)
//概括：采用二分法
//具体：    1~n数组分为1~m和m+1~n,
//         如果1~m中数目在数组中出现的次数超过m,则其中存在重复的数组,否则另一区间一定包含重复数字
//时间、空间复杂度：O(nlogn) O(1)
int getDuplication(const int* numbers,int length){//数组地址和长度
    if((numbers==nllptr)||length<=0)return -1;//异常报错
    int start=1;
    int end=length-1;
    while(end>=start){
        int middle=((end-start)>>1)+start;//取中
        int count=countRange(numbers,length,start,middle);
        if(end==start)
            if(count>1)return start;
            else break;
        if(count>(middle-start+1))end=middle;
        else start=middle+1;
    }
    return -1;
}
int countRange(const int* numbers,int length,int start,int end){//在数组中计算区间内的数字出现过的次数
    if(numbers==nullptr)return 0;//空指针返回
    int count=0;
    for(int i=0;i<length;i++)
        if(numbers[i]>=start && numbers[i]<=end)//从数组中每一个数字对序列中数组进行比对统计
            count++;
    return count;
}
//page 47 二维数组中的查找 判断二维数组中是否存在指定数字(条件：从上到下、从左到右递增)
//概括：由递增可以从右上角的数字得知该矩阵的该列是否存在该数 多次左下左下运作可得效果
bool Find(int* matrix,int rows,int columns,int number){//输入地址、数组行列、所需查找数字
    bool found=false;
    if(matrix!=nullptr && rows>0 && columns>0){
        int row=0;
        int column=columns-1;
        while(row<rows && column>=0){
            if(matrix[row*columns+column]==number){
                found=true;//找到
                break;
            }
            else if(matrix[row*columns+column]>number)column--;//如果大于则转左一列
            else row++;//如果小于则转下一行
        }
    }
    return found;
}
//page 49
int _tmain(int argc,_TCHAR*  argv[]){
    char str1[]="123";
    char str2[]="123";
    //str1!=str2
    char* str3[]="123";
    char* str4[]="123";
    //str3==str4
}
//而c#中
class Program{
    internal static void ValueOrReference(Type type){
        String result="The type"+type.Name;
        if(type.IsValueType)Console.WriteLine(result+"is a value type.")l
        else Console.WriteLine(result+"is a reference type.");
    }
    internal static void ModifyString(String text){
        text="world";
    }
    static void Main(string[] args){
        String text="hello";//public sealed class String -> 引用类型
        ValueOrReference(text.GetType());
        ModifyString(text);
        Console.WriteLine(text);
    }
}
//page 54 空格替换(将空格替换成"%20")
//基本思路：创建所需长度,而后对新字符串从后往前进行依次替换 时间复杂度O(n)
//目的：减少移动减少替换次数从而提高效率
/*length 为字符数组string的总容量*/
void ReplaceBlank(char string[],int length){
    if(string==nullptr||length<=0)return;
    /*originalLength 为字符串string的实际长度*/
    int originalLength=0;
    int numberOfBlank=0;
    int i=0;
    while(sring[i]!='\0'){
        originalLength++;
        if(string[i]=='')numberOfBlank++;
        i++;
    }
    /*newLength 为把空格替换成"%20"之后的长度*/
    int newLength=originalLength+numberOfBlank*2;//原长度+空格次数*(替换字符串长度-空格长度)
    if(newLength>length)return;
    int indexOfOriginal=originalLength;
    int indexOfNew=newLength;
    while(indexOfOriginal>=0 && indexOfNew>indexOfOriginal){
        if(string[indexOfOriginal]==''){//倒叙修改
            string[indexOfNew--]='0';
            string[indexOfNew--]='2';
            string[indexOfNew--]='%';
        }
        else string[indexOfNew--]=string[indexOfOriginal];
        indexOfOriginal--;
    }
}
//page 56 单向链表
//定义节点
struct ListNode{
    int m_nValue;
    ListNode* m_pNext;
};
//末尾添加节点
void AddToTail(ListNode** pHead,int value){
    ListNode* pNew=new ListNode();
    pNew->m_nValue=value;
    pNew->m_pNext=nullptr;
    if(*pHead==nullptr)*pHead=pNew;//指向指针的指针
    else {
        ListNode* pNode=*pHead;//指向指针的指针,从头开始
        while(pNode->m_pNext!=nullptr)pNode=pNode->m_pNext;//跑到根节点
        pNode->m_pNext=pNew;//添加节点
    }
}
//找到第一个含有某值的节点并删除该节点
void RemoveNode(ListNode** pHead,int value){
    if(pHead==nullptr||*pHead==nullptr)return;
    ListNode* pToBeDeleted=nullptr;
    if((*pHead)->m_nValue==value){
        pToBeDeleted=*pHead;
        *pHead=(*pHead)->m_pNext;
    }else{
        ListNode* pNode=*pHead;
        while(pNode->m_pNext!=nullptr && pNode->m_pNext->m_nValue!=value)pNode=pNode->m_pNext;//非空或不相等
        if(pNode->m_pNext!=nullptr && pNode->m_pNext->m_nValue==value){//非空且相等
            pToBeDeleted=pNode->m_pNext;
            pNode->m_pNext=pNode->m_pNext->m_pNext;
        }
    }
    if(pToBeDeleted!=nullptr){
        delete pToBeDeleted;
        pToBeDeleted=nullptr;
    }
}
//page 58 从尾到头打链表
struct ListNode{
    int m_nKey;
    ListNode* m_pNext;
};
//解法1 后进先出 栈
void PrintListReversingly_Iteratively(ListNode* pHead){
    std::stack<ListNode*> nodes;//建立栈
    ListNode* pNode=pHead;
    while(pNode!=nullptr){
        nodes.push(pNode);//存入
        pNode=pNode->m_pNext;
    }
    while(!nodes.empty()){
        pNode=nodes.top();//后进先出
        printf("%d\t",pNode->m_nValue);
        nodes.pop();//去除顶端
    }
}
//解法2 递归
void PrintListReversingly_Recursively(ListNode* pHead){
    if(pHead!=nullptr){//非空判断
        if(pHead->m_pNext!=nullptr)PrintListReversingly_Recursively(pHead->m_pNext);//递归
        printf("%d\t",pHead->m_nValue);//输出
    }
    //若链表过长不建议使用,容易导致栈溢出
}
//page 62 重建二叉树
struct BinaryTreeNode{
    int m_nValue;
    BinaryTreeNode* m_pLeft,m_pRight;
};
BinaryTreeNode* Construct(int* preorder,int* inorder,int length){
    if(preorder==nullptr||inorder==nullptr||length<=0)return nullptr;   
    return ConstructCore(preorder,preorder+length-1,inorder,inorder+length-1);
}
BinaryTreeNode* ConstructCore(
    int* startPreorder,int* endPreorder,
    int* startInorder,int* endInorder
)
{
    //前序遍历序列的第一个数字是根节点的值
    int rootValue=startPreorder[0];
    BinaryTreeNode* root=new BinatyTreeNode();
    root->m_nValue=rootValue;
    root->m_pLetf=root->m_pRight=nullptr;
    if(startPreoroder==endPreorder)
        if(startInorder==endInorder && *startPreorder==*startInorder)return root;
        else throw std::exception("Invalid input.")
    //在中序遍历序列中找到根节点的值
    int* rootInorder=startInorder;
    while(rootInorder<=endInorder && *rootInorder!=rootValue)rootInorder++;
    if(rootInorder==endInorder && *rootInorder!=rootValue)throw std::exception("Invalid input.");
    int leftLength=rooInorder-startInorder;
    int* leftPreorderEnd=startPreorder+leftLength;
    if(leftLength>0)root->m_pLeft=ConstructCore(startPreorder+1,leftPreorderEnd,startInorder,rootInorder-1);
    if(leftLength<endPreorder-startPreorder)
        root->m_pRight=ConstructCore(leftPreorderEnd+1,endPreorder,rootInorder+1,endInorder);
    return root;
}
//page 66 二叉树下的节点(求中序遍历情况下的下一个节点)
BinaryTreeNode* GetNext(BinaryTreeNode* pNode){
    if(pNode==nullptr)return nullptr;
    BinaryTreeNode* pNext=nullptr;//所求的下一个节点
    if(pNode->m_pRight!=nullptr){//可能在右子节点的情况
        BinaryTreeNode* pRight=pNode->m_pRight;//指向右子节点
        while(pRigth->m_pLeft!=nullptr)pRight=pRight->m_pLeft;
        pNext=pRight;//节点的右子节点的最左节点为所求的下一个节点
    }else if(pNode->m_pParent!=nullptr){//当节点无右子节点情况下,可能在父节点的情况
        BinaryTreeNode* pCurrent=pNode;
        BinaryTreeNode* pParent=pNode->m_pParent;//指向父节点
        //如果节点是父节点的左节点,父节点则是下一个节点
        while(pParent!=nullptr && pCurrent==pParent->m_pRight){
            //如果节点是父节点的右节点,寻找父节点中,使父节点为左节点的祖节点
            pCurrent=pParent;
            pParent=pParent->m_pParent;
        }
        pNext=pParent;
    }
    return pNext;
}
//page 68 两个栈实现队列 (将两个先进后出的栈实现先进先出的队列)
template<typename T>class CQueue{
    public:
        CQueue(void);//队列
        ~CQueue(void);
        void appendTail(const T& node);//对前栈插入
        T deleteHead();//双栈转换
    private:
        stack<T> stack1;//前栈
        stack<T> stack2;//后栈
}
template<typename T> void Cqueue<T>::appendTail(const T& element){
    stack1.push(element);//对前栈插入
}
template<typename T> T Cqueue<T>::deleteHead(){//双栈转换
    if(stack2.size()<=0)//后栈无数则进栈
        while(stack1.size()>0){//前栈有数则继续
            T& data=stack1.top();
            stack1.pop();
            stack2.push(data);
        }
    if(stack2.size()==0)throw new exception("queue is empty");//后栈无数退出
    T head=stack2.top();
    stack2.pop();
    return head;
}
//思考:两个队列实现栈
//求sum(1~n)
//递归
int AddFrom1ToN_Recursive(int n){
    return n<=0?0:n+AddFrom1ToN_Recursive(n-1);
}
//循环
int AddFrom1To_Interative(int n){
    int result=0;
    for(int i=1;i<=n;i++)result+=i;
    return result;
}
//page 75 低效斐波那契
long long Fibonacci(unsigned int n){
    if(n<=0)return 0;
    if(n==1)return 1;
    return Fibonacci(n-1)+Fibonacci(n-2);
}
//时间复杂度O(n)
long long Fibonacci(unsigned int n){
    int result[2]={0,1};
    if(n<2)return result[n];
    long long fibNMinusOne=1;
    long long fibNMinusTwo=0;
    long long fibN=0;
    for(unsigned int i=2;i<=n;i++){
        fibN=fibNMinusOne+fibNMinusTwo;
        fibNMinusTwo=fibNMinusOne;
        fibNMinusOne=fibN;
    }
    return fibN;
}
//时间复杂度O(nlogn) 但不实用解析 page 76
//page 80 查找和排序
int Partition(int data[],int length,int start,int end){
    if(data==nullptr||length<=0||start<0||end>=length)
        throw new std::exception("Invalid Parameters");
    int index=RandomInRange(start,end);
    Swap(&data[index],&data[end]);
    int small=start-1;
    for(index=start;index<end;index++)
        if(data[index]<data[end]){
            small++;
            if(small!=index)Swap(&data[index],&data[samll]);
        }
    small++;
    Swap(&data[small],&data[end]);
    return small;
}
//page 81 快排
void QuickSort(int data[],int length,int start,int end){
    if(start==end)return;
    int index=Partition(data,length,start,end);
    if(index>start)QuickSort(data,length,start,index-1);
    if(index<end)QuickSort(data,length,index+1,end);
}
//page 82 排序 时间效率O(n)
void SortAges(int ages[],int length){
    if(ages==nullp||length<=0)return;
    const int oldestAge=99;
    int timesOfAge[oldestAge+1];
    for(int i=0;i<=oldestAge;i++)timesOfAge[i]=0;
    for(int i=0;i<length;i++){
        int age=ages[i];
        if(age<0||age>oldestAge)throw new std::exception("age out of range");
        timesOfAge[age]++;
    }
    int index=0;
    for(int i=0;i<=oldestAge;i++)
        for(int j=0;j<timesOfAge[i];j++)
            ages[index]=i,index++;
}
//page 84 对旋转(将升序列截断换序)的数进行搜索最小数 时间复杂度(logn)
//概括:取中值,若大于左右,则中值为左
//           若小于左右,则中值为右(对分思路)
//bug:存在相同数会异常
int Min(int* numbers,int length){
    if(numbers==nullptr||length<=0)
        throw new std::exception("Invalid parameters");
    int index1=0;
    int index2=length-1;
    int indexMid=index1;
    while(numbers[index1]>=numbers[index2]){
        if(index2-index1==1){//相邻 终止
            indexMid=index2;
            break;
        }
        indexMid=(index1+index2)/2;
        if(numbers[indexMid]>=numbers[index1])index1=indexMid;
        else if(numbers[indexMid]<=numbers[index2])index2=indexMid;
    }
    return numbers[indexMid];
}
//优化 若三数相等->顺序查找
int Min(int* numbers,int length){
    if(numbers==nullptr||length<=0)
        throw new std::exception("Invalid parameters");
    int index1=0;
    int index2=length-1;
    int indexMid=index1;
    while(numbers[index1]>=numbers[index2]){
        if(index2-index1==1){
            indexMid=index2;
            break;
        }
        indexMid=(index1+index2)/2;
        //如果三数相等，则只能顺序查找
        if(numbers[index1]==numbers[index2] && numbers[indexMid]==numbers[index1])
            return MinInOrder(numbers,index1,index2);
        if(numbers[indexMid]>=numbers[index1])index1=indexMid;
        else if(numbers[indexMid]<=numbers[index2])index2=indexMid;
    }
    return numbers[indexMid];
}
int MinInOrder(int* numbers,int index1,int index2){
    int result=numbers[index1];
    for(int i=index1+1;i<=index2;i++)
        if(result>numbers[i])
            result=numbers[i];
    return result;
}
//page 89 回溯法 矩阵中的路径
//在矩阵中寻找一条路径能复现所需的字符串
bool hasPath(char* matrix,int rows,int cols,char* str){
    if(matrix==nullptr||rows<1||cols<1||str==nullptr)return false;
    bool* visited=new bool[rows* cols];
    memset(visited,0,row*cols);
    int pathLength=0；
    for(int row=0;row<rows;row++)
        for(int col=0;col<cols;col++)
            if(hasPathCore(matrix,rows,cols,row,col,str,pathLength,visited))
                return true;
    delete[] visited;
    return false;
}
bool hasPathCore(const char* matrix,int rows,int cols,int row,int col,
                const char* str,int& pathLength,bool* visited){
    if(str[pathLength]=='\0')return true;
    bool hasPath=false;
    if(row>=0 && row<rows && col>=0 && col<cols 
        && matrix[row*cols+col]==str[pathLength] && !visited[row*cols+col]){
        pathLength++;
        visited[row*cols+col]=true;
        hasPath=hasPathCore(matrix,rows,cols,row,col-1,str,pathLength,visited) ||
                hasPathCore(matrix,rows,cols,row-1,col,str,pathLength,visited) ||
                hasPathCore(matrix,rows,cols,row,col+1,str,pathLength,visited) ||
                hasPathCore(matrix,rows,cols,row+1,col,str,pathLength,visited) 
        if(!hasPath){
            pathLength--;
            visited[row*cols+col]=flase;
        }
    }
    return hasPath;
}
//page 92 机器人的运动范围  (坐标的位数之和以内)
int movingCount(int threshold,int rows,int cols){
    if(threshold<0||rows<=||cols<=0)return 0;
    bool* visited=new bool[rows*cols];
    for(int i=0;i<rows*cols;i++)visited[i]=false;
    int count=movingCountCore(threshold,rows,cols,0,0,visited);
    delete[] visited;
    return count;
}
int movingCountCore(int threshold,int rows,int cols,int row,int col,bool* visited){
    int count=0;
    if(check(threshold,rows,cols,row,col,visited)){
        visited[row*cols+col]=true;
        count=1 +movingCountCore(threshold,rows,cols,row-1,col,visited)
                +movingCountCore(threshold,rows,cols,row,col-1,visited)
                +movingCountCore(threshold,rows,cols,row+1,col,visited)
                +movingCountCore(threshold,rows,cols,row,col+1,visited);
    }
    return count;
}
//是否能进入方格
bool check(int threshold,int rows,int cols,int row,int col,bool* visited){
    if(row>=0 && row<=rows && col>=0 &&col<cols
        && getDigitSum(row)+getDigitSum(col)<=threshold &&!visited[row*cols+col])
        return true;
    return false;
}
//位数计算
int getDisitSum(int number){
    int sum=0;
    while(number>0){
        sum+=number%10;
        number/=10;
    }
    return sum;
}
//page 96 剪绳子(长n切m断求最大乘积) 动态规划
int maxProductAfterCutting_solution(int length){
    if(length<2)return 0;
    if(length==2)return 1;
    if(length==3)return 2;
    int* products=new int[length+1];
    products[0]=0;
    products[1]=1;
    products[2]=2;
    products[3]=3;
    int max=0;
    for(int i=4;i<=length;i++){
        max=0;
        for(int j=1;j<=i/2;j++){
            int product=products[j]*products[i-j];
            if(max<product)max=product;
            products[i]=max;
        }
    }
    max=products[length];
    delete[] products;//new后记得delete
    return max;
}
//贪心算法
int maxProductAfterCutting_solution2(int length){
    if(length<2)return 0;
    if(length==2)return 1;
    if(length==3)return 2;
    int timesOf3=length/3;
    if(length-timesOf3*3==1)timesOf3-=1;
    int timesOf2=(length-timesOf3*3)/2l
    return (int)(pow(3,timesOf3))*(int)(pow(2,timesOf2));
}
//page 100 二进制中1的个数
//容易死循环的解法 由于负数移位后首位为1而出错
int NumberOf1(int n){
    int count=0;
    while(n){
        if(n&1)count++;//换成除会降低效率
        n=n>>1;
    }
    return count;
}
//常规解法
int NumberOf2(int n){
    int count=0;
    unsigned int flag=1;
    while(flag){
        if(n & flag)//与运算 判断末位是否为1
            count++;
        flag = flag <<1;
    }
    return count;
}
//更优思路
int NumberOf3(int n){
    int count=0;
    while(n){
        count++;
        n=(n-1)&n;//-1后后置位按位取反 与逻辑之后只会取前置位
    }
    return count;
}
//page 110 数值的整数次方
//bug:exponent小于1或负数
double PowerWithUnsignedExponent(double base,int exponent){
    double result=1.0;
    for(int i=1;i<=exponent;i++)
        result*=base;
    return result;
}
//改进方案
bool g_InvalidInput=false;
double Power(double base,int exponent){
    g_InvalidInput=false;
    if(equal(base,0.0) && exponent<0){//base为0且幂次小于零 -> 出错
        //出错时返回0且g_InvalidInput为true
        g_InvalidInput=true;
        return 0.0;
    }
    unsigned int absExponent=(unsigned int)(exponent);
    if(exponent<0)absExponent=(unsigned int)(-exponent);//负幂次化正
    double result=PowerWithUnsignedExponent(base,absExponent);//求幂次,运用以上函数
    if(exponent<0)result=1.0/result;//负幂次反倒数求倒数
    return result;
}
//更高效方案 指数为正的情况下,对分计算高次幂
double PowerWithUnsignedExponent(double base,unsigned int exponent){
    if(exponent==0)return 1;
    if(exponent==1)return base;
    double result=PowerWithUnsignedExponent(base,exponent>>1);
    result*=result;
    if(exponent & 0x1==1)return result*=base;//与代替除以二 提高效率
    return result;
}
//page 115 打印从1到最大的n位数(注意大数)
void Print1ToMaxOfNDigits(int n){
    if(n<=0)return;//报错
    char* number=new char[n+1];
    memset(number,'0',n);
    number[n]='\0';
    while(!Increment(number))//函数表示数字的字符串number上增加1
        PrintNumber(number);
    delete[] number;
}
bool Increment(char* number){//数字的字符串number上增加1
    bool isOverflow=false;
    int nTakeOver=0;
    int nLength=strlen(number);
    for(int i=nLength-1;i>=0;i--){
        int nSum=number[i]-'0'+nTakeOver;
        if(i==nLength-1)nSum++;
        if(nSum>=10){
            if(i==0)isOverflow=true;
            else {
                nSum-=10;
                nTakeOver=1;
                number[i]='0'+nSum;
            }
        }else{
            number[i]='0'+nSum;
            break;
        }
    }
    return isOverflow;
}
//以阅读习惯 去0
void PrintNumber(char* number){
    bool isBeginning0=true;
    int nLength=strlen(number);
    for(int i=0;i<nLength;i++){
        if(isBeginning0 && number[i]!='0')isBeginning0=false;
        if(!isBeginning0)printf("%c",number[i]);
    }
    printf("\t");
}
//page 117 全排列解法
void Print1ToMaxOfNDigits(int n){
    if(n<=0)return;
    char* number=new char[n+1];
    number[n]='\0';
    for(int i=0;i<10;i++){
        number[0]=i+'0';
        Print1ToMaxOfNDigitsRecursively(number,n,0);
    }
    delete[] number;
}
void Print1ToMaxOfNDigitsRecursively(char* number,int length,int index){
    if(index==length-1){
        PrintNumber(number);//运用上式函数
        return;
    }
    for(int i=0;i<10;i++){
        number[index+1]=i+'0';
        Print1ToMaxOfNDigitsRecursively(number,length,index+1);
    }
}
//page 120 删除链表的节点
struct ListNode{
    int m_nValue;
    ListNode* m_pNext;
};
void DeleteNode(ListNode** pListHead,ListNode* pToBeDeleted){
    //bug:需要确保删除的节点存在 否则会出大问题
    if(!pListHead||!pToBeDeleted)return;
    if(pToBeDeleted->m_pNext!=nullptr){
        //要删除的节点不是尾节点
        ListNode* pNext=pToBeDeleted->m_pNext;
        pToBeDeleted->m_nValue=pNext->m_nValue;
        pToBeDeleted->m_pNext=pNext->m_pNext;
        delete pNext;
        pNext=nullptr;
    }else if(*pListHead==pToBeDeleted){
        //链表只有一个节点 删除头节点(也是尾节点)
        delete pToBeDeleted;
        pToBeDeleted=nullptr;
        *pListHead=nullptr;
    }else{
        //链表中有多个节点 删除尾节点
        ListNode* pNode=*pListHead;
        while(pNode->m_pNext!=pToBeDeleted)
            pNode=pNode->m_pNext;
        pNode->m_pNext=nullptr;
        delete pToBeDeleted;
        pToBeDeleted=nullptr;
    }
}
//page 123 删除链表中重复的节点
void DeletedDuplication(ListNode** pHead){
    if(pHead==nullptr||*pHead==nullptr)return;
    ListNode* pPreNode=nullptr;
    ListNode* pNode=*pHead;
    while(pNode!=nullptr){
        ListNode* pNext=pNode->m_pNext;
        bool needDelete=false;
        if(pNext!=nullptr && pNext->m_nValue==pNode->m_nValue)
            needDelete=true;
        if(!needDelete){//跳过
            pPreNode=pNode;
            pNode=pNode->m_pNext;
        }else{//开始删除
            int value=pNode->m_nValue;
            ListNode* pToBeDel=pNode;
            while(pToBeDel!=nullptr && pToBeDel->m_nValue==value){
                pNext=pToBeDel->m_pNext;
                delete pToBeDel;
                pToBeDel=nullptr;
                pToBeDel=pNext;
            }
            if(pPreNode==nullptr)*pHead=pNext;
            else pPreNode->m_pNext=pNext;
            pNode=pNext;
        }
    }
}
//page 125 正则表达式匹配(这个不太会)
//'.'表示任意一个字符
//'*'表示它前面的字符可以出现任意次(含0次)
bool match(char* str,char* pattern){
    if(str==nullptr||pattern==nullptr)return false;
    return matchCore(str,pattern);
}
bool matchCore(char* str,char* pattern){
    if(*str=='\0' && *pattern=='\0')return true;
    if(*str!='\0' && *pattern=='\0')return false;
    if(*(pattern+1)=='*'){
        if(*pattern==*str||(*pattern=='.' && *str!='\0'))
            return  matchCore(str+1,pattern+2) ||
                    matchCore(str+1,pattern)   ||
                    matchCore(str,pattern+2);
        else return matchCore(str,pattern+2);
    }
    if(*str==*pattern||(*pattern=='.' && *str!='\0'))
        return matchCore(str+1,pattern+1);
    return false;
}
//page 127 表示数值的字符串
bool isNumeric(const char* str){
    if(str==nullptr)return false;
    bool numeric=scanInteger(&str);
    if(*str=='.'){
        str++;
        numeric=scanUnsignedInteger(&str)||numeric;
    }
    if(*str=='e'||*str=='E'){
        str++;
        numeric=numeric && scanInteger(&str);
    }
    return numeric && *str=='\0';
}
bool scanUnsignedInteger(const char** str){
    const char* before=*str;
    while(**str!='\0' && **str>='\0' && **str<='9')(*srt)++;
    return *str>before;
}
bool scanInteger(const char** str){
    if(**str=='+'||**str=='.')(*str)++;
    return scanUnsignedInteger(str);
}
//page 131 调整数组顺序使奇数位于偶数前面
// void ReorderOddEven(int* pDATA,unsigned int length){
void ReorderOddEven(int* pDATA,unsigned int length,bool (*func)(int)){//改为
    if(pData==nullptr||length==0)return;
    int* pBegin=pData;
    int* pEnd=pData+length-1;
    while(pBegin<pEnd){
        //向后移动pBegin 直到指向偶数
        // while(pBegin<pEnd && (*pBegin & 0x1)!=0)pBegin++;
        while(pBegin<pEnd && !func(*pBegin))pBegin++;//改为
        //向前移动pEnd 直到指向奇数
        // while(pBegin<pEnd && (*pEnd & 0x1)==0)pEnd--;
        while(pBegin<pEnd && func(*pBegin))pEnd--;//改为
        if(pBegin<pEnd){
            int temp=*pBegin;
            *pBegin=*pEnd;
            *pEnd=temp;
        }
    }
}
//page 132中附加 将会包装效果
bool isEven(int n){
    return (n&1)==0;
}
void ReorderOddEven(int* pData,unsigned int length){
    Reorder(pData,length,isEven);
}
//page 135 链表中倒数第k个节点
//注意:1.空指针 2.总结点少于k 3.k=0
struct ListNode{
    int m_nValue;
    ListNode* m_pNext;
};
ListNode* FindKthToTail(ListNode* pListHead,unsigned int k){
    if(pListHead==nullptr||k==0)return nullptr;//1 & 3
    ListNode* pAhead=pListHead;
    ListNode* pBehind=nullptr;
    for(unsigned int i=0;i<k-1;i++){//走k-1步
        if(pAhead->m_pNext!=nullptr)pAhead=pAhead->m_pNext;
        else return nullptr;//2
    }
    pBehind=pListHead;
    while(pAhead->m_pNext!=nullptr){//同时走 到终点
        pAhead=pAhead->m_pNext;
        pBehind=pBehind->m_pNext;
    }
    return pBehind;
}
//page 140 链表中环的入口节点
//概括:定义两个指针 一个走一步 一个走两步 相遇则有环
ListNode* MeetingNode(ListNode* pHead){
    if(pHead==nullptr)return nullptr;
    ListNode* pSlow=pHead->m_pNext;
    if(pSlow==nullptr)return nullptr;
    ListNode* pFast=pSlow->m_pNext;
    while(pFast!=nullptr && pSlow!=nullptr){
        if(pFast==pSlow)return pFast;
        pSlow=pSlow->m_pNext;
        pFast=pFast->m_pNext;
        if(pFast!=nullptr)pFast=pFast->m_pNext;
    }
    return nullptr;
}
ListNode* EntryNodeOfLoop(List* pHead){
    ListNode* meetingNode=MeetingNode(Head);
    if(meetingNode==nullptr)return nullptr;
    int nodesInLoop=1;//得到环中节点的数目
    ListNode* pNode1=meetingNode;
    while(pNode1->m_pNext!=m_pNext!=meetingNode){
        pNode1=pNode1->m_pNext;
        nodesInLoop++;
    }
    pNode1=pHead;//先移动pNode1 次数为环中节点数目
    for(int i=0;i<nodeInLoop;i++)pNode1=pNode1->m_pNext;
    ListNode* pNode2=pHead;
    while(pNode!=pNode2){//再同时移动
        pNode1=pNode1->m_nNext;
        pNode2=pNode2->m_nNext;
    }
    return pNode1;
}
//page 142 反转链表
//注意:1.只有一个节点 2.反转断裂 3.头节点不是尾节点
struct ListNode{
    int m_nKey;
    ListNode* m_pNext;
};
ListNode* ReverseList(ListNode* pHead){//似乎有点问题!! !
    ListNode* pReversedHead=nullptr;
    ListNode* pNode=pHead;
    ListNode* pPrev=nullptr;
    while(pNode!=nullptr){
        ListNode* pNext=pNode->m_pNext;
        if(pNext==nullptr)pReversedHead=pNode;
        pNode->m_pNext=pPrev;
        pPrev=pNext;
        pNode=pNext;
    }
    return pReversedHead;
}
//page 147 双链合并(升序)
ListNode* Merge(ListNode* pHead1,ListNode* pHead2){
    if(pHead1==nullptr)return pHead2;
    else if(pHead2==nullptr)return pHead1;//若俩皆空 则反nullptr 同理
    ListNode* pMergedHead=nullptr;
    if(pHead->m_nValue<pHead2->m_nValue){
        pMergedHead=pHead1;
        pMergedHead->m_pNext=Merge(pHead2,pHead1->m_pNext);
    }else{
        pMergedHead=pHead2;
        pMergedHead->m_pNext=Merge(pHead1,pHead2->m_pNext);
    }
    return pMergedHead;
}
//page 150 树的子结构(判断B是不是A的子结构)
struct BinaryTreeNode{
    double m_dbValue;
    BinaryTreeNode* m_pLeft;
    BinaryTreeNode* m_pRight;
};
bool HasSubtree(BinaryTreeNode* pRoot1,BinaryTreeNode* pRoot2){
    bool result=false;
    if(pRoot1!=nullptr && pRoot2!=nullptr){
        if(Equal(pRoot1->m_dbValue,pRoot2->m_dbValue))result=DoseTree1HaveTree2(p,Root1,pRoot2);
        if(!result)result=HasSubtree(pRoot1->m_pLeft,pRoot2);
        if(!result)result=HasSubtree(pRoot1->m_pRight,pRoot2);
    }
}
bool DoseTree1HaveTree2(BinaryTreeNode* pRoot1,BinaryTreeNode* pRoot2){
    if(pRoot2==nullptr)return true;
    if(pRoot1==nullptr)return false;
    if(!Equal(pRoot1->m_dbValue,pRoot2->m_dbValue))return false;
    return  DoseTree1HaveTree2(pRoot1->m_pLeft,pRoot2->m_pLeft)&&
            DoseTree1HaveTree2(pRoot1->m_pRight,pRoot2->m_pRight);
}
bool Equal(double num1,double num2){//因为是double 数据存在误差，因此需要进行计算
    // if((num1-num2>-0.0000001) && (num1-num2<0.0000001))return true;
    if(abs(num1-num2)<0.0000001)return true;//个人优化
    else return false;
}
//page 158 二叉树的镜像
struct BinaryTreeNode{
    int m_nValue;
    BinaryTreeNode* m_pLeft;
    BinaryTreeNode* m_pRight;
};
void MirrorRecursively(BinaryTreeNode* pNode){
    if(pNode==nullptr)return;
    if(pNode->m_pLeft==nullptr && pNode->m_pRight==nullptr)return;
    BinaryTreeNode* pTemp=pNode->m_pLeft;//互换三式
    pNode->m_pLeft=pNode->m_pRight;
    pNode->m_pRight=pTemp;
    if(pNode->m_pLeft)MirrorRecursively(pNode->m_pLeft);
    if(pNode->m_pRight)MirrorRecursively(pNode->m_pRight);
}
//page 160 对称二叉树
bool isSymmetrical(BrinaryTreeNode* pRoot){
    return isSymmetrical(pRoot,pRoot);
}
bool isSymmetrical(BinaryTreeNode* pRoot1,BinaryTreeNode* pRoot2){
    if(pRoot1==nullptr && pRoot2==nullptr)return true;
    if(pRoot1==nullptr || pRoot2==nullptr)return false;
    if(pRoot1->m_nValue!=pRoot2->m_nValue)return false;
    return isSymmetrical(pRoot1->m_pLeft,pRoot2->m_pRight)
        && isSymmetrical(pRoot1->m_pRight,pRoot2->m_pLeft);
}
//page 162 顺时针打印矩阵
void PrintMatrixClockwisely(int** numbers,int columns,int rows){
    if(numbers==nullptr || columns<=0 || rows<=0)return;
    while(columns>start*2 && rows>start*2){
        PrintMatrixInCircle(numbers,columns,rows,start);
        start++;
    }
}
void PrintMatrixInCirele(int** numbers,int columns,int rows,int start){
    int endX=columns-1-start;
    int endY=rows-1-start;
    for(int i=start;i<=endX;i++){
        int number=numbers[start][i];printNumber(number);
    }
    if(start<endY){
        for(int i=start+1;i<=endY;i++){
            int number=numbers[i][endX];printNumber(number);
        }
    if(start<endX && start<endY)
        for(int i=endX-1;i>=start;i--){
            int number=numbers[endY][i];printNumber(number);
        }
    if(start<endX && start<endY-1)
        for(int i=endY-1;i>=start+1;i--){
            int number=numbers[i][start];printNumber(number);
        }
}
//page 167 包含min函数的栈 这个看不懂
template <typename T> void StackWithMin<T>::push(const T& value){
    m_data.push(value);
    if(m_min.size()==0 || value<m_min.top())m_min.push(value);
    else m_min.push(m_min.top());
}
template <typename T> void StackWithMin<T>::pop(){
    assert(m_data.size()>0 && m_min.size()>0);
    m_data.pop();
    m_min.pop();
}
template <typename T> const T& StackWithMin<T>::min() const{
    seert(m_data.size()>0 && m_min.size()>0);
    return m_min.top();
}
//page 169 栈的压入 弹出序列
bool IsPopOrder(const int* pPush,const int* pPop,int nLength){
    bool bPossible=flse;
    if(pPush!=nullptr && pPop!=nullptr && nLength<0){
        const int* pNextPush=pPush;
        const int* pNextPop=pPop;
        std::stack<int> stackData;
        while(pNextPop-pPop<nLength){
            while(stackData.empty() || stackData.top()!=*pNextPop){
                if(pNextPush-pPush==nLength)break;
                stackData.push(*pNextPush);
                pNextPush++;
            }
            if(stackData.top()!=*pNextPop)break;
            stackData.pop();
            pNextPop++;
        }
        if(stackData.empty() && pNextPop-pPop==nLength)bPossible=true;
    }
    return bPossible;
}
//page 从上到下打印二叉树
struct BinaryTreeNode{
    int m_nValue;
    BinaryTreeNode* m_pLeft;
    BinaryTreeNode* m_pRight;
};
void PrintFromTopToBottom(BinaryTreeNode* pTreeRoot){
    if(!pTreeRoot)return;
    std::dequeue<BinaryTreeNode *>dequeueTreeNode;
    dequeueTreeNode.push_back(pTreeRoot);
    while(dequeueTreeNode.size()){
        BinaryTreeNode* pNode=dequeTreeNode.front();
        dequeueTreeNode.pop_front();
        print("%d",pNode->m_nValue);
        if(pNode->m_pLeft)dequeueTreeNode.push_back(pNode->m_pLeft);
        if(pNode->m_pRight)dequeueTreeNode.push_back(pNode->m_pRight);
    }
}
//page 174 分行从上到下打印二叉树
void Print(BinaryTreeNode* pRoot){
    if(pRoot==nullptr)return;
    std::queue<BinaryTreeNode*> nodes;
    nodes.push(pRoot);
    int nextLevel=0;
    int toBePrinted=1;
    while(!nodes.empty()){
        BinaryTreeNode* pNode=nodes.front();
        printf("%d",pNode->m_nValue);
        if(pNode->m_pLeft!=nullptr){
            nodes.push(pNode->m_pLeft);
            nextLevel++;
        }
        if(pNode->m_pRight!=nullptr){
            nodes.push(pNode->m_pRight);
            nextLevel++;
        }
        nodes.pop();
        toBePrinted--;
        if(toBePrinted==0){
            printf("\n");
            toBePrinted=nextLevel;
            nextLevel=0;
        }
    }
}
//page 178 之字形打印二叉树 
void Print(BinaryTreeNode* pRoot){
    if(pRoot==nullptr)return;
    std::stacl<BinaryTreeNode*> level[2];
    int current=0;
    int next=1;
    levels[current].push(pRoot);
    while(!level[0].empty() || !levels[1].enpty()){
        BinaryTreeNode*  pNode=levels[current].top();
        levels[current].pop();
        printf("%d",pNode->m_nValue);
        if(current==0){//奇偶层分正反序
            if(pNode->m_pLeft!=nullptr)levels[next].push(pNode->m_pLeft);
            if(pNode->m_pRight!=nullptr)levels[next].push(pNode->m_pRight);
        }else{
            if(pNode->m_pRight!=nullptr)levels[next].push(pNode->m_pRight);
            if(pNode->m_pLeft!=nullptr)levels[next].push(pNode->pLeft);
        }
        if(levels[current].empty()){
            printf("\n");
            current=1-current;
            next=1-next;
        }
    }
}
//page 181 二叉搜索树的后序遍历序列
bool VerifySquenceOfBST(int sequence[],int length){
    if(sequence==nullptr||length<=0)return false;
    int root=sequence[Length-1];
    for(int i=0;;i<length-1;i++)
        if(sequence[i]>root)
            break;
    for(int j=i;j<length-1;j++)
        if(sequence[j]<root)
            return false;
    bool left=true;
    if(i>0)left=VerifySquenceOfBST(sequence,i);
    bool right=true;
    if(i<length-1)right=VerifySquenceOfBST(sequence+i,length-i-1);
    return (left && right);
}
//page 184 二叉树中和为某一种的路径
struct BinaryTreeNode{
    int m_nValue;
    BinaryTreeNode* m_pLeft;
    BinaryTreeNode* m_pRight;
};
void FindPath(BinaryTreeNode* pRoot,int expectedSum){
    if(pRoot==nullptr)return;
    std::vector<int> path;
    int currentSum=0;
    FindPath(pRoot,expectedSum,path,currentSum);
}
void FindPath(BinaryTreeNode* pRoot,int expectedSum,std::vector<int> &path,init currentSum){
    currentSum+=pRoot->m_nValue;
    path.push_back(pRoot->m_nValue);
    //如果是叶节点 并且路径上节点值和等于输入的值
    //则打印输出这条路径
    bool isLeaf=pRoot->m_pLeft==nullptr && pRoot->m_pRight==nullptr;
    if(currentSum==expectedSum && isLeaf){
        printf("A path is found");
        std::vector<int>::iterator iter=path.begin();
        for(;iter!=path.end();iter++)
            printf("%d\t",*iter);
        printf("\n");
    }
    //如果不是叶节点 则遍历它的子节点
    if(pRoot->m_pLeft!=nullptr)FindPath(pRoot->m_pLeft,expectedSum,path,currentSum);
    if(pRoot->m_pRight!=nullptr)FindPath(pRoot->m_pRight,expectedSum,path,currentSum);
    //在返回父节点之前 在路径上删除当前节点
    path.pop_back();
}
//page 188 复杂链表的复制
struct ComplexListNode{
    int m_nValue;
    ComplexListNode* m_pNext;
    ComplexListNode* m_pSibling;
};
void CloneNodes(ComplexListNode* pHead){
    ComplexListNode* pNode=pHead;
    while(pNode!=nullptr){
        ComplexListNode* pCloned=new ComplexListNode();
        pCloned->m_nValue=pNode->m_nValue;
        pCloned->m_pNext=pNode->m_pNext;
        pCloned->m_pSibling=nullptr;
        pNode->m_pNext=pCloned;
        pNode=pCloned->m_pNext;
    }
}
void ConnectSiblingNodes(ComplexListNode* pHead){
    ComplexListNode* pNode=pHead;
    while(pNode!=nullptr){
        ComplexListNode* pCloned=pNode->m_pNext;
        if(pNode->m_pSibling!=nullptr)
            pCloned->m_pSibling=pNode->m_pSibling->m_pNext;
        pNode=pCloned->m_pNext;
    }
}
ComplexListNode* ReconnectNodes(ComplexListNode* pHead){
    ComplexListNode* pNode=pHead;
    ComplexListNode* pClonedHead=nullptr;
    ComplexListNode* pClonedNode=nullptr;
    if(pNode!=nullptr){
        pClonedHead=pClonedNode=pNode->m_pNext;
        pNode->m_pNext=pClonedNode->m_pNext;
        pNode=pNode->m_pNext;
    }
    while(pNode!=nullptr){
        pClonedNode->m_pNext=pNode->m_pNext;
        pClonedNode=pClonedNode->m_pNext;
        pNode->m_pNext=pClonedNode->m_pNext;
        pNode=pNode->m_pNext;
    }
    return pClonedHead;
}
ComplexListNode* Clone(ComplexListNode* pHead){
    CloneNodes(pHead);
    ConnectSiblingNodes(pHead);
    return ReconnectNodes(pHead);
}
//page 193 二叉搜索树 -> 双向链表
struct BinaryTreeNode{
    int m_nValue;
    BinaryTreeNode* m_pLeft;
    BinaryTreeNode* m_pRight;
};
BinaryTreeNode* Convert(BinaryTreeNode* pRootOfTree){
    BinaryTreeNode* pLastNodeInList=nullptr;
    ConvertNode(pRootOfTree,&pLastNodeInList);
    //pLastNodeInList指向双向链表的尾节点
    //返回头节点
    BinaryTreeNode* pHeadOfList=pLastNodeInList;
    while(pHeadOfList!=nullptr && pHeadOfList->m_pLeft!=nullptr)        
        pHeadOfList=pHeadOfList->m_pLeft;
    return pHeadOfList;
}
void ConvertNode(BinaryTreeNode* pNode,BinaryTreeNode** pLastNodeInList){
    if(pNode==nullptr)return ;
    BinaryTreeNode* pCurrent=pNode;
    if(pCurrent->m_pLeft!=nullptr)ConvertNode(pCurrent->m_pLeft,pLastNodeInList);
    pCurrent->m_pLeft=*pLastNodeInList;
    if(*pLastNodeInList!=nullptr)
        (*pLastNodeInList)->m_pRight=pCurrent;
    *pLastNodeInList=pCurrent;
    if(pCurrent->m_pRight!=nullptr)ConvertNode(pCurrent->m_pRight,pLastNodeInList);
}
//page 195 序列化 反序列化二叉树
//缺点:1.不能有数值重复 2.所有数据读出后才能反序列化
void Serialize(BinaryTreeNode* pRoot,ostream& stream){
    if(pRoot==nullptr){
        stream<<"$,";
        return;
    }
    stream<<pRoot->m_nValue<<",";
    Serialize(pRoot->m_pLeft,stream);
    Serialize(pRoot->m_pRight,stream);
}
//反序列化
void Deserialize(BinaryTreeNode** pRoot,istream& stream){
    int number;
    if(ReadStream(stream,&number)){
        *pRoot=new BinaryTreeNode();
        (*pRoot)->m_nValue=number;
        (*pRoot)->m_pLeft=nullptr;
        (*pRoot)->m_pRight=nullptr;
        Deserialize(&((*pRoot)->m_pLeft),stream);
        Deserialize(&((*pRoot)->m_pRight),stream);
    }
}
//page 198 字符串的排列 (全排列)
void Permutation(char* pStr){
    if(pStr==nullptr)return;
    Premutation(pStr,pStr);
}
void Permutation(char* pStr,char* pBegin){
    if(*pBegin=='\0')printf("%s\n",pStr);
    else{
        for(char* pCh=pBegin;*pCh!='\0';pCh++){
            char temp=*pCh;
            *pCh=*pBegin;
            *pBegin=temp;
            Premutation(pStr,pBegin+1);
            temp=*pCh;
            *pCh=*pBegin;
            *pBegin=temp;
        }
    }
}
//c+:引用/指针传递复杂类型参数 (避免采用传值 形参到实参会产生一次复制 行为多余)
//c#:多次字符串拼接 StringBuilder的Append来完成 (避免多次用String "+"运算来拼接)
//page 206 数组中出现次数超过一半的数字
//大概:排序 取中
int MoreThanHalfNum(int* numbers,int length){
    if(CheckInvalidArray(numbers,length))return 0;
    int middle=length>>1;
    int start=0;
    int end=length-1;
    int index=Partition(numbers,length,start,end);
    while(index!=middle){
        if(index>middle){
            end=index-1;
            index=Partition(numbers,length,start,end);
        }else{
            start=index+1;
            index=Partition(numbers,length,start,end);
        }
    }
    int result=numbers[middle];
    if(!CheckMoreThanHalf(numbers,length,result))result=0;
    return result;
}
//考虑无效输入
bool g_bInputInvalid=false;
bool CheckInvalidArray(int* numbers,int length){
    g_bInputInvalid=false;
    if(numbers==nullptr || length<=0)g_bInputInvalid=true;
    return g_bInputInvalid;
}
bool CheckMoreThanHalf(int* numbers,int length,int number){
    int times=0;
    for(int i=0;i<length;i++)
        if(numbers[i]==number)
            times++;
    bool isMoreThanHalf=true;
    if(time*2<=length){
        g_bInputInvalid=true;
        isMoreThanHalf=false;
    }
    return isMoreThanHalf;
}
//解法2  根据数组特点找出 时间复杂度O(n)
//大概:符合++ 不符合-- 若是正数说明是该值
bool CheckInvalidArray(int* numbers,int length){
    g_bInputInvalid=false;
    if(numbers==nullptr || length<=0)g_bInputInvalid=true;
    return g_bInputInvalid;
}
int MoreThanHalfNum(int* numbers,int length){
    if(CheckInvalidArray(numbers,length))return 0;
    int result=numbers[0];
    int times=1;
    for(int i=1;i<length;i++)
        if(times==0){
            result=numbers[i];
            times=1;
        }else if(numbers[i]==result)times++;
        else time--;
    if(!CheckMoreThanHalf(numbers,length,result))result=0;
    return result;
}
//page 210 最小的k个数
//限制:修改输入的数组
void GetLeastNumbers(int* input,int n,int* output,int k){       
    if(input==nullptr || output==nullptr || k>n || n<=0 || k<=0)return ;
    int start=0;
    int end=n-1;
    int index=Partition(input,n,start,end);
    whlie(index!=k-1)
        if(index>k-1){
            end=index-1;
            index=Partition(input,n,start,end);//分组函数
        }else{
            start=index+1;
            index=Partition(input,n,start,end);
        }
    for(int i=0;i<k;i++)
        output[i]=input[i];
}
//时间复杂度O(nlogk) 堆/红黑树解法 适用大量数据
//大概:建立k长容器 将其中最值与序列值比对 替换成最值
//慢一点 但是不会修改数据
typedef multiset<int,greater<int> > intSet;
typedef multiset<int,greater<int> >::iterator setIterator;
void GetLeastNumbers(const vector<int>& data,intSet& leastNumbers,int k){
    leastNumber.clear();
    if(k<1 || data.size()<k)return ;//个人认为等于k应该也要退出
    vector<int>::const_iterator iter=data.begin();
    for(;iter!=data.end();iter++){
        if((leastNumerbs.size())<k)leastNumbers.insert(*iter);
        else {
            setIterator iterGreatest=leastNumbers.begin();
            if(*iter<*(leastNumbers.begin())){
                leastNumbers.erase(iterGreatest);
                leastNumbers.insert(*iter);
            }
        }
    }
}
//个人思考:可以使用快排的思路 以一数为基准寻找数组左右大小互换后 左列必小于基准 加上基准 一共n+1个数与k比较
//若n+1>k 则只需在n+1中再以二分寻找k个数
//若n+1<k 则先取n+1序列 随后在后列中寻找(k-n-1)序列
//若n+1=k 则直接返回n+1序列
//page 216 数据流中位数
//二叉搜索树   插入平均O(logn) 最差O(n)   得到中位数 平均O(logn) 最差O(n)
//AVL树       插入 O(logn)               得到中位数 O(1)
//最大堆最小堆 插入 O(logn)               得到中位数 O(1)
//基于stl中函数push_heap pop_heap vector实现堆
template<typename T>class DynamicArray{
    public:
        void Insert(T num){
            if(((min.size()+max.size())&1)==0){
                if(max.size()>0 && num<max[0]){
                    max.push_back(num);
                    push_heap(max.begin(),max.end(),less<T>());//没看懂
                    num=max[0];
                    pop_heap(max.begin(),max.end(),less<T>());
                    max.pop_back();
                }
                min.push_back(num);
                push_heap(min.begin(),min.end(),greater<T>());
            }else{
                if(min.size()>0 && min[0]<num){
                    min.push_back(num);
                    push_heap(min.begin(),min.end(),greater<T>());
                    num=min[0];
                    pop_heap(min.begin(),min.end(),greater<T>());
                    min.pop_back();
                }
                max.push_back(num);
                push_heap(max.begin(),max.end(),less<T>());
            }
        }
        T GetMedian(){
            int size=min.size()+max.size();
            if(size==0)throw exception("No numbers are available");
            T median=0;
            if((size & 1)==1)median=min[0];
            else median=(min[0]+max[0])/2;
            return median;
        }
    private:
        vector<T> min;
        vector<T> max;
};
//page 219 连续子数组的最大和
//解法1 数论思想
//大概:小于等于0截断 大于零累计 并且存储最大值
bool g_InvalidInput=false;
int FindGreatestSumOfSubArray(int* pData,int nLength){
    if((pData==nullptr) || (nLength<=0)){
        g_InvalidInput=true;
        return 0;
    }
    g_InvalidInput=false;
    int nCurSum=0;
    int nGreatestSum=0x80000000；
    for(int i=0;i<nLength;i++){
        if(nCurSum<=0)nCurSum=pData[i];
        else nCurSum+=pData[i];
        if(nCurSum>nGreatestSum)nGreatestSum=nCurSum;
    }
    return nGreatestSum;
}
//解法2 动态规划
//f(i) =    pData[i]        ,i=0  || f(i-1)<=0
//          f(i-1)+pData[i] ,i!=0 && f(i-1)>0
//page 221 1~n整数中1出现的次数
//解法1 爆搜模拟 低效
int NumberOf1Between1AndN(unsigned int n){
    int number=0;
    for(unsigned int i=1;i<=n;i++)
        number+=NumberOf1(i);
    return number;
}
int NumberOf1(unsigned int n){
    int number=0;
    while(n){
        if(n%10==1)number++;
        n/=10;
    }
    return number;
}
//解法2 数论规律 1~1345 / 1346~21345 -> 1346~11345 / 11346~21345
//假设以求21345的1出现次数为例
int NumberOf1Between1AndN(int n){
    if(n<=0)return 0;
    char strN[50];
    sprintf(strN,"%d",n);
    return NumberOf1(strN);
}
int NumberOf1(const char* strN){
    if(!strN || *strN<'0' || *strN>'9' || *strN=='\0')return 0;
    int first=*strN-'0';
    unsigned int length=static_cast<unsigned int>(strlen(strN));
    if(length==1 && first==0)return 0;
    if(length==1 && fitst>0)return 1;
    //假设 strN是 21345
    //numFirstDigit是数字10000~19999的第一位中的数目
    int numFirstDigit=0;
    if(first>1)numFirstDigit=PowerBase10(length-1);
    else if(first==1)numFirstDigit=atoi(strN+1)+1;
    //numOtherDigits是1346~21345除第一位之外的数组中的数目
    int numOtherDigits=first*(length-1)*PowerBase10(length-2);
    //numRecursive是1~1345中的数目
    int numRecursive=NumberOf1(strN+1);
    return numFirstDigit+numOtherDigits+numRecursive;
}
int PowerBase10(unsigned int n){
    int result=1;
    for(unsigned int i=0;i<n;i++)
        result*=10;
    return result;
}
//page 225 数字序列中某一位的数字 0123456789101112...
int digitAtIndex(int index){
    if(index<0)return -1;
    int digits=1;
    while(true){
        int numbers=countOfIntegers(digits);
        if(index<numbers*digits)
            return digitAtIndex(index,digits);
        index-=digits*numbers;
        digits++;
    }
    return -1;
}
int countOfIntegers(int digits){
    if(digits==1)return 10;
    int count=(int)std::pow(10,digits-1);
    return 9*count;
}
int digitAtIndex(int index,int digits){
    int number=beginNumber(digits)+index/digits;
    int indexFromRight=digits-index%digits;
    for(int i=1;i<indexFromRight;i++)
        number/=10;
    return number%10;
}
int beginNumber(int digits){
    if(digits==1)return 0;
    return (int)std::pow(10,digits-1);
}
//page 228 把数组排成最小数(数字数组进行组合)
//大概:通过strcat的特性进行比对
//自反 对称 传递
const int g_MaxNumberLength=10;
char* g_StrCombine1=new char[g_MaxNumberLength*2+1];
char* g_StrCombine2=new char[g_MaxNumberLength*2+1];
void PrintMinNumber(int* numbers,int length){
    if(numbers==nullptr || length<=0)return ;
    char** strNumbers=(char**)(new int[length]);
    for(int i=0;i<length;i++){
        strNumbers[i]=new char[g_MaxNumberLength+1];
        sprintf(strNumber[i],"%d",numbers[i]);
    }
    qsort(strNumbers,length,sizeof(char*),compare);
    for(int i=0;i<length;i++)
        printf("%s",strNumbers[i]);
    printf("\n");
    for(int i=0;i<length;i++)
        delete[] strNumbers[i];
}
int compare(const void* strNumber1,const void* strNumber2){
    strcpy(g_StrCombine1,*(const char**)strNumber1);
    strcat(g_StrCombine1,*(const char**)strNumber2);
    strcpy(g_StrCombine2,*(const char**)strNumber2);
    strcat(g_StrCombine2,*(const char**)strNumber1);
    return strcmp(g_StrCombine1,g_StrCombine2);
}
//page 232 把数字翻译成字符串 1 -> "b"  11 -> "1"
//大概:自上而下 从右到左翻译并计算次数
//注: i和i+1位在10~25内 可以翻译成一个字符串
//12258为例 -> 1&2258 / 12&258 -> 12&25&8 / 12&2&5&8
//               ↘ 1&2258 -> 1&22&5&8 / 1&2&258
//                                         ↘ 1&2&2&5&8 / 1&2&25&8
int GetTranslationCount(int number){
    if(number<0)return 0;
    string numberInString=to_string(number);
    return GerTranslationCount(numberInString);
}
int GetTranslationCount(const string& number){
    int length=number.length();
    int* counts=new int[length];
    int count=0;
    for(int i=length-1;i>=0;i--){
        count=0;
        if(i<length-1)count=counts[i+1];
        else count=1;
        if(i<length-1){
            // int digit1=number[i]-'0';
            // int digit2=number[i+1]-'0';
            // int converted=digit1*10+digit2;
            int converted=(number[i]-'0')*10+(number[i+1]-'0');
            if(converted>=10 && converted<=25){
                if(i<length-2)count+=counts[i+2];
                else count+=1;
            }
        }
        counts[i]=count;
    }
    count=counts[0];
    delete[] counts;
    return count;
}
//page 234 礼物的最大值(矩阵内 左上角开始仅右/下移达右下角取最大值)
int getMaxValue_solution1(const int* values,int rows,int  cols){
    if(values==nullptr || rows<=0 || cols<=0)return 0;
    int** maxValues=new int*[rows];
    for(int i=0;i<rows;i++)
        maxValues[i]=new int[cols];
    for(int i=0;i<rows;i++){
        for(int j=0;j<cols;j++){
            int left=0;
            int up=0;
            if(i>0)up=maxValues[i-1][j];
            if(j>0)left=maxValues[i][j-1];
            maxValues[i][j]=std::max(left,up)+values[i*cols+j];
        }
    } 
    int maxValue=maxValues[rows-1][cols-1];
    for(int i=0;i<rows;i++)
        delete[] maxValues[i];
    delete[] maxValues;
    return maxValue;
}
//优化算法
int getMaxValue_solution2(const int* values,int rows,int  cols){
    if(values==nullptr || rows<=0 || cols<=0)return 0;
    int* maxValues=new int[rows];//双指针变成单指针
    for(int i=0;i<rows;i++){
        for(int j=0;j<cols;j++){
            int left=0;
            int up=0;
            if(i>0)up=maxValues[i];
            if(j>0)left=maxValues[j-1];
            maxValues[j]=std::max(left,up)+values[i*cols+j];
        }
    } 
    int maxValue=maxValues[cols-1];
    delete[] maxValues;
    return maxValue;
}
//page 237 最长不重复字符的子字符串
//解法 动态规划
int longestSubstringWithoutDuplication(const std::string& str){//不知道为什么要用&
    int curLength=0;
    int maxLength=0;
    int* position=new int[26];
    for(int i=0;i<26;i++)//标记 -1则未出现过
        position[i]=-1;
    for(int i=0;i<str.length();i++){
        int prevIndex=position[str[i]-'a'];
        if(prevIndex<0 || i-prevIndex>curLength)curLength++;//若字母未出现过 或 出现重复字符
        else {//若出现过
            if(curLength>maxLength)maxLength=curLength;//刷新最大
            curLength=i-prevIndex;
        }
        position[str[i]-'a']=i;//记录位置
    }
    if(curLength>maxLnegth)maxLength=curLength;//刷新最大
    delete[] position;
    return maxLength;
}
//page 240 丑数 (只包含因子2、3、5)
//解法1 低效爆搜
bool IsUgly(int number){
    while(number%2==0)number/=2;
    while(number%3==0)number/=3;
    while(number%5==0)number/=5;
    return (number==1)?true:false;
}
int GetUglyNumber(int index){
    if(index<=0)return 0;
    int number=0;
    int uglyFound=0;
    while(uglyFound<index){
        number++;
        if(IsUgly(number))uglyFound++;
    }
    return number;
}
//解法2 对已经存在的数列分别进行乘2、3、5后排序列
//缺陷:占用一定空间
int GetUglyNumber_Solution2(int index){
    if(index<=0)return 0;
    int* pUglyNumbers=new int[index];
    pUglyNumbers[0]=1;
    int nextUglyIndex=1;
    int* pMultiply2=pUglyNumbers;
    int* pMultiply3=pUglyNumbers;
    int* pMultiply5=pUglyNumbers;
    while(nextUglyIndex<index){
        int min=Min(*pMiltiply2*2,*pMiltiply3*3,*pMiltiply5*5);
            //std::min(min(*pMiltiply2*2,*pMiltiply3*3),*pMiltiply5*5)
        pUglyNumbers[nextUglyIndex]=min;
        while(*pMultiply2*2<=pUglyNumbers[nextUglyIndex])pMultiply2++;//向后移 使得大于最小基准
        while(*pMultiply3*3<=pUglyNumbers[nextUglyIndex])pMultiply3++;
        while(*pMultiply5*5<=pUglyNumbers[nextUglyIndex])pMultiply5++;
        nextUglyIndex++;
    }
    int ugly=pUglyNumbers[nextUglyIndex-1];
    delete[] pUglyNumbers;
    return ugly;
}
int Min(int number1,int number2,int number3){
    int min=(number1<number2)?number1:number2;
    min=(min<number3)?min:number3;
    return min;
}
//pape 244 第一个只出现一次的字符
//扫一遍记录次数 第一个出现次数为1则是所求字符
//哈希表思路
char FitstNotRepeatingChar(char* pString){
    if(pString==nullptr)return '\0';
    const int tableSize=256;
    unsigned int hashTable[tableSize];
    for(unsigned int i=0;i<tableSize;i++)hashTable[i]=0;
    char* pHashKey=pString;
    while(*(pHashKey)!='\0')hashTable[*(pHashKey++)]++;
    pHashKey=pString;
    while(*pHashKey!='\0'){
        if(hashTable[*pHashKey]==1)return *pHashKey;
        pHashKey++;
    }
    return '\0';
}
//page 247 
class CharStatistics{
    public:
        CharStatistics():index(0){
            for(int i=0;i<256;i++)
                occurrence[i]=-1;
        }
        void Insert(char ch){
            if(occurrence[ch]==-1)occurrence[ch]=index;
            else if(occurrence[ch]>=0)occurrence[ch]=-2;
            index++;
        }
        char FirstAppearingOnce(){
            char ch='\0'
            int minIndex=numeric_limits<int>::max();
            for(int i=0;i<256;i++){
                if(occurrence[i]>=0 && occurrence[i]<minIndex){
                    ch=(char)i;
                    minIndex=occurrence[i];
                }
            }
            return ch;
        }
    private:
        int occurrence[256];
        int index;
};
//page 251 数组中的逆序对
int InversePairs(int* data,int length){
    if(data==nullptr || length<0)return 0;
    int* copt=new int[length];
    for(int i=0;i<length;i++)copy[i]=data[i];
    int count=InversePairsCore(data,copy,0,length-1);
    delete[] copy;
    return 0;
}
int InversePairsCore(int* data,int* copy,int start,int end){
    if(start==end){
        copy[start]=data[start];
        return 0;
    }
    int length=(end-start)/2;
    int left=InversePairsCore(copy,data,start,start+length);
    int right=InversePairsCore(copy,data,start+length+1,end);
    int i=start+length;
    int j=end;
    int indexCopy=end;
    int count=0;
    while(i>=start && j>=start+length+1){
        if(data[i]>data[j]){
            copy[indexCopy--]=data[i--];
            count+=j-start-length;
        }else{
            copy[indexCopy--]=data[j--];
        }
    }
    for(;i>=start;i--)
        copy[indexCopy--]=data[i];
    for(;j>=start+length+1;j--)
        copy[indexCopy--]=data[j];
    return left+right+count;
}
//page 253 两个链表的第一个公共节点
//大概:将两个单链表放入栈中从链表末尾进行比对
struct ListNode{
    int m_nKey;
    ListNode* m_pNext;
};
ListNode* FindFirstCommonNode(ListNode* pHead1,ListNode* pHead2){
    unsigned int nLength1=GetListLength(pHead1);
    unsigned int nLength2=GEtListLength(pHead2);
    ListNode* pListHeadLong=pHead1;
    ListNode* pListHeadShort=pHead2;
    if(pLength2>nLength1){
        pListHeadLong=pHead2;
        pListHeadShort=pHead1;
        nLengthDif=nLength2-nLength1;
    }
    for(int i=0;i<nLenthDif;i++)
        pListHeadLong=pListHeadLong->m_pNext;
    while(  (pListHeadLong!=nullptr) && 
            (pListHeadShort!=nullptr) && 
            (pListHeadLong!=pListHeadShort)){
        pListHeadLong=pListHeadLong->m_pNext;
        pListHeadShotr=pListHeadShort->m_pNext;
    }
    ListNode* pFirstCommonNode=pListHeadLong;
    return pFirstCommonNode;
}
unsigned int GetListLength(ListNode* pHead){
    unsigned int nLength=0;
    ListNode* pNode=pHead;
    while(pNode!=nullptr){
        nLength++;
        pNode=pNode->m_pNext;
    }
    return nLength;
}
//另一个思路 计算两个链表的长度 随后将两个链表移到同一个倒数长度的位置 之后协同移步依次进行比对可以得出
//注:嵌入式开发更需要注重内存上的应用
//page 263 在排序数组中查找数字
int GetFirstK(int* data,int length,int k,int start,int end){
    if(start>end)return -1;
    int minddleIndex=(start+end)/2;
    int middleData=data[middleIndex];
    if(middleData==k){
        if((middleIndex>0 && data[middleIndex-1]!=k) || middleIndex==0)
            return middleIndex;
        else end=middleIndex-1;
    }else if(middleData>k)end=middledex-1;
    else start=middleIndex+1;
    return GetFirstK(data,length,k,start,end);
}
int GetLastK(int* data,int length,int k,int start,int end){
    if(start>end)return -1;
    int middleIndex=(start+end)/2;
    int middleData=data[middleIndex];
    if(middleData==k){
        if((middleIndex<length-1 && data[middleIndex+1]!=k) || middleIndex==length-1)
            return middleIndex;
        else start=middleIndex+1;
    }else if(middleData<k)start=middleIndex+1;
    else end=middleIndex-1;
    return GetLastK(data,length,k,start,end);
}
int GetNumberOfK(int* data,int length,int k){
    int number=0;
    if(data!=nullptr && length>0){
        int first=GetFirstK(data,length,k,0,length-1);
        int last=GetLastK(data,length,k,0,length-1);
        if(first>-1 && last>-1)
            number=last-first+1;
    }
    return number;
}
//page 266 0~n-1中缺失的数字
int GetMissingNumber(const int* numbers,int length){
    if(numbers==nullptr || length<=0)return -1;
    int left=0;
    int right=length-1;
    while(left<=right){
        int middle=(right+left)>>1;
        if(numbers[middle]!=middle){
            if(midde==0 || numbers[middle-1]==middle-1)
                return middle;
            right=middle-1;
        }else left=middle+1;
    }
    if(left==length)return length;
    return -1;
}
//page 268 数组中数值和下标相等的元素 经典二分法
int GetNumberSameAsIndex(const int* numbers,int length){
    if(numbers==nullptr || length<=0)return -1;
    int left=0;
    int right=length-1;
    while(left<=right){
        int middle=left+((right-left)>>1);
        if(numbers[middle]==middle)return middle;
        if(numbers[middle]>middle)right=middle-1;
        else left=middle+1;
    }
    return -1;
}
//page 270 二叉搜索树的第k个大节点
//中序遍历
BinaryTreeNode* KthNode(BinaryTreeNode* pRoot,unsigned int k){
    if(pRoot==nullptr || k=0)return nullptr;
    return KthNodeCore(pRoot,k);
}
BinaryTreeNode* KthNodeCore(BinaryTreeNode* pRoot,unsigned int& k){
    BinaryTreeNode* target=nullptr;
    if(pRoot->m_pLeft!=nullptr)target=KthNodeCore(pRoot->m_pLeft,k);
    if(target==nullptr){
        if(k==1)target=pRoot;
        k--;
    }
    if(target==nullptr && pRoot->m_pRight!=nullptr)
        target=KthNodeCore(pRoot->m_pRight,k);
    return target;
}
//page 271 二叉树深度
struct BinaryTreeNode{
    int m_nValue;
    BinaryTreeNode* m_pLeft;
    BinaryTreeNode* m_pRight;
};
int TreeDepth(BinaryTreeNode* pRoot){
    if(pRoot==nullptr)return 0;
    int nLeft=TreeDepth(pRoot->m_pLeft);
    int nRight=TreeDepth(pRoot->m_pRight);
    return (nLeft>nRight)?(nLeft+1):(nRight+1);
}
//page 273 平衡二叉树
//基础的方式
bool IsBalanced(BinaryTreeNode* pRoot){
    if(pRoot==nullptr)return true;
    int left=TreeDepth(pRoot->m_pLeft);
    int right=TreeDepth(pRoot->m_pRight);
    int diff=left-right;
    if(diff>1 || diff<-1)return false;
    return IsBalanced(pRoot->m_pLeft) && IsBalanced(pRoot->m_pRight);
}
//思路二 分叉遍历法
bool IsBalanced(BinaryTreeNode* pRoot,int* pDepth){
    if(pRoot==nullptr){
        *pDepth=0;
        return true;
    }
    int left,right;
    if(IsBalanced(pRoot->m_pLeft,&left) && IsBalanced(pRoot->m_pRight,&right)){//其中一节点无指向后
        //注意是引用
        // int diff=left-right;
        // if(diff<=1 && diff>=-1){
        //     *pDepth=1+(left>right?left:right);
        //     return true;
        // }
        int diff=left-right;
        if(abs(diff)<=1){
            *pDepth=1+max(left,right);
            return true;
        }
        *pDepth=1+max(left,right);//修改成
    }
    return false;
}
bool IsBalanced(BinaryTreeNode* pRoot){
    int depth=0;
    return IsBalanced(pRoot,&depth);
}
//page 277 数组中出现数字的次数
//数组中只出现一次的两个数字
//大概:对每个数进行异或来筛选 随后对剩下的数对异或的结果进行筛选
void FindNumsAppearOnce(int data[],int length,int* num1,int* num2){
    if(data==nullptr || length<2)return ;
    int resultExclusiveOR=0;
    for(int i=0;i<lenth;i++)
        resultExclusiveOR^=data[i];
    unsigned int indexOf1=FindFirstBitls1(resultExclusiveOR);
    *num1=*num2=0;
    for(int j=0;j<length;j++){
        if(IsBit1(data[j],indexOf1))*num1^=data[j];
        else *num2^=data[j];
    }
}
unsigned int FindFirstBitls1(int num){
    int indexBit=0;
    while(((num&1)==0) && (indexBit<8*sizeof(int))){
        num=num>>1;
        indexBit++;
    }
    return indexBit;
}
bool IsBit1(int num,unsigned int indexBit){
    num=num>>indexBit;
    return (num&1);
}
//数组中唯一只出现一次 其他出现三次
//思路 每一位和都为被三整除 剩下的为出现一次的数
int FindNumberAppearingOnce(int numbers[],int length){
    if(numbers==nullptr || length<=0)
        throw new std::exception("Invalid input.");
    int bitSum[32]={0};
    for(int i=0;i<length;i++){
        int bitMask=1;
        for(int j=31;j>=0;j--){
            int bit=numbers[i]&bitMask;
            if(bit!=0)bitSum[j]+=1;
            bitMask=bitMask<<1;
        }
    }
    int result=0;
    for(int i=0;i<32;i++){
        result=result<<1;
        result+=bitSum[i]%3;
    }
    return result;
}
//page 281 和为s的数字
//左右和大于s 选择s之前的数 小于s则选择1之后的数
bool FindNumbersWithSum(int data[],int length,int sum,int* num1,int* num2){
    bool found=false;
    if(length<1 || num1==nullprt || num2==nullptr)return found;
    int ahead=length-1;
    int behind=0;
    while(ahead>behind){
        long long curSum=data[ahead]+data[[behind];
        if(curSum==sum){
            *num1=data[behind];
            *num2=data[ahead];
            found=true;
            break;
        }else if(curSum>sum)ahead--;
        else behind++;
    }
    return found;
}
//page 283 和为s的连续正数序列
//初始化{1,2}当2小于s时     当总和小于s让n+1计入
//                         当总和大于s让1移出重新判断
void FindContinuousSequence(int sum){
    if(sum<3)return ;
    int small=1;
    int big=2;
    int middle=(1+sum)/2;
    int curSum=small+big;
    while(small<middle){
        if(curSum==sum)PrintContinuousSequence(small,big);
        while(curSum>sum && small<middle){
            curSum-=small;
            small++;
            if(curSum==sum)PrintContinuousSequence(small,big);
        }
        big++;
        curSum+=big;
    }
}
void PrintContinuousSequence(int small,int big){
    for(int i=small;i<=big;i++)
        printf("%d",i);
    printf("\n");
}
//page 285 翻转字符串
void Reverse(char* pBegin,char* pEnd){
    if(pBegin==nullptr || pEnd==nullptr)return;
    while(pBegin<pEnd){
        char temp=*pBegin;
        *pBegin=*pEnd;
        *pEnd=temp;
        pBegin++;
        pEnd--;
    }
}
char* ReverseSentence(char *pData){
    if(pData==nullptr)return nullptr;
    char* pBegin=pData;
    char* pEnd=pData;
    while(*pEnd!='\0')
        pEnd++;
    pEnd--;
    Reverse(pBegin,pEnd);
    pBegin=pEnd=pData;
    while(*pBegin!='\0'){
        if(*pBegin==''){
            pBegin++;
            pEnd++;
        }else if(*pEnd=='' || *pEnd=='\0'){
            Reverse(pBegin,--pEnd);
            pBegin=++pEnd;
        }else pEng++;
    }
    return pData;
}
//page 287 左旋转字符串
char* LeftRotateString(char* pStr,int n){
    if(pStr!=nullptr){
        int nLength=static_cast<int>(strlen(pStr));
        if(nLength>0 && n>0 && n<nLength){
            char* pFirstStart=pStr;
            char* pFirstEnd=pStr+n-1;
            char* pSecondStart=pStr+n;
            char* pSecondEnd=pStr+nLength-1;
            Reverse(pFirstStart,pFirstEndl);
            Reverse(pSecondStart,pSecondEnd);
            Reverse(pFirstStart,pSecondEnd);
        }
    }
    return pStr;
}
//page 291 队列最大值
//滑动窗口
vector<int> maxInWindows(const vector<int>& num,unsigned int size){
    vector<int> maxInWindows;
    if(num.size()>=size && size>=1){
        deque<int> index;
        for(unsigned int i=0;i<size;i++){
            while(!index.empty() && num[i]>=num[index.back()])
                index.pop_back();
            index.push_back(i);
        }
        for(unsigned int i=size;i<num.size();i++){
            maxInWindows.push_back(num[index.front()])
            while(!index.empty() && num[i]>=num[index.back()])
                index.pop_back();
            if(!index.empty() && index.front()<=(int)(i-size))
                index.pop_front();
            index.push_back(i);
        }
        maxInWindows.push_back(num[mdex.front()]);
    }
    return maxInWindows;
}
//队列最大值2
template<typename T> class QueueWithMax{
    public:
    QueueWithMax():currentIndex(0){
    }
    void push_back(T number){
        while(!maximums.empty() && number>=maximums.back().number)
            maximums.pop_back();
        InternalData internalData={number,currentIndex};
        data.push_back(internalData);
        maximums.push_back(internalData);
        currentIndex++;
    }
    void pop_front(){
        if(maximums.empty())
            throw new exception("queue is empty");
        if(maximums.front().index == data.front().index)
            maximums.pop_front();
        data.pop_front();
    }
    private:
    struct InternalData{
        T number;
        int index;
    };
    deque<InternalData> data;
    deque<InternalData> maximums;
    int currentIndex;
};
//page 295 n个骰子的点数
//方法1 递归求
int g_maxValue=6;
void PrintProbability(int number){
    if(number<1)return;
    int maxSum=number*g_maxValue;
    int* pProbabilities=new int[maxSum-number+1];
    for(int i=number;i<=maxSum;i++)
        pProbabilities[i-number]=0;
    Probability(number,pProbabilities);
    int total=pow((double)g_maxValue,number);
    for(int i=number;i<=maxSum;i++){
        double ratio=(double)pProbabilities[i-number]/total;
        printf("%:%e\n",i,ratio);
    }
    delete[] pProbabilities;
}
void Probability(int number,int* pProbabilities){
    for(int i=1;i<=g_maxValue;i++)
        Probability(number,number,i,pProbabilities);
}
void Probability(int original,int current,int sum,int* pProbabilities){
    if(current==1)pProbabilities[sum-original]++;
    else for(int i=1;i<=g_maxValue;i++)
            pProbability(original,current-1,i+sum,pProbabilities);
}
//基于循环
void PrintProvbavility(int number){
    if(number<1)return;
    int* pProbabilities[2];
    pProbabilities[0]=new int[g_maxValue * number+1];
    pProbabilities[1]=new int[g_maxValue * numebr+1];
    for(int i=0;i<g_maxValue*number+1;i++){
        pProbabilities[0][i]=0;
        pProbabilities[1][i]=0;
    }
    int flag=0;
    for(int i=1;i<=g_maxValue;i++)
        pProbabilities[flag][i]=1;
    for(int k=2;k<=number;k++){
            for(int i=0;i<k;i++)
                pProbabilities[1-flag][i]=0;
        for(int i=k;i<=g_maxValue*k;i++){
            pProbabilities[1-flag][i]=0;
            for(int j=1;j<=i && j<=g_maxValue;j++)
                pProbabilities[1-flag][i]+=pProbabilities[flag][i-j];
        }
    }
    flag=1-flag;
    double total=pow((double)g_maxValue,number);
    for(int i=number;i<=g_maxValue*number;i++){
        double rotio=(double)pProbabilities[flag][i]/total;
        printf("%d:%e\n",i,ratio);
    }
    delete[] pProbabilities[0];
    delete[] pProbabilities[1];
}
//page 299 判断牌是否顺子
//先排序后判断
bool IsContinuous(int* numbers,int length){
    if(numbers==nullptr || length<1)return false;
    qsort(numbers,length,sizeof(int),compare);
    int numberOfZero=0;
    int numberOfGap=0;
    for(int i=0;i<length && numbers[i]==0;i++)
        numberOfZero++;
    int samll=numberOfZero;
    int big=small+1;
    while(big<length){
        if(numbers[samll]==numbers[big])reutrn false;
        numberOfGap+=numbers[big]-numbers[small]-1;
        small=big;
        big++;
    }
    return (numberOfGap>numberOfZero)?false:true;
}
int compare(const void* arg1,const void* arg2){ 
    return *(int*)arg1-*(int*)arg2;
}
//page 301 约瑟夫环
//模拟
int LastRemaining(unsigned int n,unsigned int m){
    if(n<1 || m<1)return -1;
    unsigned int i=0;
    list<int> numbers;
    for(i=0;i<n;i++)
        numbers.push_back(i);
    list<int>::iterator current=numbers.begin();
    while(numbers.size()>1){
        for(int i=1;i<m;i++){
            current++;
            if(current==numbers.end())
                current=numbers.begin();
        }
        list<int>::iterator next=++current;
        if(next==numbers.end())
            next=numbers.begin();
        current--;
        numbers.erase(current);
        current=next;
    }
    return *(current);
}
//循环
int LastRemaining(unsigned int n,unsigned int m){
    if(n<1 || m<1)return -1;
    int last=0;
    for(int i=2;i<=n;i++)
        last=(last+m)%i;
    return last;
}
//page 股票的最大利润(即计算升序中最大的差额)
int MaxDiff(const int* numbers,unsigned length){
    if(numbers==nullptr && length<2)return 0;
    int min=numbers[0];
    int maxDiff=numbers[1]-min;
    for(int i=2;i<length;i++){
        if(numbers[i-1]<min)
            min=numbers[i-1];
        int currentDiff=numbers[i]-min;
        if(currentDiff>maxDiff)
            maxDiff=currentDiff;
    }
    return maxDiff;
}
//page 307 求1~n之和 
//不能使用乘除法for while if else switch case
//方法1 构造函数
class Temp{
    public:
        Temp(){
            N++;
            Sum+=N;
        }
        static void Reset(){
            N=0;
            Sum=0;
        }
        static unsigned int GetSum(){
            return Sum;
        }
    private:
        static unsigned int N;
        static unsigned int Sum;
};
unsigned int Temp::N=0;
unsigned int Temp::Sum=0;
unsigned int Sum_Solution1(unsigned int n){
    Temp::Reset();
    Temp* a=new Temp[n];
    delete[] a;
    a=nullptr;
    return Temp::GetSum();
}
//方法2 虚函数
class A;
A* Array[2];
class A{
    public:
        virtual unsigned int Sum(unsigned int n){
            return 0;
        }
};
class B:public A{
    public:
        virtual unsigned int Sum(unsigned int n){
            return Array[!!n]->Sum(n-1)+n;
        }
};
int Sum_Solution2(int n){
    A a;
    B b;
    Array[0]=&a;
    Array[1]=&b;
    int value=Array[1]->Sum(n);
    return value;
}
//方法3 利用函数指针求解
typedef unsigned int (*fun)(unsigned int);
unsigned int Solution3_Teminator(unsigned int n){
    return 0;
}
unsigned int Sum_Solution3(unsigned int n){
    static fun f[2]={Solution3_Teminator,Sum_Solution3};
    return n+f[!!n](n-1);
}
//方法4 模板类型求解
//看不懂
template <unsigned int n> struct Sum_Solution4{
    enum Value{N=Sum_Solution4<n - 1>::N+n};
};
template <> struct Sum_Solution4<1>{
    enum Value{N=1};
};
//page 311 不用加减乘除作加法
//位运算代替加法
//二进制相加不进位 记录进位 再将前两步相加
int Add(int num1,int num2){
    int sum,carry;
    do{
        sum=num1^num2;
        carry=(num1&num2)<<1;
        num1=sum;
        num2=carry;
    }while(num2!=0);//别忘记分号
    return num1;
}
//page 313 构建乘积数组
void multiply(const vector<double> & array1,vector<double> & array2){
    int length1=array1.size();
    int length2=array2.size();
    if(length1==length2 && length2>1){
        array2[0]=1;
        for(int i=1;i<length1;i++)
            array2[i]=array2[i-1]*array1[i-1];
        double temp=1;
        for(int i=length1-2;i>=0;i--){
            temp*=array[i+1];
            array2[i]*=temp;
        }
    }
}
//page 323 输出与书中不符
//书中叙述 n1为随机 n2为0 但是经过程序得到
// n1:2 n2:0
class A{
private:int n1;int n2;
public:
    A():n2(0),n1(n2+2){}
void Print(){cout<<"n1:"<<n1<<" n2:"<<n2<<endl;}
};
int main(){
    A a;
    a.Print();
    return 0;
}
//page 324 字符串转数字
int g_nStatus=kValid;
int StrToInt(const char* str){
    g_nStatus=kInvalid;
    long long num=0;
    if(str!=nullptr && *str!='\0'){
        bool minus=false;
        if(*str=='+')str++;
        else if(*str=='-')str++,minus=true;
        if(*str!='\0')
            num=StrToIntCore(str,minus);
    }
    return (int)num;
}
long long StrToIntCore(const char* digit,bool minus){
    long long num=0;
    while(*digit!='\0'){
        if(*digit>='0' && *digit<='9'){
            int flag=minus?-1:1;
            num=num*10+flag*(*digit-'\0');
            if((!minus && num>0x7FFFFFFF) || (minus && num<(signed int)0x80000000)){
                num=0;
                break;
            }
            digit++;
        }else{
            num=0;
            break;
        }
    }
    if(*digit=='\0'){
        g_nStatus=kValid;
    }
    return num;
}
//page 330 树中两个节点的最低公共祖先
bool GetNodePath(TreeNode* pRoot,TreeNode* pNode,list<TreeNode*>& path){
    if(pRoot==pNode)return true;
    path.push_back(pRoot);
    bool found=false;
    vector<TreeNode*>::iterator i=pRoot->m_vChildren.begin();
    while(!found && i <pRoot->m_vChildren.end()){
        found=GetNodePath(*i,pNode,path);
        i++;
    }
    if(!found)path.pop_back();
    return found;
}
TreeNode* GetLastCommonNode(const list<TreeNode*> & path1,const list<TreeNode*> & path2){
    list<TreeNode*>::const_iterator iterator1=path1.begin();
    list<TreeNode*>::const_iterator iterator2=path2.begin();
    TreeNode* pLast=nullptr;
    while(iterator1 !=path1.end() && iterator2!=path2.end()){
        if(*iterator1 == *iterator2)
            pLast=*iterator1;
        iterator1++;
        iterator2++;
    }
    return pLast;
}
TreeNode* GetLastCommonParent(TreeNode* pRoot,TreeNode* pNode1,TreeNode* pNode2){
    if(pRoot=nullptr || pNode1==nullptr || pNode2==nullptr)return nullptr;
    list<TreeNode*> path1;
    GetNodePath(pRoot,pNode1,path1);
    list<TreeNode*> path2;
    GetNodePath(pRoot,pNode2,path2);
    return GetLastCommonNode(path1,path2);
}