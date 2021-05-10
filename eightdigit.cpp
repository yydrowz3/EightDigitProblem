#include "eightdigit.h"

eightDigit::eightDigit()
{

}


void eightDigit::init(int ST[LIMIT], int ED[LIMIT]) //初始化
{
    S0.parent = Sg.parent = NULL;
    S0.depth = Sg.depth = 0;
    S0.value = Sg.value = 0;
    for(int i = 0; i < LIMIT; i++)
    {
        S0.state[i] = ST[i];
        Sg.state[i] = ED[i];
        End[i / ROW][i % COL] = ED[i];  //终点状态提前保存好,便于判断是否已搜到终点
    }
}

bool eightDigit::inversionJudge()   //逆序数判断是否有解
{
    int cntStart = 0, cntEnd = 0;
    for(int i = 0; i < LIMIT - 1; i++)
        for(int j = i + 1; j < LIMIT; j++)
            if(S0.state[i] != 0 && S0.state[j] != 0 && S0.state[j] < S0.state[i])
                cntStart++;
    for(int i = 0; i < LIMIT - 1; i++)
        for(int j = i + 1; j < LIMIT; j++)
            if(Sg.state[i] != 0 && Sg.state[j] != 0 && Sg.state[j] < Sg.state[i])
                cntEnd++;

    if(cntStart % 2 == cntEnd % 2)
        return true;
    else
        return false;
}

int eightDigit::valueCalc(Node a)   //计算权值 f(x) = g(x) + h(x)
{
    int start[ROW][COL], cnt = 0;
    for(int i = 0; i < LIMIT; i++)
        start[i / ROW][i % COL] = a.state[i];
    for(int i = 0 ; i < ROW; i++)
        for(int j = 0; j < COL; j++)
            if(start[i][j] != End[i][j])
            {
                for(int u = 0; u < ROW; u++)
                    for(int v = 0; v < COL; v++)
                        if(start[i][j] == End[u][v])
                            cnt += abs(i - u) + abs(j - v);
            }

    return cnt;
}

bool eightDigit::equalJudge(Node a, Node b) //判断是否相等
{
    for(int i = 0; i < LIMIT; i++)
        if(a.state[i] != b.state[i])
            return false;

    return true;
}

void eightDigit::createNode(Node &S)    //建立子节点
{
    int blank;
    for(blank = 0; blank < LIMIT; blank++)  //找到空白格子的坐标
        if(S.state[blank] == 0)
            break;
    int x = blank / ROW, y = blank % COL;
    for(int i = 0; i < 4; i++)
    {
        int newX = x, newY = y;     //对一个节点的上下左右邻节点逐个判断
        if(i == 0) newX = x - 1;
        if(i == 1) newY = y - 1;
        if(i == 2) newX = x + 1;
        if(i == 3) newY = y + 1;
        int newBlank = newX * ROW + newY;
        if(newX >= 0 && newX < ROW && newY >= 0 && newY < COL)  //如果节点位置有效
        {
            Node tempNode = S;
            tempNode.state[blank] = S.state[newBlank];
            tempNode.state[newBlank] = 0;   //更新节点属性
            if(S.parent != NULL && (*S.parent).state[newBlank] == 0)    //如果该节点上一步已经判断过,就直接跳过
                continue;
            tempNode.parent = &S;
            tempNode.value = valueCalc(tempNode);   //更新值
            tempNode.depth = S.depth + 1;
            openTable.push(tempNode);
        }
    }
}

void eightDigit::AStarSearch()  //A*搜索
{
    openTable.push(S0); //起始节点先加入优先队列
    while(!openTable.empty())
    {
        searchedTimeCount++;    //计数
        closeTable.push(openTable.top());
        openTable.pop();    //出队
        if(equalJudge(closeTable.back(), Sg))   //判断是否已到终点
            break;
        else
            createNode(closeTable.back());  //生成子节点
    }
    Node temp;
    temp = closeTable.back();
    while(temp.parent != NULL)  //将节点加入栈,形成路径
    {
        Path.push(temp);
        temp = *(temp.parent);
    }
    Path.push(temp);
}

int eightDigit::getKey(Node temp)   //获得状态对应的键值
{
    int key = 0;
    for(int i = 0; i < LIMIT; i++)
        key = key * 10 + temp.state[i];

    return key;
}

void eightDigit::BFSSearch()    //BFS搜索
{
    int nextX[4] = {-1, 0, 1, 0}, nextY[4] = {0, 1, 0, -1};
    queue<Node> Q;
    Q.push(S0);
    Vis[getKey(S0)] = 1;
    while(!Q.empty())
    {
        searchedTimeCount++;    //计数器
        closeTable.push(Q.front());
        Q.pop();    //出队
        Node temp = closeTable.back();
        if(equalJudge(temp, Sg))    //判断是否已到终点
            break;

        int blank;
        for(blank = 0; blank < LIMIT; blank++)
            if(temp.state[blank] == 0)
                break;
        int x = blank / ROW, y = blank % COL;   //更新空白的坐标
        for(int i = 0; i < 4; i++)  //将相邻节点入队
        {
            int newX = x + nextX[i], newY = y + nextY[i];
            int newBlank = newX * ROW + newY;
            if(newX >= 0 && newX < ROW && newY >= 0 && newY < COL)  //判断坐标是否合理
            {
                Node T = temp;
                T.state[blank] = T.state[newBlank];
                T.state[newBlank] = 0;
                if(!Vis[getKey(T)]) //判断是否已被访问过,防止死循环
                {
                    Vis[getKey(T)] = 1;
                    T.parent = &closeTable.back();
                    Q.push(T);
                }
            }
        }
    }
    Node temp = closeTable.back();
    while(temp.parent != NULL)  //将节点加入栈形成路径
    {
        Path.push(temp);
        temp = *(temp.parent);
    }
    Path.push(temp);
}
