#include <queue>
#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <time.h>

using namespace std;

struct neighbor {
	int number, weight;
	neighbor(int _number = -1, int _weight = -1) : number(_number), weight(_weight) {};
};

void matrixResult(ifstream *fIn, ofstream *fOut) {
	int n, m, a, b, c, v, temp; bool stop, flag; clock_t t;
	*fIn >> n >> m >> v;

	vector<vector<int>> matrix; matrix.resize(n);
	vector<int> column; column.assign(n, -1);
	vector<bool> check; check.assign(n, false);

	t = clock();

	for (int i = 0; i < n; i++)
		matrix[i].resize(n);


	for (int i = 0; i < m; i++) {
		*fIn >> a >> b >> c;
		matrix[a][b] = c;
		matrix[b][a] = c;
	}

	column[v] = 0;
	temp = 0;

	while (temp != -1) {
		stop = false;
		for (int i = 0; i < n && !stop; i++)
			if (column[i] == temp && !check[i]) {
				for (int j = 0; j < n; j++) {
					flag = false;
					if (matrix[i][j] > 0 && !check[j]) {
						if (column[j] != -1) {
							if (column[j] > temp + matrix[i][j])
								column[j] = temp + matrix[i][j];
						}
						else
							column[j] = temp + matrix[i][j];
						flag = true;
					}
				}
				if (!flag)
					column[i] = temp;
				check[i] = true;
				stop = true;
			}

		temp = -1;

		for (int i = 0; i < n; i++) {
			if (column[i] > 0 && !check[i])
				if (temp == -1)
					temp = column[i];
				else
					if (column[i] < temp)
						temp = column[i];
		}
	}

	t = clock() - t;
	cout << ((double)t) / CLOCKS_PER_SEC << endl;

	if (fOut) {
		for (int i = 0; i < column.size(); i++) {
			if (column[i] == -1)
				*fOut << "Вершина " << v << " не связана с вершиной " << i << endl;
			else
				if (column[i] > 0)
					*fOut << v << " - " << i << " : " << column[i] << endl;
		}
		*fOut << endl;
	}
}

void listResult(ifstream *fIn, ofstream *fOut) {
	int a, b, c, temp, dist, n, m, v; clock_t t;
	*fIn >> n >> m >> v;
	bool stop = false, flag = false;

	vector<vector<neighbor>> graph; graph.resize(n);
	vector<int> column; column.assign(n, -1);
	vector<bool> check; check.assign(n, false);
	priority_queue<int, vector<int>, greater<int>> pQueue;

	t = clock();

	for (int i = 0; i < m; i++) {
		*fIn >> a >> b >> c;
		neighbor u(a, c), v(b, c);
		graph[a].push_back(v);
		graph[b].push_back(u);
	}

	column[v] = 0;
	pQueue.push(0);

	while (!pQueue.empty() && !stop) {
		dist = pQueue.top();
		pQueue.pop();
		flag = false;
		for (int i = 0; i < column.size() && !flag; i++) {
			if (column[i] == dist && !check[i]) {
				temp = i;
				flag = true;
			}
		}

		if (flag) {
			check[temp] = true;
			for (int i = 0; i < graph[temp].size(); i++) {
				if (!check[graph[temp][i].number]) {
					if (column[graph[temp][i].number] == -1) {
						column[graph[temp][i].number] = dist + graph[temp][i].weight;
						pQueue.push(graph[temp][i].weight + dist);
					}
					else
						if (column[graph[temp][i].number] > dist + graph[temp][i].weight) {
							column[graph[temp][i].number] = dist + graph[temp][i].weight;
							pQueue.push(graph[temp][i].weight + dist);
						}
				}
			}
		}
		else stop = true;
	}

	t = clock() - t;
	cout << ((double)t) / CLOCKS_PER_SEC << endl;

	if (fOut) {
		for (int i = 0; i < column.size(); i++) {
			if (column[i] == -1)
				*fOut << "Вершина " << v << " не связана с вершиной " << i << endl;
			else
				if (column[i] > 0)
					*fOut << v << " - " << i << " : " << column[i] << endl;
		}
		*fOut << endl;
	}
}

int main() {
	ifstream fIn; ofstream fOutM, fOutL;

	int input, num;
	bool flag = true; string str;

	fOutM.open("resultmatrix.txt");
	fOutL.open("resultlist.txt");

	while (flag) {
		cout << "======" << endl;
		cin >> input;
		if (input == -1)
			flag = false;
		else {
			str = "tests\\test" + to_string(input) + ".txt";

			fIn.open(str);
		
			if (fIn) {
				cin >> num;
				switch (num) {
				case 1:
					fOutM << "Тест #" << input << endl;
					matrixResult(&fIn, &fOutM);
					break;
				case 2:
					fOutL << "Тест #" << input << endl;
					listResult(&fIn, &fOutL);
					break;
				}
			}
			else cout << "Файл отсутствует";
			fIn.close();
		}

	}

	fOutM.close();
	fOutL.close();

}
