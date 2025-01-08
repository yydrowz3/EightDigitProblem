

An cross-platform eight digit problem solution simulate program based on C/C++ and GUI is created with QT API.

Simulating the search process under different searching algorithm:

- BFS
- DFS
- A*

### Heuristic Function of `A*`

`A*` search algorithm is implemented with the Heuristic Function: `f(x) = g(x) + h(x)`.  

- `g(x)`: current searching depth
- `h(x)`: the sum of coordination difference under Manhattan distance strategy

`g(x)` functions similar as *dijkstra algorithm*, which can guarenteen the current would be the most optimal state on current search depth. **(dynamic programing)**


`h(x)` makes the searching process have the ability of 'pridiction' the direction of target, which makes it possible to select with greedy algorithm. 

After reaching the final target state, `g(x)` reaches the largest depth and `h(x)` becomes `0`, and thus the current state can be guarenteened to be the most optimal solution by comparing with the past state. 

<!--这次的启发式函数f(x) = g(x) + h(x) ，其中g(x)是当前搜索的深度，这就像是dijkstra了，总是能保证在当前深度上是最优的。h(x)是用曼哈顿距离表示当前状态与目标状态的位置坐标差的和，因此这部分就可以让搜索的过程有预测，可以用贪心的方式进行选择。达到目标状态时，g(x)为深度而h(x)为0，因此通过前一部分可以保证此时是最优解。-->

![](./eightdigitPic1.png)

![](./eightdigitPic2.png)


### How to Execute

After compiling under QT framework, execute the `EightDigitProblem.exe` file.

### How to Use

- input the initial state and the target state
- clicking the `start` button

