#include <iostream>
#include "function.h"
#include <vector>
#include <time.h>
#include <algorithm>
#include <functional>

using namespace std;

int get_key()
{
	int key = _getwch();
	if ((key == 0) || (key == 224))
		key = _getwch();
	return key;
}

size_t menu()
{
	cout << "\n\n\n";
	cout <<"1. Create new function\n";
	cout <<"2. Create random functions\n";
	cout <<"3. Delete function\n";
	cout <<"4. Delete all functions\n";
	cout <<"5. Find function with minimal derivative\'s value\n";
	cout <<"Esc. Exit\n";
	int key = 0;
	while (key != 49 && key != 50 && key != 51 && key != 52 && key != 53 && key != 27)
		key = get_key();
	return (size_t)key;
}

size_t menu_choose_function()
{
	cout << "\n\n\n";
	cout << "1. Constant\n";
	cout << "2. Linear (ax+b)\n";
	cout << "3. Quadratic (ax^2+bx+c)\n";
	cout << "4. Sinus (a'*sin(ax+b))\n";
	cout << "5. Cosine (a'*cos(ax+b))\n";
	cout << "Esc. Back\n";
	int key = 0;
	while (key != 49 && key != 50 && key != 51 && key != 52 && key != 53 && key != 27)
		key = get_key();
	return (size_t)key;
}

double enter_number()
{
	double num = 0.0;
	cin >> num;
	while (true)
	{
		if (cin.fail())
		{
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
			cout << "Invalid value\n";
			cin >> num;
		}
		if (!cin.fail())
			break;
	}
	return num;
}

shared_ptr<my_function> function_min_der_value(const vector<shared_ptr<my_function>>& functions, const double point)
{
	double value = functions[0]->derivative()->value(point);
	shared_ptr<my_function> tmp = functions[0];
	for (auto &my_function : functions)
	{
		if (my_function->derivative()->value(point) < value)
		{
			value = my_function->derivative()->value(point);
			tmp = my_function;
		}
	}
	return tmp;
}


void print_fun_der_val_der(const shared_ptr<my_function>& f, double point)
{
	cout << "f(x) = " << *f;
	cout << "\nf\'(x) = " << *f->derivative();
	cout << "\nf\'("<<point<<") = " << f->derivative()->value(point);
}

void random_fill(vector<shared_ptr<my_function>>& functions, size_t count)
{
	const unsigned coef_rand = 10;
	for (size_t i = 0; i < count; ++i)
	{
		unsigned type = rand() % 5;
		switch (type)
		{
		case 0: functions.push_back(make_shared<constant>(rand() % coef_rand));
			break;
		case 1:functions.push_back(make_shared<linear>(rand() % coef_rand, rand()% coef_rand));
			break;
		case 2:functions.push_back(make_shared<quadratic>(rand() % coef_rand, rand()% coef_rand, rand()% coef_rand));
			break;
		case 3:functions.push_back(make_shared<sinus>(rand() % coef_rand, rand()% coef_rand, rand()% coef_rand));
			break;
		case 4:functions.push_back(make_shared<cosine>(rand() % coef_rand, rand() % coef_rand, rand() % coef_rand));
			break;
		default:
			break;
		}
	}
}

void print_functions(const vector<shared_ptr<my_function>>& functions)
{
	for (auto &my_function : functions)
	{
		cout << "f(x) = " << *my_function;
		cout << endl;
	}
}

bool compare(shared_ptr<my_function>& lhs, shared_ptr<my_function>& rhs, double point)
{
	return lhs->derivative()->value(point) < rhs->derivative()->value(point);
}

//shared_ptr<my_function> function_min_der_value_al(const vector<shared_ptr<my_function>>& functions, double point)
//{
//	//auto f = bind(compare, placeholders::_1, placeholders::_2, point);
//	return *min_element(functions.begin(), functions.end(), bind(compare, placeholders::_1, placeholders::_2, point));
//}

//int main()
//{
//	srand((unsigned int)time(0));
//	vector<shared_ptr<function>> functions;
//	double point = 3.14;
//	random_fill(functions, 20);
//	print_functions(functions);
//	shared_ptr<function> a = function_min_der_value(functions, point);
//	print_fun_der_val_der(a, point);
//	getchar();
//	return 0;
//}

int main(void)
{
	srand((unsigned int)time(0));
	vector<shared_ptr<my_function>> functions;
	bool exit = false;
	while (!exit)
	{
		cout << "\n\n\n";
		print_functions(functions);
		size_t choice = menu();
		switch (choice)
		{
		case 27:
			exit = true;
			break;
		case 49:
		{
			size_t choice_function = menu_choose_function();
			switch (choice_function)
			{
			default:
			case 27:
				break;
			case 49:
			{
				cout << "\nEnter c\n";
				double c = enter_number();
				functions.push_back(make_shared<constant>(c));
				break;
			}
			case 50:
			{
				cout << "\nEnter a\n";
				double a = enter_number();
				cout << "\nEnter b\n";
				double b = enter_number();
				functions.push_back(make_shared<linear>(a, b));
				break;
			}
			case 51:
			{
				cout << "\nEnter a\n";
				double a = enter_number();
				cout << "\nEnter b\n";
				double b = enter_number();
				cout << "\nEnter c\n";
				double c = enter_number();
				functions.push_back(make_shared<quadratic>(a, b, c));
				break;
			}
			case 52:
			{
				cout << "\nEnter a'\n";
				double a = enter_number();
				cout << "\nEnter a\n";
				double arg_a = enter_number();
				cout << "\nEnter b\n";
				double arg_b = enter_number();
				functions.push_back(make_shared<sinus>(a, arg_a, arg_b));
				break;
			}
			case 53:
			{
				cout << "\nEnter a'\n";
				double a = enter_number();
				cout << "\nEnter a\n";
				double arg_a = enter_number();
				cout << "\nEnter b\n";
				double arg_b = enter_number();
				functions.push_back(make_shared<cosine>(a, arg_a, arg_b));
				break;
			}
			}

			break;
		}
		case 50:
		{
			size_t count = 0;
			cout << "\n\n\nEnter count\n";
			count = (size_t)enter_number();
			if (count > 10000)
				break;
			random_fill(functions, count);
			break;
		}
		case 51:
		{
			size_t index = 0;
			cout << "\n\n\nEnter index\n";
			index = (size_t)enter_number();
			if (index >= functions.size())
				break;
			functions.erase(functions.begin() + index);
			break;
		}
		case 52:

			functions.clear();
			break;

		case 53:
		{
			if (!functions.size())
				break;
			double point = 0.0;
			cout << "\n\n\nEnter point\n";
			point = enter_number();
			shared_ptr<my_function> a = function_min_der_value(functions, point);
			print_fun_der_val_der(a, point);
			break;
		}
		}
	}
	return 0;
}

