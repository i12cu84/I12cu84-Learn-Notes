/*
54. 螺旋矩阵

给你一个 m 行 n 列的矩阵 matrix ，请按照 顺时针螺旋顺序 ，返回矩阵中的所有元素。

 

示例 1：

输入：matrix = [[1,2,3],[4,5,6],[7,8,9]]
输出：[1,2,3,6,9,8,7,4,5]

示例 2：

输入：matrix = [[1,2,3,4],[5,6,7,8],[9,10,11,12]]
输出：[1,2,3,4,8,12,11,10,9,5,6,7]

 

提示：

    m == matrix.length
    n == matrix[i].length
    1 <= m, n <= 10
    -100 <= matrix[i][j] <= 100

code:class Solution {
public:
    vector<int> spiralOrder(vector<vector<int>>& matrix) {
        if (matrix.size() == 0 || matrix[0].size() == 0) return {};
        int rows = matrix.size(), columns = matrix[0].size();
        vector<int> order;
        int left = 0, right = columns - 1, top = 0, bottom = rows - 1;
        while (left <= right && top <= bottom) {
            for (int column = left; column <= right; column++) 
                order.push_back(matrix[top][column]);
            for (int row = top + 1; row <= bottom; row++) 
                order.push_back(matrix[row][right]);
            if (left < right && top < bottom) {
                for (int column = right - 1; column > left; column--) 
                    order.push_back(matrix[bottom][column]);
                for (int row = bottom; row > top; row--) 
                    order.push_back(matrix[row][left]);
            }
            left++;
            right--;
            top++;
            bottom--;
        }
        return order;
    }
};
*/

/*
55. 跳跃游戏

给定一个非负整数数组 nums ，你最初位于数组的 第一个下标 。

数组中的每个元素代表你在该位置可以跳跃的最大长度。

判断你是否能够到达最后一个下标。

 

示例 1：

输入：nums = [2,3,1,1,4]
输出：true
解释：可以先跳 1 步，从下标 0 到达下标 1, 然后再从下标 1 跳 3 步到达最后一个下标。

示例 2：

输入：nums = [3,2,1,0,4]
输出：false
解释：无论怎样，总会到达下标为 3 的位置。但该下标的最大跳跃长度是 0 ， 所以永远不可能到达最后一个下标。

 

提示：

    1 <= nums.length <= 3 * 104
    0 <= nums[i] <= 105

code:
class Solution {
public:
    bool canJump(vector<int>& nums) {
        int n = nums.size();
        int rightmost = 0;
        for (int i = 0; i < n; ++i) {
            if (i <= rightmost) {
                rightmost = max(rightmost, i + nums[i]);
                if (rightmost >= n - 1) {
                    return true;
                }
            }
        }
        return false;
    }
};
*/

/*
56. 合并区间

以数组 intervals 表示若干个区间的集合，其中单个区间为 intervals[i] = [starti, endi] 。请你合并所有重叠的区间，并返回 一个不重叠的区间数组，该数组需恰好覆盖输入中的所有区间 。

 

示例 1：

输入：intervals = [[1,3],[2,6],[8,10],[15,18]]
输出：[[1,6],[8,10],[15,18]]
解释：区间 [1,3] 和 [2,6] 重叠, 将它们合并为 [1,6].

示例 2：

输入：intervals = [[1,4],[4,5]]
输出：[[1,5]]
解释：区间 [1,4] 和 [4,5] 可被视为重叠区间。

 

提示：

    1 <= intervals.length <= 104
    intervals[i].length == 2
    0 <= starti <= endi <= 104

code:
class Solution {
public:
    vector<vector<int>> merge(vector<vector<int>>& intervals) {
        if (intervals.size() == 0)
            return {};
        sort(intervals.begin(), intervals.end());
        vector<vector<int>> merged;
        for (int i = 0; i < intervals.size(); ++i) {
            int L = intervals[i][0], R = intervals[i][1];
            if (!merged.size() || merged.back()[1] < L)
                merged.push_back({L, R});
            else merged.back()[1] = max(merged.back()[1], R);
        }
        return merged;
    }
};
*/

/*
57. 插入区间

给你一个 无重叠的 ，按照区间起始端点排序的区间列表。

在列表中插入一个新的区间，你需要确保列表中的区间仍然有序且不重叠（如果有必要的话，可以合并区间）。

 

示例 1：

输入：intervals = [[1,3],[6,9]], newInterval = [2,5]
输出：[[1,5],[6,9]]

示例 2：

输入：intervals = [[1,2],[3,5],[6,7],[8,10],[12,16]], newInterval = [4,8]
输出：[[1,2],[3,10],[12,16]]
解释：这是因为新的区间 [4,8] 与 [3,5],[6,7],[8,10] 重叠。

示例 3：

输入：intervals = [], newInterval = [5,7]
输出：[[5,7]]

示例 4：

输入：intervals = [[1,5]], newInterval = [2,3]
输出：[[1,5]]

示例 5：

输入：intervals = [[1,5]], newInterval = [2,7]
输出：[[1,7]]

 

提示：

    0 <= intervals.length <= 104
    intervals[i].length == 2
    0 <= intervals[i][0] <= intervals[i][1] <= 105
    intervals 根据 intervals[i][0] 按 升序 排列
    newInterval.length == 2
    0 <= newInterval[0] <= newInterval[1] <= 105

code:
class Solution {
public:
    vector<vector<int>> insert(vector<vector<int>>& intervals, vector<int>& newInterval) {
        int left = newInterval[0], right = newInterval[1];
        bool placed = false;
        vector<vector<int>> ans;
        for (auto& interval: intervals) {
            if (interval[0] > right) {
                if (!placed) {
                    ans.push_back({left, right});
                    placed = true;                    
                }
                ans.push_back(interval);
            }
            else if (interval[1] < left)
                ans.push_back(interval);
            else {
                left = min(left, interval[0]);
                right = max(right, interval[1]);
            }
        }
        if (!placed)
            ans.push_back({left, right});
        return ans;
    }
};
*/

/*
59. 螺旋矩阵 II

给你一个正整数 n ，生成一个包含 1 到 n2 所有元素，且元素按顺时针顺序螺旋排列的 n x n 正方形矩阵 matrix 。

 

示例 1：

输入：n = 3
输出：[[1,2,3],[8,9,4],[7,6,5]]

示例 2：

输入：n = 1
输出：[[1]]

 

提示：

    1 <= n <= 20

code:
class Solution {
public:
    vector<vector<int>> generateMatrix(int n) {
        int num = 1;
        vector<vector<int>> matrix(n, vector<int>(n));
        int left = 0, right = n - 1, top = 0, bottom = n - 1;
        while (left <= right && top <= bottom) {
            for (int column = left; column <= right; column++) 
                matrix[top][column] = num++;
            for (int row = top + 1; row <= bottom; row++) 
                matrix[row][right] = num++;
            if (left < right && top < bottom) {
                for (int column = right - 1; column > left; column--) 
                    matrix[bottom][column] = num++;
                for (int row = bottom; row > top; row--) 
                    matrix[row][left] = num++;
            }
            left++;
            right--;
            top++;
            bottom--;
        }
        return matrix;
    }
};
*/

/*
61. 旋转链表

给你一个链表的头节点 head ，旋转链表，将链表每个节点向右移动 k 个位置。

 

示例 1：

输入：head = [1,2,3,4,5], k = 2
输出：[4,5,1,2,3]

示例 2：

输入：head = [0,1,2], k = 4
输出：[2,0,1]

 

提示：

    链表中节点的数目在范围 [0, 500] 内
    -100 <= Node.val <= 100
    0 <= k <= 2 * 109

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
    ListNode* rotateRight(ListNode* head, int k) {
        if (k == 0 || head == nullptr || head->next == nullptr)  return head;
        int n = 1;
        ListNode* iter = head;
        while (iter->next != nullptr) {
            iter = iter->next;
            n++;
        }
        int add = n - k % n;
        if (add == n) return head;
        iter->next = head;
        while (add--) iter = iter->next;
        ListNode* ret = iter->next;
        iter->next = nullptr;
        return ret;
    }
};
*/

/*
62. 不同路径

一个机器人位于一个 m x n 网格的左上角 （起始点在下图中标记为 “Start” ）。

机器人每次只能向下或者向右移动一步。机器人试图达到网格的右下角（在下图中标记为 “Finish” ）。

问总共有多少条不同的路径？

 

示例 1：

输入：m = 3, n = 7
输出：28

示例 2：

输入：m = 3, n = 2
输出：3
解释：
从左上角开始，总共有 3 条路径可以到达右下角。
1. 向右 -> 向下 -> 向下
2. 向下 -> 向下 -> 向右
3. 向下 -> 向右 -> 向下

示例 3：

输入：m = 7, n = 3
输出：28

示例 4：

输入：m = 3, n = 3
输出：6

 

提示：

    1 <= m, n <= 100
    题目数据保证答案小于等于 2 * 109

code:
class Solution {
public:
    int uniquePaths(int m, int n) {
        vector<vector<int>> f(m, vector<int>(n));
        for (int i = 0; i < m; ++i) 
            f[i][0] = 1;
        for (int j = 0; j < n; ++j) 
            f[0][j] = 1;
        for (int i = 1; i < m; ++i) 
            for (int j = 1; j < n; ++j) 
                f[i][j] = f[i - 1][j] + f[i][j - 1];
        return f[m - 1][n - 1];
    }
};
*/

/*
63. 不同路径 II

一个机器人位于一个 m x n 网格的左上角 （起始点在下图中标记为 “Start” ）。

机器人每次只能向下或者向右移动一步。机器人试图达到网格的右下角（在下图中标记为 “Finish”）。

现在考虑网格中有障碍物。那么从左上角到右下角将会有多少条不同的路径？

网格中的障碍物和空位置分别用 1 和 0 来表示。

 

示例 1：

输入：obstacleGrid = [[0,0,0],[0,1,0],[0,0,0]]
输出：2
解释：3x3 网格的正中间有一个障碍物。
从左上角到右下角一共有 2 条不同的路径：
1. 向右 -> 向右 -> 向下 -> 向下
2. 向下 -> 向下 -> 向右 -> 向右

示例 2：

输入：obstacleGrid = [[0,1],[0,0]]
输出：1

 

提示：

    m == obstacleGrid.length
    n == obstacleGrid[i].length
    1 <= m, n <= 100
    obstacleGrid[i][j] 为 0 或 1

code:
class Solution {
public:
    int uniquePathsWithObstacles(vector<vector<int>>& obstacleGrid) {
        int n = obstacleGrid.size(), m = obstacleGrid[0].size();
        vector <int> f(m);
        f[0] = 1;
        for (int i = 0; i < n; ++i)
            for (int j = 0; j < m; ++j) {
                if (obstacleGrid[i][j] == 1) {
                    f[j] = 0;
                    continue;
                }
                if (j - 1 >= 0 && obstacleGrid[i][j - 1] == 0)
                    f[j] += f[j - 1];
            }
        return f.back();
    }
};
*/

/*
64. 最小路径和

给定一个包含非负整数的 m x n 网格 grid ，请找出一条从左上角到右下角的路径，使得路径上的数字总和为最小。

说明：每次只能向下或者向右移动一步。

 

示例 1：

输入：grid = [[1,3,1],[1,5,1],[4,2,1]]
输出：7
解释：因为路径 1→3→1→1→1 的总和最小。

示例 2：

输入：grid = [[1,2,3],[4,5,6]]
输出：12

 

提示：

    m == grid.length
    n == grid[i].length
    1 <= m, n <= 200
    0 <= grid[i][j] <= 100

code:
class Solution {
public:
    int minPathSum(vector<vector<int>>& grid) {
        if (grid.size() == 0 || grid[0].size() == 0)
            return 0;
        int rows = grid.size(), columns = grid[0].size();
        auto dp = vector < vector <int> > (rows, vector <int> (columns));
        dp[0][0] = grid[0][0];
        for (int i = 1; i < rows; i++)
            dp[i][0] = dp[i - 1][0] + grid[i][0];
        for (int j = 1; j < columns; j++)
            dp[0][j] = dp[0][j - 1] + grid[0][j];
        for (int i = 1; i < rows; i++) {
            for (int j = 1; j < columns; j++)
                dp[i][j] = min(dp[i - 1][j], dp[i][j - 1]) + grid[i][j];
        return dp[rows - 1][columns - 1];
    }
};
*/

/*
71. 简化路径

给你一个字符串 path ，表示指向某一文件或目录的 Unix 风格 绝对路径 （以 '/' 开头），请你将其转化为更加简洁的规范路径。

在 Unix 风格的文件系统中，一个点（.）表示当前目录本身；此外，两个点 （..） 表示将目录切换到上一级（指向父目录）；两者都可以是复杂相对路径的组成部分。任意多个连续的斜杠（即，'//'）都被视为单个斜杠 '/' 。 对于此问题，任何其他格式的点（例如，'...'）均被视为文件/目录名称。

请注意，返回的 规范路径 必须遵循下述格式：

    始终以斜杠 '/' 开头。
    两个目录名之间必须只有一个斜杠 '/' 。
    最后一个目录名（如果存在）不能 以 '/' 结尾。
    此外，路径仅包含从根目录到目标文件或目录的路径上的目录（即，不含 '.' 或 '..'）。

返回简化后得到的 规范路径 。

 

示例 1：

输入：path = "/home/"
输出："/home"
解释：注意，最后一个目录名后面没有斜杠。 

示例 2：

输入：path = "/../"
输出："/"
解释：从根目录向上一级是不可行的，因为根目录是你可以到达的最高级。

示例 3：

输入：path = "/home//foo/"
输出："/home/foo"
解释：在规范路径中，多个连续斜杠需要用一个斜杠替换。

示例 4：

输入：path = "/a/./b/../../c/"
输出："/c"

 

提示：

    1 <= path.length <= 3000
    path 由英文字母，数字，'.'，'/' 或 '_' 组成。
    path 是一个有效的 Unix 风格绝对路径。

code:
//lambda
class Solution {
public:
    string simplifyPath(string path) {
        auto split = [](const string& s, char delim) -> vector<string> {
            vector<string> ans;
            string cur;
            for (char ch: s) {
                if (ch == delim) {
                    ans.push_back(move(cur));
                    cur.clear();
                }
                else cur += ch;
            }
            ans.push_back(cur);
            return ans;
        };
        vector<string> names = split(path, '/'), stack;
        for (string& name: names)
            if (name == ".."){
                if (!stack.empty())
                    stack.pop_back();
            }
            else if (!name.empty() && name != ".")
                stack.push_back(move(name));
        string ans;
        if (stack.empty())
            ans = "/";
        else {
            for (string& name: stack)
                ans += "/" + move(name);
        }
        return ans;
    }
};
//both
class Solution {
public:
    string simplifyPath(string path) {
        vector<string> names,stack;
        string cur;
        for(char ch:path){
            if(ch=='/'){
                names.push_back(move(cur));
                cur.clear();
            }
            else cur+=ch;
        }
        names.push_back(cur);
        for (string& name: names)
            if (name == ".."){
                if (!stack.empty())
                    stack.pop_back();
            }
            else if (!name.empty() && name != ".")
                stack.push_back(move(name));
        string ans;
        if (stack.empty())
            ans = "/";
        else {
            for (string& name: stack)
                ans += "/" + move(name);
        }
        return ans;
    }
};
*/

/*
73. 矩阵置零

给定一个 m x n 的矩阵，如果一个元素为 0 ，则将其所在行和列的所有元素都设为 0 。请使用 原地 算法。

 

示例 1：

输入：matrix = [[1,1,1],[1,0,1],[1,1,1]]
输出：[[1,0,1],[0,0,0],[1,0,1]]

示例 2：

输入：matrix = [[0,1,2,0],[3,4,5,2],[1,3,1,5]]
输出：[[0,0,0,0],[0,4,5,0],[0,3,1,0]]

 

提示：

    m == matrix.length
    n == matrix[0].length
    1 <= m, n <= 200
    -231 <= matrix[i][j] <= 231 - 1

 

进阶：

    一个直观的解决方案是使用  O(mn) 的额外空间，但这并不是一个好的解决方案。
    一个简单的改进方案是使用 O(m + n) 的额外空间，但这仍然不是最好的解决方案。
    你能想出一个仅使用常量空间的解决方案吗？

code:
class Solution {
public:
    void setZeroes(vector<vector<int>>& matrix) {
        int m = matrix.size(), n = matrix[0].size();
        int flag_col0 = false;
        for (int i = 0; i < m; i++) {
            if (!matrix[i][0])
                flag_col0 = true;
            for (int j = 1; j < n; j++)
                if (!matrix[i][j])
                    matrix[i][0] = matrix[0][j] = 0;
        }
        for (int i = m - 1; i >= 0; i--) {
            for (int j = 1; j < n; j++)
                if (!matrix[i][0] || !matrix[0][j])
                    matrix[i][j] = 0;
            if (flag_col0)
                matrix[i][0] = 0;
        }
    }
};
*/
