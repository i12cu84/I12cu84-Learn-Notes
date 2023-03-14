C++ STL

C++ STL（标准模板库）是一套功能强大的 C++ 模板类，提供了通用的模板类和函数，
    这些模板类和函数可以实现多种流行和常用的算法
和数据结构，如向量、链表、队列、栈。

C++ 标准模板库的核心包括以下三个组件：

容器（Containers）: 容器是用来管理某一类对象的集合。C++ 提供了各种不同类型的容器，比如 deque、list、vector、map 等。
算法（Algorithms）: 算法作用于容器。它们提供了执行各种操作的方式，包括对容器内容执行初始化、排序、搜索和转换等操作。
迭代器（iterators）: 迭代器用于遍历对象集合的元素。这些集合可能是容器，也可能是容器的子集。

这三个组件都带有丰富的预定义函数，帮助我们通过简单的方式处理复杂的任务。
C++ STL常用容器

    vector：向量
    stack：栈
    set：集合
    queue：队列
    list：双向链表
    map：地图
    string：字符串
    deque：双端队列
    priority_queue：优先队列

对于容器，主要的操作有：

    容器的建立
    插入元素
    删除元素
    查询
    遍历
    计算元素个数
    检查元素是否为空
    输出容器包含的内容

vector

vector包含着一系列连续存储的元素,其行为和数组类似。访问Vector中的任意元素或从末尾添加元素都可以
    在常量级时间复杂度内完成，而查找特定值的元素所处的位置或是在Vector中插入元素则是线性时间复杂度。

构造函数:

    vector(); 无参数 - 构造一个空的vector
    vector(size_type num); 数量(num) - 构造一个大小为num，值为Type默认值的Vector
    vector(size_type num, const TYPE &val); 数量(num)和值(val) 
        - 构造一个初始放入num个值为val的元素的Vector
    vector(const vector &from); vector(from) - 构造一个与vector from 相同的vector
    vector(input_iterator start, input_iterator end); 迭代器(start)和迭代器(end) 
        - 构造一个初始值为[start,end)区间元素的Vector(注:半开区间).
    vector(initializer_list<value_type> il, const allocator_type& alloc = allocator_type()); 
        C++11新提供的方法，类似如下方式：
        std::vector<int>a{1, 2, 3, 4, 5};
        std::vector<int>a = {1, 2, 3, 4, 5};

常用API：

    Operators : 对vector进行赋值或比较
        v1 == v2
        v1 != v2
        v1 <= v2
        v1 >= v2
        v1 < v2
        v1 > v2
        v[]
    assign()对Vector中的元素赋值
    at() : 返回指定位置的元素
    back() : 返回最末一个元素
    begin() : 返回第一个元素的迭代器
    capacity() : 返回vector所能容纳的元素数量(在不重新分配内存的情况下）
    clear() : 清空所有元素
    empty() : 判断Vector是否为空（返回true时为空）
    end() : 返回最末元素的迭代器(译注:实指向最末元素的下一个位置)
    erase() : 删除指定元素
    front() : 返回第一个元素
    get_allocator() : 返回vector的内存分配器
    insert() : 插入元素到Vector中
    max_size() : 返回Vector所能容纳元素的最大数量（上限）
    pop_back() : 移除最后一个元素
    push_back() : 在Vector最后添加一个元素
    rbegin() : 返回Vector尾部的逆迭代器
    rend() : 返回Vector起始的逆迭代器
    reserve() : 设置Vector最小的元素容纳数量
    resize() : 改变Vector元素数量的大小
    size() : 返回Vector元素数量的大小
    swap() : 交换两个Vector

stack

C++ stack（堆栈）实现了一个先进后出（FILO）的数据结构。

构造函数：

    stack<T> stkT; : 采用模板类实现，stack对象的默认构造形式
    stack(const stack &stk); : 拷贝构造函数

常用方法：

    size(): 返回栈中的元素数
    top(): 返回栈顶的元素
    pop(): 从栈中取出并删除元素
    push(x): 向栈中添加元素x
    empty(): 在栈为空时返回true

set

Sets are containers that store unique elements following a specific order.

集合中以一种特定的顺序保存唯一的元素。

构造函数:

    set(); 无参数 - 构造一个空的set
    set(InputIterator first, InputIterator last) : 迭代器的方式构造set
    set(const set &from); : copyd的方式构造一个与set from 相同的set
    set(input_iterator start, input_iterator end); 迭代器(start)和迭代器(end) 
        - 构造一个初始值为[start,end)区间元素的Vector(注:半开区间).
    set (initializer_list<value_type> il, const key_compare& comp = key_compare(), 
        const allocator_type& alloc = allocator_type()); C++11新提供的方法，类似如下方式：
        std::set<int>a{1, 2, 3, 4, 5};

example:

// constructing sets




bool fncomp (int lhs, int rhs) {return lhs<rhs;}

struct classcomp {
  bool operator() (const int& lhs, const int& rhs) const
  {return lhs<rhs;}
};

int main ()
{
  std::set<int> first;                           // empty set of ints

  int myints[]= {10,20,30,40,50};
  std::set<int> second (myints,myints+5);        // range

  std::set<int> third (second);                  // a copy of second

  std::set<int> fourth (second.begin(), second.end());  // iterator ctor.

  std::set<int,classcomp> fifth;                 // class as Compare

  bool(*fn_pt)(int,int) = fncomp;
  std::set<int,bool(*)(int,int)> sixth (fn_pt);  // function pointer as Compare

  return 0;
}

常用API：

    begin() : 返回指向第一个元素的迭代器
    clear() : 清除所有元素
    count() : 返回某个值元素的个数
    empty() : 如果集合为空，返回true
    end() : 返回指向最后一个元素的迭代器
    equal_range() : 返回集合中与给定值相等的上下限的两个迭代器
    erase() : 删除集合中的元素
    find() : 返回一个指向被查找到元素的迭代器
    get_allocator() : 返回集合的分配器
    insert() : 在集合中插入元素
    lower_bound() : 返回指向大于（或等于）某值的第一个元素的迭代器
    key_comp() : 返回一个用于元素间值比较的函数
    max_size() : 返回集合能容纳的元素的最大限值
    rbegin() : 返回指向集合中最后一个元素的反向迭代器
    rend() : 返回指向集合中第一个元素的反向迭代器
    size() : 集合中元素的数目
    swap() : 交换两个集合变量
    upper_bound() : 返回大于某个值元素的迭代器
    value_comp() : 返回一个用于比较元素间的值的函数

queue

C++队列是一种容器适配器，它给予程序员一种先进先出(FIFO)的数据结构。

构造函数：

    explicit queue (const container_type& ctnr);
    explicit queue (container_type&& ctnr = container_type());
    template <class Alloc> explicit queue (const Alloc& alloc);
    template <class Alloc> queue (const container_type& ctnr, const Alloc& alloc);
    template <class Alloc> queue (container_type&& ctnr, const Alloc& alloc);
    template <class Alloc> queue (const queue& x, const Alloc& alloc);
    template <class Alloc> queue (queue&& x, const Alloc& alloc);

example:

// constructing queues






int main ()
{
  std::deque<int> mydeck (3,100);        // deque with 3 elements
  std::list<int> mylist (2,200);         // list with 2 elements

  std::queue<int> first;                 // empty queue
  std::queue<int> second (mydeck);       // queue initialized to copy of deque

  std::queue<int,std::list<int>> third; // empty queue with list as underlying container
  std::queue<int,std::list<int>> fourth (mylist);

  std::cout << "size of first: " << first.size() << '\n';
  std::cout << "size of second: " << second.size() << '\n';
  std::cout << "size of third: " << third.size() << '\n';
  std::cout << "size of fourth: " << fourth.size() << '\n';

  return 0;
}

Output:

size of first: 0
size of second: 3
size of third: 0
size of fourth: 2

常用API：

    back() : 返回最后一个元素
    empty() : 如果队列空则返回真
    front() : 返回第一个元素
    pop() : 删除第一个元素
    push() : 在末尾加入一个元素
    size() : 返回队列中元素的个数

list

Lists将元素按顺序储存在链表中. 与 向量(vectors)相比, 它允许快速的插入和删除，但是随机访问却比较慢.

构造函数：

    list (const allocator_type& alloc = allocator_type());
    list (size_type n, const value_type& val = value_type(), 
        const allocator_type& alloc = allocator_type());
    template <class InputIterator> list (InputIterator first, InputIterator last, 
        const allocator_type& alloc = allocator_type());
    list (const list& x);

常用API：

    assign() : 给list赋值
    back() : 返回最后一个元素
    begin() : 返回指向第一个元素的迭代器
    clear() : 删除所有元素
    empty() : 如果list是空的则返回true
    end() : 返回末尾的迭代器
    erase() : 删除一个元素
    front() : 返回第一个元素
    get_allocator() : 返回list的配置器
    insert() : 插入一个元素到list中
    max_size() : 返回list能容纳的最大元素数量
    merge() : 合并两个list
    pop_back() : 删除最后一个元素
    pop_front() : 删除第一个元素
    push_back() : 在list的末尾添加一个元素
    push_front() : 在list的头部添加一个元素
    rbegin() : 返回指向第一个元素的逆向迭代器
    remove() : 从list删除元素
    remove_if() : 按指定条件删除元素
    rend() : 指向list末尾的逆向迭代器
    resize() : 改变list的大小
    reverse() : 把list的元素倒转
    size() : 返回list中的元素个数
    sort() : 给list排序
    splice() : 合并两个list
    swap() : 交换两个list
    unique() : 删除list中重复的元素

map

C++ Maps是一种关联式容器，包含“关键字/值”对

构造函数：

    map (const key_compare& comp = key_compare(), const allocator_type& alloc = allocator_type());
    template <class InputIterator> map (InputIterator first, InputIterator last,
        const key_compare& comp = key_compare(),const allocator_type& = allocator_type());
    map (const map& x);
    map (const map& x, const allocator_type& alloc);
    map (map&& x);
    map (map&& x, const allocator_type& alloc);
    map (initializer_list<value_type> il, const key_compare& comp = key_compare(), 
        const allocator_type& alloc = allocator_type());

example:

// constructing maps




bool fncomp (char lhs, char rhs) {return lhs<rhs;}

struct classcomp {
  bool operator() (const char& lhs, const char& rhs) const
  {return lhs<rhs;}
};

int main ()
{
  std::map<char,int> first;

  first['a']=10;
  first['b']=30;
  first['c']=50;
  first['d']=70;

  std::map<char,int> second (first.begin(),first.end());

  std::map<char,int> third (second);

  std::map<char,int,classcomp> fourth;                 // class as Compare

  bool(*fn_pt)(char,char) = fncomp;
  std::map<char,int,bool(*)(char,char)> fifth (fn_pt); // function pointer as Compare

  return 0;
}

常用API：

    begin() : 返回指向map头部的迭代器
    clear() : 删除所有元素
    count() : 返回指定元素出现的次数
    empty() : 如果map为空则返回true
    end() : 返回指向map末尾的迭代器
    equal_range() : 返回特殊条目的迭代器对
    erase() : 删除一个元素
    find() : 查找一个元素
    get_allocator() : 返回map的配置器
    insert() : 插入元素–
    key_comp() : 返回比较元素key的函数
    lower_bound() : 返回键值>=给定元素的第一个位置
    max_size() : 返回可以容纳的最大元素个数
    rbegin() : 返回一个指向map尾部的逆向迭代器
    rend() : 返回一个指向map头部的逆向迭代器
    size() : 返回map中元素的个数
    swap() : 交换两个map
    upper_bound() : 返回键值>给定元素的第一个位置
    value_comp() : 返回比较元素value的函数

string
1.string构造函数

    string();//创建一个空的字符串
    string(const string& str);//使用一个string对象初始化另一个string对象
    string(const char* s);//使用字符串s初始化
    string(int n,char c);//使用n个字符c初始化

2.string基本赋值操作

    string& operator=(const char* s);//char*类型字符串 赋值给当前的字符串
    string& operator=(const string &s);//把字符串s赋值给当前的字符串
    string& operator=(char c);//字符赋值给当前的字符串
    string& assign(const char* s);//把字符串s赋值给当前的字符串
    string& assign(const char* s,int n);//把字符串s的前n个字符赋值给当前的字符串
    string& assign(const string &s);//把字符串s赋值给当前的字符串
    string& assign(int n,char c);//用n个字符c赋值给当前字符串
    string& assign(const string &s,int start,int n);//将s从start开始n个字符赋值给字符串

3.string存取字符操作

    char& operator[](int n);//通过[]方式取字符
    char& at(int n);//通过at方法获取字符

4.string拼接操作

    string& operator+=(const string& str);//重载+=运算符
    string& operator+=(const char* str);//重载+=运算符
    string& operator+=(const char c);//重载+=运算符
    string& append(const char *s);//把字符串s连接到当前字符串结尾
    string& append(const char *s,int n);//把字符串s的前n个字符连接到当前字符串结尾
    string& append(const string &s);//同operator+=（）
    string& append(const string &s,int pos,int n);//把字符串s中从pos开始的n个字符连接到当前字符串结尾
    string& append(int n,char c);//在当前字符串结尾添加n个字符c

5.string查找和替换

    int find(const string& str,int pos = 0)const;//查找str第一次出现的位置，从pos开始查找
    int find(const char* s,int pos = 0)const;//查找s第一次出现位置，从pos开始查找
    int find(const char *s,int pos,int n)const;//从pos位置查找s的前n个字符第一次位置
    int find(const char c,int pos = 0)const;//查找字符c第一次出现位置
    int rfind(const string& str, int pos = npos)const;//查找str最后一次出现位置，从pos开始查找
    int rfind(const char* s,int pos = npos)const;//查找s最后一次出现位置，从pos开始查找
    int rfind(const char* s,int pos,int n )const;//从pos查找s的前n个字符最后一次位置
    int rfind(const char c,int pos = 0)const;//查找字符c最后一次出现位置
    string& replace(int pos,int n,const string& str);//替换从pos开始的n个字符为字符串str
    string& replace(int pos,int n,const char* s);//替换从pos开始的n个字符为字符串s

6.string 比较操作

    int compare(const string &s)const;//与字符串s比较
    int compare(const char*s)const;//与字符串s比较
    compare函数在>时返回1，<时返回-1，相等时返回0，比较区分大小写，逐个字符比较

7.string子串

    string substr(int pos = 0,int n = npos)const;//返回由pos开始的n个字符组成的字符串

8.string插入和删除操作

    string& insert(int pos,const char* s);//插入字符串
    string& insert(int pos,const string &str);//插入字符串
    string& insert(int pos,int n,char c);//在指定位置插入n个字符c
    string& erase(int pos,int n = npos);//删除从pos开始的n个字符

deque

deque是Double-Ended Queues(双向队列)的缩写。

双向队列和向量很相似，但是它允许在容器头部快速插入和删除（就像在尾部一样）。
1.deque构造函数

    deque<T> queT;//queue采用模板类实现，queue对象的默认构造形式
    deque<T> queT(size);//构造大小为size的deque，其中值为T类型的默认值
    deque<T> queT(size, val);//构造大小为size的deque，其中值为val
    deque(const deque &que);//拷贝构造函数
    deque(input_iterator start, input_iterator end);//迭代器构造函数

example:

// constructing deques




int main ()
{
  unsigned int i;

  // constructors used in the same order as described above:
  std::deque<int> first;                                // empty deque of ints
  std::deque<int> second (4,100);                       // four ints with value 100
  std::deque<int> third (second.begin(),second.end());  // iterating through second
  std::deque<int> fourth (third);                       // a copy of third

  // the iterator constructor can be used to copy arrays:
  int myints[] = {16,2,77,29};
  std::deque<int> fifth (myints, myints + sizeof(myints) / sizeof(int) );

  std::cout << "The contents of fifth are:";
  for (std::deque<int>::iterator it = fifth.begin(); it!=fifth.end(); ++it)
    std::cout << ' ' << *it;

  std::cout << '\n';

  return 0;
}

Output:

The contents of fifth are: 16 2 77 29 

2.deque存取、插入和删除操作

    back();//返回最后一个元素
    front();//返回第一个元素
    insert();//
    pop_back();//删除尾部的元素
    pop_front();//删除头部的元素
    push_back();//在尾部加入一个元素
    push_front();//在头部加入一个元素
    at();//访问指定位置元素

    注：queue只有push和pop方法，在尾部加入和删除元素。

3.deque赋值操作

    operator[] (size_type n);//重载[]操作符

4.deque大小操作

    empty();//判断队列是否为空
    size();//返回队列的大小

priority_queue

优先队列类似队列， 但是在这个数据结构中的元素按照一定的规则排列有序。

在优先队列中，元素被赋予优先级。当访问元素时，具有最高优先级的元素最先删除。优先队列具有最高优先级先出 
（first in, largest out）的行为特征。

首先要包含头文件#include, 他和queue不同的就在于我们可以自定义其中数据的优先级, 让优先级高的排在队列前面,优先出队。

优先队列具有队列的所有特性，包括队列的基本操作，只是在这基础上添加了内部的一个排序，它本质是一个堆实现的。

构造函数： priority_queue<Type, Container, Functional>

Type 就是数据类型，
Container 就是容器类型（Container必须是具备随机存取能力的容器，支持如下方法：
empty(), size(), front(), push_back(),pop_back()。比如vector,deque等等，但不能用list。STL里面默认用的是vector）。
可选
Functional 就是比较的方式。可选

当需要用自定义的数据类型时才需要传入这三个参数，使用基本数据类型时，只需要传入数据类型，
默认是大顶堆(Functional是less)。

example:

// constructing priority queues






class mycomparison
{
  bool reverse;
public:
  mycomparison(const bool& revparam=false)
    {reverse=revparam;}
  bool operator() (const int& lhs, const int&rhs) const
  {
    if (reverse) return (lhs>rhs);
    else return (lhs<rhs);
  }
};

int main ()
{
  int myints[]= {10,60,50,20};

  std::priority_queue<int> first;
  std::priority_queue<int> second (myints,myints+4);
  std::priority_queue<int, std::vector<int>, std::greater<int> >
                            third (myints,myints+4);
  // using mycomparison:
  typedef std::priority_queue<int,std::vector<int>,mycomparison> mypq_type;

  mypq_type fourth;                       // less-than comparison
  mypq_type fifth (mycomparison(true));   // greater-than comparison

  return 0;
}

    The example does not produce any output, but it constructs different priority_queue objects: 
    - First is empty. - Second contains the four ints defined for myints, with 60 (the highest) at its top. 
    - Third has the same four ints, but because it uses greater instead of the default (which is less), 
    it has 10 as its top element. - Fourth and fifth are very similar to first: they are both empty, 
    except that these use mycomparison for comparisons, which is a special stateful comparison function 
    that behaves differently depending on a flag set on construction.

api和队列基本操作相同:

    top 访问队头元素
    empty 队列是否为空
    size 返回队列内元素个数
    push 插入元素到队尾 (并排序)
    emplace 原地构造一个元素并插入队列
    pop 弹出队头元素
    swap 交换内容
