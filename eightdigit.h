#ifndef EIGHTDIGIT_H
#define EIGHTDIGIT_H

#include <iostream>
#include <queue>
#include <stack>
#include <map>
using namespace std;

const int ROW = 3, COL = 3;     //需要的一些变量的定义
const int LIMIT = ROW * COL;
struct Node
{
    int state[LIMIT];
    Node *parent;
    int value, depth;
    bool operator < (const Node &other) const
    {
        return this->depth + this->value > other.depth + other.value;
    }
};

class eightDigit
{
public:
    priority_queue<Node> openTable; //优先队列,用于A*搜索根据结点的权重选择搜索的结点
    queue<Node> closeTable; //用于保存搜索到的节点,利于最后通过地址找到父结点
    stack<Node> Path;   //用栈保存路径,方便输出
    Node S0, Sg;    //起始和终点结点
    int End[ROW][COL];  //结束的状态
    int Start[ROW][COL];    //开始的状态
    int searchedTimeCount = 0;  //记录搜索的次数
    map<int, int> Vis;  //用于记录搜索过程中已经访问过的结点

    eightDigit();
    void init(int ST[LIMIT], int ED[LIMIT]);    //初始化
    bool inversionJudge();  //通过逆序数判断
    int valueCalc(Node a);  //计算A*搜索时结点的值, f(x) = g(x) + h(x)
    bool equalJudge(Node a, Node b);    //判断两个结点是否相等,用于判断是否搜索到终点
    void createNode(Node &S);   //生成一个结点的子节点并压入队列
    void AStarSearch(); //A*搜索
    int getKey(Node temp);  //将状态转换为一个值,用于判断该状态是否已被访问过
    void BFSSearch();   //BFS搜索
};

#endif // EIGHTDIGIT_H
