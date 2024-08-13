#include<iostream>
#include"BSTree.h"
using namespace std;
int main()
{
	BSTree<int> x;
	int c;
	cin >> c;
	while(c!=-1)
	{
		x.insert(c);
		cin >> c;
	}
	x.see();
	cout << endl;

	cout<<x.get_height();
}
