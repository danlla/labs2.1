#include <iostream>
#include <ctime> 
#include "binim.h"
using namespace std;

void print(const binim& obj) {
	for (size_t i = 0; i < obj.get_row(); ++i)
	{
		for (size_t j = 0; j < obj.get_col(); ++j)
		{
			char ch = (obj(i, j) == 1) ? '#' : '_';
			cout << ch;
		}
		cout << endl;
	}
	cout << endl;
}

binim heart_image()
{
	binim heart(7, 9);
	heart(0, 2) = true;
	heart(0, 6) = true;
	heart(1, 1) = true;
	heart(1, 3) = true;
	heart(1, 5) = true;
	heart(1, 7) = true;
	heart(2, 0) = true;
	heart(2, 4) = true;
	heart(2, 8) = true;
	heart(3, 1) = true;
	heart(3, 7) = true;
	heart(4, 2) = true;
	heart(4, 6) = true;
	heart(5, 3) = true;
	heart(5, 5) = true;
	heart(6, 4) = true;
	return heart;
}

binim random_fill(size_t row, size_t col)
{
	srand((unsigned int)time(0));
	binim obj(row, col);
	for (size_t i = 0; i < row; ++i)
	{
		for (size_t j = 0; j < col; ++j)
		{
			obj(i, j) = rand() % 3 - 1;
		}
		cout << endl;
	}
	return obj;
}

int main(void)
{
	/*binim a(2, 3, 1);
	binim b(2, 4, 0);
	try {
		cout << (a == b);
	}
	catch (const logic_error& error)
	{
		cout << error.what();
	}*/

	binim a = random_fill(15, 15);
	print(a);
	//binim b = heart_image();
	//print(b);
	return 0;
}
