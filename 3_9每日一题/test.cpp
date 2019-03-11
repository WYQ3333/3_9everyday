#include<iostream>

#include<vector>
using namespace std;

#if 0
int main(){
	int w, h, result = 0;
	cin >> w >> h;
	vector<vector<int>> array;
	array.resize(h);
	for (size_t i = 0; i < array.size(); ++i){
		array[i].resize(w);
	}
	for (size_t i = 0; i < array.size(); ++i){
		for (size_t j = 0; j < array[i].size(); ++j){
			array[i][j] = 1;
		}
	}
	for (size_t i = 0; i < array.size(); ++i){
		for (size_t j = 0; j < array[i].size(); ++j){
			if (array[i][j] == 1){
				result++;
				if (i + 2 < h){
					array[i + 2][j] = 0;
				}
				if (j + 2 < w){
					array[i][j + 2] = 0;
				}
			}
		}
	}
	cout << result << endl;
	system("pause");
	return 0;
}
#endif

#if 0
#include<iostream>
#include<vector>
using namespace std;
int main()
{
	int w, h, res = 0;
	cin >> w >> h;
	vector<vector<int>> a;
	a.resize(w);
	for (auto& e : a)
		e.resize(h, 1);
	for (int i = 0; i<w; i++)
	{
		for (int j = 0; j<h; j++)
		{
			if (a[i][j] == 1)
			{
				res++;
				if ((i + 2)<w)
					a[i + 2][j] = 0;
				if ((j + 2)<h)
					a[i][j + 2] = 0;
			}
		}
	}
	cout << res;
	system("pause");
	return 0;
}
#endif

//小青蛙有一天不小心落入了一个地下迷宫, 小青蛙希望用自己仅剩的体力值P跳出这个地下迷宫。为了让问题简单,
//假设这是一个n*m的格子迷宫, 迷宫每个位置为0或者1, 0代表这个位置有障碍物, 小青蛙达到不了这个位置; 
//1代表小青蛙可以达到的位置。小青蛙初始在(0, 0)位置, 地下迷宫的出口在(0, m - 1)
//(保证这两个位置都是1, 并且保证一定有起点到终点可达的路径),
//小青蛙在迷宫中水平移动一个单位距离需要消耗1点体力值, 向上爬一个单位距离需要消耗3个单位的体力值, 
//向下移动不消耗体力值, 当小青蛙的体力值等于0的时候还没有到达出口, 小青蛙将无法逃离迷宫。
//现在需要你帮助小青蛙计算出能否用仅剩的体力值跳出迷宫(即达到(0, m - 1)位置)。

#include <iostream>
#include <vector>
using namespace std;
/*
* 声明：这份代码是照搬@null_ptr的 但是代码没什么注释，乍一看不好理解，
* 所以我作了比较详细的注释，方便参考
* 基本思想：典型的迷宫问题，DFS穷举所有路径，找出剩余体力最多的路径
*/
#define VISITED 2
int m, n, P; // 输入m，n，P
int maze[10][10]; // 迷宫地图
int dir[4][2] = { { 0, -1 }, { 0, 1 }, { -1, 0 }, { 1, 0 } }; // 左，右，上，下移动，例如：{0, -1}
int cost[4] = { -1, -1, -3, 0 }; // 左，右，上，下移动的体力消耗，例如：{0， -1}对应-1
int final_P = -200; // 剩余的体力值，初始为较小的数，保证final_P被正确更新
// 存储各点的数据结构
struct mazePoint {
	mazePoint(int _x, int _y) : x(_x), y(_y) {}
	int x, y;
};
// 存储每次遍历到的路径
vector<mazePoint> pathStack;
// 存储最终的最优路径
vector<mazePoint> minCostPath;
// 函数：打印路径
void printPath(const vector<mazePoint>& path) {
	for (int i = 0; i < path.size(); ++i) {
		cout << "[" << path[i].x << "," << path[i].y << "]";
		if (i < path.size() - 1) {
			cout << ",";
		}
	}
}
// 函数：寻找最优路径
void search(int x, int y, int cur_P) {
	// 将当前点加入路径并标记为VISITED
	pathStack.push_back(mazePoint(x, y));
	maze[x][y] = VISITED;
	// 如果当前点为出口且当前体力值>=0，则更新final_P与minCostPath，并返回
	if (x == 0 && y == m - 1 && cur_P >= 0) {
		if (cur_P > final_P) {
			final_P = cur_P;
				minCostPath = pathStack;
		}
		pathStack.pop_back(); // 为了回退至之前的节点，将当前结点弹出
		maze[x][y] = 1; // 注意：之前maze[x][y]被标记为VISITED（值为2），回退后应该将其还原
			return;
	}
	// 如果当前点并非出口且当前体力值>=0，则分别向左右上下四个方向探索，并计算相应的消耗
	// 如果新的点再边界内且为可达点，递归调用search函数
	if (cur_P > 0) {
		for (int i = 0; i < 4; ++i) {
			int nx = x + dir[i][0];
			int ny = y + dir[i][1];
			int nP = cur_P + cost[i];
			if (nx >= 0 && nx < n && ny >= 0 && ny < m && maze[nx][ny] == 1)
				search(nx, ny, nP);
		}
	}
	pathStack.pop_back(); // 为了回退至之前的节点，将当前结点弹出
	maze[x][y] = 1; // 注意：之前maze[x][y]被标记为VISITED（值为2），回退后应该将其还原为1
}
// 主函数
int main()
{
	cin >> n >> m >> P;
	for (int i = 0; i < n; ++i)
	for (int j = 0; j < m; ++j)
		cin >> maze[i][j];
	search(0, 0, P);
	if (final_P != -200) // 如果final_P更新过，输出最优路径
		printPath(minCostPath);
	else // 如果final_P为初始值-200，代表其没有被更新过，也就意味着没有可行路径
		cout << "Can not escape!"; 
	system("pause");
	return 0;
}