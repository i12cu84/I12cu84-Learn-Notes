2. 两数相加
    给你两个 非空 的链表，表示两个非负的整数。它们每位数字都是按照 逆序 的方式存储的，并且每个节点只能存储 一位 数字。
    请你将两个数相加，并以相同形式返回一个表示和的链表。
    你可以假设除了数字 0 之外，这两个数都不会以 0 开头。
    示例 1：
    输入：l1 = [2,4,3], l2 = [5,6,4]
    输出：[7,0,8]
    解释：342 + 465 = 807.
    示例 2：
    输入：l1 = [0], l2 = [0]
    输出：[0]
    示例 3：
    输入：l1 = [9,9,9,9,9,9,9], l2 = [9,9,9,9]
    输出：[8,9,9,9,0,0,0,1]
    提示：
        每个链表中的节点数在范围 [1, 100] 内
        0 <= Node.val <= 9
        题目数据保证列表表示的数字不含前导零

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
        ListNode* addTwoNumbers(ListNode* l1, ListNode* l2) {
            ListNode *head = nullptr, *tail = nullptr;
            int carry = 0;
            while (l1 || l2) {
                int n1 = l1 ? l1->val: 0;
                int n2 = l2 ? l2->val: 0;
                int sum = n1 + n2 + carry;
                if (!head)head = tail = new ListNode(sum % 10);
                else {
                    tail->next = new ListNode(sum % 10);
                    tail = tail->next;
                }
                carry = sum / 10;
                if (l1) l1 = l1->next;
                if (l2) l2 = l2->next;
            }
            if (carry > 0)tail->next = new ListNode(carry);
            return head;
        }
    };

4. 寻找两个正序数组的中位数
    给定两个大小分别为 m 和 n 的正序（从小到大）数组 nums1 和 nums2。
    请你找出并返回这两个正序数组的 中位数 。
    算法的时间复杂度应该为 O(log (m+n)) 。
    示例 1：
    输入：nums1 = [1,3], nums2 = [2]
    输出：2.00000
    解释：合并数组 = [1,2,3] ，中位数 2
    示例 2：
    输入：nums1 = [1,2], nums2 = [3,4]
    输出：2.50000
    解释：合并数组 = [1,2,3,4] ，中位数 (2 + 3) / 2 = 2.5
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
                int newIndex1 = min(index1 + k / 2 - 1, m - 1), 
                    newIndex2 = min(index2 + k / 2 - 1, n - 1);
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

5. 最长回文子串
    给你一个字符串 s，找到 s 中最长的回文子串。
    示例 1：
    输入：s = "babad"
    输出："bab"
    解释："aba" 同样是符合题意的答案。
    示例 2：
    输入：s = "cbbd"
    输出："bb"
    示例 3：
    输入：s = "a"
    输出："a"
    示例 4：
    输入：s = "ac"
    输出："a"
    提示：
        1 <= s.length <= 1000
        s 仅由数字和英文字母（大写和/或小写）组成

    code:
    class Solution {
    public:
        string longestPalindrome(string s)
        {
            string t="$#";
            for(auto c:s){
                t+=c;
                t+='#';
            }
            vector<int> p(t.size(),0);
            int mx=0,id=0,resLen=0,resCenter=0;
            for(int i=1;i<t.size();++i)
            {
                p[i]=mx>i?min(p[2*id-i],mx-i):1;
                while(t[i+p[i]]==t[i-p[i]])p[i]++;
                if(mx<i+p[i]){
                    mx=i+p[i];
                    id=i;
                }
                if(resLen<p[i]){
                    resLen=p[i];
                    resCenter=i;
                }
            }
            return s.substr((resCenter-resLen)/2,resLen-1);
        }
    };


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


8. 字符串转换整数 (atoi)
    请你来实现一个 myAtoi(string s) 函数，使其能将字符串转换成一个 32 位有符号整数（类似 C/C++ 中的 atoi 函数）。
    函数 myAtoi(string s) 的算法如下：
        读入字符串并丢弃无用的前导空格
        检查下一个字符（假设还未到字符末尾）为正还是负号，读取该字符（如果有）。 确定最终结果是负数还是正数。 如果两者都不存在，则假定结果为正。
        读入下一个字符，直到到达下一个非数字字符或到达输入的结尾。字符串的其余部分将被忽略。
        将前面步骤读入的这些数字转换为整数（即，"123" -> 123， "0032" -> 32）。如果没有读入数字，则整数为 0 。必要时更改符号（从步骤 2 开始）。
        如果整数数超过 32 位有符号整数范围 [−231,  231 − 1] ，需要截断这个整数，使其保持在这个范围内。具体来说，小于 −231 的整数应该被固定为 −231 ，大于 231 − 1 的整数应该被固定为 231 − 1 。
        返回整数作为最终结果。
    注意：
        本题中的空白字符只包括空格字符 ' ' 。
        除前导空格或数字后的其余字符串外，请勿忽略 任何其他字符。
    示例 1：
    输入：s = "42"
    输出：42
    解释：加粗的字符串为已经读入的字符，插入符号是当前读取的字符。
    第 1 步："42"（当前没有读入字符，因为没有前导空格）
    第 2 步："42"（当前没有读入字符，因为这里不存在 '-' 或者 '+'）
    第 3 步："42"（读入 "42"）
    解析得到整数 42 。
    由于 "42" 在范围 [-231, 231 - 1] 内，最终结果为 42 。
    示例 2：
    输入：s = "   -42"
    输出：-42
    解释：
    第 1 步："   -42"（读入前导空格，但忽视掉）
    第 2 步："   -42"（读入 '-' 字符，所以结果应该是负数）
    第 3 步："   -42"（读入 "42"）
    解析得到整数 -42 。
    由于 "-42" 在范围 [-231, 231 - 1] 内，最终结果为 -42 。
    示例 3：
    输入：s = "4193 with words"
    输出：4193
    解释：
    第 1 步："4193 with words"（当前没有读入字符，因为没有前导空格）
    第 2 步："4193 with words"（当前没有读入字符，因为这里不存在 '-' 或者 '+'）
    第 3 步："4193 with words"（读入 "4193"；由于下一个字符不是一个数字，所以读入停止）
    解析得到整数 4193 。
    由于 "4193" 在范围 [-231, 231 - 1] 内，最终结果为 4193 。
    示例 4：
    输入：s = "words and 987"
    输出：0
    解释：
    第 1 步："words and 987"（当前没有读入字符，因为没有前导空格）
    第 2 步："words and 987"（当前没有读入字符，因为这里不存在 '-' 或者 '+'）
    第 3 步："words and 987"（由于当前字符 'w' 不是一个数字，所以读入停止）
    解析得到整数 0 ，因为没有读入任何数字。
    由于 0 在范围 [-231, 231 - 1] 内，最终结果为 0 。
    示例 5：
    输入：s = "-91283472332"
    输出：-2147483648
    解释：
    第 1 步："-91283472332"（当前没有读入字符，因为没有前导空格）
    第 2 步："-91283472332"（读入 '-' 字符，所以结果应该是负数）
    第 3 步："-91283472332"（读入 "91283472332"）
    解析得到整数 -91283472332 。
    由于 -91283472332 小于范围 [-231, 231 - 1] 的下界，最终结果被截断为 -231 = -2147483648 。
    提示：
        0 <= s.length <= 200
        s 由英文字母（大写和小写）、数字（0-9）、' '、'+'、'-' 和 '.' 组成

    code:
    class Automaton {
        string state = "start";
        unordered_map<string, vector<string>> table = {{"start", {"start", "signed", "in_number", "end"}}, {"signed", {"end", "end", "in_number", "end"}}, {"in_number", {"end", "end", "in_number", "end"}}, {"end", {"end", "end", "end", "end"}}};
        int get_col(char c) {
            if (isspace(c)) return 0;
            if (c == '+' or c == '-') return 1;
            if (isdigit(c)) return 2;
            return 3;
        }
    public:
        int sign = 1;
        long long ans = 0;
        void get(char c) {
            state = table[state][get_col(c)];
            if (state == "in_number") 
                ans = ans * 10 + c - '0',
                ans = sign == 1 ? min(ans, (long long)INT_MAX) : min(ans, -(long long)INT_MIN);
            else if (state == "signed") sign = c == '+' ? 1 : -1;
        }
    };
    class Solution {
    public:
        int myAtoi(string str) {
            Automaton automaton;
            for (char c : str) automaton.get(c);
            return automaton.sign * automaton.ans;
        }
    };  

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

11. 盛最多水的容器
    给你 n 个非负整数 a1，a2，...，an，每个数代表坐标中的一个点 (i, ai) 。在坐标内画 n 条垂直线，垂直线 i 的两个端点分别为 (i, ai) 和 (i, 0) 。找出其中的两条线，使得它们与 x 轴共同构成的容器可以容纳最多的水。
    说明：你不能倾斜容器。
    示例 1：
    输入：[1,8,6,2,5,4,8,3,7]
    输出：49 
    解释：图中垂直线代表输入数组 [1,8,6,2,5,4,8,3,7]。在此情况下，容器能够容纳水（表示为蓝色部分）的最大值为 49。
    示例 2：
    输入：height = [1,1]
    输出：1
    示例 3：
    输入：height = [4,3,2,1,4]
    输出：16
    示例 4：
    输入：height = [1,2,1]
    输出：2
    提示：
        n == height.length
        2 <= n <= 105
        0 <= height[i] <= 104
    code:
    class Solution {
    public:
        int maxArea(vector<int>& height) {
            int area=0,left=0,right=height.size()-1;
            while(left<right){
                area=max(area,min(height[left],height[right])*(right-left));
                if(height[left]>height[right])right--;
                else left++;
            }
            return area;
        }
    };

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


15. 三数之和
    给你一个包含 n 个整数的数组 nums，判断 nums 中是否存在三个元素 a，b，c ，使得 a + b + c = 0 ？请你找出所有和为 0 且不重复的三元组。
    注意：答案中不可以包含重复的三元组。
    示例 1：
    输入：nums = [-1,0,1,2,-1,-4]
    输出：[[-1,-1,2],[-1,0,1]]
    示例 2：
    输入：nums = []
    输出：[]
    示例 3：
    输入：nums = [0]
    输出：[]
    提示：
        0 <= nums.length <= 3000
        -105 <= nums[i] <= 105
    code:
    class Solution {
    public:
        vector<vector<int>> threeSum(vector<int>& nums) {
            int n = nums.size();
            sort(nums.begin(), nums.end());
            vector<vector<int>> ans;
            for (int first = 0; first < n; ++first) {
                if (first > 0 && nums[first] == nums[first - 1]) continue;
                int third = n - 1, target = -nums[first];
                for (int second = first + 1; second < n; ++second) {
                    if (second > first + 1 && nums[second] == nums[second - 1]) continue;
                    while (second < third && nums[second] + nums[third] > target) --third;
                    if (second == third) break;
                    if (nums[second] + nums[third] == target) ans.push_back({nums[first], nums[second], nums[third]});
                }
            }
            return ans;
        }
    };

16. 最接近的三数之和
    给你一个长度为 n 的整数数组 nums 和 一个目标值 target。请你从 nums 中选出三个整数，使它们的和与 target 最接近。
    返回这三个数的和。
    假定每组输入只存在恰好一个解。
    示例 1：
    输入：nums = [-1,2,1,-4], target = 1
    输出：2
    解释：与 target 最接近的和是 2 (-1 + 2 + 1 = 2) 。
    示例 2：
    输入：nums = [0,0,0], target = 1
    输出：0
    提示：
        3 <= nums.length <= 1000
        -1000 <= nums[i] <= 1000
        -104 <= target <= 104

    code:
    class Solution {
    public:
        int threeSumClosest(vector<int>& nums, int target) {
            sort(nums.begin(), nums.end());
            int n = nums.size();
            int best = 1e7;
            auto update = [&](int cur) {//lambda cpp11特性
                if (abs(cur - target) < abs(best - target)) best = cur;
            };
            for (int i = 0; i < n; ++i) {
                if (i > 0 && nums[i] == nums[i - 1]) continue;
                int j = i + 1, k = n - 1;
                while (j < k) {
                    int sum = nums[i] + nums[j] + nums[k];
                    if (sum == target) return target;
                    update(sum);
                    if (sum > target) {
                        int k0 = k - 1;
                        while (j < k0 && nums[k0] == nums[k]) --k0;
                        k = k0;
                    } else {
                        int j0 = j + 1;
                        while (j0 < k && nums[j0] == nums[j]) ++j0;
                        j = j0;
                    }
                }
            }
            return best;
        }
    };

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
    //Definition for singly-linked list.
    //struct ListNode {
    //    int val;
    //    ListNode *next;
    //    ListNode() : val(0), next(nullptr) {}
    //    ListNode(int x) : val(x), next(nullptr) {}
    //    ListNode(int x, ListNode *next) : val(x), next(next) {}
    //};
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

26. 删除有序数组中的重复项
    给你一个 升序排列 的数组 nums ，请你 原地 删除重复出现的元素，使每个元素 只出现一次 ，返回删除后数组的新长度。元素的 相对顺序 应该保持 一致 。
    由于在某些语言中不能改变数组的长度，所以必须将结果放在数组nums的第一部分。更规范地说，如果在删除重复项之后有 k 个元素，那么 nums 的前 k 个元素应该保存最终结果。
    将最终结果插入 nums 的前 k 个位置后返回 k 。
    不要使用额外的空间，你必须在 原地 修改输入数组 并在使用 O(1) 额外空间的条件下完成。
    判题标准:
    系统会用下面的代码来测试你的题解:
    int[] nums = [...]; // 输入数组
    int[] expectedNums = [...]; // 长度正确的期望答案
    int k = removeDuplicates(nums); // 调用
    assert k == expectedNums.length;
    for (int i = 0; i < k; i++) {
        assert nums[i] == expectedNums[i];
    }
    如果所有断言都通过，那么您的题解将被 通过。
    示例 1：
    输入：nums = [1,1,2]
    输出：2, nums = [1,2,_]
    解释：函数应该返回新的长度 2 ，并且原数组 nums 的前两个元素被修改为 1, 2 。不需要考虑数组中超出新长度后面的元素。
    示例 2：
    输入：nums = [0,0,1,1,1,2,2,3,3,4]
    输出：5, nums = [0,1,2,3,4]
    解释：函数应该返回新的长度 5 ， 并且原数组 nums 的前五个元素被修改为 0, 1, 2, 3, 4 。不需要考虑数组中超出新长度后面的元素。
    提示：
        0 <= nums.length <= 3 * 104
        -104 <= nums[i] <= 104
        nums 已按 升序 排列

    code:
    class Solution {
    public:
        int removeDuplicates(vector<int>& nums) {
            nums.erase(unique(nums.begin(),nums.end()),nums.end());
            return nums.size();
        }
    };
33. 搜索旋转排序数组
    整数数组 nums 按升序排列，数组中的值 互不相同 。
    在传递给函数之前，nums 在预先未知的某个下标 k（0 <= k < nums.length）上进行了 旋转，使数组变为 [nums[k], nums[k+1], ..., nums[n-1], nums[0], nums[1], ..., nums[k-1]]（下标 从 0 开始 计数）。例如， [0,1,2,4,5,6,7] 在下标 3 处经旋转后可能变为 [4,5,6,7,0,1,2] 。
    给你 旋转后 的数组 nums 和一个整数 target ，如果 nums 中存在这个目标值 target ，则返回它的下标，否则返回 -1 。
    示例 1：
    输入：nums = [4,5,6,7,0,1,2], target = 0
    输出：4
    示例 2：
    输入：nums = [4,5,6,7,0,1,2], target = 3
    输出：-1
    示例 3：
    输入：nums = [1], target = 0
    输出：-1
    提示：
        1 <= nums.length <= 5000
        -10^4 <= nums[i] <= 10^4
        nums 中的每个值都 独一无二
        题目数据保证 nums 在预先未知的某个下标上进行了旋转
        -10^4 <= target <= 10^4
    进阶：你可以设计一个时间复杂度为 O(log n) 的解决方案吗？
    code:
    class Solution {
    public:
        int search(vector<int>& nums, int target) {
            int n = (int)nums.size();
            if (!n) return -1;
            if (n == 1) return nums[0] == target ? 0 : -1;
            int l = 0, r = n - 1;
            while (l <= r) {
                int mid = (l + r) / 2;
                if (nums[mid] == target) return mid;
                if (nums[0] <= nums[mid]) {
                    if (nums[0] <= target && target < nums[mid]) r = mid - 1;
                    else l = mid + 1;
                } else {
                    if (nums[mid] < target && target <= nums[n - 1]) l = mid + 1;
                    else r = mid - 1;
                }
            }
            return -1;
        }
    };

43. 字符串相乘
    给定两个以字符串形式表示的非负整数 num1 和 num2，返回 num1 和 num2 的乘积，它们的乘积也表示为字符串形式。
    注意：不能使用任何内置的 BigInteger 库或直接将输入转换为整数。
    示例 1:
    输入: num1 = "2", num2 = "3"
    输出: "6"
    示例 2:
    输入: num1 = "123", num2 = "456"
    输出: "56088"
    提示：
        1 <= num1.length, num2.length <= 200
        num1 和 num2 只能由数字组成。
        num1 和 num2 都不包含任何前导零，除了数字0本身。
    code:
    class Solution {
    public:
        string multiply(string num1, string num2) {
            if (num1 == "0" || num2 == "0") return "0";//注意是"0"
            int m = num1.size(), n = num2.size();
            auto ansArr = vector<int>(m + n);
            for (int i = m - 1; i >= 0; i--) {
                int x = num1.at(i) - '0';
                for (int j = n - 1; j >= 0; j--) {
                    int y = num2.at(j) - '0';
                    ansArr[i + j + 1] += x * y;
                }
            }
            for (int i = m + n - 1; i > 0; i--) {//注意i>0
                ansArr[i - 1] += ansArr[i] / 10;
                ansArr[i] %= 10;
            }
            int index = ansArr[0] == 0 ? 1 : 0;
            string ans;
            while (index < m + n) {
                ans.push_back(ansArr[index]);
                index++;
            }
            for (auto &c: ans) c += '0';//注意要&c以此修改ans成数值
            return ans;
        }
    };

46. 全排列
    给定一个不含重复数字的数组 nums ，返回其 所有可能的全排列 。你可以 按任意顺序 返回答案。
    示例 1：
    输入：nums = [1,2,3]
    输出：[[1,2,3],[1,3,2],[2,1,3],[2,3,1],[3,1,2],[3,2,1]]
    示例 2：
    输入：nums = [0,1]
    输出：[[0,1],[1,0]]
    示例 3：
    输入：nums = [1]
    输出：[[1]]
    提示：
        1 <= nums.length <= 6
        -10 <= nums[i] <= 10
        nums 中的所有整数 互不相同
        //emplace_back和push_back知识点https://blog.csdn.net/p942005405/article/details/84764104
    code:
    class Solution {
    public:
        void SwapVector(vector<vector<int>> &ref,vector<int> &output,int now,int last){
            if(now==last){
                ref.push_back(output);//ref.emplace_back(output);更优
                return ;
            }
            for(int i=now;i<last;i++){
                swap(output[i],output[now]);
                SwapVector(ref,output,now+1,last);
                swap(output[i],output[now]);
            }
            return ;
        }
        vector<vector<int>> permute(vector<int>& nums) {
            vector<vector<int>> ref;
            SwapVector(ref,nums,0,(int)nums.size());
            return ref;
        }
    };

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
            for (auto &x:nums) {
                pre = max(pre + x, x);
                maxAns = max(maxAns, pre);
            }
            return maxAns;
        }
    };
    
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
    code:
    class Solution {
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

70. 爬楼梯
    假设你正在爬楼梯。需要 n 阶你才能到达楼顶。
    每次你可以爬 1 或 2 个台阶。你有多少种不同的方法可以爬到楼顶呢？
    示例 1：
    输入：n = 2
    输出：2
    解释：有两种方法可以爬到楼顶。
    1. 1 阶 + 1 阶
    2. 2 阶
    示例 2：
    输入：n = 3
    输出：3
    解释：有三种方法可以爬到楼顶。
    1. 1 阶 + 1 阶 + 1 阶
    2. 1 阶 + 2 阶
    3. 2 阶 + 1 阶
    code:
    class Solution {
    public:
        int climbStairs(int n) {
            if(n==1)return 1;
            else if (n==2)return 2;
            int first=1,second=2,third;
            for(int i=3;i<=n;i++){
                third=first+second;
                first=second;
                second=third;
            }
            return third;
        }
    };

78. 子集
    给你一个整数数组 nums ，数组中的元素 互不相同 。返回该数组所有可能的子集（幂集）。
    解集 不能 包含重复的子集。你可以按 任意顺序 返回解集。
    示例 1：
    输入：nums = [1,2,3]
    输出：[[],[1],[2],[1,2],[3],[1,3],[2,3],[1,2,3]]
    示例 2：
    输入：nums = [0]
    输出：[[],[0]]
    提示：
        1 <= nums.length <= 10
        -10 <= nums[i] <= 10
        nums 中的所有元素 互不相同
    code:
    class Solution {
    public:
        vector<int> t;
        vector<vector<int>> ans;
        vector<vector<int>> subsets(vector<int>& nums) {
            int n = nums.size();
            for (int mask = 0; mask < (1 << n); ++mask) {
                t.clear();
                for (int i = 0; i < n; ++i) 
                    if (mask & (1 << i)) 
                        t.push_back(nums[i]);
                ans.push_back(t);
            }
            return ans;
        }
    };

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
    进阶：你可以设计实现一个时间复杂度为 O(m + n) 的算法解决此问题吗？
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

89. 格雷编码
    n 位格雷码序列 是一个由 2n 个整数组成的序列，其中：
        每个整数都在范围 [0, 2n - 1] 内（含 0 和 2n - 1）
        第一个整数是 0
        一个整数在序列中出现 不超过一次
        每对 相邻 整数的二进制表示 恰好一位不同 ，且
        第一个 和 最后一个 整数的二进制表示 恰好一位不同
    给你一个整数 n ，返回任一有效的 n 位格雷码序列 。
    示例 1：
    输入：n = 2
    输出：[0,1,3,2]
    解释：
    [0,1,3,2] 的二进制表示是 [00,01,11,10] 。
    - 00 和 01 有一位不同
    - 01 和 11 有一位不同
    - 11 和 10 有一位不同
    - 10 和 00 有一位不同
    [0,2,3,1] 也是一个有效的格雷码序列，其二进制表示是 [00,10,11,01] 。
    - 00 和 10 有一位不同
    - 10 和 11 有一位不同
    - 11 和 01 有一位不同
    - 01 和 00 有一位不同
    示例 2：
    输入：n = 1
    输出：[0,1]
    提示：
        1 <= n <= 16
    code:
    class Solution {
    public:
        vector<int> grayCode(int n) {
            vector<int> ret;
            ret.reserve(1 << n);
            ret.push_back(0);
            for (int i = 1; i <= n; i++) {
                int m = ret.size();
                for (int j = m - 1; j >= 0; j--) {
                    ret.push_back(ret[j] | (1 << (i - 1)));
                }
            }
            return ret;
        }
    };

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
    返回它的最大深度 3 。
    code:
    /**
    * Definition for a binary tree node.
    * struct TreeNode {
    *     int val;
    *     TreeNode *left;
    *     TreeNode *right;
    *     TreeNode() : val(0), left(nullptr), right(nullptr) {}
    *     TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
    *     TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
    * };
    */
    class Solution {
    public:
        int maxDepth(TreeNode* root) {
            if (root == nullptr) return 0;
            return max(maxDepth(root->left), maxDepth(root->right)) + 1;
        }
    };

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
	
122. 买卖股票的最佳时机 II
    给定一个数组 prices ，其中 prices[i] 表示股票第 i 天的价格。
    在每一天，你可能会决定购买和/或出售股票。你在任何时候 最多 只能持有 一股 股票。你也可以购买它，然后在 同一天 出售。
    返回 你能获得的 最大 利润 。
    示例 1:
    输入: prices = [7,1,5,3,6,4]
    输出: 7
    解释: 在第 2 天（股票价格 = 1）的时候买入，在第 3 天（股票价格 = 5）的时候卖出, 这笔交易所能获得利润 = 5-1 = 4 。
        随后，在第 4 天（股票价格 = 3）的时候买入，在第 5 天（股票价格 = 6）的时候卖出, 这笔交易所能获得利润 = 6-3 = 3 。
    示例 2:
    输入: prices = [1,2,3,4,5]
    输出: 4
    解释: 在第 1 天（股票价格 = 1）的时候买入，在第 5 天 （股票价格 = 5）的时候卖出, 这笔交易所能获得利润 = 5-1 = 4 。
        注意你不能在第 1 天和第 2 天接连购买股票，之后再将它们卖出。因为这样属于同时参与了多笔交易，你必须在再次购买前出售掉之前的股票。
    示例 3:
    输入: prices = [7,6,4,3,1]
    输出: 0
    解释: 在这种情况下, 没有交易完成, 所以最大利润为 0。
    提示：
        1 <= prices.length <= 3 * 104
        0 <= prices[i] <= 104
    code:
    class Solution {
    public:
        int maxProfit(vector<int>& prices) {
            int num=prices.size(),ans=0;
            for(int i=1;i<num;++i){
                ans+=max(0,prices[i]-prices[i-1]);
            }
            return ans;
        }
    };

124. 二叉树中的最大路径和
    路径 被定义为一条从树中任意节点出发，沿父节点-子节点连接，达到任意节点的序列。同一个节点在一条路径序列中 至多出现一次 。该路径 至少包含一个 节点，且不一定经过根节点。
    路径和 是路径中各节点值的总和。
    给你一个二叉树的根节点 root ，返回其 最大路径和 。
    示例 1：
    输入：root = [1,2,3]
    输出：6
    解释：最优路径是 2 -> 1 -> 3 ，路径和为 2 + 1 + 3 = 6
    示例 2：
    输入：root = [-10,9,20,null,null,15,7]
    输出：42
    解释：最优路径是 15 -> 20 -> 7 ，路径和为 15 + 20 + 7 = 42
    提示：
        树中节点数目范围是 [1, 3 * 104]
        -1000 <= Node.val <= 1000
    code:
    /**
    * Definition for a binary tree node.
    * struct TreeNode {
    *     int val;
    *     TreeNode *left;
    *     TreeNode *right;
    *     TreeNode() : val(0), left(nullptr), right(nullptr) {}
    *     TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
    *     TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
    * };
    */
    class Solution {
    public:
        int maxSum = INT_MIN;
        int maxGain(TreeNode* node) {
            if (node == nullptr) return 0;
            int leftGain = max(maxGain(node->left), 0);
            int rightGain = max(maxGain(node->right), 0);
            int priceNewpath = node->val + leftGain + rightGain;
            maxSum = max(maxSum, priceNewpath);
            return node->val + max(leftGain, rightGain);
        }
        int maxPathSum(TreeNode* root) {
            maxGain(root);
            return maxSum;
        }
    };

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
            for (auto e: nums) ret ^= e;
            return ret;
        }
    };

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
    /**
    * Definition for singly-linked list.
    * struct ListNode {
    *     int val;
    *     ListNode *next;
    *     ListNode(int x) : val(x), next(NULL) {}
    * };
    */
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

142. 环形链表 II
    给定一个链表的头节点  head ，返回链表开始入环的第一个节点。 如果链表无环，则返回 null。
    如果链表中有某个节点，可以通过连续跟踪 next 指针再次到达，则链表中存在环。 为了表示给定链表中的环，评测系统内部使用整数 pos 来表示链表尾连接到链表中的位置（索引从 0 开始）。如果 pos 是 -1，则在该链表中没有环。注意：pos 不作为参数进行传递，仅仅是为了标识链表的实际情况。
    不允许修改 链表。
    示例 1：
    输入：head = [3,2,0,-4], pos = 1
    输出：返回索引为 1 的链表节点
    解释：链表中有一个环，其尾部连接到第二个节点。
    示例 2：
    输入：head = [1,2], pos = 0
    输出：返回索引为 0 的链表节点
    解释：链表中有一个环，其尾部连接到第一个节点。
    示例 3：
    输入：head = [1], pos = -1
    输出：返回 null
    解释：链表中没有环。
    提示：
        链表中节点的数目范围在范围 [0, 104] 内
        -105 <= Node.val <= 105
        pos 的值为 -1 或者链表中的一个有效索引
    进阶：你是否可以使用 O(1) 空间解决此题？
    code:
    /**
    * Definition for singly-linked list.
    * struct ListNode {
    *     int val;
    *     ListNode *next;
    *     ListNode(int x) : val(x), next(NULL) {}
    * };
    */
    class Solution {
    public:
        ListNode *detectCycle(ListNode *head) {
            ListNode *slow = head, *fast = head;
            while (fast != nullptr && fast->next != nullptr) {
                slow = slow->next;
                fast = fast->next->next;
                if (fast == slow) {
                    ListNode *ptr = head;
                    while (ptr != slow) {
                        ptr = ptr->next;
                        slow = slow->next;
                    }
                    return ptr;
                }
            }
            return nullptr;
        }
    };

146. LRU 缓存(none)
    请你设计并实现一个满足  LRU (最近最少使用) 缓存 约束的数据结构。
    实现 LRUCache 类：
        LRUCache(int capacity) 以 正整数 作为容量 capacity 初始化 LRU 缓存
        int get(int key) 如果关键字 key 存在于缓存中，则返回关键字的值，否则返回 -1 。
        void put(int key, int value) 如果关键字 key 已经存在，则变更其数据值 value ；如果不存在，则向缓存中插入该组 key-value 。如果插入操作导致关键字数量超过 capacity ，则应该 逐出 最久未使用的关键字。
    函数 get 和 put 必须以 O(1) 的平均时间复杂度运行。
    示例：
    输入
    ["LRUCache", "put", "put", "get", "put", "get", "put", "get", "get", "get"]
    [[2], [1, 1], [2, 2], [1], [3, 3], [2], [4, 4], [1], [3], [4]]
    输出
    [null, null, null, 1, null, -1, null, -1, 3, 4]
    解释
    LRUCache lRUCache = new LRUCache(2);
    lRUCache.put(1, 1); // 缓存是 {1=1}
    lRUCache.put(2, 2); // 缓存是 {1=1, 2=2}
    lRUCache.get(1);    // 返回 1
    lRUCache.put(3, 3); // 该操作会使得关键字 2 作废，缓存是 {1=1, 3=3}
    lRUCache.get(2);    // 返回 -1 (未找到)
    lRUCache.put(4, 4); // 该操作会使得关键字 1 作废，缓存是 {4=4, 3=3}
    lRUCache.get(1);    // 返回 -1 (未找到)
    lRUCache.get(3);    // 返回 3
    lRUCache.get(4);    // 返回 4
    提示：
        1 <= capacity <= 3000
        0 <= key <= 10000
        0 <= value <= 105
        最多调用 2 * 105 次 get 和 put
    code:
        struct DLinkedNode {
        int key, value;
        DLinkedNode* prev;
        DLinkedNode* next;
        DLinkedNode(): key(0), value(0), prev(nullptr), next(nullptr) {}
        DLinkedNode(int _key, int _value): key(_key), value(_value), prev(nullptr), next(nullptr) {}
    };
    class LRUCache {
    private:
        unordered_map<int, DLinkedNode*> cache;
        DLinkedNode* head;
        DLinkedNode* tail;
        int size;
        int capacity;
    public:
        LRUCache(int _capacity): capacity(_capacity), size(0) {
            head = new DLinkedNode(), tail = new DLinkedNode();
            head->next = tail;
            tail->prev = head;
        }
        int get(int key) {
            if (!cache.count(key)) return -1;
            DLinkedNode* node = cache[key];
            moveToHead(node);
            return node->value;
        }
        void put(int key, int value) {
            if (!cache.count(key)) {
                DLinkedNode* node = new DLinkedNode(key, value);
                cache[key] = node;
                addToHead(node);
                ++size;
                if (size > capacity) {
                    DLinkedNode* removed = removeTail();
                    cache.erase(removed->key);
                    delete removed;
                    --size;
                }
            }
            else {
                DLinkedNode* node = cache[key];
                node->value = value;
                moveToHead(node);
            }
        }
        void addToHead(DLinkedNode* node) {
            node->prev = head;
            node->next = head->next;
            head->next->prev = node;
            head->next = node;
        }
        void removeNode(DLinkedNode* node) {
            node->prev->next = node->next;
            node->next->prev = node->prev;
        }
        void moveToHead(DLinkedNode* node) {
            removeNode(node);
            addToHead(node);
        }
        DLinkedNode* removeTail() {
            DLinkedNode* node = tail->prev;
            removeNode(node);
            return node;
        }
    };

    /**
    * Your LRUCache object will be instantiated and called as such:
    * LRUCache* obj = new LRUCache(capacity);
    * int param_1 = obj->get(key);
    * obj->put(key,value);
    */

148. 排序链表(none)
    给你链表的头结点 head ，请将其按 升序 排列并返回 排序后的链表 。
    示例 1：
    输入：head = [4,2,1,3]
    输出：[1,2,3,4]
    示例 2：
    输入：head = [-1,5,3,4,0]
    输出：[-1,0,3,4,5]
    示例 3：
    输入：head = []
    输出：[]
    提示：
        链表中节点的数目在范围 [0, 5 * 104] 内
        -105 <= Node.val <= 105
    进阶：你可以在 O(n log n) 时间复杂度和常数级空间复杂度下，对链表进行排序吗？
    code:
    /**
    * Definition for singly-linked list.
    * struct ListNode {
    *     int val;
    *     ListNode *next;
    *     ListNode() : val(0), next(nullptr) {}
    *     ListNode(int x) : val(x), next(nullptr) {}
    *     ListNode(int x, ListNode *next) : val(x), next(next) {}
    * };
    */
    class Solution {
    public:
        ListNode* sortList(ListNode* head, ListNode* tail = nullptr) {
            if (head == nullptr) return head;
            if (head->next == tail) {
                head->next = nullptr;
                return head;
            }
            ListNode* slow = head, *fast = head;
            while (fast != tail) {
                slow = slow->next, fast = fast->next;
                if (fast != tail) fast = fast->next;
            }
            ListNode* mid = slow;
            return merge(sortList(head, mid), sortList(mid, tail));
        }
        ListNode* merge(ListNode* head1, ListNode* head2) {
            ListNode* dummyHead = new ListNode(0);
            ListNode* temp = dummyHead, *temp1 = head1, *temp2 = head2;
            while (temp1 != nullptr && temp2 != nullptr) {
                if (temp1->val <= temp2->val) temp->next = temp1, temp1 = temp1->next;
                else temp->next = temp2, temp2 = temp2->next;
                temp = temp->next;
            }
            if (temp1 != nullptr) temp->next = temp1;
            else if (temp2 != nullptr) temp->next = temp2;
            return dummyHead->next;
        }
    };

155. 最小栈
    设计一个支持 push ，pop ，top 操作，并能在常数时间内检索到最小元素的栈。
    实现 MinStack 类:
        MinStack() 初始化堆栈对象。
        void push(int val) 将元素val推入堆栈。
        void pop() 删除堆栈顶部的元素。
        int top() 获取堆栈顶部的元素。
        int getMin() 获取堆栈中的最小元素。
    示例 1:
    输入：
    ["MinStack","push","push","push","getMin","pop","top","getMin"]
    [[],[-2],[0],[-3],[],[],[],[]]
    输出：
    [null,null,null,null,-3,null,0,-2]
    解释：
    MinStack minStack = new MinStack();
    minStack.push(-2);
    minStack.push(0);
    minStack.push(-3);
    minStack.getMin();   --> 返回 -3.
    minStack.pop();
    minStack.top();      --> 返回 0.
    minStack.getMin();   --> 返回 -2.
    提示：
        -231 <= val <= 231 - 1
        pop、top 和 getMin 操作总是在 非空栈 上调用
        push, pop, top, and getMin最多被调用 3 * 104 次
    code:
    class MinStack {
        stack<int> x_stack;
        stack<int> min_stack;
    public:
        MinStack() {
            min_stack.push(INT_MAX);
        }
        void push(int x) {
            x_stack.push(x);
            min_stack.push(min(min_stack.top(), x));
        }
        void pop() {
            x_stack.pop();
            min_stack.pop();
        }
        int top() {
            return x_stack.top();
        }
        int getMin() {
            return min_stack.top();
        }
    };
    /**
    * Your MinStack object will be instantiated and called as such:
    * MinStack* obj = new MinStack();
    * obj->push(val);
    * obj->pop();
    * int param_3 = obj->top();
    * int param_4 = obj->getMin();
    */

160. 相交链表
    给你两个单链表的头节点 headA 和 headB ，请你找出并返回两个单链表相交的起始节点。如果两个链表不存在相交节点，返回 null 。
    图示两个链表在节点 c1 开始相交：
    题目数据 保证 整个链式结构中不存在环。
    注意，函数返回结果后，链表必须 保持其原始结构 。
    自定义评测：
    评测系统 的输入如下（你设计的程序 不适用 此输入）：
        intersectVal - 相交的起始节点的值。如果不存在相交节点，这一值为 0
        listA - 第一个链表
        listB - 第二个链表
        skipA - 在 listA 中（从头节点开始）跳到交叉节点的节点数
        skipB - 在 listB 中（从头节点开始）跳到交叉节点的节点数
    评测系统将根据这些输入创建链式数据结构，并将两个头节点 headA 和 headB 传递给你的程序。如果程序能够正确返回相交节点，那么你的解决方案将被 视作正确答案 。
    示例 1：
    输入：intersectVal = 8, listA = [4,1,8,4,5], listB = [5,6,1,8,4,5], skipA = 2, skipB = 3
    输出：Intersected at '8'
    解释：相交节点的值为 8 （注意，如果两个链表相交则不能为 0）。
    从各自的表头开始算起，链表 A 为 [4,1,8,4,5]，链表 B 为 [5,6,1,8,4,5]。
    在 A 中，相交节点前有 2 个节点；在 B 中，相交节点前有 3 个节点。
    示例 2：
    输入：intersectVal = 2, listA = [1,9,1,2,4], listB = [3,2,4], skipA = 3, skipB = 1
    输出：Intersected at '2'
    解释：相交节点的值为 2 （注意，如果两个链表相交则不能为 0）。
    从各自的表头开始算起，链表 A 为 [1,9,1,2,4]，链表 B 为 [3,2,4]。
    在 A 中，相交节点前有 3 个节点；在 B 中，相交节点前有 1 个节点。
    示例 3：
    输入：intersectVal = 0, listA = [2,6,4], listB = [1,5], skipA = 3, skipB = 2
    输出：null
    解释：从各自的表头开始算起，链表 A 为 [2,6,4]，链表 B 为 [1,5]。
    由于这两个链表不相交，所以 intersectVal 必须为 0，而 skipA 和 skipB 可以是任意值。
    这两个链表不相交，因此返回 null 。
    提示：
        listA 中节点数目为 m
        listB 中节点数目为 n
        1 <= m, n <= 3 * 104
        1 <= Node.val <= 105
        0 <= skipA <= m
        0 <= skipB <= n
        如果 listA 和 listB 没有交点，intersectVal 为 0
        如果 listA 和 listB 有交点，intersectVal == listA[skipA] == listB[skipB]
    进阶：你能否设计一个时间复杂度 O(m + n) 、仅用 O(1) 内存的解决方案？
    code:
    class Solution {
    public:
        ListNode *getIntersectionNode(ListNode *headA, ListNode *headB) {
            if (headA == nullptr || headB == nullptr) {
                return nullptr;
            }
            ListNode *pA = headA, *pB = headB;
            while (pA != pB) {
                pA = pA == nullptr ? headB : pA->next;
                pB = pB == nullptr ? headA : pB->next;
            }
            return pA;
        }
    };

169. 多数元素
    给定一个大小为 n 的数组，找到其中的多数元素。多数元素是指在数组中出现次数 大于 ⌊ n/2 ⌋ 的元素。
    你可以假设数组是非空的，并且给定的数组总是存在多数元素。
    示例 1：
    输入：[3,2,3]
    输出：3
    示例 2：
    输入：[2,2,1,1,1,2,2]
    输出：2
    进阶：
        尝试设计时间复杂度为 O(n)、空间复杂度为 O(1) 的算法解决此问题。
    code:
    class Solution {
    public:
        int majorityElement(vector<int>& nums) {
            sort(nums.begin(),nums.end());
            return nums[nums.size()/2];
            // 方法 2
            // unordered_map<int, int> counts;
            // int majority = 0, cnt = 0;
            // for (int num: nums) {
            //     ++counts[num];
            //     if (counts[num] > cnt) {
            //         majority = num;
            //         cnt = counts[num];
            //     }
            // }
            // return majority;
        }
    };

206. 反转链表
    给你单链表的头节点 head ，请你反转链表，并返回反转后的链表。
    示例 1：
    输入：head = [1,2,3,4,5]
    输出：[5,4,3,2,1]
    示例 2：
    输入：head = [1,2]
    输出：[2,1]
    示例 3：
    输入：head = []
    输出：[]
    提示：
        链表中节点的数目范围是 [0, 5000]
        -5000 <= Node.val <= 5000
    进阶：链表可以选用迭代或递归方式完成反转。你能否用两种方法解决这道题？
    code:
    class Solution {
    public:
        ListNode* reverseList(ListNode* head) {
            ListNode* prev = nullptr;
            ListNode* curr = head;
            while (curr) {
                ListNode* next = curr->next;
                curr->next = prev;
                prev = curr;
                curr = next;
            }
            return prev;
        }
    };

215. 数组中的第K个最大元素
    给定整数数组 nums 和整数 k，请返回数组中第 k 个最大的元素。
    请注意，你需要找的是数组排序后的第 k 个最大的元素，而不是第 k 个不同的元素。
    示例 1:
    输入: [3,2,1,5,6,4] 和 k = 2
    输出: 5
    示例 2:
    输入: [3,2,3,1,2,4,5,5,6] 和 k = 4
    输出: 4
    提示：
        1 <= k <= nums.length <= 104
        -104 <= nums[i] <= 104
    code:
    /**
    * Definition for singly-linked list.
    * struct ListNode {
    *     int val;
    *     ListNode *next;
    *     ListNode() : val(0), next(nullptr) {}
    *     ListNode(int x) : val(x), next(nullptr) {}
    *     ListNode(int x, ListNode *next) : val(x), next(next) {}
    * };
    */
    class Solution {
    public:
        ListNode* reverseList(ListNode* head) {
            ListNode* pre = nullptr;
            ListNode* cur = head;
            while (cur) {
                ListNode* next = cur->next;
                cur->next = pre;
                pre = cur;
                cur = next;
            }
            return pre;
        }
    };

217. 存在重复元素
    给你一个整数数组 nums 。如果任一值在数组中出现 至少两次 ，返回 true ；如果数组中每个元素互不相同，返回 false 。
    示例 1：
    输入：nums = [1,2,3,1]
    输出：true
    示例 2：
    输入：nums = [1,2,3,4]
    输出：false
    示例 3：
    输入：nums = [1,1,1,3,3,4,3,2,4,2]
    输出：true
    提示：
        1 <= nums.length <= 105
        -109 <= nums[i] <= 109
    code:
    class Solution {
    public:
        bool containsDuplicate(vector<int>& nums) {
            sort(nums.begin(),nums.end());
            for(int i=1;i<nums.size();++i){
                if(nums[i-1]==nums[i]){
                    return true;
                }
            }
            return false;
        }
    };

230. 二叉搜索树中第K小的元素
    给定一个二叉搜索树的根节点 root ，和一个整数 k ，请你设计一个算法查找其中第 k 个最小元素（从 1 开始计数）。
    示例 1：
    输入：root = [3,1,4,null,2], k = 1
    输出：1
    示例 2：
    输入：root = [5,3,6,2,4,null,null,1], k = 3
    输出：3
    提示：
        树中的节点数为 n 。
        1 <= k <= n <= 104
        0 <= Node.val <= 104
    进阶：如果二叉搜索树经常被修改（插入/删除操作）并且你需要频繁地查找第 k 小的值，你将如何优化算法？
    code:
    /**
    * Definition for a binary tree node.
    * struct TreeNode {
    *     int val;
    *     TreeNode *left;
    *     TreeNode *right;
    *     TreeNode() : val(0), left(nullptr), right(nullptr) {}
    *     TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
    *     TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
    * };
    */
    class Solution {
    public:
        vector<int> TreeNode_Vec;
        int kthSmallest(TreeNode* root, int k) {
            TreeNode_2Vec(root);
            return TreeNode_Vec[k-1];
        }
        void TreeNode_2Vec(TreeNode* root){
            if(root == nullptr)return;
            TreeNode_2Vec(root->left);
            TreeNode_Vec.push_back(root->val);
            TreeNode_2Vec(root->right);
        }
    };
    //方法2 更快
    class Solution {
    public:
        vector<int> TreeNode_Vec;
        int num_size=0;
        int kthSmallest(TreeNode* root, int k) {
            TreeNode_2Vec(root,k);
            return TreeNode_Vec[k-1];
        }
        void TreeNode_2Vec(TreeNode* root,int k){
            if(root == nullptr || num_size>k )return;
            ++num_size;
            TreeNode_2Vec(root->left,num_size);
            TreeNode_Vec.push_back(root->val);
            TreeNode_2Vec(root->right,num_size);
        }
    };
    //方法3 更快
    class Solution {
    public:
        int kthSmallest(TreeNode* root, int k) {
            stack<TreeNode *> stack;
            while (root != nullptr || stack.size() > 0) {
                while (root != nullptr) {
                    stack.push(root);
                    root = root->left;
                }
                root = stack.top();
                stack.pop();
                --k;
                if (k == 0) break;
                root = root->right;
            }
            return root->val;
        }
    };

231. 2 的幂
    给你一个整数 n，请你判断该整数是否是 2 的幂次方。如果是，返回 true ；否则，返回 false 。
    如果存在一个整数 x 使得 n == 2x ，则认为 n 是 2 的幂次方。
    示例 1：
    输入：n = 1
    输出：true
    解释：20 = 1
    示例 2：
    输入：n = 16
    输出：true
    解释：24 = 16
    示例 3：
    输入：n = 3
    输出：false
    示例 4：
    输入：n = 4
    输出：true
    示例 5：
    输入：n = 5
    输出：false
    提示：
        -231 <= n <= 231 - 1
    进阶：你能够不使用循环/递归解决此问题吗？
    code:
    class Solution {
    public:
        bool isPowerOfTwo(int n) {
            return n>0 && !(n&(n-1));
        }
    };

235. 二叉搜索树的最近公共祖先
    给定一个二叉搜索树, 找到该树中两个指定节点的最近公共祖先。
    百度百科中最近公共祖先的定义为：“对于有根树 T 的两个结点 p、q，最近公共祖先表示为一个结点 x，满足 x 是 p、q 的祖先且 x 的深度尽可能大（一个节点也可以是它自己的祖先）。”
    例如，给定如下二叉搜索树:  root = [6,2,8,0,4,7,9,null,null,3,5]
    示例 1:
    输入: root = [6,2,8,0,4,7,9,null,null,3,5], p = 2, q = 8
    输出: 6 
    解释: 节点 2 和节点 8 的最近公共祖先是 6。
    示例 2:
    输入: root = [6,2,8,0,4,7,9,null,null,3,5], p = 2, q = 4
    输出: 2
    解释: 节点 2 和节点 4 的最近公共祖先是 2, 因为根据定义最近公共祖先节点可以为节点本身。
    说明:
        所有节点的值都是唯一的。
        p、q 为不同节点且均存在于给定的二叉搜索树中。
    code:
    /**
    * Definition for a binary tree node.
    * struct TreeNode {
    *     int val;
    *     TreeNode *left;
    *     TreeNode *right;
    *     TreeNode(int x) : val(x), left(NULL), right(NULL) {}
    * };
    */
    class Solution {
    public:
        TreeNode* lowestCommonAncestor(TreeNode* root, TreeNode* p, TreeNode* q) {
            TreeNode* ancestor = root;
            while (true) {
                if (p->val < ancestor->val && q->val < ancestor->val) 
                    ancestor = ancestor->left;
                else if (p->val > ancestor->val && q->val > ancestor->val) 
                    ancestor = ancestor->right;
                else break;
            }
            return ancestor;
        }
    };

236. 二叉树的最近公共祖先
    给定一个二叉树, 找到该树中两个指定节点的最近公共祖先。
    百度百科中最近公共祖先的定义为：“对于有根树 T 的两个节点 p、q，最近公共祖先表示为一个节点 x，满足 x 是 p、q 的祖先且 x 的深度尽可能大（一个节点也可以是它自己的祖先）。”
    示例 1：
    输入：root = [3,5,1,6,2,0,8,null,null,7,4], p = 5, q = 1
    输出：3
    解释：节点 5 和节点 1 的最近公共祖先是节点 3 。
    示例 2：
    输入：root = [3,5,1,6,2,0,8,null,null,7,4], p = 5, q = 4
    输出：5
    解释：节点 5 和节点 4 的最近公共祖先是节点 5 。因为根据定义最近公共祖先节点可以为节点本身。
    示例 3：
    输入：root = [1,2], p = 1, q = 2
    输出：1
    提示：
        树中节点数目在范围 [2, 105] 内。
        -109 <= Node.val <= 109
        所有 Node.val 互不相同 。
        p != q
        p 和 q 均存在于给定的二叉树中。
    code:
    /**
    * Definition for a binary tree node.
    * struct TreeNode {
    *     int val;
    *     TreeNode *left;
    *     TreeNode *right;
    *     TreeNode(int x) : val(x), left(NULL), right(NULL) {}
    * };
    */
    class Solution {
    public:
        TreeNode* ans;
        bool dfs(TreeNode* root, TreeNode* p, TreeNode* q) {
            if (root == nullptr) return false;
            bool lson = dfs(root->left, p, q);
            bool rson = dfs(root->right, p, q);
            if ((lson && rson) || ((root->val == p->val || root->val == q->val) && (lson || rson))) 
                ans = root;
            return lson || rson || (root->val == p->val || root->val == q->val);
        }
        TreeNode* lowestCommonAncestor(TreeNode* root, TreeNode* p, TreeNode* q) {
            dfs(root, p, q);
            return ans;
        }
    };

237. 删除链表中的节点
    请编写一个函数，用于 删除单链表中某个特定节点 。在设计函数时需要注意，你无法访问链表的头节点 head ，只能直接访问 要被删除的节点 。
    题目数据保证需要删除的节点 不是末尾节点 。
    示例 1：
    输入：head = [4,5,1,9], node = 5
    输出：[4,1,9]
    解释：指定链表中值为 5 的第二个节点，那么在调用了你的函数之后，该链表应变为 4 -> 1 -> 9
    示例 2：
    输入：head = [4,5,1,9], node = 1
    输出：[4,5,9]
    解释：指定链表中值为 1 的第三个节点，那么在调用了你的函数之后，该链表应变为 4 -> 5 -> 9
    提示：
        链表中节点的数目范围是 [2, 1000]
        -1000 <= Node.val <= 1000
        链表中每个节点的值都是 唯一 的
        需要删除的节点 node 是 链表中的节点 ，且 不是末尾节点
    code:
    /**
    * Definition for singly-linked list.
    * struct ListNode {
    *     int val;
    *     ListNode *next;
    *     ListNode(int x) : val(x), next(NULL) {}
    * };
    */
    class Solution {
    public:
        void deleteNode(ListNode* node) {
            ListNode* temp = node->next;
            node->val = temp->val;
            node->next = temp->next;
            delete temp;
        }
    };

238. 除自身以外数组的乘积
    给你一个整数数组 nums，返回 数组 answer ，其中 answer[i] 等于 nums 中除 nums[i] 之外其余各元素的乘积 。
    题目数据 保证 数组 nums之中任意元素的全部前缀元素和后缀的乘积都在  32 位 整数范围内。
    请不要使用除法，且在 O(n) 时间复杂度内完成此题。
    示例 1:
    输入: nums = [1,2,3,4]
    输出: [24,12,8,6]
    示例 2:
    输入: nums = [-1,1,0,-3,3]
    输出: [0,0,9,0,0]
    提示：
        2 <= nums.length <= 105
        -30 <= nums[i] <= 30
        保证 数组 nums之中任意元素的全部前缀元素和后缀的乘积都在  32 位 整数范围内
    进阶：你可以在 O(1) 的额外空间复杂度内完成这个题目吗？（ 出于对空间复杂度分析的目的，输出数组不被视为额外空间。）
    code:
    class Solution {
    public:
        vector<int> productExceptSelf(vector<int>& nums) {
            int length = nums.size(),R = 1;
            vector<int> answer(length);
            answer[0] = 1;
            for (int i = 1; i < length; i++) 
                answer[i] = nums[i - 1] * answer[i - 1];
            for (int i = length - 1; i >= 0; i--) {
                answer[i] = answer[i] * R;
                R *= nums[i];
            }
            return answer;
        }
    };

292. Nim 游戏
    你和你的朋友，两个人一起玩 Nim 游戏：
        桌子上有一堆石头。
        你们轮流进行自己的回合， 你作为先手 。
        每一回合，轮到的人拿掉 1 - 3 块石头。
        拿掉最后一块石头的人就是获胜者。
    假设你们每一步都是最优解。请编写一个函数，来判断你是否可以在给定石头数量为 n 的情况下赢得游戏。如果可以赢，返回 true；否则，返回 false 。
    示例 1：
    输入：n = 4
    输出：false 
    解释：以下是可能的结果:
    1. 移除1颗石头。你的朋友移走了3块石头，包括最后一块。你的朋友赢了。
    2. 移除2个石子。你的朋友移走2块石头，包括最后一块。你的朋友赢了。
    3.你移走3颗石子。你的朋友移走了最后一块石头。你的朋友赢了。
    在所有结果中，你的朋友是赢家。
    示例 2：
    输入：n = 1
    输出：true
    示例 3：
    输入：n = 2
    输出：true
    提示：
        1 <= n <= 231 - 1
    code:
    class Solution {
    public:
        bool canWinNim(int n) {
            return n % 4 != 0;
        }
    };

344. 反转字符串
    编写一个函数，其作用是将输入的字符串反转过来。输入字符串以字符数组 s 的形式给出。
    不要给另外的数组分配额外的空间，你必须原地修改输入数组、使用 O(1) 的额外空间解决这一问题。
    示例 1：
    输入：s = ["h","e","l","l","o"]
    输出：["o","l","l","e","h"]
    示例 2：
    输入：s = ["H","a","n","n","a","h"]
    输出：["h","a","n","n","a","H"]
    提示：
        1 <= s.length <= 105
        s[i] 都是 ASCII 码表中的可打印字符
    code:
    class Solution {
    public:
        void reverseString(vector<char>& s) {
            int n = s.size();
            for (int left = 0, right = n - 1; left < right; ++left, --right) {
                swap(s[left], s[right]);
            }
        }
    };

557. 反转字符串中的单词 III
    给定一个字符串 s ，你需要反转字符串中每个单词的字符顺序，同时仍保留空格和单词的初始顺序。
    示例 1：
    输入：s = "Let's take LeetCode contest"
    输出："s'teL ekat edoCteeL tsetnoc"
    示例 2:
    输入： s = "God Ding"
    输出："doG gniD"
    提示：
        1 <= s.length <= 5 * 104
        s 包含可打印的 ASCII 字符。
        s 不包含任何开头或结尾空格。
        s 里 至少 有一个词。
        s 中的所有单词都用一个空格隔开。
    code:
    class Solution {
    public: 
        string reverseWords(string s) {
            int length = s.length();
            int i = 0;
            while (i < length) {
                int start = i;
                while (i < length && s[i] != ' ') 
                    i++;
                int left = start, right = i - 1;
                while (left < right) {
                    swap(s[left], s[right]);
                    left++;
                    right--;
                }
                while (i < length && s[i] == ' ') 
                    i++;
            }
            return s;
        }
    };
