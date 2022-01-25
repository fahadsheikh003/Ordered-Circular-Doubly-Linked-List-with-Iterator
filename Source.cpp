//Fahad Waheed

#include<iostream>
#include"List.h"

using namespace std;

int main()
{
	List<int> L;

	for (int i = 0; i < 10; i++)
		L.Insert(i * 10);

	L.Insert(-5);
	L.Insert(5);
	L.Insert(100);

	cout << L[5] << endl;
	
	List<int>::Interator it;
	it = L.begin();
	do
	{
		cout << *it << "  ";
		it++;
	} while (it != L.end());
}