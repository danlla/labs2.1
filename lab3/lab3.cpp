#include <iostream>
#include <utility>
#include <vector>
#include <list>
#include <memory>
#include "vector.h"
#include "list.h"
#include "shared_ptr.h"
#include "unique_ptr.h"

template<typename T> using collection_type = list<T>;
template<typename T> using shared_ptr_type = shared_ptr<T>;
template<typename T> using unique_ptr_type = unique_ptr<T>;

template<typename T>
void print_collection(const collection_type<T>& collection) {
	for (auto &i : collection)
	{
		std::cout << i << " ";
	}
	std::cout << std::endl;
}

void fill_collection(collection_type<int>& first, size_t size) {
	for (size_t i = 0; i < size; ++i) {
		first.insert(first.begin(), (int)i);
	}
}



class point
{
	int x;
	int y;
public:
	point(int x, int y) : x(x), y(y){}
	int get_x()
	{
		return x;
	}
	int get_y()
	{
		return y;
	}
};

int main(void)
{
	collection_type<int> collection;
	fill_collection(collection, 10);
	collection.erase(collection.begin()+3);
	print_collection(collection);

	


	shared_ptr<point> sp1(new point(1, 1));
	auto sp2 = sp1;
	//sp2.reset();
	auto sp3 = std::move(sp1);
	//sp2 = nullptr;
	printf("%d", sp3.use_count());

	unique_ptr<point> up1(new point(1, 1));
	auto up2 = std::move(up1);
	printf("%d %d", up2->get_x(), up2->get_y());
	return 0;
}
