//千峰 stl  BV1UT4y1R7Yv
//作用域 访问方式
namespace A{ //作用域
    int data=0;
    void fun();
}
//访问 方式
void mian(){
    cout<<A::data;
}
//命名空间可以嵌套
/函数定义要注明作用域
void A::fun(){
    cout<<"A -> fun";
}
//别名
namespace B=A;
//访问个别
void main(){
    using A::data;//会和普通变量产生名字冲突
    cout<<data;
}
//::a 可以访问全局变量a a->局部变量


//BV1by4y1g7YR
p1

![](../assets/2022-03-26-21-45-51.png)
![](../assets/2022-03-26-21-59-31.png)
![](../assets/2022-03-26-22-00-15.png)
![](../assets/2022-03-26-22-00-33.png)

p2

![](../assets/2022-03-26-22-14-12.png)

![](../assets/2022-03-26-22-14-26.png)
![](../assets/2022-03-26-22-30-20.png)

p3

vector push_back() 尾插法
begin() 起始项
end() 最终项

p4

//遍历算法 algorithm头文件
void fun(int value){cout<<value;}
for_each(vector.begin(),vector.end(),fun)

p5

//容器嵌套容器
vector<int> v1;
vector<int> v2;
vector<vector<int>> v;
v.push_back(v1);
v.push_back(v2);
//遍历 嵌套的容器
vector<vector<int>>::iterator it;
for(it=v.begin();it!=v.end();it++){
    vector<int>::iterator mit;//定义向量迭代器
    for(mit=(*it).begin();mit!=(*it).end();mit++){
        cout<<*mit;
    }
    cout<<endl;
}

p6

stirng assign
![](../assets/2022-03-27-17-27-20.png)

p7

at
![](../assets/2022-03-27-17-31-59.png)
![](../assets/2022-03-27-17-34-10.png)
![](../assets/2022-03-27-17-34-25.png)

p8

string拼接 append
![](../assets/2022-03-27-17-36-21.png)

p9

string查找替换 find rfind replace
![](../assets/2022-03-27-17-41-11.png)

p10

string比较compare 提取子串insert 插入删除erase
![](../assets/2022-03-27-17-44-02.png)

string / c-style字符串转换 (string的c_str方法)
![](../assets/2022-03-27-17-50-58.png)
const char *p = str5.c_str();
或者 
char *p = const_cast str5.c_str();

p11

vector 随机访问的迭代器 单端动态数组
满时 重新开辟更大的空间 
![](../assets/2022-03-27-17-55-23.png)
size大小 capacity容量 (双倍扩容)

p12

vector assign赋值 swap交换 vector<int> v(5个,数字10)
![](../assets/2022-03-27-18-00-08.png)

size 大小 empty 1是空 resize重新v定义大小 reserve 预留空间 at越界异常 front头元素 back尾元素
![](../assets/2022-03-27-18-03-05.png)


可以通过使用 * vector.begin() 或 *( vector.end() - 1) 来获得 vector 中第一个或最后一个的值；
也可以直接使用 vector.front() 、vector.back() 来得到 vector 首尾的值。

p13

vector 记录开辟空间的次数
![](../assets/2022-03-27-18-09-40.png)
![](../assets/2022-03-27-18-13-51.png)

用swap收缩空间
vector<int>(v1).swap(v1); //拷贝构造特点
![](../assets/2022-03-27-18-16-46.png)

p14

vector insert(位置,个数,数字)插入 push_back尾插 pop_back尾删 erase(a,b) 删除(a~b)迭代器元素 erase删除指定元素 clear删除所有
![](../assets/2022-03-27-18-19-20.png)

p15

deque 双端动态数组
![](../assets/2022-03-27-18-21-48.png)
没有容量概念 分段连续空间组合而成(vector相反)

分段连续
![](../assets/2022-03-27-18-24-08.png)

p16

deque begin开始 end结尾
push_back尾插 push_front头插
pop_back尾删 pop_front头删
at访问
insert添加 清空删除同理
![](../assets/2022-03-27-18-29-38.png)
![](../assets/2022-03-27-18-30-17.png)

p18

stack 栈 先进后出
![](../assets/2022-03-27-19-17-31.png)

push压入 empty空判断 top顶 pop删顶
![](../assets/2022-03-27-19-18-44.png)

p19

queue 队列 先进先出
![](../assets/2022-03-27-19-20-48.png)

push压入 empty空判断 front头 pop删头
![](../assets/2022-03-27-19-21-26.png)

p19

list 链表 双向循环链表
![](../assets/2022-03-27-19-22-58.png)

![](../assets/2022-03-27-19-24-04.png)
![](../assets/2022-03-27-19-24-38.png)
![](../assets/2022-03-27-19-24-53.png)

p22

list不能使用algorithm的sort(随机访问)->只能用自带的list.sort

默认升序 ->降序方法
list.sort(greater<int>());//使用自带
或者
bool myCompareInt(int v1,int v2){
    return v1>v2;
}
list.sort(myCompareInt);

p23

set 根据键值自动排序 键值和实值是同一个
multiset 容器
底层红黑树
一旦插入不允许修改 (只读迭代器)

insert插入 erase删除
![](../assets/2022-03-27-20-06-55.png)
![](../assets/2022-03-27-20-07-19.png)

p24

set 存放自定义数据 需要定义排序规则
set<类型,排序规则> 变量名字;
//必须用仿函数 修改排序规则
//仿函数 本质就是重载函数调用运算符小括号的类
class Data{
    public:
    int a;
    int b;
    public:
    Data(int a,int b){
        this->a=a;
        this->b=b;
    }
}
class MyCompareData{
    public:
    bool operator()(Data ob1,Data ob2){//小括号运算符号重载
        return ob1.a<ob2.a;
    }
}
void printSetData(set<Data,MyCompareData> &s){
    set<Data,MyCompareData>::const_iterator it=s.begin();
    for(;it!=s.end();it++){
        cout<<(*it).a<<" "<<(*it).b<<endl;
    }
}
int main(){
    set<Data,MyCompareData> s;
    s.insert(Data(10,20));
    s.insert(Data(30,30));
    printSetData(s);
}

p25

set容器上下限 lower_bound upper_bound
![](../assets/2022-03-27-20-26-15.png)
![](../assets/2022-03-27-20-36-24.png)

p26

multiset 允许键值重复

p27

pair 对值
![](../assets/2022-03-27-21-06-47.png)

p28

map 键值和实值分开 根据键值自动排序 键值必须唯一
![](../assets/2022-03-27-21-14-31.png)
![](../assets/2022-03-27-21-17-00.png)
![](../assets/2022-03-27-21-22-42.png)

p29

multimap 允许k值相同

p31

stl容器场景
![](../assets/2022-03-27-21-41-28.png)

函数对象 仿函数
![](../assets/2022-03-27-21-42-35.png)
![](../assets/2022-03-27-21-44-06.png)

p32

谓词
![](../assets/2022-03-27-21-46-15.png)
普通函数方式
![](../assets/2022-03-27-21-48-04.png)
函数对象方式 重载小括号运算符
![](../assets/2022-03-27-21-49-10.png) 
![](../assets/2022-03-27-21-50-22.png)

find_if 一元
![](../assets/2022-03-27-21-54-13.png)
![](../assets/2022-03-27-21-54-59.png)

![](../assets/2022-03-27-21-56-17.png)
![](../assets/2022-03-27-21-56-51.png)

二元
![](../assets/2022-03-27-21-58-16.png)
![](../assets/2022-03-27-21-58-35.png)

![](../assets/2022-03-27-22-00-00.png)
![](../assets/2022-03-27-22-00-18.png)

p33

内建函数对象
头文件numeric
![](../assets/2022-03-27-22-02-25.png)
bind2nd(没看懂) 将两个参数整合成了一个
![](../assets/2022-03-27-22-08-24.png)

p34

自定义适配器:打包参数
绑定bind2nd和bind1st区别
//需要继承于binary_function 写参数 
//const原因是 变成仅可读(意义未知?)
![](../assets/2022-03-27-22-16-09.png)
![](../assets/2022-03-27-22-15-30.png)

p35

取反适配器
not1 一个参数 一元取反
not2 两个参数 二元取反
lambda 匿名函数
![](../assets/2022-03-27-22-20-37.png)
->
![](../assets/2022-03-27-22-23-44.png)

p36

函数指针适配器
![](../assets/2022-03-27-22-30-58.png)

p37

成员函数适配器
![](../assets/2022-03-27-22-34-41.png)
修正->
mem_fun_ref转
![](../assets/2022-03-27-22-36-56.png)
![](../assets/2022-03-27-22-37-37.png)

p38

常见遍历
头文件 algorithm
for_each算法 遍历
![](../assets/2022-03-27-22-40-23.png)

transform算法 搬运
![](../assets/2022-03-27-22-43-26.png)

![](../assets/2022-03-27-22-45-57.png)

p39

常见查找
![](../assets/2022-03-27-22-50-38.png)

![](../assets/2022-03-27-22-50-54.png)

![](../assets/2022-03-27-22-51-14.png)
![](../assets/2022-03-27-22-53-22.png)

![](../assets/2022-03-27-22-55-26.png)
![](../assets/2022-03-27-22-55-01.png)

![](../assets/2022-03-27-22-56-05.png)
![](../assets/2022-03-27-22-55-56.png)

p40

常见排序
![](../assets/2022-03-27-22-57-03.png)
![](../assets/2022-03-27-22-58-53.png)

![](../assets/2022-03-27-22-59-14.png)

![](../assets/2022-03-27-23-00-32.png)
![](../assets/2022-03-27-23-01-16.png)
![](../assets/2022-03-27-23-01-27.png)

![](../assets/2022-03-27-23-02-18.png)

p41

常见拷贝 替换算法
![](../assets/2022-03-27-23-04-01.png)
![](../assets/2022-03-27-23-04-24.png)
![](../assets/2022-03-27-23-05-14.png)
输出迭代器
![](../assets/2022-03-27-23-06-12.png)

![](../assets/2022-03-27-23-07-10.png)
![](../assets/2022-03-27-23-07-43.png)

![](../assets/2022-03-27-23-08-19.png)
![](../assets/2022-03-27-23-09-01.png)

![](../assets/2022-03-27-23-10-26.png)

p42

常见算数生成算法
![](../assets/2022-03-27-23-12-01.png)
![](../assets/2022-03-27-23-13-52.png)

![](../assets/2022-03-27-23-14-38.png)
![](../assets/2022-03-27-23-14-50.png)

p43

常见集合算法
![](../assets/2022-03-27-23-18-08.png)
![](../assets/2022-03-27-23-18-16.png)
![](../assets/2022-03-27-23-20-34.png)
修正返回迭代器
![](../assets/2022-03-27-23-21-04.png)

![](../assets/2022-03-27-23-21-27.png)
![](../assets/2022-03-27-23-21-54.png)

![](../assets/2022-03-27-23-22-13.png)











