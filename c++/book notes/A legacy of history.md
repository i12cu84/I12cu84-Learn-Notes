#include<bits/stdc++.h>
using namespace std;
//验证剑指offer page 144 似乎有问题
struct ListNode{
    int m_nKey;
    ListNode* m_pNext;
};
ListNode* ReverseList(ListNode* pHead){//似乎有点问题
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
int main(){
    ListNode node[3];
    node[0].m_nKey=1;
    node[0].m_pNext=node+1;
    node[1].m_nKey=2;
    node[1].m_pNext=node+2;
    node[2].m_nKey=3;
    node[2].m_pNext=nullptr;
    cout<<(node[0]).m_nKey<<endl;
    cout<<(*node[0].m_pNext).m_nKey<<endl;
    cout<<(*node[1].m_pNext).m_nKey<<endl;
    ReverseList(node);
    cout<<(node[0]).m_nKey<<endl;
    cout<<(node[1]).m_nKey<<endl;
    cout<<(node[2]).m_nKey<<endl;cout<<endl;
    cout<<(*ReverseList(node)).m_nKey<<endl;
    cout<<(*(*ReverseList(node)).m_pNext).m_nKey<<endl;
}