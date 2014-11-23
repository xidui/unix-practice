//
//  main.cpp
//  RBTree
//
//  Created by apple on 14-11-23.
//  Copyright (c) 2014年 apple. All rights reserved.
//

#include <iostream>

using namespace std;

struct Node
{
    Node* pLeft;
    Node* pRight;
    Node* pParent;
    int32_t iValue;
    bool bRed;
    void print(){
        cout<<(bRed ? "R" : "B")<<iValue;
    };
};

Node* root = NULL;
int32_t size = 0;

void LRotate(Node* node)
{
    if (NULL == node->pRight)
    {
        return;
    }
    // node是根节点
    if (NULL == node->pParent)
    {
        root = node->pRight;
        root->pParent = NULL;
        
        node->pParent = root;
        node->pRight = root->pLeft;
        root->pLeft = node;
        if (node->pRight != NULL)
        {
            node->pRight->pParent = node;
        }
        return;
    }
    
    // node是内部节点
    node->pRight->pParent = node->pParent;
    if (node->pParent->pLeft == node)
    {
        node->pParent->pLeft = node->pRight;
    }
    else
    {
        node->pParent->pRight = node->pRight;
    }
    node->pParent = node->pRight;
    node->pRight = node->pParent->pLeft;
    node->pParent->pLeft = node;
    if (node ->pRight != NULL)
    {
        node->pRight->pParent = node;
    }
}

void RRotate(Node* node)
{
    if (NULL == node->pLeft)
    {
        return;
    }
    // node是根节点
    if (NULL == node->pParent)
    {
        root = node->pLeft;
        root->pParent = NULL;
        
        node->pParent = root;
        node->pLeft = root->pRight;
        root->pRight = node;
        if (node->pLeft != NULL)
        {
            node->pLeft->pParent = node;
        }
        return;
    }
    
    // node是内部节点
    node->pLeft->pParent = node->pParent;
    if (node->pParent->pRight == node)
    {
        node->pParent->pRight = node->pLeft;
    }
    else
    {
        node->pParent->pLeft = node->pLeft;
    }
    node->pParent = node->pLeft;
    node->pLeft = node->pParent->pRight;
    node->pParent->pRight = node;
    if (node ->pLeft != NULL)
    {
        node->pLeft->pParent = node;
    }
}

void adjust(Node* node)
{
    if (node == NULL)
    {
        return;
    }
    if (node->pParent == NULL)
    {
        // node是根节点
        node->bRed = false;
        return;
    }
    
    // 1.如果插入节点的父节点是黑色的，无需调整
    if (node->pParent->bRed == false)
    {
        return;
    }
    // 2.插入节点的叔叔节点是红色的
    // 插入节点变黑色，父亲叔叔变红色，祖父变红色，对祖父作调整
    if (node->pParent->pParent->pLeft != NULL && node->pParent->pParent->pLeft->bRed &&
        node->pParent->pParent->pRight != NULL && node->pParent->pParent->pRight->bRed)
    {
        node->pParent->pParent->pLeft->bRed = false;
        node->pParent->pParent->pRight->bRed = false;
        node->pParent->pParent->bRed = true;
        adjust(node->pParent->pParent);
        return;
    }
    // 3.插入节点的叔叔节点是黑色的,父节点红色
    if (node->pParent->pParent->pLeft == node->pParent && node->pParent->pLeft == node)
    {
        // 变色，再对祖父节点作右旋
        node->pParent->bRed = false;
        node->pParent->pParent->bRed = true;
        RRotate(node->pParent->pParent);
    }
    else if (node->pParent->pParent->pRight == node->pParent && node->pParent->pRight == node)
    {
        node->pParent->bRed = false;
        node->pParent->pParent->bRed = true;
        LRotate(node->pParent->pParent);
    }
    else if(node->pParent->pParent->pLeft == node->pParent && node->pParent->pRight == node)
    {
        LRotate(node->pParent);
        adjust(node);
    }
    else
    {
        RRotate(node->pParent);
        adjust(node);
    }
}

void insert(int32_t value, Node* node)
{
    if (node == NULL)
    {
        // 根节点
        root = new Node();
        root->bRed = false;
        root->iValue = value;
        return;
    }
    // 插入
    Node* pTemp;
    if (node->iValue > value)
    {
        if (node->pLeft != NULL)
        {
            insert(value, node->pLeft);
        }
        else
        {
            node->pLeft = new Node();
            pTemp = node->pLeft;
        }
    }
    else
    {
        if (node->pRight != NULL)
        {
            insert(value, node->pRight);
        }
        else
        {
            node->pRight = new Node();
            pTemp = node->pRight;
        }
    }
    
    if (pTemp != NULL)
    {
        pTemp->pParent = node;
        pTemp->iValue = value;
        pTemp->bRed = true;
        // 开始调整
        adjust(pTemp);
        pTemp = NULL;
    }
}

void print_pre(Node* node)
{
    if (NULL == node)
    {
        return;
    }
    node->print();
    print_pre(node->pLeft);
    print_pre(node->pRight);
}

void print_mid(Node* node)
{
    if (NULL == node)
    {
        return;
    }
    print_mid(node->pLeft);
    node->print();
    print_mid(node->pRight);
}

int main(int argc, const char * argv[])
{
    insert(1, root);
    insert(2, root);
    insert(3, root);
    insert(4, root);
    insert(5, root);
    insert(6, root);
    insert(7, root);
    print_pre(root);
    print_mid(root);
    return 0;
}

