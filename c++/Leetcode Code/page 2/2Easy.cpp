/*
53. 最大子数组和

给你一个整数数组 nums ，请你找出一个具有最大和的连续子数组（子数组最少包含一个元素），返回其最大和。

子数组 是数组中的一个连续部分。

 

示例 1：

输入：nums = [-2,1,-3,4,-1,2,1,-5,4]
输出：6
解释：连续子数组 [4,-1,2,1] 的和最大，为 6 。

示例 2：

输入：nums = [1]
输出：1

示例 3：

输入：nums = [5,4,-1,7,8]
输出：23

 

提示：

    1 <= nums.length <= 105
    -104 <= nums[i] <= 104

code:
class Solution {
public:
    int maxSubArray(vector<int>& nums) {
        int pre = 0, maxAns = nums[0];
        for (int i=0;i<nums.size();i++){//auto &x: nums) {
            pre = max(pre + nums[i], nums[i]);
            maxAns = max(maxAns, pre);
        }
        return maxAns;
    }
};
*/

/*
58. 最后一个单词的长度

给你一个字符串 s，由若干单词组成，单词前后用一些空格字符隔开。返回字符串中最后一个单词的长度。

单词 是指仅由字母组成、不包含任何空格字符的最大子字符串。

 

示例 1：

输入：s = "Hello World"
输出：5

示例 2：

输入：s = "   fly me   to   the moon  "
输出：4

示例 3：

输入：s = "luffy is still joyboy"
输出：6

 

提示：

    1 <= s.length <= 104
    s 仅有英文字母和空格 ' ' 组成
    s 中至少存在一个单词

code:
class Solution {
public:
    int lengthOfLastWord(string s) {
        bool IsWord=false;
        int WordSize=0;
        for(int i=s.length()-1;i>=0;i--){
            if(IsWord && s[i]==' ')break;
            if(s[i]!=' '){
                IsWord=true;
                WordSize++;
            }
        }
        return WordSize;
    }
};
*/

/*
66. 加一

给定一个由 整数 组成的 非空 数组所表示的非负整数，在该数的基础上加一。

最高位数字存放在数组的首位， 数组中每个元素只存储单个数字。

你可以假设除了整数 0 之外，这个整数不会以零开头。

 

示例 1：

输入：digits = [1,2,3]
输出：[1,2,4]
解释：输入数组表示数字 123。

示例 2：

输入：digits = [4,3,2,1]
输出：[4,3,2,2]
解释：输入数组表示数字 4321。

示例 3：

输入：digits = [0]
输出：[1]

 

提示：

    1 <= digits.length <= 100
    0 <= digits[i] <= 9
code:
class Solution {
public:
    vector<int> plusOne(vector<int>& digits) {
        if(digits.back() < 9) {
            digits.back() = digits.back() + 1;
            return digits;
        }
        bool flag = false;
        for(int i = digits.size() - 1 ; i >= 0 ; -- i) {
            if(digits[i] == 9) digits[i] = 0,flag = true;
            else if(digits[i] != 9 && flag) {
                digits[i] += 1;
                flag = false;
                break;
            }
        }
        if(flag) digits.insert(digits.begin() , 1);
        return digits;
    }
};
*/

/*
67. 二进制求和

给你两个二进制字符串，返回它们的和（用二进制表示）。

输入为 非空 字符串且只包含数字 1 和 0。

 

示例 1:

输入: a = "11", b = "1"
输出: "100"

示例 2:

输入: a = "1010", b = "1011"
输出: "10101"

 

提示：

    每个字符串仅由字符 '0' 或 '1' 组成。
    1 <= a.length, b.length <= 10^4
    字符串如果不是 "0" ，就都不含前导零。

code:
class Solution {
public:
    string addBinary(string a, string b) {
        string ans;
        //倒转
        reverse(a.begin(), a.end());
        reverse(b.begin(), b.end());
        int n = max(a.size(), b.size()), carry = 0;
        for (size_t i = 0; i < n; ++i) {
            //size_t提高代码可移植性 有效性 可读性(表示为长度)
            if(i < a.size()){
                carry+=(a[i]=='1');
                //carry+=(a.at(i)=='1');
            }else carry+=0;
            // carry += i < a.size() ? (a.at(i) == '1') : 0;
            carry += i < b.size() ? (b.at(i) == '1') : 0;
            ans.push_back((carry % 2) ? '1' : '0');
            carry /= 2;
        }
        if (carry) ans.push_back('1');
        reverse(ans.begin(), ans.end());
        return ans;
    }
};
*/


/*
69. Sqrt(x)

给你一个非负整数 x ，计算并返回 x 的 算术平方根 。

由于返回类型是整数，结果只保留 整数部分 ，小数部分将被 舍去 。

注意：不允许使用任何内置指数函数和算符，例如 pow(x, 0.5) 或者 x ** 0.5 。

 

示例 1：

输入：x = 4
输出：2

示例 2：

输入：x = 8
输出：2
解释：8 的算术平方根是 2.82842..., 由于返回类型是整数，小数部分将被舍去。

 

提示：

    0 <= x <= 231 - 1

code:
class Solution {
public:
    int mySqrt(int x) {
        if(x==0)return 0;
        long long ans=exp(0.5*log(x));
        return (ans+1)*(ans+1)>x?ans:ans+1;
    }
};
*/

/*
70. 爬楼梯

假设你正在爬楼梯。需要 n 阶你才能到达楼顶。

每次你可以爬 1 或 2 个台阶。你有多少种不同的方法可以爬到楼顶呢？

注意：给定 n 是一个正整数。

示例 1：

输入： 2
输出： 2
解释： 有两种方法可以爬到楼顶。
1.  1 阶 + 1 阶
2.  2 阶

示例 2：

输入： 3
输出： 3
解释： 有三种方法可以爬到楼顶。
1.  1 阶 + 1 阶 + 1 阶
2.  1 阶 + 2 阶
3.  2 阶 + 1 阶

code:
class Solution {
public:
    int climbStairs(int n) {
        //斐波那契数列解法  
        if(n==1)return 1;
        else if(n==2)return 2;
        int first=1,second=2,third;
        for(int i=3;i<=n;i++){
            third=first+second;
            first=second;
            second=third;
        }
        return second;
    }
};
*/

/*
83. 删除排序链表中的重复元素

存在一个按升序排列的链表，给你这个链表的头节点 head ，请你删除所有重复的元素，使每个元素 只出现一次 。

返回同样按升序排列的结果链表。

 

示例 1：

输入：head = [1,1,2]
输出：[1,2]

示例 2：

输入：head = [1,1,2,3,3]
输出：[1,2,3]

 

提示：

    链表中节点数目在范围 [0, 300] 内
    -100 <= Node.val <= 100
    题目数据保证链表已经按升序排列

code:
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode() : val(0), next(nullptr) {}
 *     ListNode(int x) : val(x), next(nullptr) {}
 *     ListNode(int x, ListNode *next) : val(x), next(next) {}
 * };
class Solution {
public:
    ListNode* deleteDuplicates(ListNode* head) {
        if(!head)return head;
        ListNode * cur=head;
        while(cur->next){
            if(cur->val==cur->next->val){
                ListNode *temp=cur->next;
                cur->next=cur->next->next;
                delete temp;
            }
            else
            {
                cur=cur->next;
            }
        }
        return head;
    }
};
*/

/*
88. 合并两个有序数组

给你两个按 非递减顺序 排列的整数数组 nums1 和 nums2，另有两个整数 m 和 n ，分别表示 nums1 和 nums2 中的元素数目。

请你 合并 nums2 到 nums1 中，使合并后的数组同样按 非递减顺序 排列。

注意：最终，合并后数组不应由函数返回，而是存储在数组 nums1 中。为了应对这种情况，nums1 的初始长度为 m + n，其中前 m 个元素表示应合并的元素，后 n 个元素为 0 ，应忽略。nums2 的长度为 n 。

 

示例 1：

输入：nums1 = [1,2,3,0,0,0], m = 3, nums2 = [2,5,6], n = 3
输出：[1,2,2,3,5,6]
解释：需要合并 [1,2,3] 和 [2,5,6] 。
合并结果是 [1,2,2,3,5,6] ，其中斜体加粗标注的为 nums1 中的元素。

示例 2：

输入：nums1 = [1], m = 1, nums2 = [], n = 0
输出：[1]
解释：需要合并 [1] 和 [] 。
合并结果是 [1] 。

示例 3：

输入：nums1 = [0], m = 0, nums2 = [1], n = 1
输出：[1]
解释：需要合并的数组是 [] 和 [1] 。
合并结果是 [1] 。
注意，因为 m = 0 ，所以 nums1 中没有元素。nums1 中仅存的 0 仅仅是为了确保合并结果可以顺利存放到 nums1 中。

 

提示：

    nums1.length == m + n
    nums2.length == n
    0 <= m, n <= 200
    1 <= m + n <= 200
    -109 <= nums1[i], nums2[j] <= 109

code:
class Solution {
public:
    void merge(vector<int>& nums1, int m, vector<int>& nums2, int n) {
        for (int i = 0; i != n; ++i) {
            nums1[m + i] = nums2[i];
        }
        sort(nums1.begin(), nums1.end());
    }
};
*/

/*
94. 二叉树的中序遍历

给定一个二叉树的根节点 root ，返回它的 中序 遍历。

 

示例 1：

输入：root = [1,null,2,3]
输出：[1,3,2]

示例 2：

输入：root = []
输出：[]

示例 3：

输入：root = [1]
输出：[1]

示例 4：

输入：root = [1,2]
输出：[2,1]

示例 5：

输入：root = [1,null,2]
输出：[1,2]

 

提示：

    树中节点数目在范围 [0, 100] 内
    -100 <= Node.val <= 100

code:
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode() : val(0), left(nullptr), right(nullptr) {}
 *     TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
 *     TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
 * };
class Solution {
public:
    void inorder(TreeNode* root, vector<int>& res) {
        if (!root) return;
        inorder(root->left, res);
        res.push_back(root->val);
        inorder(root->right, res);
    }
    vector<int> inorderTraversal(TreeNode* root) {
        vector<int> res;
        inorder(root, res);
        return res;
    }
};
*/

/*
100. 相同的树

给你两棵二叉树的根节点 p 和 q ，编写一个函数来检验这两棵树是否相同。

如果两个树在结构上相同，并且节点具有相同的值，则认为它们是相同的。

 

示例 1：

输入：p = [1,2,3], q = [1,2,3]
输出：true

示例 2：

输入：p = [1,2], q = [1,null,2]
输出：false

示例 3：

输入：p = [1,2,1], q = [1,1,2]
输出：false

 

提示：

    两棵树上的节点数目都在范围 [0, 100] 内
    -104 <= Node.val <= 104

code:
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode() : val(0), left(nullptr), right(nullptr) {}
 *     TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
 *     TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
 * };
class Solution {
public:
    bool isSameTree(TreeNode* p, TreeNode* q) {
        if (p == nullptr && q == nullptr) return true;
        else if (p == nullptr || q == nullptr)return false;
        else if (p->val != q->val) return false;
        else return isSameTree(p->left, q->left) && isSameTree(p->right, q->right);
    }
};
*/