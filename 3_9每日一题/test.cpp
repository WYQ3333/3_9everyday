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