#include "pch.h"
#include <iostream>

#include <ctime>
#include <vector>

#include "buble_sort.h"

#define SIZE 16384

int* RandomMixing(size_t size);
int* LowDiapasoneMixing(size_t size);
int* UniqueRandomMixing(size_t size);
int* ReverseArray(size_t size);
int* SortedArray(size_t size);

int main(int argc, char** args)
{
	srand(time(0));
	int* p = SortedArray(SIZE);

	vptsl::buble_sort<int> cbs(p, SIZE); //можно создать counted_buble_sort, который работает междленее, но считает кол-во перестановок и компараций
	cbs.start_sort();
	std::wcout << L"Done!" << std::endl;
	//std::wcout << L"Count iterations: " << cbs.count_iterations() << std::endl;
	//std::wcout << L"Count swaps: " << cbs.count_swap() << std::endl;
	//std::wcout << L"K: " << (float)cbs.count_swap() / cbs.count_iterations() << std::endl;
	delete[] p;

	return 0;
}

int* RandomMixing(size_t size)
{
	int* p = new int[size];
	for (size_t i = 0; i < size; ++i)
		p[i] = rand() % 255 - 127;
	return p;
}
int* LowDiapasoneMixing(size_t size)
{
	int* p = new int[size];
	for (size_t i = 0; i < size; ++i)
		p[i] = rand() % 4;
	return p;
}
int* UniqueRandomMixing(size_t size)
{
	std::vector<int> arrVal;
	for (size_t i = 0; i < size; ++i)
		arrVal.push_back(i);

	int* p = new int[size];
	size_t j = 0;
	for (size_t i = 0; i < size; ++i)
	{
		j = rand() % arrVal.size();
		p[i] = arrVal[j];
		arrVal.erase(arrVal.cbegin() + j, arrVal.cbegin() + j + 1);
	}
	return p;
}
int* ReverseArray(size_t size)
{
	int* p = new int[size];
	for (size_t i = 0; i < size; ++i)
		p[i] = i;
	return p;
}
int* SortedArray(size_t size)
{
	int* p = new int[size];
	for (size_t i = 0; i < size; ++i)
		p[i] = size - i;
	return p;
}