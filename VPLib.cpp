#include "pch.h"
#include <Windows.h>
#include <iostream>

#include <ctime>
#include <vector>

#include "bubble_sort.h"

#define SIZE 16384
#define COUNT_TESTS 8

int* RandomMixing(size_t size);
int* LowDiapasoneMixing(size_t size);
int* UniqueRandomMixing(size_t size);
int* ReverseArray(size_t size);
int* SortedArray(size_t size);

void SortHandler(wchar_t* text, int*(*pFn)(size_t size));


int main(int argc, char** args)
{
	srand(time(0));

	SortHandler(L"Random array(127...-128):", RandomMixing);
	SortHandler(L"Low range array(0...3):", LowDiapasoneMixing);
	SortHandler(L"Array of unique values:", UniqueRandomMixing);
	SortHandler(L"Reverse array:", ReverseArray);
	SortHandler(L"Sorted array:", SortedArray);

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

void SortHandler(wchar_t* text, int*(*pFn)(size_t size))
{
	int *p = nullptr;
	LARGE_INTEGER frequency = { 0 };
	LARGE_INTEGER t1 = { 0 }, t2 = { 0 };
	double elapsedTime = 0;
	double summElapsedTime = 0;

	std::wcout << text << std::endl;
	std::wcout << L"Time of sorts: " << std::endl;
	for (size_t i = 0; i < COUNT_TESTS; ++i)
	{
		p = pFn(SIZE);
		vptsl::bubble_sort<int> sort(p, SIZE);

		QueryPerformanceFrequency(&frequency);
		QueryPerformanceCounter(&t1);
		sort.start_sort();
		QueryPerformanceCounter(&t2);
		elapsedTime = (t2.QuadPart - t1.QuadPart) * 1000.0 / frequency.QuadPart;
		summElapsedTime += elapsedTime;
		std::wcout << i + 1 << L".\t\t" << elapsedTime << L" ms" << std::endl;
	}
	std::wcout << std::endl << L"Avg. time:\t" << summElapsedTime / COUNT_TESTS
		<< L" ms" << std::endl << std::endl << std::endl;


	long avgCountSwaps = 0;
	long avgCountCompare = 0;
	std::wcout << L"Count of comparation, swap and koeficient" << std::endl;
	for (size_t i = 0; i < COUNT_TESTS; ++i)
	{
		p = pFn(SIZE);
		vptsl::counted_bubble_sort<int> sort(p, SIZE);

		sort.start_sort();
		std::wcout << i + 1 << L".\t" << sort.count_iterations() 
			<< '\t' << sort.count_swap() << '\t' 
			<< ((double)sort.count_swap() / sort.count_iterations()) * 100 << '%' << std::endl;
		avgCountCompare += sort.count_iterations();
		avgCountSwaps += sort.count_swap();
	}
	std::wcout << std::endl << "Avg:\t" << avgCountCompare / COUNT_TESTS << '\t' << avgCountSwaps / COUNT_TESTS << '\t'
		<< ((double)avgCountSwaps / avgCountCompare) * 100 << '%' << std::endl << std::endl << std::endl;

	delete[] p;
}
