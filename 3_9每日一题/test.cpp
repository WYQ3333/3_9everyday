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

//С������һ�첻С��������һ�������Թ�, С����ϣ�����Լ���ʣ������ֵP������������Թ���Ϊ���������,
//��������һ��n*m�ĸ����Թ�, �Թ�ÿ��λ��Ϊ0����1, 0�������λ�����ϰ���, С���ܴﵽ�������λ��; 
//1����С���ܿ��Դﵽ��λ�á�С���ܳ�ʼ��(0, 0)λ��, �����Թ��ĳ�����(0, m - 1)
//(��֤������λ�ö���1, ���ұ�֤һ������㵽�յ�ɴ��·��),
//С�������Թ���ˮƽ�ƶ�һ����λ������Ҫ����1������ֵ, ������һ����λ������Ҫ����3����λ������ֵ, 
//�����ƶ�����������ֵ, ��С���ܵ�����ֵ����0��ʱ��û�е������, С���ܽ��޷������Թ���
//������Ҫ�����С���ܼ�����ܷ��ý�ʣ������ֵ�����Թ�(���ﵽ(0, m - 1)λ��)��

#include <iostream>
#include <vector>
using namespace std;
/*
* ��������ݴ������հ�@null_ptr�� ���Ǵ���ûʲôע�ͣ�էһ��������⣬
* ���������˱Ƚ���ϸ��ע�ͣ�����ο�
* ����˼�룺���͵��Թ����⣬DFS�������·�����ҳ�ʣ����������·��
*/
#define VISITED 2
int m, n, P; // ����m��n��P
int maze[10][10]; // �Թ���ͼ
int dir[4][2] = { { 0, -1 }, { 0, 1 }, { -1, 0 }, { 1, 0 } }; // ���ң��ϣ����ƶ������磺{0, -1}
int cost[4] = { -1, -1, -3, 0 }; // ���ң��ϣ����ƶ����������ģ����磺{0�� -1}��Ӧ-1
int final_P = -200; // ʣ�������ֵ����ʼΪ��С��������֤final_P����ȷ����
// �洢��������ݽṹ
struct mazePoint {
	mazePoint(int _x, int _y) : x(_x), y(_y) {}
	int x, y;
};
// �洢ÿ�α�������·��
vector<mazePoint> pathStack;
// �洢���յ�����·��
vector<mazePoint> minCostPath;
// ��������ӡ·��
void printPath(const vector<mazePoint>& path) {
	for (int i = 0; i < path.size(); ++i) {
		cout << "[" << path[i].x << "," << path[i].y << "]";
		if (i < path.size() - 1) {
			cout << ",";
		}
	}
}
// ������Ѱ������·��
void search(int x, int y, int cur_P) {
	// ����ǰ�����·�������ΪVISITED
	pathStack.push_back(mazePoint(x, y));
	maze[x][y] = VISITED;
	// �����ǰ��Ϊ�����ҵ�ǰ����ֵ>=0�������final_P��minCostPath��������
	if (x == 0 && y == m - 1 && cur_P >= 0) {
		if (cur_P > final_P) {
			final_P = cur_P;
				minCostPath = pathStack;
		}
		pathStack.pop_back(); // Ϊ�˻�����֮ǰ�Ľڵ㣬����ǰ��㵯��
		maze[x][y] = 1; // ע�⣺֮ǰmaze[x][y]�����ΪVISITED��ֵΪ2�������˺�Ӧ�ý��仹ԭ
			return;
	}
	// �����ǰ�㲢�ǳ����ҵ�ǰ����ֵ>=0����ֱ������������ĸ�����̽������������Ӧ������
	// ����µĵ��ٱ߽�����Ϊ�ɴ�㣬�ݹ����search����
	if (cur_P > 0) {
		for (int i = 0; i < 4; ++i) {
			int nx = x + dir[i][0];
			int ny = y + dir[i][1];
			int nP = cur_P + cost[i];
			if (nx >= 0 && nx < n && ny >= 0 && ny < m && maze[nx][ny] == 1)
				search(nx, ny, nP);
		}
	}
	pathStack.pop_back(); // Ϊ�˻�����֮ǰ�Ľڵ㣬����ǰ��㵯��
	maze[x][y] = 1; // ע�⣺֮ǰmaze[x][y]�����ΪVISITED��ֵΪ2�������˺�Ӧ�ý��仹ԭΪ1
}
// ������
int main()
{
	cin >> n >> m >> P;
	for (int i = 0; i < n; ++i)
	for (int j = 0; j < m; ++j)
		cin >> maze[i][j];
	search(0, 0, P);
	if (final_P != -200) // ���final_P���¹����������·��
		printPath(minCostPath);
	else // ���final_PΪ��ʼֵ-200��������û�б����¹���Ҳ����ζ��û�п���·��
		cout << "Can not escape!"; 
	system("pause");
	return 0;
}