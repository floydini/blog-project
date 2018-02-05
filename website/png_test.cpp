#include<iostream>
#include<fstream>
using namespace std;

fstream ff;
char a[10000000];

int main() {
	ff.open("img/common/andrew-avatar.png",ios::in | ios::binary | ios::app);
	ff.seekg(0, std::ios::end);
	int len = ff.tellg();
	cout << len << endl;
	ff.seekg(0, std::ios::beg);
	ff.read(a, len);
	for(int i = 0; i < len; i++)
		cout << a[i] << " ";
}
