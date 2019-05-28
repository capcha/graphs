#include <iostream>
#include <vector>
#include <fstream>
#include <time.h>
#include <random>
#include <string>

using namespace std;

struct neighbor {
	int number, weight;
	neighbor(int _number = -1, int _weight = -1) : number(_number), weight(_weight) {};
};

void generator(ofstream *file) {
	int n = 0, m = 0, v = 0;
	n = rand() % 20 + 1;
	if (n == 1)
		m = 0;
	else
		m = rand() % (n * (n - 1) / 2);
	v = rand() % n;
	*file << n << ' ' << m << ' ' << v << endl;
	vector<neighbor> tempVec;
	int temp0, temp1, iter = 0; bool flag;
	while (iter < m) {
		temp0 = rand() % n;
		temp1 = rand() % n;
		neighbor temp(temp0, temp1);
		if (iter == 0) {
			if (temp.number != temp.weight) {
				tempVec.push_back(temp);
				*file << temp0 << ' ' << temp1 << ' ' << rand() % 20 + 1 << endl;
				iter++;
			}
		}
		else {
			flag = true;
			for (int j = 0; j < tempVec.size() && flag; j++) {
				if (temp.number == tempVec[j].number && temp.weight == tempVec[j].weight
					|| temp.number == tempVec[j].weight && temp.weight == tempVec[j].number
					|| temp.number == temp.weight) {
					flag = false;
				}
			}
			if (flag) {
				tempVec.push_back(temp);
				*file << temp0 << ' ' << temp1 << ' ' << rand() % 20 + 1 << endl;
				iter++;
			}
		}
	}
	*file << endl;
}

void fullGen(ofstream *file) {
	int n = rand() % 20 + 1, m = n * (n - 1) / 2, v = rand() % n;
	*file << n << ' ' << m << ' ' << v << endl;
	for (int i = 0; i < n; i++) {
		for (int j = i + 1; j < n; j++) 
			*file << i << ' ' << j << ' ' << rand() % 20 + 1 << endl;
	}
	*file << endl;
}

int main() {
	ofstream fOut; string str; bool flag = true; int input, num;
	srand(time(NULL));

	while (flag) {
		cout << "======" << endl;
		cin >> input;
		if (input == -1)
			flag = false;
		else {
			str = "test" + to_string(input) + ".txt";
			fOut.open(str);
			cin >> num;
			switch (num) {	
			case 1:
				generator(&fOut);
				break;
			case 2:
				fullGen(&fOut);
				break;
			}
			generator(&fOut);
			fOut.close();
		}
	}
	fOut.close();
}
