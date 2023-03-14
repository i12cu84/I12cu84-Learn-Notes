/*
101. 对称二叉树

给你一个二叉树的根节点 root ， 检查它是否轴对称。

 

示例 1：

输入：root = [1,2,2,3,4,4,3]
输出：true

示例 2：

输入：root = [1,2,2,null,3,null,3]
输出：false

 

提示：

    树中节点数目在范围 [1, 1000] 内
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
    bool check(TreeNode *p, TreeNode *q) {
        if (!p && !q) return true;
        if (!p || !q) return false;
        return p->val == q->val && 
        check(p->left, q->right) && 
        check(p->right, q->left);
    }
    bool isSymmetric(TreeNode* root) {
        return check(root, root);
    }
};
*/

/*
104. 二叉树的最大深度

给定一个二叉树，找出其最大深度。

二叉树的深度为根节点到最远叶子节点的最长路径上的节点数。

说明: 叶子节点是指没有子节点的节点。

示例：
给定二叉树 [3,9,20,null,null,15,7]，

    3
   / \
  9  20
    /  \
   15   7

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
    int maxDepth(TreeNode* root) {
        if (root == nullptr) return 0;
        return max(maxDepth(root->left), maxDepth(root->right)) + 1;
    }
};
*/

/*
108. 将有序数组转换为二叉搜索树

给你一个整数数组 nums ，其中元素已经按 升序 排列，请你将其转换为一棵 高度平衡 二叉搜索树。

高度平衡 二叉树是一棵满足「每个节点的左右两个子树的高度差的绝对值不超过 1 」的二叉树。

 

示例 1：

输入：nums = [-10,-3,0,5,9]
输出：[0,-3,9,-10,null,5]
解释：[0,-10,5,null,-3,null,9] 也将被视为正确答案：

示例 2：

输入：nums = [1,3]
输出：[3,1]
解释：[1,3] 和 [3,1] 都是高度平衡二叉搜索树。

 

提示：

    1 <= nums.length <= 104
    -104 <= nums[i] <= 104
    nums 按 严格递增 顺序排列

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
    TreeNode* sortedArrayToBST(vector<int>& nums) {
        return helper(nums, 0, nums.size() - 1);
    }
    TreeNode* helper(vector<int>& nums, int left, int right) {
        if (left > right) return nullptr;
        int mid = (left + right) / 2;
        TreeNode* root = new TreeNode(nums[mid]);
        root->left = helper(nums, left, mid - 1);
        root->right = helper(nums, mid + 1, right);
        return root;
    }
};
*/

/*
111. 二叉树的最小深度

给定一个二叉树，找出其最小深度。

最小深度是从根节点到最近叶子节点的最短路径上的节点数量。

说明：叶子节点是指没有子节点的节点。

示例 1：

输入：root = [3,9,20,null,null,15,7]
输出：2

示例 2：

输入：root = [2,null,3,null,4,null,5,null,6]
输出：5

提示：

    树中节点数的范围在 [0, 105] 内
    -1000 <= Node.val <= 1000

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
    int minDepth(TreeNode* root) {
        if (root == nullptr) return 0;
        if (root->left == nullptr && root->right == nullptr) return 1;
        int min_depth = INT_MAX;
        if (root->left != nullptr) min_depth = min(minDepth(root->left), min_depth);
        if (root->right != nullptr) min_depth = min(minDepth(root->right), min_depth);
        return min_depth + 1;
    }
};
*/

/*
112. 路径总和

给你二叉树的根节点 root 和一个表示目标和的整数 targetSum 。判断该树中是否存在 根节点到叶子节点 的路径，这条路径上所有节点值相加等于目标和 targetSum 。如果存在，返回 true ；否则，返回 false 。

叶子节点 是指没有子节点的节点。

 

示例 1：

输入：root = [5,4,8,11,null,13,4,7,2,null,null,null,1], targetSum = 22
输出：true
解释：等于目标和的根节点到叶节点路径如上图所示。

示例 2：

输入：root = [1,2,3], targetSum = 5
输出：false
解释：树中存在两条根节点到叶子节点的路径：
(1 --> 2): 和为 3
(1 --> 3): 和为 4
不存在 sum = 5 的根节点到叶子节点的路径。

示例 3：

输入：root = [], targetSum = 0
输出：false
解释：由于树是空的，所以不存在根节点到叶子节点的路径。

 提示：

    树中节点的数目在范围 [0, 5000] 内
    -1000 <= Node.val <= 1000
    -1000 <= targetSum <= 1000

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
    bool hasPathSum(TreeNode* root, int targetSum) {
        if(!root) return false;
        targetSum -= root->val; 
        if(!root->left && !root->right)  return targetSum==0;
        return hasPathSum(root->left, targetSum) || hasPathSum(root->right, targetSum);
    }
};
*/

/*
118. 杨辉三角

给定一个非负整数 numRows，生成「杨辉三角」的前 numRows 行。

在「杨辉三角」中，每个数是它左上方和右上方的数的和。

 

示例 1:

输入: numRows = 5
输出: [[1],[1,1],[1,2,1],[1,3,3,1],[1,4,6,4,1]]

示例 2:

输入: numRows = 1
输出: [[1]]

 

提示:

    1 <= numRows <= 30

code:
class Solution {
public:
    vector<vector<int>> generate(int numRows) {
        vector<vector<int>> ret(numRows);
        for (int i = 0; i < numRows; ++i) {
            ret[i].resize(i + 1);//设置容量
            ret[i][0] = ret[i][i] = 1;
            for (int j = 1; j < i; ++j)
                ret[i][j] = ret[i - 1][j] + ret[i - 1][j - 1];
        }
        return ret;
    }
};
*/

/*
119. 杨辉三角 II

给定一个非负索引 rowIndex，返回「杨辉三角」的第 rowIndex 行。

在「杨辉三角」中，每个数是它左上方和右上方的数的和。

 

示例 1:

输入: rowIndex = 3
输出: [1,3,3,1]

示例 2:

输入: rowIndex = 0
输出: [1]

示例 3:

输入: rowIndex = 1
输出: [1,1]

 

提示:

    0 <= rowIndex <= 33

 

进阶：

你可以优化你的算法到 O(rowIndex) 空间复杂度吗？

code:
class Solution {
public:
    vector<int> getRow(int rowIndex) {
        vector<vector<int>> C(rowIndex + 1);
        for (int i = 0; i <= rowIndex; ++i) {
            C[i].resize(i + 1);
            C[i][0] = C[i][i] = 1;
            for (int j = 1; j < i; ++j)
                C[i][j] = C[i - 1][j - 1] + C[i - 1][j];
        }
        return C[rowIndex];
    }
};
*/

/*
121. 买卖股票的最佳时机

给定一个数组 prices ，它的第 i 个元素 prices[i] 表示一支给定股票第 i 天的价格。

你只能选择 某一天 买入这只股票，并选择在 未来的某一个不同的日子 卖出该股票。设计一个算法来计算你所能获取的最大利润。

返回你可以从这笔交易中获取的最大利润。如果你不能获取任何利润，返回 0 。

 

示例 1：

输入：[7,1,5,3,6,4]
输出：5
解释：在第 2 天（股票价格 = 1）的时候买入，在第 5 天（股票价格 = 6）的时候卖出，最大利润 = 6-1 = 5 。
     注意利润不能是 7-1 = 6, 因为卖出价格需要大于买入价格；同时，你不能在买入前卖出股票。

示例 2：

输入：prices = [7,6,4,3,1]
输出：0
解释：在这种情况下, 没有交易完成, 所以最大利润为 0。

 

提示：

    1 <= prices.length <= 105
    0 <= prices[i] <= 104

code:
class Solution {
public:
    int maxProfit(vector<int>& prices) {
        int inf = 1e9 , minprice = inf, maxprofit = 0;
        for (int price: prices) 
            maxprofit = max(maxprofit, price - minprice),
            minprice = min(price, minprice);
        return maxprofit;
    }
};
*/

/*
125. 验证回文串

给定一个字符串，验证它是否是回文串，只考虑字母和数字字符，可以忽略字母的大小写。

说明：本题中，我们将空字符串定义为有效的回文串。

 

示例 1:

输入: "A man, a plan, a canal: Panama"
输出: true
解释："amanaplanacanalpanama" 是回文串

示例 2:

输入: "race a car"
输出: false
解释："raceacar" 不是回文串

 

提示：

    1 <= s.length <= 2 * 105
    字符串 s 由 ASCII 字符组成

code:
class Solution {
public:
    bool isPalindrome(string s) {
        int n = s.size(), left = 0, right = n - 1;
        //方法3
        while(left<right){
            while(!isalnum(s[left])){
                left++;
                if(left>=right)
                    return true;
            }
            while(!isalnum(s[right]))
                right--;
            if(tolower((char)s[left])!=tolower((char)s[right]))
                return false;
            left++;
            right--;
        }
        return true;
        // //方法2
        // string sgood;
        // for (char ch: s) 
        //     if (isalnum(ch)) 
        //         sgood += tolower(ch);
        // // //方法3
        // // int n = sgood.size(), left = 0, right = n - 1;
        // // while (left < right) {
        // //    if (sgood[left] != sgood[right]) 
        // //         return false;
        // //     ++left;
        // //     --right;
        // // }
        // // return true;
        // string sgood_rev(sgood.rbegin(), sgood.rend());
        // return sgood == sgood_rev;
    }
};
*/

/*
136. 只出现一次的数字

给定一个非空整数数组，除了某个元素只出现一次以外，其余每个元素均出现两次。找出那个只出现了一次的元素。

说明：

你的算法应该具有线性时间复杂度。 你可以不使用额外空间来实现吗？

示例 1:

输入: [2,2,1]
输出: 1

示例 2:

输入: [4,1,2,1,2]
输出: 4

code:
class Solution {
public:
    int singleNumber(vector<int>& nums) {
        int ret = 0;
        for (int e: nums) ret ^= e;
        return ret;
    }
};
*/

/*
141. 环形链表

给你一个链表的头节点 head ，判断链表中是否有环。

如果链表中有某个节点，可以通过连续跟踪 next 指针再次到达，则链表中存在环。 为了表示给定链表中的环，评测系统内部使用整数 pos 来表示链表尾连接到链表中的位置（索引从 0 开始）。注意：pos 不作为参数进行传递 。仅仅是为了标识链表的实际情况。

如果链表中存在环 ，则返回 true 。 否则，返回 false 。

 

示例 1：

输入：head = [3,2,0,-4], pos = 1
输出：true
解释：链表中有一个环，其尾部连接到第二个节点。

示例 2：

输入：head = [1,2], pos = 0
输出：true
解释：链表中有一个环，其尾部连接到第一个节点。

示例 3：

输入：head = [1], pos = -1
输出：false
解释：链表中没有环。

 

提示：

    链表中节点的数目范围是 [0, 104]
    -105 <= Node.val <= 105
    pos 为 -1 或者链表中的一个 有效索引 。

 

进阶：你能用 O(1)（即，常量）内存解决此问题吗？

code:
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode(int x) : val(x), next(NULL) {}
 * };
class Solution {
public:
    bool hasCycle(ListNode *head) {
        if(head==NULL || head->next==NULL)return false;
        ListNode *one=head;
        ListNode *two=head->next;
        while(one!=two){
            if(two==NULL || two->next==NULL)return false;
            one=one->next;
            two=two->next->next;
        }
        return true;
    }
};
*/

/*
144. 二叉树的前序遍历

给你二叉树的根节点 root ，返回它节点值的 前序 遍历。

 

示例 1：

输入：root = [1,null,2,3]
输出：[1,2,3]

示例 2：

输入：root = []
输出：[]

示例 3：

输入：root = [1]
输出：[1]

示例 4：

输入：root = [1,2]
输出：[1,2]

示例 5：

输入：root = [1,null,2]
输出：[1,2]

 

提示：

    树中节点数目在范围 [0, 100] 内
    -100 <= Node.val <= 100

 

进阶：递归算法很简单，你可以通过迭代算法完成吗？

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
    vector<int> preorderTraversal(TreeNode *root) {
        vector<int> res;
        preorder(root, res);
        return res;
    }
    void preorder(TreeNode *root, vector<int> &res) {
        if (root == NULL) return;
        res.push_back(root->val);
        preorder(root->left, res);
        preorder(root->right, res);
    }
};
*/

/*
145. 二叉树的后序遍历

给你一棵二叉树的根节点 root ，返回其节点值的 后序遍历 。

 

示例 1：

输入：root = [1,null,2,3]
输出：[3,2,1]

示例 2：

输入：root = []
输出：[]

示例 3：

输入：root = [1]
输出：[1]

 

提示：

    树中节点的数目在范围 [0, 100] 内
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
    vector<int> postorderTraversal(TreeNode* root) {
        vector<int> res;
        preorder(root, res);
        return res;
    }
    void preorder(TreeNode *root, vector<int> &res) {
        if (root == NULL) return;
        preorder(root->left, res);
        preorder(root->right, res);
        res.push_back(root->val);
    }
};
*/