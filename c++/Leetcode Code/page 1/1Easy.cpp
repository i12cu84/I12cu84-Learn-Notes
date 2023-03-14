/*
1. 两数之和

给定一个整数数组 nums 和一个整数目标值 target，请你在该数组中找出 和为目标值 target  的那 两个 整数，并返回它们的数组下标。

你可以假设每种输入只会对应一个答案。但是，数组中同一个元素在答案里不能重复出现。

你可以按任意顺序返回答案。

 

示例 1：

输入：nums = [2,7,11,15], target = 9
输出：[0,1]
解释：因为 nums[0] + nums[1] == 9 ，返回 [0, 1] 。

示例 2：

输入：nums = [3,2,4], target = 6
输出：[1,2]

示例 3：

输入：nums = [3,3], target = 6
输出：[0,1]

 

提示：

    2 <= nums.length <= 104
    -109 <= nums[i] <= 109
    -109 <= target <= 109
    只会存在一个有效答案

进阶：你可以想出一个时间复杂度小于 O(n2) 的算法吗？

code:
class Solution {
public:
    vector<int> twoSum(vector<int>& nums, int target) {
        int i,j;
        for(i=0;i<nums.size();i++)
            for(j=i+1;j<nums.size();j++)
                if(nums[i]+nums[j]==target)
                    return {i,j};
        return {};
    }
};

*/

/*
7. 整数反转

给你一个 32 位的有符号整数 x ，返回将 x 中的数字部分反转后的结果。

如果反转后整数超过 32 位的有符号整数的范围 [?231,  231 ? 1] ，就返回 0。
假设环境不允许存储 64 位整数（有符号或无符号）。

 

示例 1：

输入：x = 123
输出：321

示例 2：

输入：x = -123
输出：-321

示例 3：

输入：x = 120
输出：21

示例 4：

输入：x = 0
输出：0

 

提示：

    -231 <= x <= 231 - 1

code:
class Solution {
public:
    int reverse(int x) {
        int y = 0;
        while (x != 0) {
            if (y > 214748364 || y < -214748364) {
                return 0;
            }
            y = y * 10 + x % 10;
            x = x / 10;
        }
        return y;
    }
};

*/

/*
9. 回文数

给你一个整数 x ，如果 x 是一个回文整数，返回 true ；否则，返回 false 。

回文数是指正序（从左向右）和倒序（从右向左）读都是一样的整数。例如，121 是回文，而 123 不是。

 

示例 1：

输入：x = 121
输出：true

示例 2：

输入：x = -121
输出：false
解释：从左向右读, 为 -121 。 从右向左读, 为 121- 。因此它不是一个回文数。

示例 3：

输入：x = 10
输出：false
解释：从右向左读, 为 01 。因此它不是一个回文数。

示例 4：

输入：x = -101
输出：false

 

提示：

    -231 <= x <= 231 - 1

 

进阶：你能不将整数转为字符串来解决这个问题吗？

code:
class Solution {
public:
    bool isPalindrome(int x) {
        if(x<0 || (x%10==0 && x!=0))return false;
        int y=0;
        while(!(x<=y)){
            y=y*10+x%10;
            x=x/10;
        }
        if(x==y/10 || x==y)return true;
        else return false;
    }
};

*/

/*
13. 罗马数字转整数

罗马数字包含以下七种字符: I， V， X， L，C，D 和 M。

字符          数值
I             1
V             5
X             10
L             50
C             100
D             500
M             1000

例如， 罗马数字 2 写做 II ，即为两个并列的 1 。12 写做 XII ，即为 X + II 。 27 写做  XXVII, 即为 XX + V + II 。

通常情况下，罗马数字中小的数字在大的数字的右边。但也存在特例，例如 4 不写做 IIII，而是 IV。数字 1 在数字 5 的左边，所表示的数等于大数 5 减小数 1 得到的数值 4 。同样地，数字 9 表示为 IX。这个特殊的规则只适用于以下六种情况：

    I 可以放在 V (5) 和 X (10) 的左边，来表示 4 和 9。
    X 可以放在 L (50) 和 C (100) 的左边，来表示 40 和 90。 
    C 可以放在 D (500) 和 M (1000) 的左边，来表示 400 和 900。

给定一个罗马数字，将其转换成整数。

 

示例 1:

输入: s = "III"
输出: 3

示例 2:

输入: s = "IV"
输出: 4

示例 3:

输入: s = "IX"
输出: 9

示例 4:

输入: s = "LVIII"
输出: 58
解释: L = 50, V= 5, III = 3.

示例 5:

输入: s = "MCMXCIV"
输出: 1994
解释: M = 1000, CM = 900, XC = 90, IV = 4.

 

提示：

    1 <= s.length <= 15
    s 仅含字符 ('I', 'V', 'X', 'L', 'C', 'D', 'M')
    题目数据保证 s 是一个有效的罗马数字，且表示整数在范围 [1, 3999] 内
    题目所给测试用例皆符合罗马数字书写规则，不会出现跨位等情况。
    IL 和 IM 这样的例子并不符合题目要求，49 应该写作 XLIX，999 应该写作 CMXCIX 。
    关于罗马数字的详尽书写规则，可以参考 罗马数字 - Mathematics 。

code:
class Solution {
public:
    int romanToInt(string s) {
        int t =s.size();
        int num=0;
        for(int i=0;i<t;i++)
            if(s[i]=='V') num+=5;
            else if(s[i]=='L') num+=50;
            else if(s[i]=='D') num+=500;
            else if(s[i]=='M') num+=1000;
            else if(s[i]=='I')(s[i+1]=='V'||s[i+1]=='X')?num-=1:num+=1;
            else if(s[i]=='X')(s[i+1]=='L'||s[i+1]=='C')?num-=10:num+=10;
            else if(s[i]=='C')(s[i+1]=='D'||s[i+1]=='M')?num-=100:num+=100;
        return num;
    }
};

*/

/*
14. 最长公共前缀

编写一个函数来查找字符串数组中的最长公共前缀。

如果不存在公共前缀，返回空字符串 ""。

 

示例 1：

输入：strs = ["flower","flow","flight"]
输出："fl"

示例 2：

输入：strs = ["dog","racecar","car"]
输出：""
解释：输入不存在公共前缀。

 

提示：

    1 <= strs.length <= 200
    0 <= strs[i].length <= 200
    strs[i] 仅由小写英文字母组成

code:
class Solution {
public:
    string longestCommonPrefix(vector<string>& strs) {
        int len=0,i=1;
        string s=strs[0];
        while(len<=s.size()){
            for(i=1;i<strs.size();i++){
                if(s[len]!=strs[i][len])
                    return s.substr(0,len);
            }
            len++;
        }
        return s;
    }
};

*/

/*
20. 有效的括号

给定一个只包括 '('，')'，'{'，'}'，'['，']' 的字符串 s ，判断字符串是否有效。

有效字符串需满足：

    左括号必须用相同类型的右括号闭合。
    左括号必须以正确的顺序闭合。

 

示例 1：

输入：s = "()"
输出：true

示例 2：

输入：s = "()[]{}"
输出：true

示例 3：

输入：s = "(]"
输出：false

示例 4：

输入：s = "([)]"
输出：false

示例 5：

输入：s = "{[]}"
输出：true

 

提示：

    1 <= s.length <= 104
    s 仅由括号 '()[]{}' 组成

code:
class Solution {
public:
    bool isValid(string s) {
        if (s.size() % 2 == 1) return false;
        unordered_map<char, char> pairs = {{')', '('},{']', '['},{'}', '{'}};
        stack<char> stk;
        for (char ch: s) 
            if (pairs.count(ch)) {
                if (stk.empty() || stk.top() != pairs[ch]) return false;
                stk.pop();
            }
            else stk.push(ch);
        return stk.empty();
    }
};

*/

/*
21. 合并两个有序链表

将两个升序链表合并为一个新的 升序 链表并返回。新链表是通过拼接给定的两个链表的所有节点组成的。 

 

示例 1：

输入：l1 = [1,2,4], l2 = [1,3,4]
输出：[1,1,2,3,4,4]

示例 2：

输入：l1 = [], l2 = []
输出：[]

示例 3：

输入：l1 = [], l2 = [0]
输出：[0]

 

提示：

    两个链表的节点数目范围是 [0, 50]
    -100 <= Node.val <= 100
    l1 和 l2 均按 非递减顺序 排列

code:
//
//Definition for singly-linked list.
//struct ListNode {
//    int val;
//    ListNode *next;
//    ListNode() : val(0), next(nullptr) {}
//    ListNode(int x) : val(x), next(nullptr) {}
//    ListNode(int x, ListNode *next) : val(x), next(next) {}
//};
//
class Solution {
public:
    ListNode* mergeTwoLists(ListNode* list1, ListNode* list2) {
        if(list1==nullptr){
            return list2;
        }else if(list2==nullptr){
            return list1;
        }else if(list1->val<list2->val){
            list1->next=mergeTwoLists(list1->next,list2);
            return list1;
        }else{
            list2->next=mergeTwoLists(list1,list2->next);
            return list2;
        }
    }
};

*/

/*
26. 删除有序数组中的重复项

给你一个有序数组 nums ，请你 原地 删除重复出现的元素，使每个元素 只出现一次 ，返回删除后数组的新长度。

不要使用额外的数组空间，你必须在 原地 修改输入数组 并在使用 O(1) 额外空间的条件下完成。

 

说明:

为什么返回数值是整数，但输出的答案是数组呢?

请注意，输入数组是以「引用」方式传递的，这意味着在函数里修改输入数组对于调用者是可见的。

你可以想象内部操作如下:

// nums 是以“引用”方式传递的。也就是说，不对实参做任何拷贝
int len = removeDuplicates(nums);

// 在函数里修改输入数组对于调用者是可见的。
// 根据你的函数返回的长度, 它会打印出数组中 该长度范围内 的所有元素。
for (int i = 0; i < len; i++) {
    print(nums[i]);
}

 

示例 1：

输入：nums = [1,1,2]
输出：2, nums = [1,2]
解释：函数应该返回新的长度 2 ，并且原数组 nums 的前两个元素被修改为 1, 2 。不需要考虑数组中超出新长度后面的元素。

示例 2：

输入：nums = [0,0,1,1,1,2,2,3,3,4]
输出：5, nums = [0,1,2,3,4]
解释：函数应该返回新的长度 5 ， 并且原数组 nums 的前五个元素被修改为 0, 1, 2, 3, 4 。不需要考虑数组中超出新长度后面的元素。

 

提示：

    0 <= nums.length <= 3 * 104
    -104 <= nums[i] <= 104
    nums 已按升序排列

code:
class Solution {//stl解法
public:
    int removeDuplicates(vector<int>& nums) {
        vector<int> q;
        vector<int>::iterator v;
        int num=0,now=-1;
        bool hasmath=false;
        for(v=nums.begin();v!=nums.end();v++){
            if(!hasmath){
                hasmath=true;
                now=*v;
                num++;
                q.push_back(*v);
                continue;
            }
            if(now!=(*v)){
                now=*v;
                num++;
                q.push_back(*v);
            }
        }
        nums=q;
        return num;
    }
};

//stl的erase和unique
class Solution {
public:
    int removeDuplicates(vector<int>& nums) {
        nums.erase(unique(nums.begin(),nums.end()),nums.end());
        return nums.size();
    }
};

*/

/*
27. 移除元素

给你一个数组 nums 和一个值 val，你需要 原地 移除所有数值等于 val 的元素，并返回移除后数组的新长度。

不要使用额外的数组空间，你必须仅使用 O(1) 额外空间并 原地 修改输入数组。

元素的顺序可以改变。你不需要考虑数组中超出新长度后面的元素。

 

说明:

为什么返回数值是整数，但输出的答案是数组呢?

请注意，输入数组是以「引用」方式传递的，这意味着在函数里修改输入数组对于调用者是可见的。

你可以想象内部操作如下:

// nums 是以“引用”方式传递的。也就是说，不对实参作任何拷贝
int len = removeElement(nums, val);

// 在函数里修改输入数组对于调用者是可见的。
// 根据你的函数返回的长度, 它会打印出数组中 该长度范围内 的所有元素。
for (int i = 0; i < len; i++) {
    print(nums[i]);
}

 

示例 1：

输入：nums = [3,2,2,3], val = 3
输出：2, nums = [2,2]
解释：函数应该返回新的长度 2, 并且 nums 中的前两个元素均为 2。你不需要考虑数组中超出新长度后面的元素。例如，函数返回的新长度为 2 ，而 nums = [2,2,3,3] 或 nums = [2,2,0,0]，也会被视作正确答案。

示例 2：

输入：nums = [0,1,2,2,3,0,4,2], val = 2
输出：5, nums = [0,1,4,0,3]
解释：函数应该返回新的长度 5, 并且 nums 中的前五个元素为 0, 1, 3, 0, 4。注意这五个元素可为任意顺序。你不需要考虑数组中超出新长度后面的元素。

 

提示：

    0 <= nums.length <= 100
    0 <= nums[i] <= 50
    0 <= val <= 100

code:
class Solution {
public:
    int removeElement(vector<int>& nums, int val) {
        int n=nums.size(),l=0;
        for(int r=0;r<n;r++){
            if(nums[r]!=val){
                nums[l]=nums[r];
                l++;
            }
        }
        return l;
    }
};
*/

/*
28. 实现 strStr()

实现 strStr() 函数。

给你两个字符串 haystack 和 needle ，请你在 haystack 字符串中找出 needle 字符串出现的第一个位置（下标从 0 开始）。如果不存在，则返回  -1 。

 

说明：

当 needle 是空字符串时，我们应当返回什么值呢？这是一个在面试中很好的问题。

对于本题而言，当 needle 是空字符串时我们应当返回 0 。这与 C 语言的 strstr() 以及 Java 的 indexOf() 定义相符。

 

示例 1：

输入：haystack = "hello", needle = "ll"
输出：2

示例 2：

输入：haystack = "aaaaa", needle = "bba"
输出：-1

示例 3：

输入：haystack = "", needle = ""
输出：0

 

提示：

    0 <= haystack.length, needle.length <= 5 * 104
    haystack 和 needle 仅由小写英文字符组成

code:
class Solution {
public:
    int strStr(string haystack, string needle) {
        bool flag;
        for (int i = 0; i + needle.length() <= haystack.length(); i++) {
            flag = true;
            for (int j = 0; j < needle.length(); j++) {
                if (haystack[i + j] != needle[j]) {
                    flag = false;
                    break;
                }
            }
            if (flag) {
                return i;
            }
        }
        return -1;
    }
};
*/

/*
35. 搜索插入位置

给定一个排序数组和一个目标值，在数组中找到目标值，并返回其索引。如果目标值不存在于数组中，返回它将会被按顺序插入的位置。

请必须使用时间复杂度为 O(log n) 的算法。

 

示例 1:

输入: nums = [1,3,5,6], target = 5
输出: 2

示例 2:

输入: nums = [1,3,5,6], target = 2
输出: 1

示例 3:

输入: nums = [1,3,5,6], target = 7
输出: 4

示例 4:

输入: nums = [1,3,5,6], target = 0
输出: 0

示例 5:

输入: nums = [1], target = 0
输出: 0

 

提示:

    1 <= nums.length <= 104
    -104 <= nums[i] <= 104
    nums 为无重复元素的升序排列数组
    -104 <= target <= 104

code:
class Solution {
public:
    int searchInsert(vector<int>& nums, int target) {
        int left=0,right=nums.size()-1,ans=nums.size();
        while(left<=right){
            int mid=(left+right)/2;
            if(target<=nums[mid]){
                ans=mid;
                right=mid-1;
            }else{
                left=mid+1;
            }
        }
        return ans;
    }
};
*/