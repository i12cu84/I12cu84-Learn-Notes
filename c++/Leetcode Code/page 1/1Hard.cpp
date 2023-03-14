/*
4. 寻找两个正序数组的中位数

给定两个大小分别为 m 和 n 的正序（从小到大）数组 nums1 和 nums2。请你找出并返回这两个正序数组的 中位数 。

算法的时间复杂度应该为 O(log (m+n)) 。

 

示例 1：

输入：nums1 = [1,3], nums2 = [2]
输出：2.00000
解释：合并数组 = [1,2,3] ，中位数 2

示例 2：

输入：nums1 = [1,2], nums2 = [3,4]
输出：2.50000
解释：合并数组 = [1,2,3,4] ，中位数 (2 + 3) / 2 = 2.5

示例 3：

输入：nums1 = [0,0], nums2 = [0,0]
输出：0.00000

示例 4：

输入：nums1 = [], nums2 = [1]
输出：1.00000

示例 5：

输入：nums1 = [2], nums2 = []
输出：2.00000

 

提示：

    nums1.length == m
    nums2.length == n
    0 <= m <= 1000
    0 <= n <= 1000
    1 <= m + n <= 2000
    -106 <= nums1[i], nums2[i] <= 106

code:
class Solution {
public:
    int getKthElement(const vector<int>& nums1, const vector<int>& nums2, int k) {
        int m = nums1.size(), n = nums2.size(), index1 = 0, index2 = 0;
        while (true) {
            if (index1 == m) return nums2[index2 + k - 1];
            if (index2 == n) return nums1[index1 + k - 1];
            if (k == 1) return min(nums1[index1], nums2[index2]);
            int newIndex1 = min(index1 + k / 2 - 1, m - 1), newIndex2 = min(index2 + k / 2 - 1, n - 1);
            int pivot1 = nums1[newIndex1], pivot2 = nums2[newIndex2];
            if (pivot1 <= pivot2) k -= newIndex1 - index1 + 1, index1 = newIndex1 + 1;
            else k -= newIndex2 - index2 + 1, index2 = newIndex2 + 1;
        }
    }
    double findMedianSortedArrays(vector<int>& nums1, vector<int>& nums2) {
        int totalLength = nums1.size() + nums2.size();
        if (totalLength % 2 == 1) return getKthElement(nums1, nums2, (totalLength + 1) / 2);
        else return (getKthElement(nums1, nums2, totalLength / 2) + getKthElement(nums1, nums2, totalLength / 2 + 1)) / 2.0;
    }
};
*/

/*
10. 正则表达式匹配

给你一个字符串 s 和一个字符规律 p，请你来实现一个支持 '.' 和 '*' 的正则表达式匹配。

    '.' 匹配任意单个字符
    '*' 匹配零个或多个前面的那一个元素

所谓匹配，是要涵盖 整个 字符串 s的，而不是部分字符串。
 

示例 1：

输入：s = "aa", p = "a"
输出：false
解释："a" 无法匹配 "aa" 整个字符串。

示例 2:

输入：s = "aa", p = "a*"
输出：true
解释：因为 '*' 代表可以匹配零个或多个前面的那一个元素, 在这里前面的元素就是 'a'。因此，字符串 "aa" 可被视为 'a' 重复了一次。

示例 3：

输入：s = "ab", p = ".*"
输出：true
解释：".*" 表示可匹配零个或多个（'*'）任意字符（'.'）。

 

提示：

    1 <= s.length <= 20
    1 <= p.length <= 30
    s 只包含从 a-z 的小写字母。
    p 只包含从 a-z 的小写字母，以及字符 . 和 *。
    保证每次出现字符 * 时，前面都匹配到有效的字符

code:
//code 1 
class Solution {
public:
    bool isMatch(string s, string p) {
        int m = s.size(), n = p.size();
        vector<vector<int>> f(m + 1, vector<int>(n + 1));
        f[0][0] = true;
        for (int i = 0; i <= m; ++i) 
            for (int j = 1; j <= n; ++j) 
                if (p[j - 1] == '*') {
                    f[i][j] |= f[i][j - 2];
                    if (matches(i, j - 1, p, s)) f[i][j] |= f[i - 1][j];
                }
                else if (matches(i, j, p, s)) f[i][j] |= f[i - 1][j - 1];
        return f[m][n];
    }
    bool matches (int i, int j,string p,string s) {
        if (i == 0) return false;
        if (p[j - 1] == '.') return true;
        return s[i - 1] == p[j - 1];
    }
};
//code 2 优化后 lambda用法
class Solution {
public:
    bool isMatch(string s, string p) {
        int m = s.size(), n = p.size();
        auto matches = [&](int i, int j) {
            if (i == 0) return false;
            if (p[j - 1] == '.') return true;
            return s[i - 1] == p[j - 1];
        };
        vector<vector<int>> f(m + 1, vector<int>(n + 1));
        f[0][0] = true;
        for (int i = 0; i <= m; ++i) 
            for (int j = 1; j <= n; ++j) 
                if (p[j - 1] == '*') {
                    f[i][j] |= f[i][j - 2];
                    if (matches(i, j - 1)) f[i][j] |= f[i - 1][j];
                }
                else if (matches(i, j)) f[i][j] |= f[i - 1][j - 1];
        return f[m][n];
    }
};
*/

/*
23. 合并K个升序链表

给你一个链表数组，每个链表都已经按升序排列。

请你将所有链表合并到一个升序链表中，返回合并后的链表。

 

示例 1：

输入：lists = [[1,4,5],[1,3,4],[2,6]]
输出：[1,1,2,3,4,4,5,6]
解释：链表数组如下：
[
  1->4->5,
  1->3->4,
  2->6
]
将它们合并到一个有序链表中得到。
1->1->2->3->4->4->5->6

示例 2：

输入：lists = []
输出：[]

示例 3：

输入：lists = [[]]
输出：[]

 

提示：

    k == lists.length
    0 <= k <= 10^4
    0 <= lists[i].length <= 500
    -10^4 <= lists[i][j] <= 10^4
    lists[i] 按 升序 排列
    lists[i].length 的总和不超过 10^4

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
    struct Status {
        int val;
        ListNode *ptr;
        bool operator < (const Status &rhs) const {
            return val > rhs.val;
        }
    };
    priority_queue <Status> q;
    ListNode* mergeKLists(vector<ListNode*>& lists) {
        for (auto node: lists) 
            if (node) 
                q.push({node->val, node});
        ListNode head, *tail = &head;
        while (!q.empty()) {
            auto f = q.top(); 
            q.pop();
            tail->next = f.ptr; 
            tail = tail->next;
            if (f.ptr->next) 
                q.push({f.ptr->next->val, f.ptr->next});
        }
        return head.next;
    }
};
*/

/*
25. K 个一组翻转链表

给你一个链表，每 k 个节点一组进行翻转，请你返回翻转后的链表。

k 是一个正整数，它的值小于或等于链表的长度。

如果节点总数不是 k 的整数倍，那么请将最后剩余的节点保持原有顺序。

进阶：

    你可以设计一个只使用常数额外空间的算法来解决此问题吗？
    你不能只是单纯的改变节点内部的值，而是需要实际进行节点交换。

 

示例 1：

输入：head = [1,2,3,4,5], k = 2
输出：[2,1,4,3,5]

示例 2：

输入：head = [1,2,3,4,5], k = 3
输出：[3,2,1,4,5]

示例 3：

输入：head = [1,2,3,4,5], k = 1
输出：[1,2,3,4,5]

示例 4：

输入：head = [1], k = 1
输出：[1]

提示：

    列表中节点的数量在范围 sz 内
    1 <= sz <= 5000
    0 <= Node.val <= 1000
    1 <= k <= sz

code:
*/