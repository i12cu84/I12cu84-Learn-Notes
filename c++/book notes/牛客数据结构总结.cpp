1、树

AVL 平衡二叉树 二叉排序树
左右高度差值不超过1
左子树-右子树深度=平衡因子BF
大于1则不平衡

红黑树 二叉查找树
每个节点非红即黑 根节点为黑 每个叶节点为黑 一个节点为红其子节点必黑任意节点根到叶黑节点相同

区别 AVL高度平衡 频繁插入删除会引起频繁的rebalance 效率下降
    红黑树高度不平衡 插入最多两次旋转 删除最多三次旋转 都为O(logn)

哈夫曼编码
最优前缀码二叉树 0和1分组 用于数据压缩
以自底向上方式构造表示最优前缀码的二叉树
算法以|C|个叶节点开始 执行|C|-1次合并运算后产生最终所要求的树

B+ 多路搜索树 平衡查找树
每个节点可以有多个孩子 按照关键字大小有序排列
所有记录点都是按照键值大小顺序放在同一层的叶结点中
相对于B树特点
    每个节点上的指针上限为2d不是2d+1(d是节点的出度)
    内节点不存储data 只存储key
    叶节点不存储指针

map和unordered_map都是红黑树底层实现

map内部元素排列有序
优点 查找删除增加都为O(logn) 
缺点 平均时间复杂度较慢 与n有关

umap底层基于哈希表 无序
优点 查找删除增加速度快 复杂度为O(c)
缺点 以key->value对的形式存储 空间占用率高
    时间复杂度不稳定 平均O(c) 极端可能O(n)

epoll通过红黑树 双向链表实现(没看懂)
通过epoll_create()系统调用在内核中创建eventpoll句柄，包括红黑树根节点和双向链表头节点
通过epoll_ctl()系统调用，向对象的红黑树结构中增删改事件，返0成功 返-1失败
通过epoll_wait()系统调用判断双向链表是否为空，为空则阻塞。
当文件描述符状态改变，fd 上的回调函数被调用，该函数将 fd 加入到双向链表中，epoll_wait函数被唤醒，返回就绪事件。

红黑树左右旋转
    旋转：通过改变树中某些结点的颜色以及指针结构来保持对红黑树进行插入和删除操作后的红黑性质。
    左旋：对某个结点 x 做左旋操作时，假设其右孩子为 y 而不是 T.nil：
    以 x 到 y 的链为“支轴”进行。使 y 成为该子树新的根结点，x 成为 y 的左孩子，y 的左孩子成为 x 的右孩子。   
    右旋：对某个结点 x 做右旋操作时，假设其左孩子为 y 而不是 T.nil：
    以 x 到 y 的链为“支轴”进行。使 y 成为该子树新的根结点，x 成为 y 的右孩子，y 的右孩子成为 x 的左孩子。

实现二叉树层序遍历并输出(没看懂)
    void layerTrace(BTreeNode *T){
        if(T== nullptr)return;
        BTreeNode *p=T;
        queue<BTreeNode*>q;
        q.push(p);
        while(!q.empty()){
            p=q.front();
            q.pop();
            cout<<<<p->data;
            if(p->left!= nullptr)q.push(p->left);
            if(p->right!= nullptr)q.push(p->right);   
        }
    }
    
二叉树序列化反序列化(没看懂)
>序列化：必须保存一个中序遍历结果，然后外加一个前序或者后序遍历结果
>反序列化：根据两次遍历生成的结果恢复二叉树，代码如下(前序和中序)：
    ```TreeNode* helper(vector<int>pre,int startPre,int endPre,vector<int>in,int
    startIn,int endIn){
        if(startPre>endPre||startIn>endIn)
            return nullptr;
        TreeNode * root=new TreeNode(pre[startPre]);
        for(int i=startIn;i<=endIn;++i){
            if(in[i]==pre[startPre]){
                root->left=helper(pre,startPre+1,startPre+i-startIn,in,startIn,i-1);
                root->right=helper(pre,i-startIn+startPre+1,endPre,in,i+1,endIn);
                break;
            }
        }
        return root;   
    }
    TreeNode* reConstructBinaryTree(vector<int> pre,vector<int> vin){
        TreeNode *root=helper(pre,0,pre.size()-1,vin,0,vin.size()-1);
        return root;
    }















2、堆heap与栈stack

stack overflow(栈溢出)    
概念：向栈中写入超过本身内容长度，因而导致栈中与其相邻的变量的值被改变。
    原因：
        1. 局部数组过大。函数内部的数组过大。
            一是增大栈空间,二是改用动态分配，使用堆。
        2. 递归调用层次太多。递归函数执行压栈操作，压栈太多会导致堆栈溢出。
        3. 指针或数组越界。例如进行字符串拷贝，或处理用户输入等等。
    栈溢出例子：
        int main(int argc, char* argv[]) {
            char buf[256];
            strcpy(buf,argv[1]);   //发生了缓冲区溢出错误，源缓冲区内容由用户输入
            printf("Input:%s\n",buf);
            return 0;
        }

栈和堆的区别 为什么栈快
区别：
    栈是由高地址向低地址扩展
    栈的分配效率较高
    栈中内存是由 OS 自动申请和释放，存放参数、局部变量等
    栈由于其先进后出的特性，不会产生内存碎片

    堆是由低地址向高地址扩展
    堆中的内存需要手动申请和手动释放
    堆中频繁调用 malloc 和 free 产生内存碎片，降低效率
    堆的分配效率较低

栈快原因：
    栈是操作系统提供的数据结构，计算机底层对栈提供了一系列支持：分配专门的寄存器存储栈的地址，
    压栈和入栈有专门的指令执行；
    堆是由函数库提供的，需要一些列分配、合并和释放内存的算法，因此效率较低。

两个栈实现一个队列   
    class Solution {
        public:
        void push(int node) {
            stack1.push(node);
        }
        int pop() {
            if(stack2.size()!=0){
                int tmp = stack2.top();
                stack2.pop();
                return tmp;
            }
            else{
                while(stack1.size()!=0){
                    int tmp = stack1.top();
                    stack1.pop();
                    stack2.push(tmp);
                }
                return pop();//(没看懂这个)感觉有问题
            }
        }   
        private:
        stack<int> stack1,stack2;
    }；

    完全二叉树
    小根堆 根节点小于左子女 小于右子
    大根堆 根节点大于左子女 大于右子















3、数组

数组array 链表list的区别

    数组的特点：
    将元素连续存放在内存中，可以通过下标迅速访问数组中任何元素。
    插入数据和删除数据效率低，
    插入数据时，这个位置后面的数据在内存中都要向后移。
    删除数据时，这个数据后面的数据都要往前移动。
    随机读取效率很高

    优点：
    1. 随机访问性强
    2. 查找速度快
    缺点:
    1. 插入和删除效率低
    2. 可能浪费内存   
    3. 内存空间要求高，必须有足够的连续内存空间。
    4. 数组大小固定，不能动态拓展

    链表的特点：
    内存中通过存在元素中的指针联系到一起。
    访问链表中元素，需要从第一个元素开始，一直找到需要的元素位置。
    增加和删除元素对于链表数据结构就非常简单了，只修改元素中的指针
    不指定大小，扩展方便。链表大小不用定义，数据随意增删。
    
    优点:
    1. 插入删除速度快
    2. 内存利用率高，不会浪费内存
    3. 大小没有固定，拓展很灵活。
    缺点:
    不能随机查找，必须从第一个开始遍历，查找效率低

    如果应用需要快速访问数据，很少或不插入和删除元素，就应该用数组。
    如果应用需要经常插入和删除元素你就需要用链表数据结构了。

2、一个长度为 N 的整形数组，数组中每个元素的取值范围是[0,n-1],判断该数组否有重复的数
把每个数放到自己对应序号的位置上，如果其他位置上有和自己对应序号相同的数，那么即为有重复的数值。时间复杂度为 O(N),
同时为了节省空间复杂度，可以在原数组上进行操作，空间复杂度为 O(1)
    bool IsDuplicateNumber(int *array, int n){
        if(array==NULL) return false;
        int i,temp;
        for(i=0;i<n;i++){
            while(array[i]!=i){
                if(array[array[i]]==array[i])
                    return true;
                temp=array[array[i]];   
                array[array[i]]=array[i];
                array[i]=temp;
            }
        }
        return false;
    }















4、排序
快排
    int once_quick_sort(vector<int> &data, int left, int right){
        int key = data[left];
        while (left < right){
            while (left < right && key <= data[right])
                right--;
            if (left < right)
                data[left++] = data[right];
            while (left < right && key > data[left])
                left++;
            if (left < right)
                data[right--] = data[left];
        }
        data[left] = key;
        return left;
    }
    int quick_sort(vector<int> & data, int left, int right){
        if (left >= right )
            return 1;
        int middle = 0;
        middle = once_quick_sort(data, left, right);
        quick_sort(data, left, middle-1);
        quick_sort(data, middle + 1, right);
    }

求第k大的数的方法以及复杂度 当有相同元素时其他方法

    首先使用快速排序算法将数组按照从大到小排序，然后取第 k 个，其时间复杂度最快为O(nlogn)

    使用堆排序，建立最大堆，然后调整堆，知道获得第 k 个元素，其时间复杂度为 O(n+klogn)

    首先利用哈希表统计数组中个元素出现的次数，
    然后利用计数排序的思想，线性从大到小扫描过程中，前面有 k-1 个数则为第 k 大的数利用快排思想，
    从数组中随机选择一个数 i，然后将数组分成两部分 Dl,Dr，Dl 的元素都小于 i,Dr 的元素都大于 i。
    然后统计 Dr 元素个数，如果 Dr 元素个数等于 k-1,那么第 k 大的数即为 k，
    如果 Dr 元素个数小于 k,那么继续求 Dl 中第 k-Dr 大的元素；如果 Dr 元素个数大于 k,
    那么继续求 Dr 中第 k 大的元素。
    当有相同元素的时候，首先利用哈希表统计数组中个元素出现的次数，然后利用计数排序的思想，线性从大到小扫
    描过程中，前面有 k-1 个数则为第 k 大的数，平均情况下时间复杂度为 O(n)   

排序算法时间复杂度
    插入排序：对于一个带排序数组来说，其初始有序数组元素个数为1，然后从第二个元素，
    插入到有序数组中。对于每一次插入操作，从后往前遍历当前有序数组，
    如果当前元素大于要插入的元素，则后移一位；如果当前元素小于或等于要插入的元素，
    则将要插入的元素插入到当前元素的下一位中。

    希尔排序：先将整个待排序记录分割成若干子序列，然后分别进行直接插入排序，待整个序
    列中的记录基本有序时，在对全体记录进行一次直接插入排序。其子序列的构成不是简单的逐段
    分割，而是将每隔某个增量的记录组成一个子序列。希尔排序时间复杂度与增量序列的选取有关，
    其最后一个值必须为 1.

    归并排序：该算法采用分治法；对于包含 m 个元素的待排序序列，将其看成 m 个长度为 1
    的子序列。然后两两合归并，得到 n/2 个长度为 2 或者 1 的有序子序列；然后再两两归并，
    直到得到 1 个长度为 m 的有序序列。

    冒泡排序：对于包含 n 个元素的带排序数组，重复遍历数组，首先比较第一个和第二个元素，
    若为逆序，则交换元素位置；然后比较第二个和第三个元素，重复上述过程。每次遍历会把当前
    前 n-i 个元素中的最大的元素移到 n-i 位置。遍历 n 次，完成排序。
    快速排序：通过一趟排序将要排序的数据分割成独立的两部分，其中一部分的所有数据都比
    另外一部分的所有数据都要小，然后再按此方法对这两部分数据分别进行快速排序，整个排序过
    程可以递归进行，以此达到整个数据变成有序序列。

    选择排序：每次循环，选择当前无序数组中最小的那个元素，然后将其与无序数组的第一个
    元素交换位置，从而使有序数组元素加 1，无序数组元素减 1.初始时无序数组为空。
    堆排序：堆排序是一种选择排序，利用堆这种数据结构来完成选择。其算法思想是将带排序
    数据构造一个最大堆（升序）/最小堆（降序），然后将堆顶元素与待排序数组的最后一个元素
    交换位置，此时末尾元素就是最大/最小的值。然后将剩余 n-1 个元素重新构造成最大堆/最小堆。
    各个排序的时间复杂度、空间复杂度及稳定性如下：   

    时间复杂度(最好~最坏-平均)              空间复杂度 稳定性 复杂性
    插入排序        n2      n2      n       1       稳定    简单
    希尔排序        nlgn    n2      n2      1       不稳定  较复杂
    选择排序        n2      n2      n2      1       不稳定  简单
    堆排序          nlgn    nlgn    nlgn    1       不稳定  较复杂
    冒泡排序        n2      n2      n       1       稳定    简单
    快速排序        nlgn    n2      nlgn    nlgn    不稳定  较复杂
    归并排序        nlgn    nlgn    nlgn    n       稳定    较复杂

    计数排序思想：如果比元素 x 小的元素个数有 n 个，则元素 x 排序后位置为 n+1。
    1）找出待排序的数组中最大的元素；
    2）统计数组中每个值为 i 的元素出现的次数，存入数组 C 的第 i 项；
    3）对所有的计数累加（从 C 中的第一个元素开始，每一项和前一项相加）；
    4）反向填充目标数组：将每个元素 i 放在新数组的第 C(i)项，每放一个元素就将 C(i)减去1。
    时间复杂度：O(n+k)，k 是待排序数的范围。

    桶排序：
    1）设置一个定量的数组当作空桶子；
    2）寻访序列，并且把记录一个一个放到对应的桶子去；
    3）对每个不是空的桶子进行排序。
    4）从不是空的桶子里把项目再放回原来的序列中。
    时间复杂度：O(n+C) ，C 为桶内排序时间。

海量数据如何去取最大的 k 个
    1.直接全部排序（只适用于内存够的情况）
    当数据量较小的情况下，内存中可以容纳所有数据。则最简单也是最容易想到的方法是将数
    据全部排序，然后取排序后的数据中的前 K 个。
    这种方法对数据量比较敏感，当数据量较大的情况下，内存不能完全容纳全部数据，这种方
    法便不适应了。即使内存能够满足要求，该方法将全部数据都排序了，而题目只要求找出 top K
    个数据，所以该方法并不十分高效，不建议使用。

    2.快速排序的变形 （只使用于内存够的情况）
    这是一个基于快速排序的变形，因为第一种方法中说到将所有元素都排序并不十分高效，
    只需要找出前 K 个最大的就行。   
    这种方法类似于快速排序，首先选择一个划分元，将比这个划分元大的元素放到它的前面，
    比划分元小的元素放到它的后面，此时完成了一趟排序。
    如果此时这个划分元的序号 index 刚好等于 K，那么这个划分元以及它左边的数，
    刚好就是前 K 个最大的元素；
    如果 index > K，那么前 K 大的数据在 index 的左边，那么就继续递归的从 index-1 个数中进行一趟排序；
    如果 index < K，那么再从划分元的右边继续进行排序，直到找到序号 index 刚好等于 K 为止。
    再将前 K 个数进行排序后，返回 Top K 个元素。
    这种方法就避免了对除了 Top K 个元素以外的数据进行排序所带来的不必要的开销。

    3.最小堆法
    这是一种局部淘汰法。先读取前 K 个数，建立一个最小堆。然后将剩余的所有数字依次与最小堆的堆顶进行比较，
    如果小于或等于堆顶数据，则继续比较下一个；否则，删除堆顶元素，
    并将新数据插入堆中，重新调整最小堆。当遍历完全部数据后，最小堆中的数据即为最大的 K 个数。

    4.分治法
    将全部数据分成 N 份，前提是每份的数据都可以读到内存中进行处理，找到每份数据中最大的 K 个数。
    此时剩下 N*K 个数据，如果内存不能容纳 N*K 个数据，则再继续分治处理，分成 M份，
    找出每份数据中最大的 K 个数，如果 M*K 个数仍然不能读到内存中，则继续分治处理。
    直到剩余的数可以读入内存中，那么可以对这些数使用快速排序的变形或者归并排序进行处理。

    5.Hash 法
    如果这些数据中有很多重复的数据，可以先通过 hash 法，把重复的数去掉。
    这样如果重复率很高的话，会减少很大的内存用量，从而缩小运算空间。
    处理后的数据如果能够读入内存，则可以直接排序；否则可以使用分治法或者最小堆法来处理数据。















哈希

hash 表的实现，包括 STL 中的哈希桶长度常数。
    构造哈希和处理哈希冲突两个方面：
    对于构造哈希来说，主要包括直接地址法、平方取中法、除留余数法等。
    对于处理哈希冲突来说，最常用的处理冲突的方法有开放定址法、再哈希法、链地址法、建立公共溢出区等方法。
    SGL 版本使用链地址法，使用一个链表保持相同散列值的元素。(没看懂)
    虽然链地址法并不要求哈希桶长度必须为质数，但 SGI STL 仍然以质数来设计哈希桶长度，
    并且将 28 个质数（逐渐呈现大约两倍的关系）计算好，以备随时访问，同时提供一个函数，
    用来查询在这 28 个质数之中，“最接近某数并大于某数”的质数。

hash 表如何 rehash，怎么处理其中保存的资源
    C++的 hash 表中有一个负载因子 loadFactor，当 loadFactor<=1 时，hash 表查找的期望复杂度为 O(1).
    因此，每次往 hash 表中添加元素时，我们必须保证是在 loadFactor <1 的情况下，才能够添加。
    因此，当 Hash 表中 loadFactor==1 时，Hash 就需要进行 rehash。rehash 过程中，会模仿
    C++的 vector 扩容方式，Hash 表中每次发现 loadFactor ==1 时，就开辟一个原来桶数组的两倍
    空间，称为新桶数组，然后把原来的桶数组中元素全部重新哈希到新的桶数组中。

哈希表的桶个数为什么是质数，合数有何不妥？
哈希表的桶个数使用质数，可以最大程度减少冲突概率，使哈希后的数据分布的更加均匀。
如果使用合数，可能会造成很多数据分布会集中在某些点上，从而影响哈希表效率。
算法：给定一个数字数组，返回哈夫曼树的头指针
struct BTreeNode* CreateHuffman(ElemType a[], int n){
    int i, j;
    struct BTreeNode **b, *q;
    b = malloc(n*sizeof(struct BTreeNode));
    for (i = 0; i < n; i++){
        b[i] = malloc(sizeof(struct BTreeNode));
        b[i]->data = a[i];
        b[i]->left = b[i]->right = NULL;
    }
    for (i = 1; i < n; i++){
        int k1 = -1, k2;
        for (j = 0; j < n; j++){
            if (b[j] != NULL && k1 == -1){
                k1 = j;
                continue;
            }
            if (b[j] != NULL){   
                k2 = j;
                break;
            }
        }
        for (j = k2; j < n; j++){
            if (b[j] != NULL){
                if (b[j]->data < b[k1]->data){
                    k2 = k1;
                    k1 = j;
                }
                else if (b[j]->data < b[k2]->data)
                k2 = j;
            }
        }
        q = malloc(sizeof(struct BTreeNode));
        q->data = b[k1]->data + b[k2]->data;
        q->left = b[k1];
        q->right = b[k2];
        b[k1] = q;
        b[k2] = NULL;
    }   
    free(b);
    return q;
}

解决 hash 冲突的方法

定义：哈希表关键字集合过大，关键字不同的元素可能会映象到同一地址上

开放定址法: 当发生地址冲突时，按照某种方法继续探测哈希表中的其他存储单元，直到找到空位置为止。

再哈希法：当发生哈希冲突时使用另一个哈希函数计算地址值，直到冲突不再发生。这种方法不易产生聚集，但是增加计算时间，同时需要准备许多哈希函数。

链地址法：将所有哈希值相同的Key通过链表存储。key 按顺序插入到链表中

建立公共溢出区：采用一个溢出表存储产生冲突的关键字。如果公共溢出区还产生冲突，再采用处理冲突方法处理。















动态规划(看不懂 这个不太擅长 暂时跳过)

最长公共连续子序列
int substr(string & str1, string &str2){
    int len1 = str1.length();
    int len2 = str2.length();
    vector<vector<int>>dp(len1,vector<int>(len2,0));
    for (int i = 0; i < len1; i++)
        dp[i][0] = str1[i]==str1[0]?1:0;
    for (int j = 0; j <= len2; j++)
        dp[0][j] = str1[0]==str2[j]?1:0;
    for (int i = 1; i < len1; i++)
        for (int j = 1; j < len2; j++)
            if (str1[i] == str2[j])
                dp[i][j] = dp[i - 1][j - 1]+1;
    int longest = 0;
    int longest_index = 0;
    for (int i = 0; i < len1; i++)
        for (int j = 0; j < len2; j++)
            if (longest < dp[i][j])
                longest = dp[i][j],longest_index = i;
    //字符串为从第 i 个开始往前数 longest 个
    for (int i = longest_index-longest+1; i <=longest_index; i++)
        cout << str1[i] << endl;
    return longest;
}

求一个字符串最长回文子串
int LongestPalindromicSubstring(string & a){
    int len = a.length();
    vector<vector<int>>dp(len, vector<int>(len, 0));
    for (int i = 0; i < len; i++)
        dp[i][i] = 1;
    int max_len = 1;
    int start_index = 0;
    for (int i= len - 2; i >= 0; i--){
        for (int j = i + 1; j < len; j++){
            if (a[i] == a[j]){
                if (j - i == 1)
                    dp[i][j] = 2;
                else
                    if (j - i > 1)
                        dp[i][j] = dp[i + 1][j - 1] + 2;   
                if (max_len < dp[i][j]){
                    max_len =dp[i][j];
                    start_index = i;
                }
            }
            else dp[i][j] = 0;
        }
    }
    cout << "max len is " << max_len << endl;
    cout << "star index is" << start_index << endl;
    return max_len;
}

查找最长回文子串
int LongestPalindromicSubstring(string & a){
    int len = a.length();
    vector<vector<int>>dp(len, vector<int>(len, 0));   
    for (int i = 0; i < len; i++)
        dp[i][i] = 1;
    int max_len = 1,start_index = 0;
    for (int i= len - 2; i >= 0; i--)
        for (int j = i + 1; j < len; j++)
            if (a[i] == a[j]){
                if (j - i == 1)
                    dp[i][j] = 2;
                else
                    if (j - i > 1)
                        dp[i][j] = dp[i + 1][j - 1] + 2;
                if (max_len < dp[i][j]){   
                max_len =
                dp[i][j];
                start_index = i;
                }
            }
            else dp[i][j] = 0;
    cout << "max len is " << max_len << "star index is" << start_index << endl;
    return max_len;
}















链表

合并两个有序链表
class Solution {
    public:
    ListNode* mergeTwoLists(ListNode* l1, ListNode* l2) {
        if(l1 == NULL)
            return l2;
        if(l2 == NULL)
            return l1;
        if(l1->val < l2->val){
            l1->next=mergeTwoLists(l1->next,l2);
            return l1;
        }
        else{
            l2->next=mergeTwoLists(l1,l2->next);
            return l2;
        }
    }
};

反转链表
Void reversal_list(mylist * a_list){
    mylist * forward_node = nullptr;
    mylist * cur_node = a_list->next;
    mylist* next_node = cur_node->next;
    if(cur_node == nullptr)
        return ;
    while(1){
        cur_node->next = forward_node;
        forward_node = cur_node;
        cur_node = next_node;
        if(cur_node == nullptr)
            break;
        next_node = cur_node->next;
    }
    a_list->next = forward_node;
}

链表是否为回文链表  
思路：使用栈存储链表前半部分，然后一个个出栈，与后半部分元素比较，如果链表长度未知，
可以使用快慢指针的方法，将慢指针指向的元素入栈，然后如果快指针指向了链表尾部，此时慢指针指向了链表中间
bool is_palindromic_list2(mylist *a_list){
    if(a_list == nullptr)
        return false;
    stack<int>list_value;
    mylist * fast =a_list;
    mylist *slow =a_list;
    while(fast->next!=nullptr && fast->next->next!=nullptr){
        list_value.push(slow->next->value);
        slow = slow->next;
        fast = fast->next->next;
    }
    cout<<"middle elem value is "<<slow->next->value<<endl;
    if(fast->next != nullptr){
        cout<<"the list has odd num of node"<<endl;
        slow =slow->next;
    }
    int cur_value;   
    while(!list_value.empty()){
        cur_value = list_value.top();
        cout<<"stack top value is"<<cur_value<<endl;
        cout<<"list value is "<<slow->next->value<<endl;
        if(cur_value != slow->next->value)
            return false;
        list_value.pop();
        slow = slow->next;
    }
    return true;
}

链表反转
struct ListNode {
    int val;
    struct ListNode *next;
    ListNode(int x) :val(x), next(NULL) {}
}
ListNode* ReverseList(ListNode* pHead){   
    if(!pHead||!pHead->next)return pHead;
    ListNode *pre=nullptr;
    ListNode *p=pHead;
    ListNode *next=pHead->next;
    while(p){
        p->next=pre;
        pre=p;
        p=next;
        if(next)
            next=next->next;
    }
    return pre;
}

判断两个单向链表是否相交
1、单向链表
    单向链表（单链表）是链表的一种，其特点是链表的链接方向是单向的，对链表的访问要通过顺序读取从头部开始；
    链表是使用指针进行构造的列表；又称为结点列表，因为链表是由一个个结点组装起来的；
    其中每个结点都有指针成员变量指向列表中的下一个结点。
    列表是由结点构成，head 指针指向第一个成为表头结点，而终止于最后一个指向 nuLL 的指针。
2、判断两个链表是否相交
    1）方法 1：   
    链表相交之后，后面的部分节点全部共用，可以用 2 个指针分别从这两个链表头部走到尾
    部，最后判断尾部指针的地址信息是否一样，若一样则代表链表相交！
    2）方法 2：
    可以把其中一个链表的所有节点地址信息存到数组中，然后把另一个链表的每一个节点地址信息遍历数组，
    若相等，则跳出循环，说明链表相交。进一步优化则是进行 hash 排序，建立hash 表。















7、高级算法

请问加密方法都有哪些

单向加密
    单向加密又称为不可逆加密算法，其密钥是由加密散列函数生成的。单向散列函数一般用
    于产生消息摘要，密钥加密等，常见的有：
    MD5（Message Digest Algorithm 5）：是 RSA 数据安全公司开发的一种单向散列算法，非可逆，相同的明文产生相同的密文；
    SHA（Secure Hash Algorithm）：可以对任意长度的数据运算生成一个 160 位的数值。其变种由 SHA192，SHA256，SHA384 等；
    CRC-32，主要用于提供校验功能；
    算法特征：
    输入一样，输出必然相同；
    雪崩效应，输入的微小改变，将会引起结果的巨大变化；   
    定长输出，无论原始数据多大，结果大小都是相同的；
    不可逆，无法根据特征码还原原来的数据；

对称加密
    采用单钥密码系统的加密方法，同一个密钥可以同时用作信息的加密和解密，这种加密方
    法称为对称加密，也称为单密钥加密。
    特点：
    1、加密方和解密方使用同一个密钥；
    2、加密解密的速度比较快，适合数据比较长时的使用；
    3、密钥传输的过程不安全，且容易被破解，密钥管理也比较麻烦；
    优点：对称加密算法的优点是算法公开、计算量小、加密速度快、加密效率高。
    缺点：对称加密算法的缺点是在数据传送前，发送方和接收方必须商定好秘钥，然后使双
    方都能保存好秘钥。其次如果一方的秘钥被泄露，那么加密信息也就不安全了。另外，每对用户
    每次使用对称加密算法时，都需要使用其他人不知道的唯一秘钥，这会使得收、发双方所拥有的
    钥匙数量巨大，密钥管理成为双方的负担。

非对称加密
    非对称密钥加密也称为公钥加密，由一对公钥和私钥组成。公钥是从私钥提取出来的。可
    以用公钥加密，再用私钥解密，这种情形一般用于公钥加密，当然也可以用私钥加密，用公钥解
    密。常用于数字签名，因此非对称加密的主要功能就是加密和数字签名。
    特征：
    1）秘钥对，公钥(public key)和私钥(secret key)
    2）主要功能：加密和签名
    发送方用对方的公钥加密，可以保证数据的机密性（公钥加密）。
    发送方用自己的私钥加密，可以实现身份验证（数字签名）。
    3）公钥加密算法很少用来加密数据，速度太慢，通常用来实现身份验证。
    常用的非对称加密算法
    RSA：由 RSA 公司发明，是一个支持变长密钥的公共密钥算法，需要加密的文件块的长度也
    是可变的；既可以实现加密，又可以实现签名。
    DSA（Digital Signature Algorithm）：数字签名算法，是一种标准的 DSS（数字签名标准）。   
    ECC（Elliptic Curves Cryptography）：椭圆曲线密码编码。
    3、什么是 LRU 缓存
    LRU(最近最少使用)算法根据数据的历史访问记录来进行淘汰数据，其核心思想是“如果数
    据最近被访问过，那么将来被访问的几率也更高
    实现：使用一个链表保存缓存数据，将新数据插入到头部，每当缓存命中时，则将命中的数据移
    动到链表头部，当链表满的时候，将链表尾部的数据丢弃。

洗牌算法

    1、Fisher-Yates Shuffle 算法
    最早提出这个洗牌方法的是
    Ronald A. Fisher 和 Frank Yates，即Fisher–Yates Shuffle，
    其基本思想就是从原始数组中随机取一个之前没取过的数字到新的数组中，
    具体如下：
    1）初始化原始数组和新数组，原始数组长度为 n(已知)。
    2）从还没处理的数组（假如还剩 k 个）中，随机产生一个[0, k)之间的数字p（假设数组从 0 开始）。
    3）从剩下的 k 个数中把第 p 个数取出。
    4）重复步骤 2 和 3 直到数字全部取完。
    5）从步骤 3 取出的数字序列便是一个打乱了的数列。
    时间复杂度为 O(n*n)，空间复杂度为 O(n)。

    2）Knuth-Durstenfeld Shuffle Knuth 和 Durstenfeld
    在 Fisher 等人的基础上对算法进行了改进，在原始数组上对数字进行交互，
    省去了额外 O(n)的空间。该算法的基本思想和 Fisher 类似，每次从未处理的数据中随机取出一个数字，
    然后把该数字放在数组的尾部，即数组尾部存放的是已经处理过的数字。
    算法步骤为：
    1. 建立一个数组大小为 n 的数组 arr，分别存放 1 到 n 的数值；
    2. 生成一个从 0 到 n - 1 的随机数 x；   
    3. 输出 arr 下标为 x 的数值，即为第一个随机数；
    4. 将 arr 的尾元素和下标为 x 的元素互换；
    5. 同 2，生成一个从 0 到 n - 2 的随机数 x；
    6. 输出 arr 下标为 x 的数值，为第二个随机数；
    7. 将 arr 的倒数第二个元素和下标为 x 的元素互换；
    ……
    如上，直到输出 m 个数为止
    时间复杂度为 O(n)，空间复杂度为 O(1)，缺点必须知道数组长度 n。








