#include <iostream>
using namespace std;

void swap(int* np1, int *np2) {
	
	*np1 = *np1 + *np2;
	*np2 = *np1 - *np2;
	*np1 = *np1 - *np2;
	
}

void swap2(int *np1, int *np2) {
	int* temp = new int();
	*temp = *np1;
	*np1 = *np2;
	*np2 = *temp;
	delete temp;
}

int main() {

	int a = 100000000;
	int b = 200000000;
	
	swap2(&a, &b);
	
	cout << a << ',' << b <<  endl;
	
	return 0;
}
