#include "RBT_Header.h"


void removeStopWord(string *query, int &n){
	ifstream fin("StopWordList.txt");
	string temp;
	RBTree a;
	Node *b = NULL;
	while (!fin.eof()) {
		fin >> temp;
		a.insert(temp);
	}
	for (int i = 0; i < n; i++) {
		b = NULL;
		b = a.search(query[i]);
		if (b != NULL) {
			for (int j = i; j < n - 1; j++)
				query[j] = query[j + 1];
			n--;
			continue;
		}
	}
}

int main() {
	string name[4] = { "the", "cat", "is", "running"};
	int n = 4;
	removeStopWord(name, n);
	for (int i = 0; i < n; i++) {
		cout << name[i] << " ";
	}
	cout << endl;
}

